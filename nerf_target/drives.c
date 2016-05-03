#include "cubelet.h"

/**
  Enumeration for the possible states of the robot. The routines for the other
  blocks in the construction need to have this same enumeration.
*/
typedef enum {
    PAUSE,//Default to this state
    DRIVE_FORWARD,
    DRIVE_BACKWARD,
    TARGET_RESET
} state_t;

//Forward declarations
state_t get_brain_state();

//Holds the current state of the robot.
state_t state;

//The ID for the 'brain' block that is controlling the state.
//TODO: Needs to be changed for each unique robot
#define BRAIN_BLOCK_ID 186883

//The speed at which the drive block drives
#define DRIVE_SPEED 255

/**
ALL Drive blocks
**/
void setup()
{
  //Start out disabled until the `brain` shows up.
  state = PAUSE;
}
void loop()
{
  //Read the state of the robot
  state = get_brain_state();

  //Based on the state, determine out action
  switch(state){
    case DRIVE_FORWARD:
      set_drive_direction(FORWARD);
      set_drive(DRIVE_SPEED);
      break;
    case DRIVE_BACKWARD:
      set_drive_direction(BACKWARD);
      set_drive(DRIVE_SPEED);
      break;
    case PAUSE:
    case TARGET_RESET:
      //Stop driving
      set_drive(0);
      break;
  }
}

/**
  Fetch the state of the robot from the Cubelet with ID BRAIN_BLOCK_ID.

  @return The state of the robot
**/
state_t get_brain_state()
{
  return (state_t)get_block_value(BRAIN_BLOCK_ID);
}
