struct PID_receive
{
  float Kp;
  float Ki;
  float Kd;
 }PID_Receive;
void PID_receive_init()
 {
  PID_Receive.Kp=0;
  PID_Receive.Ki=0;
  PID_Receive.Kd=0;
  }
void setup() {
  // put your setup code here, to run once:
  PID_receive_init();
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    delay(100);
    PID_Receive.Kp=Serial.parseFloat();
    PID_Receive.Ki=Serial.parseFloat();
    PID_Receive.Kd=Serial.parseFloat();
   }
   while(Serial.read() >= 0){}
   Serial.print("Kp:");
   Serial.print(PID_Receive.Kp);
   Serial.print(" ");
   Serial.print("Ki:");
   Serial.print(PID_Receive.Ki);
   Serial.print(" ");
   Serial.print("Kd:");
   Serial.println(PID_Receive.Kd);
   delay(500);
}
