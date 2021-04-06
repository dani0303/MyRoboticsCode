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
    stop();
    get_poms();
    return 0;
}

void get_poms(){//process to get the pom poms from the mine
    
    enable_servos();
    set_servo_position(1, 0);
    msleep(1000);
    disable_servos();
    
    mav(3, -100);
    msleep(4500);
    stop();
    
    enable_servos();
    set_servo_position(1, 1850);
    msleep(1000);
    disable_servos();
    
    mav(3, 100);
    msleep(4500);
    stop();
    
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

void special_drive(int time){
    mav(0, 1000);
    mav(1, 1500);
    msleep(time);
}

void lineFollower(int time, int value, int value2){
    int counter = 0;
    while(counter <= time){
        if(analog(r_sensor) >= value){//right side is on the line
            //turn right
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(l_sensor) >= value){//left side is on the line
            //turn left
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }
        if(analog(r_sensor) == value2){//if right reads a certain value 
            //stop
            mav(0, 0);
            mav(1, 0);
        }
        if(analog(l_sensor) == value2){//if left reads a certain value
            //stop
            mav(0, 0);
            mav(1, 0);
        }
        else{//neither scenario meets
            //drive forward
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
    while(counter <= time){//set while loop
        if(analog(r_sensor) >= black3){//if right side is on the line
            if(analog(l_sensor) >= black3){//if left side is on the brown side
                //drive(1500, time*100);//drive forward
                special_drive(time*100);//drive sliently to the left keep correcting itself
            }
        }
        if(analog(r_sensor) <= black){//if right sensor is off the line
            if(analog(l_sensor) <= black){//if left sensor still off the line
                turn_right(50);//turn right
            }
        }
        counter++;
    }
}



