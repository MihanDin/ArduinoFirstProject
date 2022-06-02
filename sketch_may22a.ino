#include <I2Cdev.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>              
#include <iarduino_Bluetooth_HC05.h>      
MPU6050 mpu;
using namespace std;                                   
SoftwareSerial mySerial(2,3);  
iarduino_Bluetooth_HC05 hc05(4);   
 
int si=0;
  int time=0;
  int end =0;
  double myJumps[100];
  int counter=0;
  double lst;
  int firstSpeed=0;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 OK" : "MPU6050 FAIL");
pinMode(2,INPUT);   
pinMode(3,OUTPUT);  
          mySerial.begin(9600);
  delay(1000);
  
}void loop() {

   int p=0;
  if(mySerial.available()){
     p=mySerial.read();  
       Serial.write(p);     
       Serial.println();                                                           
  }
  if(p==50){
  firstSpeed=1;
  
}else if(p==49){
  if(counter>0){
   
     for(int i =0;i<counter;i++){
      Serial.println(myJumps[i]);
      int str= floor(myJumps[i])*100/100;
      myJumps[i]=0;
      mySerial.write(str+48);
    }
    counter=0;
     mySerial.write(107);
  }else{
    int str= 0;
      mySerial.write(str);
  }
   
    firstSpeed=0;
  }
  if(firstSpeed==1){
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  double value=az/2048.0+9.46;
  if(8<=value&&value<=lst&&end==0){
    end++;
Serial.println(value*1.79);
Serial.println("============");
   myJumps[counter]=value*1.79;
   counter++;
  }else{
    lst=value;
  }
  if(0<value&&value<1){
    end=0;
  }
  }
    delay(5);
}
