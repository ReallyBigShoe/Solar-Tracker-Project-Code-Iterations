//"LDRN" is "North LDR". Motor1 is associated with N & S. Motor2 is associated with E & W.
#define LDRN A0
#define LDRS A1
#define LDRW A2
#define LDRE A3
//PWM pins
#define Motor1For 3
#define Motor2For 5
#define Motor1Back 6
#define Motor2Back 9
//Adjustable Motor speed between 1 and 255
short motorSpeed = 100;
//Adjustable sensitivity 0-100 (percent) (aka the threshold you want the device to act on. If it's too low, it moves too frequently and erratically because of potential noise. Too high and it doesn't correct its position enough)
short threshold = 20;

//ofc this is initialization of the difference variable
int vertDiff = 0;
int horiDiff = 0;
//Adjustable motor action time (how long you want each motor to perform the corrective action)
int delayTime = 50;



void setup() {
  pinMode(Motor1For, OUTPUT);
  pinMode(Motor2For, OUTPUT);
  pinMode(Motor1Back, OUTPUT);
  pinMode(Motor2Back, OUTPUT);
}

void loop() {
//read the analog LDR Pins
  int valN = analogRead(LDRN);
  int valS = analogRead(LDRS);
  int valW = analogRead(LDRW);
  int valE = analogRead(LDRE);
  //finding absolute values for the light level differences.
  vertDiff = abs(valN - valS);
  horiDiff = abs(valW - valE);

  int thresholdADC = (threshold * 1023) / 100;

  //all these are comparisons between the LDRS. If there is a difference AND it's above the threshold, it moves.
  if (valN > valS && vertDiff >= thresholdADC) {
    digitalWrite(Motor1Back, LOW);
    analogWrite(Motor1For, motorSpeed);
    delay(delayTime);
    digitalWrite(Motor1For, LOW);

  } else if (valS > valN && vertDiff >= thresholdADC) {
    digitalWrite(Motor1For, LOW);
    analogWrite(Motor1Back, motorSpeed);
    delay(delayTime);
    digitalWrite(Motor1Back, LOW);
  }

  if (valW > valE && horiDiff >= thresholdADC) {
    digitalWrite(Motor2Back, LOW);
    analogWrite(Motor2For, motorSpeed);
    delay(delayTime);
    digitalWrite(Motor2For, LOW);

  } else if (valE > valW && horiDiff >= thresholdADC) {
    digitalWrite(Motor2For, LOW);
    analogWrite(Motor2Back, motorSpeed);
    delay(delayTime);
    digitalWrite(Motor2Back, LOW);
  }
  //can be reduced or removed...just thought the loops would be too fast without it
  delay (30);
}
