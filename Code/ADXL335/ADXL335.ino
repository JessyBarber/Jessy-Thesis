#include <ADXL335.h>

ADXL335 adx1 = ADXL335();

int range = 2;  //Range: 2g, 4g, 8g, 16g
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  adx1.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // int16_t x, y, z;
  // adx1.getXYZ(&x, &y, &z);
  float ax, ay, az;

  adx1.getAcceleration(&ax, &ay, &az);
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);

  delay(250);
}
