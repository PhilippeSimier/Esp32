#include <driver/adc.h>

void setup()
{
  Serial.begin(115200);
  // résolution en bits (0 4095)
  adc1_config_width(ADC_WIDTH_BIT_9);
  
  // atténuation du convertisseur sur 0 db tension de 0v à 1v
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_0);
}

void loop()
{

  int value = adc1_get_raw(ADC1_CHANNEL_6);
  Serial.println(value);
  delay(1000);
}
