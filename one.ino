#include <Servo.h>
#include <RingBuffer.h>
#include <math.h>

#define UNAVAILABLE_FOR_READ  (byte)1
#define AVAILABLE_FOR_READ  (byte)0

const int mid_pixel;
const double pix_cm;
const double dist_canvas;
const double rad_to_deg = 180.0 / PI;
const float height_displace = 3.5;
short int current_working_point = 0;

int servoA, servoB, servoC, servoD;

RingBuffer<unsigned char, 40> points_queue;

void setup() {
  Serial.begin(9600);
  Serial.write(AVAILABLE_FOR_READ);
}

void loop() {
  if(points_queue.size() < 30){
    Serial.write(AVAILABLE_FOR_READ);
  }
  if(points_queue.size() > 0){
    //Thinking about sending all the points to be calculated, but we'll see.
    ///short unsigned int[] results = calculateTriangleAngles();
  }
}

//called when a Serial message is received
void serialEvent(){
  while(Serial.available()){
    unsigned char num = Serial.read();

    points_queue.push_back(num);
    
    if(points_queue.size() > 40){
      Serial.write(UNAVAILABLE_FOR_READ);
    }
  }
}

int calculateFloorAngle(int x, int y){
  float a = abs(x - mid_pixel) * pix_cm;
  float b = (y * pix_cm) + dist_canvas;
  float c = sqrt(pow(a, 2) + pow(b, 2));

  float floorAngle = cos(a/c) * rad_to_deg;

  if(x < mid_pixel)
    return round(floorAngle);
  return round(180 - floorAngle);
}

void calculateTriangleAngles(int x, int y){
  servoA = calculateFloorAngle(x, y);
//  int g = sqrt(pow(height_displace, 2) + pow(c, 2);
  
}

float getAngleCos(int a, int b, int c){
  float result = (pow(a, 2) + pow(b, 2) - pow(c, 2) / ( 2 * a * b));
  return acos(result) * rad_to_deg;
}
