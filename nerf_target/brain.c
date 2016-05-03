/*
 The Brain blocks code: ie the block that will Orchestrates the rest of the blocks
 */
#include "cubelet.h"
#include <stdbool.h> // For true, false
#include <stdlib.h> // For random(), RAND_MAX

//What value does the distance sensor need exceed before we count it as a score
#define DISTANCE_THRESHOLD 50

//ID of the (distance) sensor used to detect if the target in down.
//TODO: Needs to be customized for each robot!
#define TARGET_SENSOR_ID 2593

//Min and max values for timing: how long drive blocks go before changing directions
#define DRIVE_COUNT_MINIMUM 3500
#define DRIVE_COUNT_MAXIMUM 6500

/** Globals **/
//Store a random number in drive_count_target. Increment drive_count until
//drive_count == drive_count_target to get a rough random time.
uint16_t drive_count_target;
uint16_t drive_count;

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

state_t state;

/** Forward declarations **/
void reset_target(void);
bool is_target_hit(void);
void set_state(state_t _state);
void move_target();
uint16_t random_drive_count();

void setup()
{
  //Defaulting to a stopped position.
  block_value = (uint8_t) PAUSE;
  drive_count_target = random_drive_count();
}

void loop()
{
  //Check if distance sensor is `high`
  if(is_target_hit())
  {
    //Reset the target
    reset_target();
  }
  else
  {
    //TOGGLE DIRECTIONS after a random period of time
    move_target();
  }
}

/**
  Synchronous function that sets the robot state to TARGET_RESET and blocks
  until the target has been successfully reset.
**/
void reset_target(void){
  //set state TARGET_RESET
  set_state(TARGET_RESET);

  //Block until the target has been reset
  while(is_target_hit())
  {
    wait(100);
  }
  set_state(DRIVE_FORWARD);
}

/**
  Determine if the target has been knocked down. Looks at the block_value of
  the Distance Cubelet with ID DISTANCE_THRESHOLD.

  @return true/false: true if the target is currently down, false otherwise.
**/
bool is_target_hit(void)
{
  if(get_block_value(TARGET_SENSOR_ID) >= DISTANCE_THRESHOLD)
  {
    return true;
  }
  else{
    return false;
  }
}

/**
  Use our block_value to hold the state of the robot. Other blocks can read
  our block value to determine the state.

  @param _state The new state for the robot.
**/
void set_state(state_t _state)
{
  block_value = (uint8_t)_state;
}

/**
  Toggles the state of the robot between DRIVE_FORWARD and DRIVE_BACKWARD.
  Switches state after a random amount of time (counts).
**/
void move_target(){
  if(drive_count >= drive_count_target)
  {
    if(block_value == DRIVE_FORWARD)
    {
      set_state(DRIVE_BACKWARD);
    }
    else if(block_value == DRIVE_BACKWARD){
      set_state(DRIVE_FORWARD);
    }
    drive_count = 0;
    drive_count_target = random_drive_count();
  }
  else{
    drive_count++;
  }
}

/**
  Generate a random number between DRIVE_COUNT_MINIMUM and DRIVE_COUNT_MAXIMUM.
  Used to choose a random amount of time to drive forwards and backwards.

  @return A random number between DRIVE_COUNT_MINIMUM and DRIVE_COUNT_MAXIMUM
**/
uint16_t random_drive_count(){
  double scaled = (double)rand()/RAND_MAX;

  return (uint16_t)(DRIVE_COUNT_MAXIMUM - DRIVE_COUNT_MINIMUM +1)*scaled + DRIVE_COUNT_MINIMUM;
}
