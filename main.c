#include "allinc.h"
using namespace std;

float fx (Individual a)
{
	float answer =  21.5 + a.x1 * sin (4*PI*a.x1) + a.x2 * sin (20 * PI * a.x2);
	eval_num++;
	return answer;
}


double gauss()
{
	float x1, x2, w, y1, y2;
	do {
		x1 = 2.0 * ((float)rand()/(float)RAND_MAX) -1.0;
		x2 = 2.0 * ((float)rand()/(float)RAND_MAX) -1.0;
		w = x1*x1 + x2*x2;
	} while (w>=1.0);

	w = sqrt ((-2.0 * log(w))/w);
	//y1=x1*w;
	y2=x2*w;
	//cout << endl << "Sigma generated: " << y2;
	return y2;
}



Individual genInd()
{
	Individual c;
	c.x1 = (rand()/(float(RAND_MAX)+15.1 ))-3.0;
	c.x2 = (rand()/(float(RAND_MAX)+1.7 ))+4.1;
 	c.fitness = fx(c);	
	return c;
}

Population genPop()
{
	Population p;
	for (int i=0; i<POP_SIZE; i++) p.pop[i]=genInd();
	return p;

}

void printInd(Individual a)
{
	cout << "x1=" << a.x1 << ", x2=" << a.x2;
}

void printPop(Population p)
{
	for (int i=0; i<POP_SIZE; i++)
	{
	       	printInd(p.pop[i]);
		cout << endl;
	}
}

void  sortSP (SelPopulation &sp)
{
	int i, j;
	Individual temp;
	for (i=0; i<(S_POP_SIZE-1); i++)
	{
		for (j=(i+1); j < S_POP_SIZE; j++)
		{
			if (sp.pop[i].fitness > sp.pop[j].fitness)
			{
				temp=sp.pop[i];
				sp.pop[i]=sp.pop[j];
				sp.pop[j]=temp;
			}
		}
	}
	
}

Individual getAlpha(Population &p)
{
	Individual lmax = p.pop[0];
	for (int i=1; i<POP_SIZE; i++) if (lmax.fitness >  p.pop[i].fitness) lmax=p.pop[i];
	return lmax;
}

Individual onePointMutate(Individual a)
{
	Individual c;
	c.sigma = a.sigma * pow(E, T*gauss());
	c.x1 = a.x1 + c.sigma * gauss();
	if (c.x1 < - 3.0) c.x1 = -3.0;
	if (c.x1 > 12.1) c.x1 = 12.1;
	c.x2 = a.x2 + c.sigma * gauss();
	if (c.x2 < 4.1) c.x2 = 4.1;
	if (c.x2 > 5.8) c.x2 = 5.8;
	c.fitness=fx(c);
	return c;
}

void mutateSPop(SelPopulation &sp)
{
	for (int i=0; i<S_POP_SIZE; i++)
	{
		sp.pop[i] = onePointMutate(sp.pop[i]);
	}
}

void evolution(Population &p)
{
	int g=0;
	SelPopulation sp;
	while (eval_num<EVAL_LIMIT)
	{
		for (int i=0; i<S_POP_SIZE; i=i+POP_SIZE)
		{
			for (int j=0; j<POP_SIZE; j++) 
			{
				sp.pop[i+j]=p.pop[j];
			}
		}
		mutateSPop(sp);
		sortSP(sp);
		for (int i=0; i<POP_SIZE; i++) p.pop[i]=sp.pop[i];

		cout << "Gen=" << g << " Evals=" << eval_num << " | f(x)=" << getAlpha(p).fitness << " | ";
		printInd(getAlpha(p));
		cout << endl;
		g++;
	}
}

int main()
{
	eval_num=0;
	srand(time(NULL));
	Population population1 = genPop();
	printPop(population1);
	cout << endl << "=========================" << endl;
	evolution(population1);
	return 0;
}
