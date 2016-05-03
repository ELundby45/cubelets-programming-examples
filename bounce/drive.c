#include "cubelet.h"

#define FRONT_DISTANCE_ID 166215
#define REAR_DISTANCE_ID 2593
#define THRESHOLD 200
#define DRIVE_SPEED 200

uint8_t direction = FORWARD;

void setup()
{

}

void loop()
{
  if(direction == FORWARD && get_block_value(FRONT_DISTANCE_ID) > THRESHOLD)
  {
    toggle_directions();
    direction = BACKWARD;
  }
  else if(direction == BACKWARD && get_block_value(REAR_DISTANCE_ID) > THRESHOLD)
  {
    toggle_directions();
    direction = FORWARD;
  }
  set_drive_direction(direction);
  set_drive(DRIVE_SPEED);
}
