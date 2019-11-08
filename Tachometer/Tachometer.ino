int inPin = 2;
int ledPin = LED_BUILTIN;

bool triggerState = false;
unsigned long lastTriggerTime = 0;

const float diametreSantimatres = 3;
const int triggersCount = 8;

const float milisecondsInOneSecond = 1000;
const float nanometresInOneCantimetre = 10000;
const float betweenTriggersDistanceInNanometres = (nanometresInOneCantimetre * diametreSantimatres * PI * 2) / triggersCount;

float totalDistance = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(inPin, INPUT);
  pinMode(ledPin, OUTPUT);

  triggerState = !(bool)digitalRead(inPin);
  lastTriggerTime = millis();
  
  // initialize serial:
  Serial.begin(9600);

  Serial.print("Between triggers distance: ");
  Serial.println(betweenTriggersDistanceInNanometres);
  Serial.println();
}

// the loop function runs over and over again forever
void loop() {
    bool newTriggerState = !(bool)digitalRead(inPin);
    
    if(newTriggerState != triggerState) {
        triggerState = newTriggerState;

        if(newTriggerState) {
          totalDistance = totalDistance + (float)betweenTriggersDistanceInNanometres;
          
          unsigned long newTriggerTime = millis();
          
          float timePassed = newTriggerTime - lastTriggerTime;                    
          float currentSpeed = betweenTriggersDistanceInNanometres / timePassed;
          float currentSpeedCantimetresPerSecond = (currentSpeed / nanometresInOneCantimetre) * milisecondsInOneSecond;
          float timePassedInSeconds = timePassed / milisecondsInOneSecond;

          Serial.print("Time Passed: ");          
          Serial.println(timePassedInSeconds);          
          Serial.print("Speed: ");
          Serial.println(currentSpeed);
          Serial.print("Distance: ");
          Serial.println(totalDistance / (float) nanometresInOneCantimetre);
          Serial.println();

          lastTriggerTime = newTriggerTime;
        }
    }

    digitalWrite(ledPin, newTriggerState);
}
