#include <kipr/library.h>

void f(int distance);
void forward(int distance);
void b(int distance);
void backward(int distance);
void l(int degree);
void turnL(int degree);
void r();
void turnR(int degree);
void v(int right, int left, int driver, int distance);
void p(double time);
void pause(double time);
void lc(char* name, int logitech);
void load_cam(char* name, int logitech);
void ss(int port, int position, int speed);
void slow_servo(int port, int position, int speed);
void lineup(int port1, int port2);
