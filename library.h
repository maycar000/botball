//------------------------------Variables------------------------------------------------
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
//p defined(pause)
void p(double time) {
	pause(time);
}

//pause defined
void pause(double time) {
	double sTime = seconds();
    while (seconds() - sTime < time) {
    	ao();
    }
}

//------------------------------ Camera -------------------------------------------
//load_cam turns on camera

//lc defined (load_cam)
void lc(char* name, int logitech) { //char* name?, int logitech?
load_cam(name, logitech);
}

//load_cam defined
void load_cam(char* name, int logitech) { 
    logitech = clamp(logitech, 0, 1);
	camera_load_config(name); 
    if (logitech) {
    	camera_open_black();
    } else {
    	camera_open();
    }
    
    for (int i = 0; i < 10; i++) { //
    	camera_update(); //Update cameras screen
        p(0.01);
    }
}



int rotate_till(int channel, int size, int resolution, int direction) {
    cmpc(0);
    direction = clamp(direction, -1, 1);
	while (1) {
        rectangle o = get_object_bbox(channel, 0);
        if (o.width * o.height > size) {
            int x = o.ulx + o.width/2;
            if (abs((x - resolution/2)) < resolution/10){
                return gmpc(0);
            }
        }
        
        double sTime = seconds();
        while (seconds() - sTime <= 0.2) {
        	mav(0, -500 * direction);
            mav(3, 500 * direction);
        }
        p(0.01);
        camera_update();
    }
}

//------------------------------ Servos ------------------------------ 

//ss defined (slow servo)
void ss(int port, int position, int speed) { //(servo port, ending position of servo, speed)
	slow_servo(port, position, speed);
}

//slow_servo defined (slow servo)
void slow_servo(int port, int position, int speed) { //(servo port, ending position, speed)
	if (get_servo_position(port)  == position) { //If servo position of "servo port" equals "position"
    	return; //Then end the code
    }
    
    int starting = get_servo_position(port); //"starting" position equals servo position of "port"
    int counter = 0;
    
    while((starting + counter)/speed != position/speed) { //While ("starting position" + "counter" (Which starts at 0 doesn't equal "position"(ex 200) /"speed" ex(50)->4)
    	if (position - starting > 0) { //if current position - starting position is more than 0
    		counter  += speed; // then counter equals counter + speed 
    	}
        if (position - starting < 0) { //if ending position - starting position is less than - then 
        	counter -= speed; //counter equals counter minus speed
        }
        
        set_servo_position(port, starting + counter); 
        msleep(10);
    }
    set_servo_position(port, position);
    msleep(100);
}

//------------------------------ Color Detection ------------------------------ 

//detect_color defined (detect color)
int detect_color(int size) {
	for (int i = 0; i < get_channel_count(); i++) { //(sets i to 0; final value of i is less than get_channel_count(); i+1)
    	for (int j = 0; j < get_object_count(i); j++) {
        	rectangle o = get_object_bbox(i, j);
            if (o.width * o.height > size) {
            	return i;
            }
        }
    }
}

//------------------------------ Lineup ------------------------------ 
void lineup(int port1, int port2) {
	while (digital(port1) == 0 || digital(port2) == 0) {
    	mav(0, -500);
        mav(3, -500);
    }
}
