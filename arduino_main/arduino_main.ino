int analogInput = A0;
int digitalInput = D5;

void setup()
{
  // Is on when light is detected.
  pinMode(digitalInput, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); // For printing in the console
}

void loop()
{
  int aSignal = analogRead(analogInput);
  int dSignal = digitalRead(digitalInput);
  Serial.print("Analog signal: ");
  Serial.println(aSignal);
  Serial.print("Digital signal: ");
  Serial.println(dSignal);
  if(aSignal>700) // || dSignal==HIGH
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
