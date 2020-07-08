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
 * Description: A project that brings Italian sign language to tiago relative to a restaurant menu.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>
 #include <string.h>
//#include </Users/crist/OneDrive/Desktop/jsmn-master/jsmn.h>
#include <\Users\crist\OneDrive\Desktop\jsmn-master\jsmn.h>

#define MAX_SPEED 7.0  // [rad/s]
#define N_PARTS 45
#define MOTOR_LEFT N_PARTS - 2
#define MOTOR_RIGHT N_PARTS - 1



static WbDeviceTag robot_parts[N_PARTS];

  //POSIZIONI BRACCIO
  double arm_target[4] = {0.37, -0.20, -0.50, 1.50};
  double arm_90_up[4] = {1.20, 0.26, -3.16, 1.27};
  double arm_90_down[4] = {1.20, -0.50, -3.16, 2.00};
  double arm_90_down2[4] = {1.40, -0.50, -3.16, 1.80};
  double arm_90_down3[4] = {1.20, -0.50, -3.16, 1.60};
  double arm_90_down4[4] = {1.00, -0.50, -3.16, 1.80};

  double arm_90_mouth[4] = {1.20, -0.80, -2.76, 2.29};
  double arm_90_mouth2[4] = {1.10, -0.90, -2.76, 2.29};
  double arm_90_mouth3[4] = {1.20, -1.00, -2.76, 2.29};
  double arm_90_mouth4[4] = {1.30, -0.90, -2.76, 2.29};
  double arm_90_mouth5[4] = {1.20, -0.80, -2.76, 1.60};

  double arm_90_45[4] = {0.10, 0.50, -2.16, 2.10};
  double arm_90_45_2[4] = {0.10, 0.50, -2.16, 2.25};
  double arm_90_45_3[4] = {0.30, 0.30, -1.90, 2.25};
  double arm_90_45_31[4] = {0.40, 0.30, -1.90, 2.25};
  double arm_90_45_32[4] = {0.50, 0.30, -1.90, 2.25};
  double arm_90_45_33[4] = {0.60, 0.30, -1.90, 2.25};

  //double arm_90_45_r[4] = {0.30, 0.50, -2.16, 1.90}; unused
  //double arm_90_45_r1[4] = {0.10, 0.50, -2.16, 1.80}; unused
  //double arm_90_45_r2[4] = {0.10, 0.50, -2.16, 1.90}; unused
  
  double arm_90_45_r3[4] = {0.07, 0.20, -1.90, 2.25}; //CC
  double arm_90_45_r4[4] = {0.07, 0.00, -1.90, 2.25}; //CC
  
  double arm_90_45_down[4] = {0.50, -0.50, -2.16, 2.10}; //NEW FEDE
  double arm_90_45_down2[4] = {0.10, -0.50, -2.16, 2.10}; //NEW FEDE

  double arm_face[4] = {0.07, -0.50, -2.90, 2.29};
  double arm_face2[4] = {0.30, -0.40, -2.90, 2.29};
  
  double arm_start_com_1[4] = {0.07, 1.02, 0.00, -0.32};

  //POSIZIONI PALMO
  double palm_front[3] = {-1.70, 0.00, 0.00};
  double palm_rear[3] = {-2.00, 0.00, -1.00};
  double palm_sx[3] = {1.70, 0.00, 1.41};
  double palm_sx2[3] = {-2.00, 0.00, 1.41};
  double palm_sx3[3] = {-2.07, 0.00, -2.07};
  double palm_dx[3] = {1.70, 0.00, -1.21};
  double palm_up[3] = {0.50, -1.39, 0.00};//TO TESTARE QUANDO SERVE
  double palm_up2[3] = {0.50, 1.39, -2.00};//TO TESTARE QUANDO SERVE
  double palm_up3[3] = {-1.80, -1.00, 0.00};
  double palm_up3_1[3] = {-1.30, -1.00, 0.00};
  //double palm_down[3] = {1.50, 1.39, 2.00};//TO TEST unused
  double palm_45[3] = {-1.80, 0.40, 0.70};
  double palm_45_2[3] = {-1.80, 0.40, 0.00};
  double palm_45_3[3] = {-2.07, 0.60, 0.00};
  double palm_45_4[3] = {-1.80, 0.80, 0.70}; //CC
  double palm_down2[3] = {1.32, -1.39, 1.77}; //CC
  //double palm_down3[3] = {1.32, -1.39, -1.77}; //CC unused
  

  //POSIZIONI DITA

  //POLLICE
  double thumb_closed[5] = {1.55, 0.79, 0.68, 0.00, 0.00};
  double thumb_open[5] = {0.00, 0.00, 0.00, 0.00, 0.00};
  double thumb_semi_closed[5] = {0.00, 0.00, 0.79, 0.00, 0.79};
  double thumb_centred[5] = {1.55,  0.40, 0.68,  0.00,  0.00};
  double thumb_semi_closed_centred[5] = {1.55,  0.79, 0.79,  0.00,  0.00}; //CC

  //INDICE
  double index_closed[7] = {0.50, 0.79, 0.30, 0.79, 0.40, 0.79, 0.79};
  double index_open[7] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  double index_semi_closed[7] = {0.00, 0.00, 0.79, 0.00, 0.79, 0.00, 0.79};
  double index_centred[7] = {0.52, 0.79, 0.00,  0.79, 0.00, 0.20, 0.00};
  double index_open_s[7] = {0.52, 0.00, 0.00,  0.00, 0.00, 0.00, 0.00};
  //double index_semi_closed_centred[7] = {0.40, 0.00, 0.79,  0.00, 0.00, 0.00, 0.00}; //CC unused

  //MEDIO
  double middle_closed[7] = {-0.08, 0.79, 0.30, 0.79, 0.40, 0.79, 0.79};
  double middle_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  double middle_semi_closed[7] = {-0.08, 0.00, 0.79, 0.00, 0.79, 0.00, 0.79};
  double middle_centred[7] = {-0.22, 0.79, 0.00,  0.79, 0.00, 0.20, 0.00};
  double middle_open_s[7] = {0.00, 0.00, 0.00,  0.00, 0.00, 0.00, 0.00};
  //double middle_semi_closed_centred[7] = {-0.08, 0.00, 0.79,  0.00,  0.00, 0.00, 0.00}; //CC unused

  //ANULARE
  double ring_closed[7] = {-0.22, 0.79, 0.32, 0.79, 0.42, 0.79, 0.79};
  double ring_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  double ring_semi_closed[7] = {-0.08, 0.00, 0.79, 0.00, 0.79, 0.00, 0.79};
  double ring_centred[7] = {-0.32, 0.79, 0.00, 0.79, 0.00, 0.20, 0.00};
  double ring_open_s[7] = {-0.20, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  //double ring_semi_closed_centred[7] = {-0.22, 0.00, 0.79, 0.00, 0.00, 0.00, 0.00}; //CC unused

  //MIGNOLO
  double little_closed[7] = {-0.52, 0.79, 0.79, 0.79, 0.37, 0.79,  0.62};
  double little_open[7] = {-0.08, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
  double little_semi_closed[7] = {-0.08, 0.00, 0.79, 0.00, 0.79, 0.00, 0.79};
  double little_centred[7] = {-0.49, 0.79, 0.00,  0.79, 0.00, 0.20, 0.00};
  double little_open_s[7] = {-0.52, 0.00, 0.00,  0.00, 0.00, 0.00, 0.00};
  //double little_semi_closed_centred[7] = {-0.52, 0.00,  0.79, 0.00, 0.00, 0.00,  0.00}; //CC unused

static void setTiagoPositionCompos(char *my_names[], int time_step, double interval, double *arm, double *palm, double *thumb, double *index, double *middle, double *ring, double *little){  //SETTING DELLA POSIZIONE COMPOSIZIONALE

  double my_target_pos[N_PARTS];
 
  for (int i = 0; i < 3; i++) {
    my_target_pos[i]=0.00;
  }
  for (int i = 3; i < 7; i++) {
    my_target_pos[i]=arm[i-3];
  }
  for (int i = 7; i < 10; i++) {
    my_target_pos[i]=palm[i-7];
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

static void rotate(int time_step, int part, double duration, double coeff){

    const double init = wb_robot_get_time();
    double start = wb_robot_get_time()+2.00;
    double stop = start+duration;

    while (wb_robot_step(time_step) != -1) {

      if(wb_robot_get_time(time_step)>=start){
        const double time = wb_robot_get_time() - init;
        const double temp = (0.3 * sin(5.0 * time) - 0.3)+coeff;
        wb_motor_set_position(robot_parts[part], temp);

        if(wb_robot_get_time(time_step)>=stop){
            break;
        }
      }
    }

}

static void rotate_and_move(int time_step, int part, int partm, double move_value, int dir, double duration, double coeff){

    const double init = wb_robot_get_time();
    double start = wb_robot_get_time()+2.00;
    double stop = start+duration;
    double c = (-0.003)*dir;
    double mv_value = move_value+c;

    while (wb_robot_step(time_step) != -1) {

      if(wb_robot_get_time(time_step)>=start){
        const double time = wb_robot_get_time() - init;
        const double temp = (0.3 * sin(5.0 * time) - 0.3)+coeff;
        wb_motor_set_position(robot_parts[part], temp);
        wb_motor_set_position(robot_parts[partm], mv_value);
        mv_value=mv_value+c;
        if(wb_robot_get_time(time_step)>=stop){
            break;
        }

      }
    }

}

//GESTO TEST

static void start_comunication(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_start_com_1, palm_dx, thumb_open, index_open, middle_open, ring_open, little_open);
    rotate(time_step, 4, 5.00, 1.00);
    setTiagoPositionCompos(names, time_step, 1.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}


static void beer(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_up, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 4.00, arm_90_down, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void water(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_45, palm_sx2, thumb_open, index_open, middle_open, ring_open, little_open);
    rotate(time_step, 9, 3.00, 0.00);
    setTiagoPositionCompos(names, time_step, 0.50, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void water_friz(char *names[], int time_step){
    water(names,time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 2.00, arm_90_down, palm_up, thumb_semi_closed, index_semi_closed, middle_semi_closed, ring_semi_closed, little_semi_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_down, palm_up, thumb_semi_closed, index_semi_closed, middle_semi_closed, ring_semi_closed, little_semi_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}


static void cocacola(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_down, palm_up, thumb_centred, index_centred, middle_centred, ring_centred, little_centred);
    rotate(time_step, 9, 3.00, 0.00);
    setTiagoPositionCompos(names, time_step, 0.50, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void coffee(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_45_2, palm_up2, thumb_centred, index_centred, middle_open, ring_open, little_open);
    rotate(time_step, 9, 3.00, 0.60);
    setTiagoPositionCompos(names, time_step, 0.50, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void fruit(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_45, palm_sx3, thumb_centred, index_centred, middle_open, ring_open, little_open);
    rotate(time_step, 7, 5.00, 0.60);
    setTiagoPositionCompos(names, time_step, 0.50, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void ice_cream(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_mouth, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 3.00, arm_90_mouth2, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth3, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth4, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth2, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth3, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth4, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_mouth, palm_sx, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void pasta(char *names[], int time_step){
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_45_3, palm_sx3, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    rotate_and_move(time_step, 9, 3, 0.30, 1, 1.00, 0.60);
    setTiagoPositionCompos(names, time_step, 2.50, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void tomato(char *names[], int time_step){
    pasta(names, time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 3.00, arm_90_down2, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down3, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down4, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down2, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down3, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down4, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.30, arm_90_down, palm_up, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void carbonara(char *names[], int time_step){
    pasta(names, time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_45_3, palm_up3, thumb_closed, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 2.00, arm_90_45_31, palm_up3_1, thumb_closed, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_45_32, palm_up3, thumb_closed, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_45_33, palm_up3_1, thumb_closed, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

static void amatriciana(char *names[], int time_step){
    pasta(names, time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_mouth, palm_front, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 2.00, arm_90_mouth2, palm_front, thumb_semi_closed, index_semi_closed, middle_semi_closed, ring_semi_closed, little_semi_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_mouth3, palm_front, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_mouth4, palm_front, thumb_semi_closed, index_semi_closed, middle_semi_closed, ring_semi_closed, little_semi_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_90_mouth, palm_front, thumb_open, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

void wine(char *names[], int time_step ) {
    setTiagoPositionCompos(names, time_step, 0.00, arm_face, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_face2, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_face, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_face2, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_face, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_face2, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.30, arm_face, palm_45, thumb_closed, index_open, middle_open, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

void white_wine(char *names[], int time_step ) {
    wine(names, time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_face, palm_45_2, thumb_closed, index_open, middle_closed, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 1.00, arm_face, palm_45_2, thumb_closed, index_open, middle_open, ring_open, little_open);
    setTiagoPositionCompos(names, time_step, 1.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

void red_wine(char *names[], int time_step ) {
    wine(names, time_step);
    setTiagoPositionCompos(names, time_step, 0.00, arm_90_mouth2, palm_45_3, thumb_closed, index_open, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.00, arm_90_mouth5, palm_45_3, thumb_closed, index_semi_closed, middle_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 1.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
}

void beef_steak(char *names[], int time_step) {
    setTiagoPositionCompos(names, time_step, 0.00, arm_face2, palm_45, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.50, arm_face, palm_45, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 1.00, arm_90_45_down, palm_down2, thumb_semi_closed_centred, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 3.00, arm_90_45_down2, palm_down2, thumb_semi_closed_centred, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 1.50, arm_90_45_r3, palm_sx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 3.00, arm_90_45_r4, palm_dx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 1.00, arm_90_45_r3, palm_dx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 4.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);

}

void cotoletta(char *names[], int time_step) {
    setTiagoPositionCompos(names, time_step, 0.00, arm_face, palm_45, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 2.50, arm_face, palm_45_4, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_face, palm_45, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 0.50, arm_face, palm_45_4, thumb_closed, index_semi_closed, middle_semi_closed, ring_closed, little_closed);
    setTiagoPositionCompos(names, time_step, 1.50, arm_90_45_r3, palm_sx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 4.00, arm_90_45_r4, palm_dx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 1.00, arm_90_45_r3, palm_dx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 3.00, arm_90_45_r4, palm_sx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 1.00, arm_90_45_r3, palm_sx, thumb_open, index_open_s, middle_open_s, ring_open_s, little_open_s);
    setTiagoPositionCompos(names, time_step, 4.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);

}


//Cri
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}
//EndCri 

void newSet(char *names[], int time_step) {
     jsmn_parser parser;

    jsmn_init(&parser);

int n;
char *JSON_STRING;
jsmntok_t t[256]; 
//read file
char var[10000];
char jsonFile[100000];
FILE *file;
file = fopen("/Users/crist/OneDrive/Desktop/test.json","r");
while(fgets(var, sizeof(var), file)!=NULL) {
  var[strcspn(var, "\n")] = '\0'; //remove newline
  //var[strcspn(var, "")] = '\0';
  strcat(jsonFile, var);
}
printf("Data read=%s\n",jsonFile);
fclose(file);
//-- 

JSON_STRING = jsonFile;

n = jsmn_parse(&parser, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));


//***
char change_position_after[100];
char arm_location[100],palm_orientation[100],thumb_configuration[100],index_configuration[100],middle_configuration[100],ring_configuration[100],little_configuration[100];
int Rchange_position_after;
//double Rarm_location,Rpalm_orientation,Rthumb_configuration,Rindex_configuration,Rmiddle_configuration,Rring_configuration,Rlittle_configuration;
//***
//***
/* Loop over all keys of the root object */
      /*char buf[100];
      sprintf(buf, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
      if (strcmp(buf, "beer") == 0)
        printf("-->%s\n", buf);
      i++;*/
      int entry = 0;
for (int i = 1; i < n; i++) {

if (jsoneq(JSON_STRING, &t[i], "beer") == 0 && entry == 0) {
      entry=1;
      //printf("iiiiii %d\n",i);
      for (int j = 1; i < n; i++) {  
        if (jsoneq(JSON_STRING, &t[j], "change_position_after") == 0) { 
          sprintf(change_position_after, "%.*s", t[j + 1].end - t[j + 1].start, JSON_STRING + t[j + 1].start);
          Rchange_position_after = atof(change_position_after);
          printf("change_position_after: %d\n", Rchange_position_after);
        }
        if (jsoneq(JSON_STRING, &t[j], "arm_location") == 0) { 
          sprintf(arm_location, "%.*s", t[j + 1].end - t[j + 1].start, JSON_STRING + t[j + 1].start);
          //Rarm_location = atof(arm_location);
          printf("arm_location: %s\n", arm_location);
        }
         if (jsoneq(JSON_STRING, &t[i], "palm_orientation") == 0) { 
          sprintf(palm_orientation, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rpalm_orientation = atof(palm_orientation);
          printf("palm_orientation: %s\n", palm_orientation);
        }
        if (jsoneq(JSON_STRING, &t[i], "thumb_configuration") == 0) { 
          sprintf(thumb_configuration, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rthumb_configuration = atof(thumb_configuration);
          printf("thumb_configuration: %s\n", thumb_configuration);
        }
        if (jsoneq(JSON_STRING, &t[i], "index_configuration") == 0) { 
          sprintf(index_configuration, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rindex_configuration = atof(index_configuration);
          printf("index_configuration: %s\n", index_configuration);
        }
        if (jsoneq(JSON_STRING, &t[i], "middle_configuration") == 0) { 
          sprintf(middle_configuration, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rmiddle_configuration = atof(middle_configuration);
          printf("middle_configuration: %s\n", middle_configuration);
        }
        if (jsoneq(JSON_STRING, &t[i], "ring_configuration") == 0) { 
          sprintf(ring_configuration, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rring_configuration = atof(ring_configuration);
          printf("ring_configuration: %s\n", ring_configuration);
        }
        if (jsoneq(JSON_STRING, &t[i], "little_configuration") == 0) { 
          sprintf(little_configuration, "%.*s", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
          //Rlittle_configuration = atof(little_configuration);
          printf("little_configuration: %s\n", little_configuration);
        } 
        j++;
        }
        //setTiagoPositionCompos(names, time_step, change_position_after, arm_location, palm_orientation, thumb_configuration, index_configuration, middle_configuration, ring_configuration, little_configuration);
        //setTiagoPositionCompos(names, time_step, 2.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
   i++; }
   }
   
   //Set setTiagoPositionCompos()
   
  
   
  }

int main(int argc, char **argv) {

    

//----------------------------------------------------------//
  /*if (jsoneq(JSON_STRING, &t[i], "location") == 0) {
      
      printf("- location: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "hand_configuration") == 0) {
      
      printf("- hand_configuration: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "hand_orientation") == 0) {
     
      printf("- hand_orientation: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    }else if (jsoneq(JSON_STRING, &t[i], "movement_speed") == 0) {
      
      printf("- movement_speed: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "movement") == 0) {
      int j;
      printf("- movement:\n");
      if (t[i + 1].type != JSMN_ARRAY) {
        continue; // We expect groups to be an array of strings
      }
      for (j = 0; j < t[i + 1].size; j++) {
        jsmntok_t *g = &t[i + j + 2];
        printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
      }
      i += t[i + 1].size + 1;
    }*/ /*else {
      printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
             JSON_STRING + t[i].start);
    }*/
//----------------------------------------------------------//
//}






  wb_robot_init();
  const int time_step = wb_robot_get_basic_time_step();  //TIME STEP DELLA SIMULAZIONE
  char *names[N_PARTS] = {"head_2_joint",
                                "head_1_joint",
                                "torso_lift_joint",

                                //MOTORI DEL BRACCIO 3-9
                                "arm_1_joint",
                                "arm_2_joint",
                                "arm_3_joint",
                                "arm_4_joint",
                                "arm_5_joint", //POLSO
                                "arm_6_joint", //POLSO
                                "arm_7_joint", //POLSO

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
  setTiagoPositionCompos(names, time_step, 0.00, arm_target, palm_rear, thumb_closed, index_closed, middle_closed, ring_closed, little_closed);
  
  // print user instructions
  printf("WELCOME TO TIAGO TITANIUM SIGN a project by Federico Dale' and Cristian Castiglione.\n");
  printf("WELCOME FOLKS\n"); //POI LO SISTEMEREMO
  printf("TO ASK FOR ATTENTION PRESS: Q\n");
  printf("\n");
  printf("TO SHOW THE LIS PRESS\n");
  printf("\n");
  printf("W for still water\n");
  printf("F for sparkling water\n");
  printf("K for cocacola\n");
  printf("B for beer\n");
  printf("R for red wine\n");
  printf("V for white wine\n");
  printf("C for coffee\n");
  printf("P for tomato\n");
  printf("G for carbonara\n");
  printf("A for amatriciana\n");
  printf("M for cotoletta\n");
  printf("S for beef steak\n");
  printf("U for fruit\n");
  printf("I for ice cream\n");

  // enable keyboard
  wb_keyboard_enable(time_step);

  //SIMULAZIONE
  while (wb_robot_step(time_step) != -1) {  //ciclo della simulazione un ciclio ogni time_step seconda

      int key = wb_keyboard_get_key();

      if (key >= 0) {
        switch (key) {
          case 'W':
              water(names, time_step);
            break;
          case 'F':
              water_friz(names, time_step);
            break;
          case 'K':
              cocacola(names, time_step);
            break;
          case 'B':
              beer(names,time_step);
            break;
          case 'R':
              red_wine(names, time_step);
            break;
          case 'V':
              white_wine(names, time_step);
            break;
          case 'C':
              coffee(names, time_step);
            break;
          case 'P':
              tomato(names,time_step);
            break;
          case 'G':
              carbonara(names, time_step);
            break;
          case 'A':
              amatriciana(names, time_step);
            break;
          case 'M':
              cotoletta(names, time_step);
            break;
          case 'S':
              beef_steak(names,time_step);
            break;
          case 'U':
              fruit(names, time_step);
            break;
          case 'I':
              ice_cream(names, time_step);
            break;
          case 'Q':
              start_comunication(names, time_step);
            break;
            case 'Z':
              newSet(names, time_step);
            break;
        }
      }
  }

  wb_robot_cleanup();

  return 0;
}
