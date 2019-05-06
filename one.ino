#include <Servo.h>
#include <RingBuffer.h>
#include <math.h>

#define UNAVAILABLE_FOR_READ  (byte)1
#define AVAILABLE_FOR_READ  (byte)0
#define PAPER_WIDTH 15 //cm
#define CANVAS_DIST 3 //cm
#define CANVAS_WIDTH 300 //px
#define ARM_ONE 9.5 //cm
#define ARM_TWO 11.5 //cm
#define HEIGHT_DISPLACE 3.125

const int mid_pixel = CANVAS_WIDTH / 2;
const double pix_cm = PAPER_WIDTH / CANVAS_WIDTH;
const double dist_canvas = CANVAS_DIST;
const double rad_to_deg = 180.0 / 3.14;


int floorAngle;
double a,b,c,g,aTone,aTtwo,aTthree,aTfour;

short int current_working_point = 0;

int servoA, servoB, servoC, servoD;

RingBuffer<unsigned char, 40> points_queue;

SoftwareSerial arduinoTwo(12, 13)

void setup() {
  Serial.begin(9600);
  Serial.write(AVAILABLE_FOR_READ);
  arduinoTwo.begin(9600);
  ard
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
  a = abs(x - mid_pixel) * pix_cm;
  b = (y * pix_cm) + dist_canvas;
  c = sqrt(pow(a, 2) + pow(b, 2));

  float temp = cos(a/c) * rad_to_deg;
  floorAngle = round(temp);

  if(x < mid_pixel)
    floorAngle = round(floorAngle);
   else
    floorAngle = round(180 - floorAngle);
  return floorAngle;
}

void calculateTriangleAngles(int x, int y){
  servoA = calculateFloorAngle(x, y);
  g = sqrt(pow(HEIGHT_DISPLACE, 2) + pow(c, 2));
  aTone = atan(HEIGHT_DISPLACE / c) * rad_to_deg;
  aTtwo = getAngleCos(g, ARM_TWO, ARM_ONE);
  servoD = 90 - round(aTone + aTtwo);
  aTthree = atan(c / HEIGHT_DISPLACE) * rad_to_deg;
  aTfour = getAngleCos(g, ARM_ONE, ARM_TWO);
  servoB = 180 - round(aTthree + aTfour);
  servoC = 180 - round(aTfour + aTtwo);
}

float getAngleCos(double a, double b, double c){
  float result = (pow(a, 2) + pow(b, 2) - pow(c, 2) / ( 2 * a * b));
  return acos(result) * rad_to_deg;
}
