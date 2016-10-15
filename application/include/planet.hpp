#ifndef PLANET_HPP
#define PLANET_HPP

//Assign. 1
struct Planet {

	Planet(float rad, float speed, float dist):
		radius{rad},
		rot_speed{speed},
		orig_distance{dist}
	{}

	float radius = 0;
	float rot_speed = 0;
	float orig_distance = 0;
}

#endif