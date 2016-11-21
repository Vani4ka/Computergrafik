#ifndef PLANET_HPP
#define PLANET_HPP

#include <vector>
#include <glm/glm.hpp>

#include "pixel_data.hpp"

//Assign. 1
struct Planet {
	Planet(std::string nam, float scal, float speed, float dist, glm::fvec3 col):
		name{nam},
		scale{scal},
		rot_speed{speed},
		orig_distance{dist},
		color{col}
	{}

	Planet(std::string nam, float scal, float speed, float dist, pixel_data tex, pixel_data map):
		name{nam},
		scale{scal},
		rot_speed{speed},
		orig_distance{dist},
		texture{tex},
		normal_map{map},
		color{1.0f, 1.0f, 1.0f}
	{}

	std::string name;

	float scale; //scaling factor
	float rot_speed;
    float orig_distance;

	std::vector<Planet> moons;

	//Assign. 3
	glm::fvec3 color;

	//Assign. 4
	pixel_data texture;
	pixel_data normal_map;
};

#endif