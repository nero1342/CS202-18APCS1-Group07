#pragma once

#include "lane.h"
#include <memory>
#include <vector>
#include "player.h"

class Game_map : public Window {
public:
	Game_map(Point upper_left, Point lower_right, int n_lanes, int lane_width);
	bool is_finished(std::shared_ptr<Player> player);
	void update_and_render();
	void import_from_file(std::ifstream& fi);
	void export_to_file(std::ofstream& fo);
	bool check_collide(std::shared_ptr<Player> player);
private:
	std::vector<std::shared_ptr<Lane>> lanes;
};

