#pragma once
#include <cstdint>
#include <stdfloat>

typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;


struct sciNo {
	double n;
	int64 exponent;
};

struct vec2i {
	int x;
	int y;
};

struct vec3i {
	int x;
	int y;
	int z;
};

struct vec2f {
	double x;
	double y;
};

struct vec3f {
	double x;
	double y;
	double z;
};
