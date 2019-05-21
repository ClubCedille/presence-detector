static const int DIGITAL_INPUT = D1;

static int getDigitalSignal()
{
  return digitalRead(DIGITAL_INPUT);
}

static bool lightIsDetected()
{
  return getDigitalSignal() == HIGH;
}

void setup()
{
  // The input pin is on when light is detected.
  // Connect a 56 kiloohm pull-down resistor to the digital input pin.
  pinMode(DIGITAL_INPUT, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (lightIsDetected())
  {
    digitalWrite(LED_BUILTIN, LOW); // LED state is inverted.
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH); // LED state is inverted.
  }
  delay(1000);
}
