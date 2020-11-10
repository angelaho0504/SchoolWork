#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "rider.h"
#include "sleeper.h"
#include "coordinator.h"

typedef struct {
  int riderId;
  int carId;
}id;

void *rider ( void *args ) {
  
  id *actual_args = args;
  
  int carId;
  
  int riderId = actual_args->riderId;

  while(1) {
    
    walkAroundTime();
    printf ("Rider %d is now walking around the park.\n", riderId);
    carId = getInLine();
    rideTime();
    printf ("Rider %d is now riding in car %d.\n", riderId, carId);
    returnCar(carId);
    printf("Rider %d returned car %d.\n", riderId, carId);
    
  }
}
