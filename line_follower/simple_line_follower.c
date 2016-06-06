#include "cubelet.h"
#include "led.h"

//The starting threshold of the distance block that determines what is a line and what isn't
#define DEFAULT_THRESHOLD 27

void setup()
{

}

void loop()
{
  //Read our distance value
  uint8_t value = get_distance();

  //Determine if we think we are on a line or not.
  if(value > DEFAULT_THRESHOLD)
  {//No line assuming reflective surface with dull line
    led_off();
    block_value = 255;
  }
  else{
    led_on();
    block_value = 0;
  }
}
