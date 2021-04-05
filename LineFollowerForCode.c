#include <kipr/wombat.h>
int r_sensor = 4;
int l_sensor = 5;
int black = 3500;
int black2 = 3000;
int black3 = 3700;

int main()
{
    lineFollower(9, black, black2);
    turnPosition();
    bridge_line_follower(2, black);
    return 0;
}

void stop(){
    mav(0, 0);
    mav(1, 0);
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

void lineFollower(int time, int value, int value2){
    int counter = 0;
    while(counter <= time){
        if(analog(r_sensor) >= value){
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(l_sensor) >= value){
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }
        if(analog(r_sensor) == value2){
            mav(0, 0);
            mav(1, 0);
        }
        if(analog(l_sensor) == value2){
            mav(0, 0);
            mav(1, 0);
        }
        else{
            drive(1000, 10 * (time*10));
        }
        counter++;
        //black + 10;
    }
}
void turnPosition(){
    turn_left(200);
    stop();
    
    drive(1500, 500);
    stop();
    
    turn_left(200);
    stop();
    
    drive(1500, 450);
    stop();
    
    turn_left(500);
    stop();
}

void bridge_line_follower(int time, int value){
    int counter = 0;
    while(counter <= time){
        if(analog(r_sensor) >= black3){
            if(analog(l_sensor) >= black3){
                drive(1500, time*100);
            }
        }
        if(analog(r_sensor) <= black){
            if(analog(l_sensor) <= black){
                turn_right(50);
            }
        }
        counter++;
    }
}



