#ifndef PLANET_HPP
#define PLANET_HPP

#include <vector>
#include <glm/glm.hpp>

//Assign. 1
struct Planet {
	Planet(float scal, float speed, float dist, fvec3 col):
		scale{scal},
		rot_speed{speed},
		orig_distance{dist},
		color_{col}
	{}

	float scale; //scaling factor
	float rot_speed;
    float orig_distance;

	std::vector<Planet> moons;

	//Assign. 3
	glm::fvec3 color_;
};

#endif