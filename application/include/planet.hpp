#ifndef PLANET_HPP
#define PLANET_HPP

//Assign. 1
struct Planet {

	Planet(float siz, float speed, float dist):
		size{siz},
		rot_speed{speed},
		orig_distance{dist}
	{}

	float size;
	float rot_speed;
	float orig_distance;
};

#endif