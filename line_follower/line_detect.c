#include "cubelet.h"
#include "led.h"

//The starting threshold of the distance block that determines what is a line and what isn't
#define DEFAULT_THRESHOLD 27

//State enumeration with only two states: line or no line.
typedef enum {
    LINE_DETECTED,
    NO_LINE_DETECTED,
} state_t;

//The threshold for what is considered a dull line vs a reflective surface.
//Defaults to DEFAULT_THRESHOLD. Changes if there is a KNOB_BLOCK as a direct neighbor
uint8_t threshold;

//Forward declarations
uint8_t get_realtime_config();
state_t determine_state(uint8_t value);

void setup()
{
  threshold = DEFAULT_THRESHOLD;
}

void loop()
{
  //Check to see if we should adjust our threshold based on a KNOB_BLOCK
  threshold = get_realtime_config();

  //Read our distance value
  uint8_t value = get_distance();

  //Determine if we think we are on a line or not.
  state_t state = determine_state(value);

  switch(state){
    case NO_LINE_DETECTED:
      block_value = 255;
    break;
    case LINE_DETECTED:
      block_value = 0;
    break;
  }
}

/**
  Searches for a KNOB_BLOCK attached as a direct neighbor, if so, gets it's
  block value to set our threshold for what is a line and what isn't.

  @return Either the new value that should be set as the threshold if a KNOB_BLOCK
  is detected, or the old threshold.
*/
uint8_t get_realtime_config()
{
  //Loop over the routing table
  for (uint8_t i = 0; i <= rt_last_row; i++)
  {
    table_entry_t* entry = &rt_entries[i];

    //If there is a knob block as a direct neighbor, use it to set the threshold
    if (entry->TTL > 0 && entry->hop_count == 1 && entry->block_type == KNOB_BLOCK)
    {
      return entry->block_value;
    }
  }
  //If no knob block was found, don't change the threshold.
  return threshold;
}

/**
  Based on a block_value determines if we detect a line or not.

  @param A block_value
  @return LINE_DETECTED or NO_LINE_DETECTED based on the input
*/
state_t determine_state(uint8_t value)
{
  if(value > threshold)
  {//No line assuming reflective surface with dull line
    led_off();
    return NO_LINE_DETECTED;
  }
  else{
    led_on();
    return LINE_DETECTED;
  }
}
