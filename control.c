#include <stdio.h>
#include <math.h>
#define G 1

typedef struct {
	float x, y, z;
} e_vector;

typedef struct {
	e_vector velocity;
	e_vector location;
	float mass;
} particle;

float time_skip = 1;

float abs_r(float p) {
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
	q.x = b.location.x - a.location.x;
	q.y = b.location.y - a.location.y;
	q.z = b.location.z - a.location.z; // Basically, we just get the distance between them as e_vector. This is relative to a - a + q = b.
	float distance = magnitude(a.location, b.location);
	printf("D %f\n", distance);
	float grav = (G*a.mass*b.mass)/(distance*distance);
	float grav_accel = grav / a.mass; // solving for a, we have the force between so we want acceleration on a.
	float total_vec = abs_r(q.x) + abs_r(q.y) + abs_r(q.z);
	float po = grav_accel/total_vec;
	r.x = q.x * po;
	r.y = q.y * po;
	r.z = q.z * po;
	return r;
}

int print_e_vector(e_vector p) {
	printf("%f %f %f\n", p.x, p.y, p.z);
	return 1;
}

e_vector compute_velocity(e_vector vel, e_vector accel[], int acceli) {
	e_vector p = vel;
	print_e_vector(vel);
	int i;
	for (i = 0; i < acceli; i++) {
		p.x += accel[i].x * time_skip;
		p.y += accel[i].y * time_skip;
		p.z += accel[i].z * time_skip;
		print_e_vector(accel[i]);
	}
	print_e_vector(p);
	return p;
}

int main(int argc, char * argv[]) {
	particle a;
	particle b;
	a.location.x = 0;
	a.location.y = 0;
	a.location.z = 0;
	b.location.x = -10;
	b.location.y = 0;
	b.location.z = 10;
	a.mass =  10000000000;
	b.mass = 1000000;
	
	e_vector q;
	q = gravity_calculate(a,b);
	printf("%f %f %f\n", q.x, q.y, q.z);
	e_vector p[] = {q, a.velocity};
	compute_velocity(a.location, p, 2);
	return 1;
}

