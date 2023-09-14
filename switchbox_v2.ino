//hw definition
#define RL_T15_O 4
#define RL_T30_O 5
#define RL_CAN1 6
#define RL_CAN2 7
#define RL_CAN3 8
#define ON HIGH
#define OFF LOW

//app definition
#define BUSOFF1_O RL_CAN1
#define BUSOFF2_O RL_CAN2
#define BUSOFF3_O RL_CAN3

//message handling
#define T30MesPos 5
#define T15MesPos 6
#define TAuxMesPos 7


void setup() {
  // put your setup code lnhere, to run once:
  Serial.begin(9600);
}

int incomingByte = 0;
int mesLength = 0;
int cmdType = 0;
char mesIndex = 0;
char mesBuf[20] = "";

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    /*
    T15 rx: dxxxxx1xx
    T30 rx: dxxxx1xxx
    TAux rx:dxxxxxx1x
    */
    if (incomingByte != -1) {
      if (incomingByte == 'd') {
        mesIndex = 0;
        mesLength = 8;
        cmdType = 1;
      }
      if (incomingByte == 'b') {
        mesIndex = 0;
        mesLength = 2;
        cmdType = 2;
      }
      mesBuf[mesIndex] = (char)incomingByte;
      mesIndex++;
      if (mesIndex > mesLength) {
        // Serial.println(mesBuf);
        switch (cmdType) {
          case 1 :
          {
            if (mesBuf[T15MesPos] == '1') {
              Serial.println("T15 ON");
              digitalWrite(RL_T15_O, ON);
            }
            else if (mesBuf[T15MesPos] == '0') {
              Serial.println("T15 OFF");
              digitalWrite(RL_T15_O, OFF);
            }
            else {
            }

            if (mesBuf[T30MesPos] == '1') {
              Serial.println("T30 ON");
              digitalWrite(RL_T30_O, ON);
            } else if (mesBuf[T30MesPos] == '0') {
              Serial.println("T30 OFF");
              digitalWrite(RL_T30_O, OFF);
            } else {
            }

            if (mesBuf[TAuxMesPos] == '1') {
              Serial.println("TAux ON");
            } else if (mesBuf[TAuxMesPos] == '0') {
              Serial.println("TAux OFF");
            } else {
            }
          break;
          }
          case 2:
          {
            if (mesBuf[1] == '1'&& mesBuf[2] == '1') {
              Serial.println("CAN1 ON");
            } 
            if (mesBuf[1] == '1'&& mesBuf[2] == '0') {
              Serial.println("CAN1 OFF");
            } 
            if (mesBuf[1] == '2'&& mesBuf[2] == '1') {
              Serial.println("CAN2 ON");
            }
            if (mesBuf[1] == '2'&& mesBuf[2] == '0') {
              Serial.println("CAN2 OFF");
            }
            if (mesBuf[1] == '3'&& mesBuf[2] == '1') {
              Serial.println("CAN3 ON");
            }
            if (mesBuf[1] == '3'&& mesBuf[2] == '0') {
              Serial.println("CAN2 OFF");
            }
          break;
          }
          default:
          break;
        }
      }
    }
  }
}
