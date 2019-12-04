#include <driver/dac.h>


void setup() {
  Serial.begin(9600);
  Serial.print("Sortie analogique ");

  dac_output_enable(DAC_CHANNEL_1);
}

void loop() {
  for(int i=0; i<255; i+=8){
    dac_output_voltage(DAC_CHANNEL_1, i);
  }
  for(int i=255; i>0; i-=8){
    dac_output_voltage(DAC_CHANNEL_1, i);
  }
}
