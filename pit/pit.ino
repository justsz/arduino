const int R = 3; //red and blue are swapped...
const int G = 5;
const int B = 6;
const int TEMP = 0;
float temp = 0;

const float minTemp = 18;
const float maxTemp = 22;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  temp = analogToCelsius(analogRead(TEMP));
  Serial.println(temp);
  
  
  if (temp > maxTemp) {
    analogWrite(R, 255);
    analogWrite(G, 0);
    analogWrite(B, 0); 
  } else if (temp < minTemp) {
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 255);
  } else {
    analogWrite(R, 0);
    analogWrite(G, 255);
    analogWrite(B, 0);
  }
  
  delay(500);
}

float analogToCelsius(int anlg) {
  //reading fraction mult by max voltage
  //one volt is 100C
  //reading can't actually go up to 500C...
  return (anlg + 1.0) / 1024.0 * 5.0 * 100.0;
}
