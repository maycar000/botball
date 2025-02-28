int clamp(int var, int min, int max) {
    if (var > max) {
        return max;
    }
    
    if (var < min) {
        return min;
    }
    return var;
}


void f(int distance {
  forward(distance);
}

void forward(int distance) {
        v(1000, 1000, 0, distance);
}

void r(); {
turnR(degree);
}

void turnR(int degree) {//12 might need to be changed
v(-1000, 1000, 3, degree * 12); //Right motor -1000 speed, left motor 1000 speed, degrees (0-360) *12 (12 is scale factor for distance to degrees)


void v(int right, int left, int driver, int distance){//(Right motor speed (-1000 to 1000), Left motor (speed -1000 to 1000), wheel to track(0,3), distance 
     driver = clamp(driver, 0, 3);
    right = clamp(right, -1000, 1000);
    left = clamp(left, -1000, 1000);

cmpc(driver); //clear position counter of driver (0 or 3)
int majority = (distance * 4) / 5; //distance = 20%
while (abs(gmpc(driver)) < majority) { //While absolute value of driver(0 or 3) motor position is less than 20% of original distance
mav(0,right); //motor 0 goes at mean average velocity of variable "right" (speed -1000 to 1000) 
mav(3,left); //motor 3 goes at mean average velocity of variable "left" (speed -1000 to 1000)
}


while (abs(gmpc(driver)) < distance) { //While absolute value of driver(0 or 3) motor position is less than distance
        mav(0, right/2); //mean average velocity of 0 is variable "right" (speed -1000 to 1000)
        mav(3, left/2); //mean average velocity of 0 is variable "left" (speed -1000 to 1000)
    }
    mav(3, -left); //mean average velocity is opposite of left (speed -1000 to 1000)
    ao(); //All off
}
