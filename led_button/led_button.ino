const int LED = 9;
const int BUTTON = 2;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

int fadeLevel = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT); 
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
 
  return current; 
}

void fade(int led, boolean fadeIn) {
 if (fadeIn) {
    for (int i = fadeLevel; i < 256; i++) {
      analogWrite(led, i);
      delay(3);
      fadeLevel = i;
    }
  } else {
    for (int i = fadeLevel; i >= 0; i--) {
      analogWrite(led, i);
      delay(3);
      fadeLevel = i;
    }
  }
  
}

void loop() {
  currentButton = debounce(lastButton);
  
  if (lastButton == LOW && currentButton == HIGH) {
    ledOn = !ledOn;
  } 
  lastButton = currentButton;
  
  fade(LED, ledOn);
}
