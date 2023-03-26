## First Time Setup 

In the Arduino IDE go to Tools->Board:""->Board Manager and download the Arduino SAMD Boards (32-bits ARM Cortex-M0+) by Arduino package. This includes drivers for MKR WAN boards. 

## Common Issues

Seems like double pressing the reset button will change the COM port, and then pressing once will set it back. Honestly just press reset button until it works and uploads. 

Double press goes from COM3 to COM6 -> COM6 is actually labelled in device manager as bootloader. Upload to bootloader and then will automatically switch back to COM3 and run.

## Libraries
- arduinoFFT
- MKRWAN
- LoRa ..........