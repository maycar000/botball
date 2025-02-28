
int k = 12; //Scale factor for distance to degrees
int rm = 0; //right motor
int lm = 3; //left motor


//------------------------------Forward & Backward------------------------------------------
//f is defined (forward)
void f(int distance {
  forward(distance);
}

//forward is defined
void forward(int distance) {
        v(1000, 1000, rm, distance);
}

//b is defined (backward)
void b(int distance) {
        backward(distance);
}

//backward is defined
void backward(int distance) {
        v(-1000, -1000, rm, distance); //velocity -1000 for both motors, tracking motor 0, distance
}

//------------------------------Left & Right Turns------------------------------
//l is defined (left turn)
void l(int degree) {
        turnL(degree);
}


//turnL is defined (left turn)
void turnL(int degree) {
        v(1000, -1000, rm, degree * k); //right motor 1000 velocity, left motor -1000 velocity, track motor 0, degrees*12 (scale factor)
}

//r is defined (right turn)
void r(); {
turnR(degree);
}

//turnR is defined (right turn)
void turnR(int degree) {//12 might need to be changed
v(-1000, 1000, lm, degree * k); //Right motor -1000 speed, left motor 1000 speed, degrees (0-360) *12 (12 is scale factor for distance to degrees)


//------------------------------------Extra------------------------------------
//v is defined (velocity)
void v(int right, int left, int driver, int distance){//(Right motor speed (-1000 to 1000), Left motor (speed -1000 to 1000), wheel to track(0,3), distance 
     driver = clamp(driver, rm, lm);
    right = clamp(right, -1000, 1000);
    left = clamp(left, -1000, 1000);

cmpc(driver); //clear position counter of driver (0 or 3)
int majority = (distance * 4) / 5; //distance = 20%
while (abs(gmpc(driver)) < majority) { //While absolute value of driver(0 or 3) motor position is less than 20% of original distance
mav(rm,right); //motor 0 goes at mean average velocity of variable "right" (speed -1000 to 1000) 
mav(lm,left); //motor 3 goes at mean average velocity of variable "left" (speed -1000 to 1000)
}


while (abs(gmpc(driver)) < distance) { //While absolute value of driver(0 or 3) motor position is less than distance
        mav(0, right/2); //mean average velocity of 0 is variable "right" (speed -1000 to 1000)
        mav(3, left/2); //mean average velocity of 0 is variable "left" (speed -1000 to 1000)
    }
    mav(lm, -left); //mean average velocity is opposite of left (speed -1000 to 1000)
    ao(); //All off
}


//Clamp is defined
int clamp(int var, int min, int max) {
    if (var > max) {
        return max;
    }
    
    if (var < min) {
        return min;
    }
    return var;
}
//------------------------------ Pause --------------------------------------------
void p(int time) {
    pause(time);
}

void pause(int time) {
    motor(rm,0);
    motor(lm,0);
    msleep(time);
}

//------------------------------ Camera -------------------------------------------
    
