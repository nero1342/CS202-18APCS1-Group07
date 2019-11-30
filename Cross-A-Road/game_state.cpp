#include "game_state.h"

Game_state::Game_state()
{
	set_pos({ 1, 1 }, { 44, 150 });
	Console::clear_screen();
	draw_rect('=');
	current_level = std::make_shared<Game_level>();
}

void Game_state::level_up()
{
	current_level = std::make_shared<Game_level>(current_level->get_level_id() + 1);
	// Message 
}

void Game_state::render()
{
	current_level ->render();
}

void Game_state::do_tick()
{
	current_level->do_tick();
	if (current_level->is_finished()) level_up();
}

void Game_state::import_from_file(const std::string& file_path)
{

}

void Game_state::export_to_file(const std::string& file_path)
{
}

void Game_state::process_input(const char & ch)
{
	current_level->process_input(ch);
}
