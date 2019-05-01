#include <math.h>

const int mid_pixel;
const double pix_cm;
const double dist_canvas;
const double rad_to_deg = 180.0 / PI;
const float height_displace = 3.5;

int servoA, servoB, servoC, servoD;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){
    Serial.read();
    int[] results = calculateTriangleAngles();
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
  int g = sqrt(pow(height_displace, 2) + pow(c, 2);
  
}

float getAngleCos(int a, int b, int c){
  float result = (pow(a, 2) + pow(b, 2) - pow(c, 2) / ( 2 * a * b));
  return acos(result) * rad_to_deg;
}

int send(int[] data){
    for(int i : data){
      Serial.write(i);
    }
    return 0;
}
