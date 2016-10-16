#ifndef PLANET_HPP
#define PLANET_HPP

//Assign. 1
struct Planet {

	Planet(float siz, float speed, float dist):
		size{siz},
		rot_speed{speed},
		distance_from_sun{dist}
	{
        scale = size / (695700 * 2); //size / (max radius (sun) * (1/scaling_max))
        orig_distance = 6 * distance_from_sun / 4503443661; //distance / (max distance (neptune) * (1/max distance))
    }

    //real
	float size; //in km
	float rot_speed;
	float distance_from_sun; //in km

    //virtual
    float scale; //scaling factor
    float orig_distance;
};

#endif