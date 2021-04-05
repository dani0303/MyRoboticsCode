#include <kipr/wombat.h>
int r_sensor = 4;
int l_sensor = 5;
int black = 3500;
int black2 = 3000;
int black3 = 3700;

int main()
{
    linefollower(2, black, black2);
    lineFollower(7, black, black2);
    dostuff();
    lineFollowerFINAL(5);
    //lineFollowerFINAL(5);
    //linefollower(1);
    //mav(0, 1500);
    //mav(1, 1500);
    //msleep(6500);
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

void linefollower(int time){
    int counter = 0;
    while(counter <= time){
        if(analog(r_sensor) >= black2){
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(l_sensor) >= black2){
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }
        else{
            drive(1000, 10 * (time*10));
        }
        counter++;
        //black + 10;
    }
}

void lineFollowerFINAL(int time){
    int counter = 1;
    while(counter <= 100 * time){
        if(analog(r_sensor) >= 3000){
            if(analog(l_sensor) != 3000){
                drive(1500, (counter*100));
            }
        }
        if(analog(r_sensor) <= 3000){
            if(analog(l_sensor) <= 3000){
                turn_left(5);
                ao();
                msleep(10);
                drive(1500, 100);
                ao();
                msleep(10);
                turn_right(5);
                ao();
                msleep(10);
            }
        }
        counter++;
    }
}


void dostuff(){
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
