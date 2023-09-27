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
     1. SCL--A5-Pin 19
     2. SDA--A4-Pin 18
     3. VCC--5v
     4. GND--GND

3. Keypad (8 Pins)
      Left to Right--Pin 9 to Pin 2  (Rows: Pin 9 to Pin 6, Columns: Pin 5 to Pin 2)

4. MFRC522
     1. SDA--Pin 10
     2. SCK--Pin 13
     3. MOSI--Pin 11
     4. MISO--Pin 12
     5. IRQ--NIL
     6. GND--GND
     7. RST--A0-Pin 14
     8. 3.3V--3.3V   

5. USB-TTL Converter
     1. DTR--Reset(If not working, keep disconnected)(**Hold Reset Button on Arduino while uploading program to emulate the reset**)
     2. RXD--TXD
     3. TXD--RXD
     4. 5V--Vin
     5. GND--GND
     6. 3V3--NIL
