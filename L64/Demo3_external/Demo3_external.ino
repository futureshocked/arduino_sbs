  #include <Wire.h> //I2C library
  #include <EEEPROM.h> // This library is available at https://github.com/futureshocked/EEEPROM
  
  EEEPROM eeeprom = EEEPROM();

  void setup() 
  {
    char somedata[] = "this is data from the eeprom"; // data to write
    Wire.begin(); // initialise the connection
    Serial.begin(9600);
    eeeprom.i2c_eeprom_write_page(0x50, 0, (byte *)somedata, sizeof(somedata)); // write to EEPROM 

    delay(10); //add a small delay

    Serial.println("Memory written");
  }

  void loop() 
  {
    int addr=0; //first address
    byte b = eeeprom.i2c_eeprom_read_byte(0x50, 0); // access the first address from the memory

    while (b!=0) 
    {
      Serial.print((char)b); //print content to serial port
      addr++; //increase address
      b = eeeprom.i2c_eeprom_read_byte(0x50, addr); //access an address from the memory
    }
    Serial.println(" ");
    delay(2000);

  }
