#ifndef ALLINC
#define ALLINC

#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <math.h>

#define POP_SIZE 30
#define S_POP_SIZE 300
#define E 2.7182818
#define PI 3.141592
#define GENERATIONS 3000
#define EVAL_LIMIT 20000
#define T 1/sqrt(2)
int eval_num;

struct Individual {
	float x1, x2;
	float sigma;
	float fitness;
};

struct Population{
	Individual pop[POP_SIZE];
};

struct SelPopulation{
	Individual pop[S_POP_SIZE];
};

#endif
