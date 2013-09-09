const int R = 3; //red and blue are swapped...
const int G = 5;
const int B = 6;
const int BUTTON = 12;
boolean lastButton = LOW;
boolean currentButton = LOW;
const int colorCount = 8;
int currentColor = 7;
int colors[colorCount][3] = {
  {255, 0, 0}, //red
  {0, 255, 0}, //green
  {0, 0, 255}, //blue
  {127, 0, 127}, //purple
  {0, 127, 127}, //teal
  {127, 127, 0}, //orange
  {85, 85, 85}, //white
  {0, 0, 0} //off  
};


void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BUTTON, INPUT); 
}

void loop() {
  currentButton = debounce(lastButton);
  
  if (lastButton == LOW && currentButton == HIGH) {
    cycleColor();
  } 
  lastButton = currentButton;
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
 
  return current; 
}

void cycleColor() {
  currentColor = (currentColor + 1) % colorCount;
  analogWrite(R, colors[currentColor][0]);
  analogWrite(G, colors[currentColor][1]);
  analogWrite(B, colors[currentColor][2]);
}
