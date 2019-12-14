#pragma once

#include "game_map.h"
#include "player.h"
#include <memory>

class Game_level : public Window {
public:
	Game_level(int level_id = 1);
	~Game_level();
	void update_and_render();
	bool is_finished(); 
	void process_input(const char &ch);
	int get_level_id();
	void import_from_file(std::ifstream &fi);
	void export_to_file(std::ofstream& fo);
	bool check_collide();
private:
	int level_id = 0;
	std::shared_ptr<Game_map> current_map = nullptr;
	std::shared_ptr<Player> player = nullptr;
};

