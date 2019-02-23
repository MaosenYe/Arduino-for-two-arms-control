#include <PWM.h>
long percentage=0;//占空比
unsigned int left_percentage = 0;
unsigned right_percentage =0;
int left_hand_pin=10;
int right_hand_pin=9;
int32_t frequency = 50; //frequency (in Hz)
int angle_pin = A3; // 读取的角度429-523 平衡473
struct pid   //PID结构体的定义
{
  float SetAngle;
  float ActualAngle;
  float err;
  float err_last;
  float Kp,Ki,Kd;
  float voltage_change;
  float integral;
}PID;

 void PID_init() //结构体初始化
 {
  printf("PID_init begin \n");
  PID.SetAngle=0.0;
  PID.ActualAngle=0.0;
  PID.err=0.0;
  PID.err_last=0.0;
  PID.voltage_change=0.0;
  PID.integral=0.0;
  PID.Kp=0.2;       //自己设定
  PID.Ki=0.015;     //自己设定
  PID.Kd=0.2;       //自己设定
  printf("PID_init end \n");
 }

float PID_realize()//PID算法实现
{
  PID.SetAngle=473;           //设定值
  PID.err=PID.SetAngle-PID.ActualAngle; //设定值-实际值
  PID.integral+=PID.err;          //积分值，偏差累加
  PID.voltage_change=PID.Kp*PID.err+PID.Ki*PID.integral+PID.Kd*(PID.err-PID.err_last);
  PID.err_last=PID.err;         //上一个偏差值
  PID.voltage_change=PID.voltage_change*1.0;    //算出实际值
  return PID.voltage_change;         //返回
}
void motor_correct()
{
    percentage=6553;
  pwmWriteHR(left_hand_pin, percentage);
  pwmWriteHR(right_hand_pin, percentage);
  delay(3000);
  percentage=3276;
  pwmWriteHR(left_hand_pin, percentage);
  pwmWriteHR(right_hand_pin, percentage);
  delay(3000);
  percentage =4000;
  pwmWrite(left_hand_pin, percentage);
  pwmWrite(right_hand_pin, percentage);
 }
void setup() {
  // put your setup code here, to run once:
  InitTimersSafe();
  Serial.begin(9600); 
  //sets the frequency for the specified pin
  bool success1= SetPinFrequencySafe(left_hand_pin, frequency);
  bool success2= SetPinFrequencySafe(right_hand_pin, frequency);
  if(success1||success2) {
    pinMode(left_hand_pin, OUTPUT);
    pinMode(right_hand_pin, OUTPUT);   
  }
  PID_init();
  motor_correct();
}

void loop() 
{
  // put your main code here, to run repeatedly:
    PID.ActualAngle= analogRead(angle_pin);
    left_percentage=300000000;
    right_percentage=300000000;
    pwmWrite(left_hand_pin, left_percentage);
    pwmWrite(right_hand_pin, right_percentage);
    delay(1000);
    PID_realize();
    left_percentage=left_percentage+PID.voltage_change;
    right_percentage=right_percentage-PID.voltage_change;
    pwmWrite(left_hand_pin, left_percentage);
    pwmWrite(right_hand_pin, right_percentage);

}
