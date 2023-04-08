// ultrasonic pins
const int trigPin = 2;
const int echoPin = 1;

// check ultrasonic distance function
double getDistance() {
  double distance;
  long duration;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance in metres
  distance = duration * 0.034 / 2;
  
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  double ultraDistance = getDistance();
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (metres): ");
  Serial.println(ultraDistance);
}
