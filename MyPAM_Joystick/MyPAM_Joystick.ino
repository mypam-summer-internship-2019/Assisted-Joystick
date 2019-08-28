//////////////////////////////////////////////////
static int pot1 = A3 ;
static int pot2 = A1;

static double pot1Val;
static double pot2Val;

static double prePot1Val;
static double prePot2Val;

double mappValue = 2.35;

double xOffset = -220;
double yOffset = -220;
double xPos = 0;
double yPos = 0;

double preXPos = 0;
double preYPos = 0;

float xError = 0;
float yError = 0;

float kP = 5;
float kI = -0.8;
float kD = -5;

float kPG = 3;
float kIG = -0.93;
float kDG = -4;

float pX = 1;
float iX = 1;
float dX = 1;

float pY = 1;
float iY = 1;
float dY = 1;

int within = 3;

int xSpeed = 0;
int ySpeed = 0;

int m2L = 5;
int m2R = 6;

int m1L = 9;
int m1R = 10;

float targetX = 140;
float targetY = 140;

String data;
//////////////////////////////////////////////////

void setup() 
{
  Serial.begin(38400);

  pinMode(2,OUTPUT);
  
  pinMode(pot1,INPUT);
  pinMode(pot2,INPUT); 

  pinMode(m1L, OUTPUT);
  pinMode(m1R,OUTPUT); 
  
  pinMode(m2L, OUTPUT);
  pinMode(m2R,OUTPUT); 
}

void loop() 
{
  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);

  xPos = (pot1Val / mappValue)+ xOffset;
  yPos = (pot2Val / mappValue)+ yOffset;
  
  while (Serial.available() == 0) {}
  targetX = (Serial.parseFloat());
  
  while (Serial.available() == 0) {}
  targetY = (Serial.parseFloat());

  while (Serial.available() == 0) {}
  kPG = Serial.parseFloat();

  while (Serial.available() == 0) {}
  kIG = Serial.parseFloat();

  while (Serial.available() == 0) {}
  kDG = Serial.parseFloat();

  if (digitalRead(2) == 1)
  {
    assistance();
  }

  else{
   delay(5);
   digitalWrite(m1R,0);
   digitalWrite(m1L,0);
   digitalWrite(m2R,0);
   digitalWrite(m2L,0);
  }
/*
  if (yPos > 105)
  {
    yPos = 105;
  }
  else if (yPos < -105)
  {
    yPos = -105;
  }

  if (xPos > 150)
  {
    xPos = 150;
  }
  else if (xPos < -150)
  {
    xPos = -150;
  }
*/

  pot1Val = analogRead(pot1);
  pot2Val = analogRead(pot2);

  xPos = (pot1Val / mappValue)+ xOffset;
  yPos = (pot2Val / mappValue)+ yOffset;
  
  data = (String)(xPos) + "|";
  data = data + (yPos);
  data = data + "|";
  data = data + pot1Val;
  data = data + "|";
  data = data + pot2Val;
  delay (1);
  Serial.println(data);
}



void assistance()
{
/////PID - X/////////
xError = targetX - xPos;
pX = xError * kP;
iX = (iX + xError) * kI;
dX = (xPos - preXPos) * kD;
preXPos = xPos;

xSpeed = pX + iX + dX;

if (xSpeed > 255)
{
  xSpeed = 255;
}

else if (xSpeed < 100 && xSpeed > 5)
{
  xSpeed = 100;
}

if (xSpeed < -255)
{
  xSpeed = -255;
}

else if (xSpeed > -100 && xSpeed < -5)
{
  xSpeed = -100;
}

if (targetX > xPos - within && targetX < xPos + within)
{
  digitalWrite(m1R,0);
  digitalWrite(m1L,0);
  //iX = 0;
}
else if (xSpeed < 0)
{
  analogWrite(m1L,abs(xSpeed));
  digitalWrite(m1R,0);
}
else
{
  analogWrite(m1R,abs(xSpeed));
  digitalWrite(m1L,0);
}

/////PID - Y/////////
yError = targetY - yPos;
pY = yError * kP;
iY = (iY + yError) * kI;
dY = (yPos - preYPos) * kD;
preYPos = yPos;
ySpeed = pY + iY + dY;

if (ySpeed > 255)
{
  ySpeed = 255;
}

else if (ySpeed < 100 && ySpeed > 5)
{
  ySpeed = 100;
}

if (ySpeed < -255)
{
  ySpeed = -255;
}

else if (ySpeed > -100 && ySpeed < -5)
{
  ySpeed = -100;
}

if (targetY > yPos - within && targetY < yPos + within)
{
  digitalWrite(m2R,0);
  digitalWrite(m2L,0);
  //iY = 0;
}
else if (ySpeed < 0)
{
  analogWrite(m2L,abs(ySpeed) );
  digitalWrite(m2R,0);
}
else
{
  analogWrite(m2R,abs(ySpeed));
  digitalWrite(m2L,0);
}
}

///////////Controller Info/////////////////////////////
/*
90 Degrees = about  550 - 300 = 250
250 / 90 = 2.77778 (10 bit ADC)


kP = 1.51;
kI =0.15
kD = 0.34
*/
/////////////////////////////////////////////////////
