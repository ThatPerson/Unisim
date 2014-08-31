#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define G 1

typedef struct {
	float x, y, z;
} e_vector;

typedef struct {
	e_vector velocity;
	e_vector location;
	float mass;
} particle;



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
	if (distance == 0) {
		distance = 0.001;
	}
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

e_vector compute_velocity(e_vector vel, e_vector accel[], int acceli, float time_skip) {
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

int print_particle_set(particle p[], int pl, float time, float max_time) {
	printf("= %3f%% ========= %4f seconds ===============\n", 100*(time/max_time), time);
	int i;
	for (i = 0; i < pl; i++) {
		printf("%d: %f/%f/%f - %f/%f/%f\n", i, p[i].location.x, p[i].location.y, p[i].location.z, p[i].velocity.x, p[i].velocity.y, p[i].velocity.z);
	}
	return 1;
}

particle generate_particle(void) {
	particle q;
	q.mass = 100;
	q.location.x = 0;
	q.location.y = 0;
	q.location.z = 0;
	q.velocity.x = (rand()%10)-5;
	q.velocity.y = (rand()%10)-5;
	q.velocity.z = (rand()%10)-5;
	return q;
}

int main(int argc, char * argv[]) {
	printf("%d: %s\n", argc, argv[0]);
	/* 
		1: name
		2: no particles
		3: timeswap
		4: timebase
		5: timelength
	*/
	


	srand(time(NULL));



	if (argc < 5) {
		printf("unisim [number of particles] [time] [printtime] [length to run]\n");
		return 1;
	}
	
	float timelength = atof(argv[4]);
	float timebase = atof(argv[3]);
	float timeswap = atof(argv[2]);
	int length = atoi(argv[1]);
	particle a[length];
	
	int i,p;
	for (i = 0; i < length; i++) {
		a[i] = generate_particle();
	}
	print_particle_set(a, length, 3, 6);
	
	float curr = 0, max = timebase/timeswap;
	curr = max;
	float ip;
	int pp, qp;
	e_vector tmp[1];
	for (ip = 0; ip < timelength; ip += timeswap) {
	
		for (pp = 0; pp < length; pp++) {
			for (qp = 0; qp < length; qp++) {
				if (qp != pp) {
					tmp[0] = gravity_calculate(a[pp], a[qp]);
					a[pp].velocity = compute_velocity(a[pp].velocity, tmp, 1, timeswap);
				}
			}
		}
		for (pp = 0; pp < length; p++) {
			a[pp].location.x += a[pp].velocity.x;
			a[pp].location.y += a[pp].velocity.y;
			a[pp].location.z += a[pp].velocity.z;
		}
	
		//Calculate shit;
		if (curr == max) {
			printf("PRINT OUT %d\n", (int)(ip+0.5));
			print_particle_set(a, length, ip, timelength);
			curr = 0;
		}
		curr++;
		
	}
	/*
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
*/	return 1;
}

