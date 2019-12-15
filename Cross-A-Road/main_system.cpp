#include "main_system.h"
#include "Windows.h"
#include <conio.h>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include "console.h"
#include "random.h"

void Game_module::show_main()
{
	Random::Init();
	Console::full_screen();
	Menu menu;
	while (true) {
		Console::clear_screen();
		menu.set_pos({ 1, 10 }, { 40, 160 });
		menu.load_menu();
		switch (menu.get_input()) {
		case MENU_NAME::NEW_GAME:
			start_new_game();
			break;
		case MENU_NAME::LOAD_GAME:
			// Load game
			load_game();
			break;
		case MENU_NAME::SETTINGS:
			// Settings game
			break;
		case MENU_NAME::QUIT:
			exit(0);
		}
	}
	//start_game();
}

void Game_module::show_pause_menu()
{
	Menu menu(0);
	Console::clear_screen();
	menu.set_pos({ 1, 10 }, { 40, 160 });
	menu.load_menu();
	int choose = menu.get_input();
	switch (choose) {
	case PAUSE_MENU_NAME::RESUME2:
		break;
	case PAUSE_MENU_NAME::NEW_GAME2:
		current_state = std::make_shared<Game_state>();
		current_state->init();
		break;
	case PAUSE_MENU_NAME::LOAD_GAME2:
		// Load game
		load_game();
		break;
	case PAUSE_MENU_NAME::SAVE_GAME2:
		// Save game
		save_game();
		break;
	case PAUSE_MENU_NAME::SETTINGS2:
		// Settings game
		break;
	case PAUSE_MENU_NAME::QUIT2:
		exit(0);
	}
}

void Game_module::do_menu_choice()
{
}

void Game_module::start_new_game()
{
	auto new_state = std::make_shared<Game_state>();
	new_state->render_only();
	new_state->init();
	start_game(new_state);
}

void Game_module::start_game(std::shared_ptr<Game_state> start_state)
{
	current_state = start_state;
	std::mutex mtx;
	bool is_running = true, is_pause = false;

	current_state->render();

	auto main_game_loop = [&](char &ch) //char input 
	{
		while (true) {
			{
				std::lock_guard<std::mutex> locker(mtx);
				if (!is_running) return;
				if (is_pause) continue;
			}
			current_state->update_and_render();
			current_state->process_input(ch);
			ch = '.';
			//std::cout << "Main game loop\n";
			// Sleep(30);
		}
	};

	char ch = '.';

	std::thread t1(main_game_loop, std::ref(ch));
	// input loop
	while (true) {
		
		// process input
		ch = _getch();
		//std::cout << "Input: " << ch << '\n';
		switch (ch) {
		case 'a':
			mtx.lock();
			is_running = false;
			mtx.unlock();
			t1.join();
			return;
		case 'p':
			// Pause menu
		case ESC: 
			// Pause menu
			is_pause ^= 1;
			if (is_pause) {
				Sleep(100);
				show_pause_menu();
				is_pause ^= 1;
				current_state->render_only();
			}
			break;
		}
	}
}

void Game_module::load_game()
{
	system("md SaveGame");
	// Get file name
	std::string filename = "First";
	filename = "SaveGame/" + filename + ".map";

	auto new_state = std::make_shared<Game_state>();
	new_state ->import_from_file(filename);
	if (current_state == nullptr) start_game(new_state);
	else current_state = new_state;
}

void Game_module::save_game()
{
	// Get file name
	system("md SaveGame");
	std::string filename = "First";
	filename = "SaveGame/" + filename + ".map";
	current_state->export_to_file(filename);
}