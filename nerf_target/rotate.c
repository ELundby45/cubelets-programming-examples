#include "cubelet.h"

//The time to push the arm used to reset the target forward or pull it back
#define DELAY_TIME 400

//The ID of the block setting the state of the robot
//TODO: This ID needs to be changed for every unique robot.
#define BRAIN_BLOCK_ID 186883

//The amount of time to wait before reseting the target. Allows for other action
//blocks the 'celebrate' ie: make noise or turn on flashlights.
#define CELEBRATION_DELAY 2000

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

state_t get_brain_state();

//Holds the state of the robot
state_t state;

//Helper byte to allow for something to happen just once per round.
uint8_t once = 0;

void setup()
{

}

/**
  Rotate block
**/
void loop()
{
  //Read the state of the robot
  state = get_brain_state();

  //The only state we are responsible for is reseting the target.
  if(state == TARGET_RESET)
  {
    if(once == 0)
    {//Only allow celebration one time, if the target fails to reset, keep resetting quickly until it sticks.
      //Let the speakers and flashlights go for a bit.
      wait(CELEBRATION_DELAY);
      once = 1;
    }

    //Rotate forward for some time,
    set_rotate_direction(BACKWARD);
    set_rotate(255);
    wait(DELAY_TIME);

    //Rotate backward for some time
    set_rotate_direction(FORWARD);
    set_rotate(127);
    wait(DELAY_TIME);

    //Stop rotating
    set_rotate(0);
    wait(DELAY_TIME);
  }
  else {
    once = 0;
    //do nothing
    set_rotate(0);
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
