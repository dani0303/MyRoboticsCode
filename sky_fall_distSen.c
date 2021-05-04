#include <kipr/wombat.h>
//CONSTANTS TIME
int startPVC = 2500;
int quick_correct = 8;
int backSensor = 3;
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
        if(analog(0) <= 4000){
            ao();
            msleep(100);
            start();
            pvc_position_sequence();
            /*
			lineRampFollower(7, black, black2);
            turnPosition();
            drive(1500, 500);
            stop();
            bridge_line_follower(2, black3);
            stop();
            turn_left(180);
            stop();
            lower_claw();
            stop();
            drive(500, 2500);//2500
            stop();
            getPoms();
            stop();
            
            mav(3, 543);
            msleep(375);
            clawStop();
            
            drive(-500, 2500);
            stop();
            
            //enable_servos();
            //set_servo_position(1, 0);
            //msleep(100);
            //disable_servos();
            */
            ao();
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

void turnPosition(){
    drive(1500, 350);
    stop();
    
    turn_left(300);
    stop();
    
    drive(1500, 550);
    stop();
    
    turn_left(200);
    stop();
    
    drive(1500, 300);
    stop();
    
    turn_left(250);
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

void distSensor(int value1, int value2, int time){
    int counter = 0;
    while(counter <= 100){
        if(analog(backSensor) >= value1){
            drive(500, time*10);
             if(analog(backSensor) >= value2){
            	 stop();
                 counter = 100;
        	}
        }
        counter ++;
    }
}

void pvc_pullout(){
    distSensor(1000, 800, 190);
    turn_right(500);
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

void line_grd_follower(float time, int sensor1, int sensor2){//takes time and speed value to make it the robot detect the line
    int counter = 0;
    while(counter <= 100 * time){
        if(analog(Ramp_r_sensor) >= sensor1){//3839
            ao();
            msleep(10);
            turn_right(150);
            ao();
            msleep(10);
        }
        if(analog(Ramp_l_sensor) >= sensor2){//3839
            ao();
            msleep(10);
            turn_left(150);
            ao();
            msleep(10);
        }else{
            drive(500, 10 + (time*10));
        }
        counter++;
    }
}

void start(){
    
    arm_change(0, 0, 0, 30);
    
    startPOS();//move from start to PVC
    stop();//turns motor off for 1seconds
    lowerArm();//lowers arm to get PVC
    stop();//turns off robot for 1second
    close_claw();
    stop();
    pvc_pullout();
    drive(900, 2200);
    stop();
    turn_right(1200);
    stop();
    
    distSensor(2500, 890, 550);
    printf("Hello");
    stop();
    
    turn_left(500);
    stop();
    msleep(1000);
    
    line_grd_follower(1.5, 3800, 3700);
    stop();
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
