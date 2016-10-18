#ifndef PLANET_HPP
#define PLANET_HPP

#include <vector>

//Assign. 1
struct Planet {
	Planet(float scal, float speed, float dist):
		scale{scal},
		rot_speed{speed},
		orig_distance{dist}
	{}

	float scale; //scaling factor
	float rot_speed;
    float orig_distance;

	std::vector<Planet> moons;
};

#endif