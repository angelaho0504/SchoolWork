#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rideTime();
void walkAroundTime();

/* example of usage

int main( ) {
rideTime();
printf ("Ride over\n");
walkAroundTime();
printf ("Finished walking around  \n");
}
*/


void rideTime() {

int seconds = ( random() % 5) + 1 ;
sleep (seconds); 

}

void walkAroundTime() {

int seconds = (random() % 10) + 1 ;
sleep (seconds);

}

