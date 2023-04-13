//This test will record the max acceleration values with 3.3 V serial connection. 
//The raw acceleration data on the sending side and the max acceleration data on the receiving side will be logged
#include "Sender.h"

void setup() {
  // put your setup code here, to run once:
  //Initialise Serial connection
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Starting Serial Success");
  //Initialise LoRa connection
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  Serial.println("LoRa Modem Started");
  //Initialise LoRa connection
  LoRa.begin(915E6);
}

void loop() {
  // put your main code here, to run repeatedly:

  //FFT SAMPLING
  double real_x_axis[sample_n]{};
  double imag_x_axis[sample_n]{};
  double real_y_axis[sample_n]{};
  double imag_y_axis[sample_n]{};
  double real_z_axis[sample_n]{};
  double imag_z_axis[sample_n]{};

  //ACCEL SAMPLING
  double xAccel[sample_n] {};
  double yAccel[sample_n] {};
  double zAccel[sample_n] {};

  //SAMPLE RAW DATA
  for (int i = 0; i < sample_n; i++) {
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    delay(sample_interval);
  }

  //SAMPLE ACCEL DATA
  for (int i = 0; i < sample_n; i++) {
    double voltageX = real_x_axis[i] * vRef / (adc_resolution - 1);
    double voltageY = real_y_axis[i] * vRef / (adc_resolution - 1);
    double voltageZ = real_z_axis[i] * vRef / (adc_resolution - 1);

    xAccel[i] = (voltageX - x_zero) / sensitivity;
    yAccel[i] = (voltageY - y_zero) / sensitivity;
    zAccel[i] = ((voltageZ - z_zero) / sensitivity) - 1.0; // subtract Earth's gravity
  }
  
  // PRINT RAW ACCEL VALUES
  for (int i = 0; i < sample_n; i++) {
    Serial.print(xAccel[i]);
    Serial.print(" ");
    Serial.print(yAccel[i]);
    Serial.print(" ");
    Serial.println(zAccel[i]);
  }

  //FIND AND PRINT MAX ACCEL VALS
  double maxXAccel = findMax(xAccel);
  double maxYAccel = findMax(yAccel);
  double maxZAccel = findMax(zAccel);

  //TRANSMIT LORA PACKET
  LoRa.beginPacket();
  // LoRa.write(buffer, packetSize);
  LoRa.write((uint8_t*)&maxXAccel, sizeof(maxXAccel));
  LoRa.write((uint8_t*)&maxYAccel, sizeof(maxYAccel));  
  LoRa.write((uint8_t*)&maxZAccel, sizeof(maxZAccel));
  LoRa.endPacket();
}
