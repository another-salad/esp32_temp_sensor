# esp32_temp_sensor  
ESP32E board, PCT 2075 sensor  
  
Simple webserver returning temp reading from sensor. Utilising Arduino libraries as I have no idea what I am doing...    
  
Board is a **FireBeetle ESP32-E**  
Arduino setup instructions (required to get VSCode up and running) and product info: https://wiki.dfrobot.com/FireBeetle_Board_ESP32_E_SKU_DFR0654  
  
**PCT2075** Arduino setup (with examples): https://learn.adafruit.com/adafruit-pct2075-temperature-sensor/arduino  
  
**Building**  
- Add WifiConfig.h to your Arduino libraries
- Install packages
- Upload to SBC via VSCode or the Arduino IDE, both rely on esptool.py  

I'm sure there is a better way to upload this to your board, but this worked for me..
