#include <kipr/wombat.h>
int r_sensor = 5;
int l_sensor = 4;
int main()
{
    mav(0, 1500);
    mav(1, 1500);
    msleep(1500);
    lineFollower(0.85);
    return 0;
}

void stop(){
    freeze(0);
    freeze(1);
    ao();
    msleep(1000);
}

void turn_left(int time){
    mav(0, -1500);
    mav(1, 1500);
    msleep(time);
}

void turn_right(int time){
    mav(0, 1000);
    mav(1, -1000);
    msleep(time);
}


void drive(int speed, int time){
    mav(0, speed);
    mav(1, speed);
    msleep(time);
}

void lineFollower(float time){
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(r_sensor) >= 3000){
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(l_sensor) >= 3000){
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }
        counter++;
        drive(1000, 1 + (time*10));
    }
}
