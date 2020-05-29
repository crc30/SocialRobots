/*
 * Copyright 1996-2020 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description: .
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define MAX_SPEED 7.0  // [rad/s]
#define N_PARTS 45
#define MOTOR_LEFT N_PARTS - 2
#define MOTOR_RIGHT N_PARTS - 1

static WbDeviceTag robot_parts[N_PARTS];

//POSIZIONI BRACCIO
  double arm_target[7] = {0.37, -0.20, -0.50, 1.50, 0.50, 0.00, 0.00};
  double arm_90_up[7] = {1.20, 0.26, -3.16, 1.27, 1.70, 0.00, 1.41};
  double arm_90_down[7] = {1.20, -0.50, -3.16, 2.00, 1.70, -0.90, 1.41}; 
                              
  //POSIZIONI DITA
                                
  //POLLICE                              
  double thumb_closed[5] = {1.55, 0.79, 0.68, 0.00, 0.00}; 
  double thumb_open[5] = {-0.08, 0.00, 0.00, 0.00, 0.00}; 
  
  //INDICE
  double index_closed[7] = {0.50, 0.79, 0.30, 0.79, 0.40, 0.79, 0.79};
  double index_open[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};                        
  
  //MEDIO
  double middle_closed[7] = {-0.08, 0.79, 0.30, 0.79, 0.40, 0.79, 0.79};
  double middle_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  
  //ANULARE
  double ring_closed[7] = {-0.22, 0.79, 0.32, 0.79, 0.42, 0.79, 0.79};
  double ring_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};                              
  
  //MIGNOLO
  double little_closed[7] = {-0.52, 0.79, 0.79, 0.79, 0.37, 0.79,  0.62};
  double little_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

/*static void setTiagoPosition(char *my_names[], double *my_target_pos){ //SETTING POSIZIONE NON COMPOSIZIONALE
  for (int i = 0; i < N_PARTS; i++) {
    robot_parts[i] = wb_robot_get_device(my_names[i]);
    wb_motor_set_velocity(robot_parts[i], wb_motor_get_max_velocity(robot_parts[i]) / 2.0);
    wb_motor_set_position(robot_parts[i], my_target_pos[i]);
  }
}*/


static void setTiagoPositionCompos(char *my_names[], int time_step, double interval, double *arm, double *thumb, double *index, double *middle, double *ring, double *little){  //SETTING DELLA POSIZIONE COMPOSIZIONALE
  
  double my_target_pos[N_PARTS];
  
  for (int i = 0; i < 3; i++) {
    my_target_pos[i]=0.00;
  }
  for (int i = 3; i < 10; i++) {
    my_target_pos[i]=arm[i-3];
  }
  for (int i = 10; i < 15; i++) {
    my_target_pos[i]=thumb[i-10];
  }
  for (int i = 15; i < 22; i++) {
    my_target_pos[i]=index[i-15];
  }
  for (int i = 22; i < 29; i++) {
    my_target_pos[i]=middle[i-22];
  }
  for (int i = 29; i < 36; i++) {
    my_target_pos[i]=ring[i-29];
  }
  for (int i = 36; i < 43; i++) {
    my_target_pos[i]=little[i-36];
  }
  for (int i = 43; i < N_PARTS; i++) {
    my_target_pos[i]=0;
  }
  
  double start = wb_robot_get_time()+interval;
  
  while (wb_robot_step(time_step) != -1) {
    if(wb_robot_get_time()>=start){
      for (int i = 0; i < N_PARTS; i++) {
        robot_parts[i] = wb_robot_get_device(my_names[i]);
        wb_motor_set_velocity(robot_parts[i], wb_motor_get_max_velocity(robot_parts[i]) / 2.0);
        wb_motor_set_position(robot_parts[i], my_target_pos[i]);
      }
      break;
    }
  }
  
}

//GESTO TEST
static void beer(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_up, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 4.00, arm_90_down, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}
    



int main(int argc, char **argv) {
  // init webots stuff
  wb_robot_init();

  const int time_step = wb_robot_get_basic_time_step();  //TIME STEP DELLA SIMULAZIONE, 16msec*125=2 secondi
  

  // get devices
  // initialize the robot's information
  const char *names[N_PARTS] = {"head_2_joint",
                                "head_1_joint",
                                "torso_lift_joint",
                                
                                //MOTORI DEL BRACCIO 3-9               
                                "arm_1_joint",
                                "arm_2_joint",
                                "arm_3_joint",
                                "arm_4_joint",
                                "arm_5_joint",
                                "arm_6_joint",
                                "arm_7_joint",
                                
                                //POLLICE 10-14
                                "hand_right_thumb_abd_joint",
                                "hand_right_thumb_virtual_1_joint",
                                "hand_right_thumb_flex_1_joint",
                                "hand_right_thumb_virtual_2_joint",
                                "hand_right_thumb_flex_2_joint",
                                
                                //INDICE 15-21
                                "hand_right_index_abd_joint", //muove il dito a dx e sx
                                "hand_right_index_virtual_1_joint", //prima falange
                                "hand_right_index_flex_1_joint",
                                "hand_right_index_virtual_2_joint",
                                "hand_right_index_flex_2_joint",
                                "hand_right_index_virtual_3_joint",
                                "hand_right_index_flex_3_joint",
                                
                                //MEDIO 22-28
                                "hand_right_middle_abd_joint",
                                "hand_right_middle_virtual_1_joint",
                                "hand_right_middle_flex_1_joint",
                                "hand_right_middle_virtual_2_joint",
                                "hand_right_middle_flex_2_joint",
                                "hand_right_middle_virtual_3_joint",
                                "hand_right_middle_flex_3_joint",
                                
                                //ANULARE 29-35
                                "hand_right_ring_abd_joint",
                                "hand_right_ring_virtual_1_joint",
                                "hand_right_ring_flex_1_joint",
                                "hand_right_ring_virtual_2_joint",
                                "hand_right_ring_flex_2_joint",
                                "hand_right_ring_virtual_3_joint",
                                "hand_right_ring_flex_3_joint",
                                
                                //MIGNOLO 36-42
                                "hand_right_little_abd_joint",
                                "hand_right_little_virtual_1_joint",
                                "hand_right_little_flex_1_joint",
                                "hand_right_little_virtual_2_joint",
                                "hand_right_little_flex_2_joint",
                                "hand_right_little_virtual_3_joint",
                                "hand_right_little_flex_3_joint",
                                
                                //RUOTE
                                "wheel_left_joint",
                                "wheel_right_joint"};                         
           

  //POSIZIONE INIZIALE
  setTiagoPositionCompos(names, time_step, 0.00, arm_target, thumb_open, index_open, middle_open, ring_open, little_open);
  
  // print user instructions
  printf("You can drive this robot by selecting the 3D window and pressing the keyboard arrows.\n");
  
  // enable keyboard
  wb_keyboard_enable(time_step);

  const double initialTime = wb_robot_get_time();

  //SIMULAZIONE
  while (wb_robot_step(time_step) != -1) {  //ciclo della simulazione un ciclio ogni time_step seconda

      int key = wb_keyboard_get_key();
      if (key >= 0) {
        switch (key) {
          case WB_KEYBOARD_UP: 
              beer(names,time_step);
              beer(names,time_step);        
            break;
          case WB_KEYBOARD_DOWN:
            break;
          case WB_KEYBOARD_RIGHT:
            //speeds_left = MAX_SPEED;
            //speeds_right = -MAX_SPEED;
            break;
          case WB_KEYBOARD_LEFT:
            //speeds_left = -MAX_SPEED;
            //speeds_right = MAX_SPEED;
            break;
        }
      }

        /* Hello mouvement
        const double time = wb_robot_get_time() - initialTime;
        const double temp = 0.3 * sin(5.0 * time) - 0.3;
        wb_motor_set_position(robot_parts[8], temp);
        printf("%f\n",time);*/
  }
    
  wb_robot_cleanup();
  
  return 0;
}
