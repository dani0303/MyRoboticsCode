#include <kipr/wombat.h>

int main()
{
    
    void lineFollower(float time){
    int counter = 0;
    printf("1");
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
        drive(1000, 100 + (time*10));
        counter++;
        printf(counter);
    }
}
}




void lineFollower(float time){
    int counter = 0;
    printf("1 ");
    while(counter <= 100 * time){
        if(analog(r_sensor) >= 3100){
            printf("2 ");
            ao();
            msleep(10);
            printf("3 ");
            turn_right(75);
            printf("4 ");
            ao();
            msleep(10);
            printf("5 ");
        }
        if(analog(l_sensor) >= 3100){
            printf("6 ");
            ao();
            msleep(10);
            printf("7 ");
            turn_left(75);
            printf("8 ");
            ao();
            printf("9 ");
            msleep(10);
        }
        if(analog(l_sensor) >= 3100 && analog(r_sensor) >= 3100){
            
        	break;
        }
        
        printf("10 ");
        drive(1000, 0);
        //drive(1000, 100 + (counter*100));
        printf("11 ");
        counter;
        printf("12 ");
        printf(counter);
    }
}
