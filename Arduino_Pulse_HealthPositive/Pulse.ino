void initPulse() {
  Serial.println("Initializing Pulse...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
//    SeeedOled.clearDisplay();
//    SeeedOled.setTextXY(0, 0);
//    SeeedOled.putString("MAX30105 not found");
    while (1);
  }
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void getPulseData() {
  beatAvg_prev = beatAvg;
  long irValue = particleSensor.getIR();
  if (irValue < 50000) {
//    SeeedOled.setTextXY(2, 0);
//    SeeedOled.putString("PUT FINGER");
    Serial.println("Put finger");
  }
  //  Serial.print(irValue); Serial.print("\t");
  if (checkForBeat(irValue) == true)  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
}

void checkNewData() {
  if (beatAvg == beatAvg_prev) {
    newData = false;
  }
  else {
    newData = true;
  }
}
