#ifndef MOON_HPP
#define MOON_HPP

struct Moon: public Planet {
	Moon(float scal, float speed, float dist, Planet* mine):
	Planet(scal, speed, dist),
	myPlanet{mine}
	{}

	Planet* myPlanet;
};

#endif