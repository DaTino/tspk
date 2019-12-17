/****************************************************************************
*
*       stdinc.h:	Header file for Machine Learning projects.
*
*                       Sharlee Climer
*                       January 2003
*
****************************************************************************/


#ifndef STDINC_H
#define STDINC_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
const int DIM = 3;		// dimension of points
const int NUMTRIALS = 1000;      // number of trials to run
*/

const int TRUE = 1;
const int FALSE = 0;
//const int INFINITY = 1073741823;     // 2^30 - 1

inline int max(int x, int y) { return x > y ? x : y; }
inline double max(double x, double y) { return x > y ? x : y; }
inline int min(int x, int y) { return x < y ? x : y; }
inline double min(double x, double y) { return x < y ? x : y; }
//inline int abs(int x) { return x < 0 ? -x : x; }
//inline float abs(float x) { return x < 0.0 ? -x : x; }
//inline float K(float x, float h) {return exp(-1*(x*x)/(h*h));}//kernel function

// Return a random number in [0,1]
inline double randfrac() { return ((double) rand()/RAND_MAX); }

inline void warning(char* p) { fprintf(stderr,"Warning: %s\n",p); }
inline void fatal(char* string) {fprintf(stderr,"Fatal: %s\n",string);
                                 exit(1); }

/*
typedef struct
{
  float coord[DIM];
} Point;
*/

// functions in calc.cpp:
//float calcDist(Point, Point);
float calcAvg(float *, int);
void printStatistics(float *, int, char *);


#endif
