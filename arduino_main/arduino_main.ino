int analogInput = A0;
int digitalInput = D4;

void setup()
{
  // Is on when light is detected.
  pinMode(digitalInput, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // For printing in the console
}

void loop()
{
  Serial.print("HIGH: ");
  Serial.println(HIGH); // Displays 1.
  Serial.print("LOW: ");
  Serial.println(LOW); // Displays 0.
  int aSignal = analogRead(analogInput);
  int dSignal = digitalRead(digitalInput);
  Serial.println(aSignal);
  Serial.println(dSignal);
  if(aSignal>700) // || dSignal==LOW
  {
    Serial.println("Light is detected.");
    digitalWrite(LED_BUILTIN, LOW); // LED state is inverted.
  }
  else
  {
    Serial.println("Light is not detected.");
    digitalWrite(LED_BUILTIN, HIGH); // LED state is inverted.
  }
  delay(1000);
}
