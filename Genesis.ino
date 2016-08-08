
byte state = 0;
byte xMove = 0;
byte yMove = 0;
byte scroll = 0;
byte wait;

#define mSpeed 2
#define cstart dr9
#define select 8
#define up dr7
#define down dr6
#define left dr5
#define right dr4
#define ba dr3
#define aBut 2
#define sBut 1
#define bBut 8

JoyState_t JoySt;

void setup() {
  Mouse.begin();
  JoySt.XAxis = 127;
  JoySt.YAxis = 127;
  JoySt.ZAxis = 127;
  JoySt.Buttons = 0;
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT);
  pinMode(8, OUTPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
}


void loop() {
  if (dr10== LOW){
     GetState();

    if (state & 128) {
      yMove = -mSpeed;
      if (isButton(sBut)){
        scroll = 1;
        yMove = 0;
      }
    }

    else if (state & 64) {
      yMove = mSpeed;
      if (isButton(sBut)){
        scroll = -1;
        yMove = 0;
      }
    }
    else
      yMove = 0;

    if (state & 32)
      xMove = -mSpeed;

    else if (state & 16)
      xMove = mSpeed;
    else
      xMove = 0;

    if (!isButton(sBut) || !((state & 128) || (state & 64)))
      scroll = 0;
    else
      delay(50);
    Mouse.move(xMove, yMove, scroll);

    if (isButton(aBut)) {
      Mouse.press();
    }
    else
      Mouse.release();

    if (isButton(bBut))
      delay(7);
    else
      delayMicroseconds(1250);
  }
  else{
  GetState();
  if (state & 128)
    JoySt.YAxis = 0;
  else if (state & 64)
    JoySt.YAxis = 255;
  else
    JoySt.YAxis = 127;

  if (state & 32)
    JoySt.XAxis = 0;
  else if (state & 16)
    JoySt.XAxis = 255;
  else
    JoySt.XAxis = 127;

  state = state << 4;
  state = state >> 4;
  JoySt.Buttons = state;
  Joystick.setState(&JoySt);
  
  }
}
void GetState() {
  digitalWrite(select,LOW); 
  state = up << 1 ; //up
  state += down; //down
  state = state << 1;
  digitalWrite(select,HIGH); 
  state += left; //left
  state = state << 1;
  state += right; //right
  state = state << 1;
  state += ba; //ba
  state = state << 1;
  state += cstart; //cstart
  state = state << 1;
  digitalWrite(select,LOW);
 
  state += ba; //ba
  state = state << 1;
  state += cstart;
  state = ~state;
}
bool isButton(byte button) {

  if ((state & button)) {

    return true;
  }
  else
    return false;
}

