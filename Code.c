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

void lowerArm(){
    enable_servos();
    set_servo_position(0, 1909);
    msleep(1000);
    ao();
    disable_servos();
}

void liftArm(){
    enable_servos();
    set_servo_position(0, 0);
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
    msleep(1000);
}

void pvc_pullout(){
    turn_right(150);
    stop();
    msleep(1000);
    
    drive(1500, 1250);
    stop();
    
    turn_right(500);
    stop();
    
    drive(1500, 500);
    stop();
    
    turn_right(500);
    stop();
    
    drive(1500, 700);
    stop();
    
    turn_left(300);
    stop();
    
}

void close_claw(){
    enable_servos();
    set_servo_position(1, 1720);
    msleep(100);
    disable_servos();
}

void lineFollower(float time){
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(r_sensor) >= 3839){
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(l_sensor) >= 3839){
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
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
    lowerArm();//lowers arm to get PVC
    stop();//turns off robot for 1second
    pvc_pullout();
    close_claw();
    lineFollower(1);
    
    turn_right(350);
    stop();
    
    drive(-1500, 1000);
    stop();
    
    turn_right(1550);
    stop();
    
    drive(-1500, 450);
    stop();
    
    liftArm();
    
    turn_left(100);
    stop();
    
    drive(1500, 1500);
    stop();
    
    lineFollower(0.85);
    
    turn_left(600);
    stop();
    
    drive(1500, 1300);
    stop();
    
    turn_left(570);
    stop();
    
}
