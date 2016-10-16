#ifndef PLANET_HPP
#define PLANET_HPP

//Assign. 1
struct Planet {

	Planet(float siz, float speed, float dist):
		size{size},
		rot_speed{speed},
		orig_distance{dist}
	{}

	float size = 0;
	float rot_speed = 0;
	float orig_distance = 0;
};

#endif