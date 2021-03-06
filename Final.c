#include <kipr/wombat.h>
//CONSTANTS TIME
int startPVC = 2300;
int quick_correct = 8;
int r_sensor = 4;
int l_sensor = 5;

int Ramp_r_sensor = 4;
int Ramp_l_sensor = 5;
int black = 3500;
int black2 = 3000;
int black3 = 3700;
int brown = 2800;



int main()
{
    int t = 0;
    while(t == 0){
        if(analog(0) <= 3800){
            start();
			lineRampFollower(7, black, black2);
            turnPosition();
            drive(1500, 700);
            stop();
            bridge_line_follower(2, black3);
            stop();
            turn_left(180);
            stop();
            lower_claw();
            stop();
            drive(500, 1750);
            stop();
            getPoms();
            stop();
            drive(-500, 2500);
            stop();
            shut_down_in(119000);
            break;
        }
    }
    printf("Hello World\n");
    return 0;
}

void clawStop(){
    mav(3, 0);
    msleep(500);
}

void getPoms(){
    mav(3, -543);
    msleep(4500);
    
    enable_servos();
    set_servo_position(1, 500);
    msleep(100);
    disable_servos();
    
    ao();
    msleep(500);
    
    mav(3, -543);
    msleep(250);
    clawStop();
    
    enable_servos();
    set_servo_position(1, 1900);
    msleep(100);
    disable_servos();
    
    ao();
    msleep(1000);
    
    mav(3, 543);
    msleep(4500);
    clawStop();
}

void lineRampFollower(int time, int value, int value2){
    int counter = 0;
    while(counter <= time){
        if(analog(Ramp_r_sensor) >= value){//right side is on the line
            //turn right
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_l_sensor) >= value){//left side is on the line
            //turn left
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_r_sensor) == value2){//if right reads a certain value 
            //stop
            mav(0, 0);
            mav(1, 0);
        }
        if(analog(Ramp_l_sensor) == value2){//if left reads a certain value
            //stop
            mav(0, 0);
            mav(1, 0);
        }
        else{//neither scenario meets
            //drive forward
            drive(1000, 10 * (time*11));
        }
        counter++;
        //black + 10;
    }
}

void turnPosition(){
    drive(1500, 350);
    stop();
    
    turn_left(200);
    stop();
    
    drive(1500, 500);
    stop();
    
    turn_left(200);
    stop();
    
    drive(1500, 450);
    stop();
    
    turn_left(400);
    stop();
}

void bridge_line_follower(int time, int value){
    int counter = 0;
    while(counter <= time){//set while loop
        if(analog(Ramp_r_sensor) >= black3){//if right sensor is on the line
            printf("drive ");
            drive(1500, time*50);
        }else{
            turn_right(50);
            drive(1500, 1000);
        }
        printf("counter ");
        counter++;
    }
}

void lower_claw(){
   	mav(3, -543);
    msleep(900);
    ao();
    msleep(1000);
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
    mav(0, -750);
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
    mav(0, 0);
    mav(1, 0);
    msleep(1000);
}

void pvc_pullout(){
    turn_right(350);
    stop();
    
    drive(1500, 1250);
    stop();
    
    turn_right(500);
    stop();
    
    drive(1500, 500);
    stop();
    
    turn_right(700);
    stop();
    
    drive(1500, 1050);
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
    
    drive(-1500, 1000);
    stop();
    
    liftArm();
    
    turn_left(100);
    stop();
    
    drive(1500, 1000);
    stop();
    
    turn_right(100);
    stop();
    
    drive(1500, 1250);
    stop();
    
    lineFollower(0.85);
    
    turn_left(800);
    stop();
    
    ao();
    msleep(1000);
    
    enable_servos();
    set_servo_position(1, 0);
    msleep(100);
    
    set_servo_position(0, 500);
    msleep(100);
    disable_servos();
    
    ao();
    msleep(1000);
    
    drive(1500, 1600);
    stop();
    
    turn_left(750);//750
    stop();
    
    drive(500, 1500);
    stop();
    msleep(1000);
    
}
