#ifndef PLANET_HPP
#define PLANET_HPP

#include <vector>
#include <glm/glm.hpp>

#include "pixel_data.hpp"

//Assign. 1
struct Planet {
	Planet(float scal, float speed, float dist, glm::fvec3 col):
		scale{scal},
		rot_speed{speed},
		orig_distance{dist},
		color{col}
	{}

	Planet(float scal, float speed, float dist, pixel_data tex):
		scale{scal},
		rot_speed{speed},
		orig_distance{dist},
		texture{tex}
	{
		color = {1.0f, 1.0f, 1.0f};
	}

	float scale; //scaling factor
	float rot_speed;
    float orig_distance;

	std::vector<Planet> moons;

	//Assign. 3
	glm::fvec3 color;

	//Assign. 4
	pixel_data texture;
};

#endif