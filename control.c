#include <stdio.h>
#include <math.h>
#define G 6.67*10^-11

typedef struct e_vector {
	float x, y, z;
};

typedef struct particle {
	e_vector velocity;
	e_vector location;
	float mass;
};

float abs(float p) {
	if (p < 0)
		return 0-p;
	return p;
}

float magnitude(e_vector a, e_vector b) {
	float x, y, z;
	// basically sqrt(a^2+b^2+c^2). Put it in code.
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z; // May be fking it up, not sure if this will change?
	return sqrt((x*x) + (y*y) + (z*z));
}

e_vector gravity_calculate(particle a, particle b) {
	e_vector q, r;
	q.x = b.x - a.x;
	q.y = b.y - a.y;
	q.z = b.z - a.z; // Basically, we just get the distance between them as e_vector. This is relative to a - a + q = b.
	float distance = magnitude(a.location, b.location);
	float grav = (G*a.mass*b.mass)/(distance*distance);
	float grav_accel = grav / a.mass; // solving for a, we have the force between so we want acceleration on a.
	float total_vec = abs(q.x) + abs(q.y) + abs(q.z);
	float po = grav_accel/total_vec;
	r.x = q.x * po;
	r.y = q.y * po;
	r.z = q.z * po;
	return r;
}

