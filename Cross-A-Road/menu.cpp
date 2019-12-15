#include "menu.h"
#include <algorithm>
#include <iostream>

Menu::Menu(bool is_main_menu)
{	
	if (is_main_menu) {
		content = {
			"NEW GAME",
			"LOAD GAME",
			"SETTINGS",
			"QUIT"
		};
	}
	else {
		content = {
			"RESUME",
			"NEW GAME",
			"SAVE_GAME",
			"LOAD GAME",
			"SETTINGS",
			"QUIT"
		};
	}
}


Menu::~Menu()
{
}


void Menu::load_menu()
{
	draw_rect();
	max_length = 0;
	rect.resize(content.size());
	for (int i = 0; i < content.size(); ++i) max_length = std::max(max_length, (int)content[i].size());
	for (int i = 0; i < content.size(); ++i) {
		Point current_point = { (lower_right.x + upper_left.x) / 2 - (int)content.size() + i * 2, (lower_right.y + upper_left.y - max_length) / 2};
		rect[i].set_pos(current_point + Point(-1, -2), current_point + Point(1, max_length + 1));
		rect[i].draw_rect('-');
		print_center_align(content[i], current_point.x);
	}
	cursor = 0;
}

int Menu::get_input()
{
	while (true) {
		Choose(cursor);
		while (!_kbhit());
		//

		//
		char c = _getch();
		while (c == 0 || c == 224) c = _getch();
		Unchoose(cursor);
		switch (c) {
		case KEY_UP: {
			cursor = (cursor - 1 + content.size()) % (int)content.size();
			break;
		}
		case KEY_DOWN: {
			cursor = (cursor + 1) % content.size();
			break;
		}
		case ENTER:
			return cursor;
		case ESC:
			exit(0);
			return -1;
		}
	}
}

void Menu::Unchoose(int id) {
	turn_off_reverse_color();
	rect[id].draw_full_rect(' ');
	int line = (lower_right.x + upper_left.x) / 2 - content.size() + id * 2;
	print_center_align(content[id], line);
	rect[id].draw_rect('-');
}

void Menu::Choose(int id) {
	turn_on_reverse_color();
	rect[id].draw_full_rect(' ');
	int line = (lower_right.x + upper_left.x) / 2 - content.size() + id * 2;
	print_center_align(content[id], line);
	turn_off_reverse_color();
	rect[id].draw_rect('-');
}

