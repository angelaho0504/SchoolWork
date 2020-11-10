/**
    @file ballistics.c
    @author Angela Ho (aho)
    This program prompt the user for initial projectile velocity,
    then print a table with initial angle, initial velocity,
    flight time of the projectile, and distance travels from the
    its point of origin. Each row has different degree starting
    from 0 to 90 degree with 5 degree increment.
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Gravitational acceleration */
#define GRAVITY 9.81
/** Degree per randian */
#define RADIAN 180
/** Increments of angle */
#define INCREMENT 5
/** Max angle */
#define MAX_ANGLE 90
/** Min angle */
#define MIN_ANGLE 0

/**
    Find the time a projectile is in the air given
    the angle in degree that the projectile leaves
    the ground and the its initial velocity.
    @param angle initial angle when leaving the ground
    @param v0 initial velocity
    @return t flight time of the projectile
  */
double flightTime( int angle, double v0 )
{
    double t;
    double rad = angle * ( M_PI/RADIAN );
    t = 2.0 * v0 * sin( rad ) / GRAVITY;
    return t;
}

/**
    Prints a row of the table, include the given angle,
    initial velocity, and the flight time. The distance
    the projectile travels is also reported.
    @param angle initial angle when leaving the ground
    @param v0 initial velocity
    @param t flight time of the projectile
  */
void tableRow( int angle, double v0, double t )
{
    double rad = angle * ( M_PI/RADIAN );
    double distance = v0 * t * cos( rad );
    printf( "%10d | %10.3f | %10.3f | %10.3f\n", angle, v0, t, distance );
}

/**
    Starting point of the program. Read in the initial
    velocity and prints out the full table
  */
int main()
{
    printf( "V0: \n" );
    printf( "     angle |         v0 |       time |   distance\n" );
    printf( "-----------+------------+------------+-----------\n" );
    int angle = MIN_ANGLE;
    double t;
    double v0;
    scanf( "%lf", &v0 );
    while ( angle <= MAX_ANGLE ){
        t = flightTime( angle, v0 );
        tableRow( angle, v0, t );
        angle += INCREMENT;
    }
}
