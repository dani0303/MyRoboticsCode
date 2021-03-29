#include <kipr/wombat.h>
//CONSTANTS TIME
int startPVC = 2300;
int quick_correct = 8;
int r_sensor = 5;
int l_sensor = 4;


int main()
{
    start();
    printf("Hello World\n");
    return 0;
}


void armPVC(){
    enable_servos();
    set_servo_position(0, 1909);
    msleep(1000);
    ao();
    disable_servos();
}

void turn_left_back(int time){
    mav(0,-1500);
    mav(1, 1500);
    msleep(time);
}

void startPOS(){
    mav(0, -700);
    mav(1, -750);
    msleep(startPVC);
}

void drive(int speed, int time){
    mav(0, speed);
    mav(1, speed);
    msleep(time);
}
void turn_right_back(int time){
  mav(0,500);
  mav(1,-500);
  msleep(time);  
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

void stop(){
    freeze(0);
    freeze(1);
    ao();
}

void pvc_pullout(){
    turn_right(150);
    stop();
    msleep(1000);
    
    drive(1500, 800);
    stop();
    msleep(1000);
    
    turn_right(500);
    stop();
    msleep(1000);
    
    drive(1500, 500);
    stop();
    msleep(1000);
    
    turn_right(500);
    stop();
    msleep(1000);
    
    drive(1500, 500);
    stop();
    msleep(1000);
    
    turn_left(200);
    stop();
    msleep(1000);
}

void lineFollower(int time){
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(r_sensor) >= 3839){
            turn_right(100);
            drive(500, 15);
        }
        if(analog(l_sensor) >= 3839){
            turn_left(100);
            drive(500, 15);
        }
        else{
            drive(1000, 10 + (time*10));
        }
        counter++;
    }
}


void start(){
    
    enable_servos();
    set_servo_position(1, 0);
    msleep(1000);
    disable_servos();
    
    startPOS();//move from start to PVC
    stop();//turns motor off for 1seconds
    msleep(1000);
    armPVC();//lowers arm to get PVC
    stop();//turns off robot for 1second
    msleep(1000);
    pvc_pullout();
    lineFollower(1);
}


