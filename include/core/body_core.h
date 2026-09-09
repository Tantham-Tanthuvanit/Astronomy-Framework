#pragma once

#include "include/core/dtypes.h"

class Body {
	
	public:
		sciNo mass;
		sciNo radius;
		// G*M
		double GravitationalParam;

		double axialTilt;
		double rotationalPeriod;

		double rotation;
		vec3f angularVelocity;

		vec3f velocity;
		vec3f position;
		vec3f acceleration;

		double semimajoraixs;
		double eccentricity;

		vec3f rgb;
};
