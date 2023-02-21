#include <Servo.h>
#include <math.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//#define BNO055_SAMPLERATE_DELAY_MS (250)
Adafruit_BNO055 bno = Adafruit_BNO055(); 

float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

Servo servo1, servo2, servo3;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bno.begin();
  delay(250);
  int8_t temp=bno.getTemp();
  bno.setExtCrystalUse(true);
  
  servo1.attach (3); 
  servo2.attach (5);
  
  
  servo1.write ( 90 ); // Init the servo1 angle to 90
  servo2.write ( 110 ); // Init the servo2 angle to 110
  

}

void loop() {
  
  imu::Quaternion q = bno.getQuat();
  
  ypr[0] = atan2(2.0*(q.y()*q.z() + q.w()*q.x()), q.w()*q.w() - q.x()*q.x() - q.y()*q.y() + q.z()*q.z());
  ypr[1] = asin(-2.0*(q.x()*q.z() - q.w()*q.y()));
  ypr[2] = atan2(2.0*(q.x()*q.y() + q.w()*q.z()), q.w()*q.w() + q.x()*q.x() - q.y()*q.y() - q.z()*q.z());
  
  
  Serial.print ( "N.0" );
  Serial.print (ypr [ 0 ]  *  -250 / M_PI);
  Serial.println (map (ypr [ 0 ]  *  -250 / M_PI,  1 ,  90 ,  90 ,  180 ));
  servo1.write (map (ypr [ 0 ]  *  -250 / M_PI,  1 ,  90 ,  90 ,  180 )); // Control servo1(2/20)

  Serial.print ( "N.1" );
  Serial.print (ypr [ 1 ]  *  -250 / M_PI);
  Serial.println (map (ypr [ 1 ]  *  -250 / M_PI,  1 ,  110 ,  110 ,  200 ));
  servo2.write (map (ypr [ 1 ]  *  -250 / M_PI,  1 ,  110 ,  110 ,  200 )); // Control servo2(2/20)
  
  /*
  Serial.print ( "N.2" );
  Serial.println (ypr [ 2 ]  *  180 / M_PI);
  Serial.println (map (ypr [ 2 ]  *  180 / M_PI,  - 90 ,  90 ,  0 ,  180 ));
  //servo3.write (map (ypr [ 2 ]  *  180 / M_PI,  - 90 ,  90 ,  0 ,  180 )); // Control servo3
  */
  /*
  servo1.detach();
  servo2.detach();
  */
  
  delay(250);
  
}
