const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;

void setup() { 
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double x_axis_data[] {};
  double y_axis_data[] {};
  double z_axis_data[] {};
  long int t1 = millis();
  for (int i = 0; i < 256; i++) {
    // Serial.println(i);
    x_axis_data[i] = analogRead(x_axis);
    y_axis_data[i] = analogRead(y_axis);
    z_axis_data[i] = analogRead(z_axis);
    
    delay(50);
  }
  long int t2 = millis();
  Serial.print("Time taken: "); Serial.print((t2-t1)/1000); Serial.println(" s");
}
