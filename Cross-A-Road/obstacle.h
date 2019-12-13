#pragma once
#include "entity.h"
#include <memory>

enum ObstacleType {
	OT_Car, OT_Bus, OT_Truck, OT_Bird, OT_Dinasour
};

class Obstacle : public Entity {
public:
	Obstacle();
	Obstacle(Point loca, Point direction = {0, 1});
	virtual ~Obstacle();
	virtual std::string type_name() = 0;
	virtual int obs_type() = 0;
	void do_tick();
	static std::shared_ptr<Obstacle> Create(ObstacleType type, Point loca_obs, Point dir);
	bool is_far_enough(int distance);
	void export_to_file(std::ofstream& fo);
	static std::shared_ptr<Obstacle> obs_import_from_file(std::ifstream &fi);

private:
	void move();
	int tick_passed = 0;
	Point direction;
};

