# ArduinoProject
Access Management using RFID and Keypad

This Project uses:
1. A MFRC522 RFID Reader along with 2 Mifare 1K Tags(a card and a keychain).
2. A 4*4 KEYPAD.
3. A 16*2 I2C LCD. 
4. An Arduino Uno.
5. USB-TTL Converter (For Uploading Programs).
6. Jumper Wires (M-M, M-F).


PIN Connections (To Arduino):
1. I2C LCD (4 Pins)
      SCL--A5-Pin 19
      SDA--A4-Pin 18
      VCC--5v
      GND--GND

2. Keypad (8 Pins)
      Left to Right--Pin 9 to Pin 2
                   (Pin 9 to Pin 6-Rows, Pin 5 to Pin 2-Columns)

3. MFRC522
      SDA--Pin 10
      SCK--Pin 13
      MOSI--Pin 11
      MISO--Pin 12
      IRQ--NIL
      GND--GND
      RST--A0-Pin 14
      3.3V--3.3V

4. USB-TTL Converter
      DTR--Reset(If not working, keep disconnected)(**Hold Reset Button on Arduino while uploading program to emulate the reset**)
      RXD--TXD
      TXD--RXD
      5V--Vin
      GND--GND
      3V3--NIL
