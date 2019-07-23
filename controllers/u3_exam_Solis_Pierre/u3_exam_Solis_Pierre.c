#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <math.h>
#include <stdio.h>

#define PI 3.1416
#define TIME_STEP 64
#define OBSTACLE_DISTANCE 20.0


  

int main(int argc, char **argv)
{
 int pressed_key;

 double ds_valueA = 0;
 double ds_valueB = 0;
 double Ang1 = 0;
 double Ang2 = 0;
 double Ang3 = 0;
 double Comparador = 0;
 int turn_left = 0;
 int turn_right = 0;
 int n = 0;
 int m = 0;

  void automatic (){

    ds_valueA = wb_distance_sensor_get_value (dist_sensors[0]);
    printf("Distance sensor1: %lf\n", ds_valueA);
    ds_valueB = wb_distance_sensor_get_value (dist_sensors[1]);
    printf("Distance sensor2: %lf\n", ds_valueB);

    Ang1 = wb_position_sensor_get_value(encoders[0]);
    Ang2 = wb_position_sensor_get_value(encoders[1]);
    Ang3 = wb_position_sensor_get_value(encoders[2]);

    wb_motor_set_velocity(wheels[0], -6.66);
    wb_motor_set_velocity(wheels[1], 6.66);
    wb_motor_set_velocity(wheels[2], 0);

    if(dist_sensors[0] < dist_sensors[1] && dist_sensors[0] < 200){

     wb_motor_set_velocity(wheels[0], 0);
     wb_motor_set_velocity(wheels[1], 6.66);
     wb_motor_set_velocity(wheels[2], -6.66);
   } else if(dist_sensors[1] > dist_sensors[1] && dist_sensors[1] < 200) {
   
     wb_motor_set_velocity(wheels[0], 0);
     wb_motor_set_velocity(wheels[1], -6.66);
     wb_motor_set_velocity(wheels[2], 6.66);
   }
   
  }

  void manual () {

    ds_valueA = wb_distance_sensor_get_value (dist_sensors[0]);
    printf("Distance sensor1: %lf\n", ds_valueA);
    ds_valueB = wb_distance_sensor_get_value (dist_sensors[1]);
    printf("Distance sensor2: %lf\n", ds_valueB);

    Ang1 = wb_position_sensor_get_value(encoders[0]);
    printf("encoder_1: %lf\n", Ang1);
    Ang2 = wb_position_sensor_get_value(encoders[1]);
    printf("encoder_2: %lf\n", Ang2);
    Ang3 = wb_position_sensor_get_value(encoders[2]);
    printf("encoder_3: %lf\n", Ang3);
    printf("Comparador: %lf\n",Comparador );

     if (pressed_key == WB_KEYBOARD_DOWN) {

       wb_motor_set_velocity (wheels[0], 6.36);
       wb_motor_set_velocity (wheels[1], -6.36);
       wb_motor_set_velocity (wheels[2], 0);
       
     } else if (pressed_key == WB_KEYBOARD_UP) {

       wb_motor_set_velocity (wheels[0], -6.36);
       wb_motor_set_velocity (wheels[1], 6.36);
       wb_motor_set_velocity (wheels[2], 0);
       
     } else if (pressed_key == WB_KEYBOARD_LEFT) {

       wb_motor_set_velocity (wheels[0], 0);
       wb_motor_set_velocity (wheels[1], -6.36);
       wb_motor_set_velocity (wheels[2], 6.36);
       
     } else if (pressed_key == WB_KEYBOARD_RIGHT) {

       wb_motor_set_velocity (wheels[0], 6.36);
       wb_motor_set_velocity (wheels[1], 0);
       wb_motor_set_velocity (wheels[2], -6.36);
       
     } else if(pressed_key == 'S' ) {
   
      Comparador = Ang1 + 0.785398;
      turn_left = 1;
      
     } else if(turn_left == 1) {

     if(Ang1 <= Comparador) {
     
       wb_motor_set_velocity(wheels[0], 6.36);
       wb_motor_set_velocity(wheels[1], 6.36);
       wb_motor_set_velocity(wheels[2], 6.36);
       
     } else {
   
       wb_motor_set_velocity(wheels[0], 0);
       wb_motor_set_velocity(wheels[1], 0);
       wb_motor_set_velocity(wheels[2], 0);
       turn_left = 0;
    }

    } else if(pressed_key == 'A' ) {
   
       Comparador = Ang1 - 0.785398;
       turn_right = 1;
       
    } else if(turn_right == 1) {

    if(Ang1 >= Comparador) {
     
        wb_motor_set_velocity(wheels[0], -6.36);
        wb_motor_set_velocity(wheels[1], -6.36);
        wb_motor_set_velocity(wheels[2], -6.36);
    } else {
   
        wb_motor_set_velocity(wheels[0], 0);
        wb_motor_set_velocity(wheels[1], 0);
        wb_motor_set_velocity(wheels[2], 0);
        turn_right = 0;
    }
    } else {
   
        wb_motor_set_velocity(wheels[0], 0);
        wb_motor_set_velocity(wheels[1], 0);
        wb_motor_set_velocity(wheels[2], 0);
     }
  }

  wb_motor_set_velocity(wheels[1], 0);
  wb_motor_set_velocity(wheels[0], 0);
  wb_motor_set_velocity(wheels[2], 0);


  
  wb_robot_init();
  
  wb_keyboard_enable(TIME_STEP);

 
   // Motor devices
  WbDeviceTag wheels [3];
  wheels[0] = wb_robot_get_device("wheel1");
  wheels[1] = wb_robot_get_device("wheel2");
  wheels[2] = wb_robot_get_device("wheel3");
  
  wb_motor_set_position (wheels[0], INFINITY);
  wb_motor_set_position (wheels[1], INFINITY);
  wb_motor_set_position (wheels[2], INFINITY);

   //Distance sensor devices
  WbDeviceTag dist_sensors[2];
  dist_sensors[0] = wb_robot_get_device("distance_sensor1");
  dist_sensors[1] = wb_robot_get_device("distance_sensor2");
  
  wb_distance_sensor_enable(dist_sensors[0], TIME_STEP);
  wb_distance_sensor_enable(dist_sensors[1], TIME_STEP);

   //encoder devices
  WbDeviceTag encoders [3];
  encoders[0] = wb_robot_get_device("encoder1");
  encoders[1] = wb_robot_get_device("encoder2");
  encoders[2] = wb_robot_get_device("encoder3");
  
  wb_position_sensor_enable(encoders[0], TIME_STEP);
  wb_position_sensor_enable(encoders[1], TIME_STEP);
  wb_position_sensor_enable(encoders[2], TIME_STEP);

  
  while (wb_robot_step(TIME_STEP) != -1) {

      pressed_key = wb_keyboard_get_key();

      if(pressed_key == 'W'){
      
        m = 1;
        n = 0;
        
     } else if (pressed_key == 'G'){
     
        n = 1;
        m = 0;
        
     }
    
      printf("m: %i   ",m);
      printf("n: %i\n",n);

    if(m == 1)
      manual();

    if(n == 1)
      automatic();
       
      wb_robot_cleanup();
    
    
   }
    
 
    return (0);
}
