// unsigned long timer = 0;
// long loopTime = 5000;   // microseconds

// void setup() {
//   Serial.begin(9600);
//   timer = micros();
// }

// void loop() {
//   timeSync(loopTime);
//   //int val = analogRead(0) - 512;
//   // double val = (analogRead(0) -512) / 512.0;
//   double val = (analogRead(A1));
//   sendToPC(&val);
// }

// void timeSync(unsigned long deltaT)
// {
//   unsigned long currTime = micros();
//   long timeToDelay = deltaT - (currTime - timer);
//   if (timeToDelay > 5000)
//   {
//     delay(timeToDelay / 1000);
//     delayMicroseconds(timeToDelay % 1000);
//   }
//   else if (timeToDelay > 0)
//   {
//     delayMicroseconds(timeToDelay);
//   }
//   else
//   {
//       // timeToDelay is negative so we start immediately
//   }
//   timer = currTime + timeToDelay;
// }

// void sendToPC(int* data)
// {
//   byte* byteData = (byte*)(data);
//   Serial.write(byteData, 2);
// }

// void sendToPC(double* data)
// {
//   byte* byteData = (byte*)(data);
//   Serial.write(byteData, 4);
// }