#include <math.h>
using namspace std;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

class Control
{
  private:
  int pointA;
  int pointB;

  int grid_x = 100;
  int grid_y = 100;

  int start_x = 0;
  int start_y = 0;

  int STEPS_PER_MM = 7;

  void goTo(int A, int B);
}

void Control::goTo(A, B) 
{
  int a1 = sqrt(pow(Control.start_x, 2)+pow(Control.start_y, 2));
  int a2 = sqrt(pow(Control.grid_x-Control.start_x, 2)+pow(Control.start_y, 2));
  int b1 = sqrt(pow(A, 2)+pow(B, 2));
  int b2 = sqrt((Control.grid_x-A)*(Control.grid_x-A)+B*B);
  Serial.println("Vi kommer fra punkt");
  Serial.println(a1);
  Serial.println(a2);
  Serial.println("og vil gerne til punkt");
  Serial.println(b1);
  Serial.println(b2);
  
  int move_m1 = (b1-a1)*Control.STEPS_PER_MM;
  int move_m2 = (b2-a2)*Control.STEPS_PER_MM;
  Serial.println("For at gore dette, flytter vi");
  Serial.println(move_m1);
  Serial.println("paa motor 1, og ");
  Serial.println(move_m2);
  Serial.println("paa motor 2");

  Control.start_x = A;
  Control.start_y = B;
  
}

void loop() {
  
  Control.goTo(98, 43);
  delay(1000);
  Control.goTo(40, 27);
  delay(1000);
  Serial.println("ny");
  delay(10000);

}
