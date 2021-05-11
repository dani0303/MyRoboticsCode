#include <kipr/wombat.h>
//CONSTANTS TIME
int startPVC = 3000;
int quick_correct = 8;
int backSensor = 3;
int frontSensor = 5;
int Ramp_r_sensor = 1;
int Ramp_l_sensor = 2;

int black = 3500;
int black2 = 3000;
int black3 = 3700;
int brown = 2800;



int main()
{
    int t = 0;
    while(t == 0){
        if(analog(0) >= 4000){
            ao();
            msleep(100);
            start();
            drop_pvc();
            ramp_position_sequence();
            up_the_ramp();
            go_to_well();
            ao();
            shut_down_in(119000);
            break;
        }
    }
    printf("Hello World\n");
    return 0;
}

void lower_claw(){
   	mav(3, -543);
    msleep(900);
    ao();
    msleep(1000);
}

void lowerArm(){
    arm_change(0, 1709, 0, 20);
}

void liftArm(){
    arm_change(1709, 0, 0, 20);
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
void turn_right_back(int power, int time){
  mav(0,500);
  mav(1,-500);
  msleep(time);  
}

void turn_left(int power, int time){
    mav(0, -power);
    mav(1, power);
    msleep(time);
}

void turn_right(int power, int time){
    mav(0, power);
    mav(1, -power);
    msleep(time);
}

void stop(){
    mav(0, 0);
    mav(1, 0);
    mav(3, 0);
    msleep(1000);
}

void clawStop(){
    mav(3, 0);
    msleep(500);
}

void getPoms(){
    mav(3, -543);
    msleep(4200);
    
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
    msleep(3500);
    clawStop();
}

void turnPosition(){
    drive(1500, 350);
    stop();
    
    turn_left(1000, 300);
    stop();
    
    drive(1500, 550);
    stop();
    
    turn_left(1000, 200);
    stop();
    
    drive(1500, 300);
    stop();
    
    turn_left(1000, 250);
    stop();
}

void pvc_pullout(){
    distSensor(backSensor, 1000, 800, 190);
    turn_right(1000, 500);
    stop();
}

void open_claw(){
    enable_servos();
    set_servo_position(1, 0);
    msleep(100);
    disable_servos();
}

void close_claw(){
    enable_servos();
    set_servo_position(1, 1720);
    msleep(100);
    disable_servos();
}

void move_until_sensor(){
    int counter = 0;
    while(counter <= 100){
        if(analog(Ramp_l_sensor) >= 3000){
            if(analog(Ramp_r_sensor) >= 3000){
                counter = 100;
                printf("color");
                stop();
            }
        }
        else{
            drive(500, 500);
        }
        counter ++;
    }
}

void lineRampFollower(int time, int value, int value2){
    int counter = 0;
    while(counter <= time){
        if(analog(Ramp_r_sensor) >= value){//right side is on the line
            //turn right
            ao();
            msleep(10);
            turn_right(1000, 150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_l_sensor) >= value){//left side is on the line
            //turn left
            ao();
            msleep(10);
            turn_left(1000, 150);
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

void arm_change(int op, int wp, int servoport, int speed) {   
    //allows for the servo to change in any direction
	if(op > wp){
		while(op > wp){
			if(op - wp < speed){
				//just set the claw to the end position
				set_servo_position(servoport, wp);
				op = wp;
			}else{
				//increments the position
				op -= speed;  

				//sets the servo position to the incremented position
                enable_servos();
				set_servo_position(servoport, op);
				msleep(100);
                disable_servos();
			}
		}
	}else{
		while(wp > op){
			 //if the position is less than one increment away from the wanted position
			if(wp - op < speed){
				//just set the claw to the end position
                enable_servos();
				set_servo_position(servoport, op); 
                msleep(100);
                disable_servos();
				op = wp;
			}else{
				
				//increments the position
				op += speed;
				//sets the servo position to the incremented position
                enable_servos();
				set_servo_position(servoport, op);
				msleep(100);
                disable_servos();
			}
		}
	}
}


void bridge_line_follower(int time, int value){
    int counter = 0;
    while(counter <= time){//set while loop
        if(analog(Ramp_r_sensor) >= black3){//if right sensor is on the line
            printf("drive ");
            drive(1500, time*50);
        }else{
            turn_right(1000, 50);
            drive(1500, 1000);
        }
        printf("counter ");
        counter++;
    }
}


void distSensor(int port, int value1, int value2, int time){
    int counter = 0;
    while(counter <= 100){
        if(analog(port) >= value1){
            drive(500, time*10);
             if(analog(port) >= value2){
                 counter = 100;
            	 stop();
        	}
        }
        counter ++;
    }
}


void line_grd_follower(float time, int sensor1, int sensor2){//takes time and speed value to make it the robot detect the line
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(Ramp_r_sensor) >= sensor1){//3839
            ao();
            msleep(10);
            turn_right(500, 150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_l_sensor) >= sensor2){//3839
            ao();
            msleep(10);
            turn_left(500, 150);
            ao();
            msleep(10);
        }
        /*
        if(analog(Ramp_l_sensor) >= sensor2){
            if(analog(Ramp_r_sensor) >= sensor1){
                drive(1500, 500);
            }
        }
        */
        else{
            drive(500, 10 + (time*10));
        }
        counter++;
    }
}

void line_follower_distantSensor(float time, int sensor1, int sensor2, int distance){
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(Ramp_r_sensor) >= sensor1){//3839
            ao();
            msleep(10);
            turn_right(1000, 150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_l_sensor) >= sensor2){//3839
            ao();
            msleep(10);
            turn_left(1000, 150);
            ao();
            msleep(10);
        }
        if(analog(backSensor) <= distance){
            stop();
            break;
        }
        else{
            drive(500, 10 + (time*1000));
        }
        counter++;
    }
}

void pvc_position_sequence(){
    int counter = 0;
    while(counter <= 100){
        if(analog(backSensor) >= 600){
        	drive(-1500, counter*100);
    	}
        if(analog(backSensor) >= 500){
        	stop();
            break;
    	}
        counter ++;
    }
}

void start(){
    
    arm_change(0, 0, 0, 30);
    
    startPOS();//move from start to PVC
    stop();//turns motor off for 1seconds
    enable_servos();
    set_servo_position(0, 1700);
    msleep(100);
    disable_servos();
    
    stop();//turns off robot for 1second
    close_claw();
    stop();
    distSensor(backSensor, 1000, 600, 150);
    stop();
}

void drop_pvc(){
    turn_right(1000, 500);
    stop();
    drive(500, 4000);
    stop();
    turn_right(1000, 1500);
    stop();
    move_until_sensor();
    stop();
    turn_right(500, 2200);
    stop();
}
/*
still need to work on getting the robot to go up the ramp
but so far it's going pretty well just need to keep it going
also need to back up to make the robot clear the turn
*/

void ramp_position_sequence(){
    //arm_change(1730, 0, 1, 30);
    enable_servos();
    set_servo_position(1, 0);
    msleep(100);
    disable_servos();
    stop();
    distSensor(frontSensor, 1100, 1700, 200);
    stop();
    turn_left(500, 2000);
    stop();
    distSensor(frontSensor, 900, 1300, 450);
    stop();
    turn_left(500, 750);
    stop();
    drive(500, 500);
    stop();
    turn_left(500, 500);
    stop();
    drive(500, 1500);
    stop();
    turn_left(500, 1750);//original value 1000
    stop();
    
}

void up_the_ramp(){
    drive(500, 5000);
    line_grd_follower(1.0, 3700, 3500);
    stop();
    drive(500, 3500);
    stop();
    distSensor(frontSensor, 900, 1010, 350);
    stop();
    turn_left(500, 500);
    stop();
    drive(500, 4000);
    stop();
    turn_left(500, 1200);
    stop();
    drive(500, 1500);
    stop();
    turn_left(500, 1000);
    stop();
}

void go_to_well(){
    drive(500, 1500);
    stop();
    line_grd_follower(4.5, 3800, 3700);
    stop();
}
