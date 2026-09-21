#include <cmath>
#include <include/core/math.h>

// scientific notation calculations

sciNo multiply_sciNo(sciNo& a, sciNo& b) {
	return {
		a.n * b.n,
		a.exponent + b.exponent
	};
}

sciNo divide_sciNo(sciNo &a, sciNo& b) {
	return {
		a.n / b.n,
		a.exponent - b.exponent
	};
}

// vector calculations

vec2f add_vec2_float(vec2f &a, vec2f &b) {
	return {
		a.x + b.x,
		a.y + b.y
	};
}

vec2i add_vec2_int(vec2i &a, vec2i &b) {
	return {
		a.x + b.x,
		a.y + b.y
	};
}

vec3f add_vec3_float(vec3f &a, vec3f &b) {
	return {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
}

vec3i add_vec3_int(vec3i &a, vec3i &b) {
	return {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
}

vec2f sub_vec2_float(vec2f &a, vec2f &b) {
	return {
		a.x - b.x,
		a.y - b.y
	};
}

vec2i sub_vec2_int(vec2i &a, vec2i &b) {
	return  {
		a.x - b.x,
		a.y - b.y
	};
}

vec3f sub_vec3_float(vec3f &a, vec3f &b) {
	return {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};
}

vec3i sub_vec3_int(vec3i &a, vec3i &b) {
	return {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};
}
