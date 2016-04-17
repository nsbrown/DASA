/*
 * dasadraw.c
 * Copyright Craig A. Damon, 2016
 *   all rights reserved, may be freely used to demonstrate the dasa interface
 *
 *  Created on: Feb 19, 2016
 *      Author: Craig A. Damon
 */

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "dgs.h"

/* the current display position */
float actualX;
float actualY;
float actualZ;
float tilt = 45;   // degrees of tilt on the shower head


char onOff;

int lastMS = 0; 
char moving = 0;

extern DasaServerInfo currentState;
extern DasaServerInfo * requestedState;

#define SHOWER_FLOOR 200
#define SHOWER_BACK 200
#define BAR_THICKNESS 6.0f
#define HALF_BAR (BAR_THICKNESS/2)


static int getMS()
{
  static int firstTime = 1;
  static struct timeval previous_time;
  struct timeval new_time;
  if (firstTime)
    {
      firstTime = 0;
      gettimeofday(&previous_time,NULL);
      return 0;
    }
  gettimeofday(&new_time,NULL);
  int ms = (new_time.tv_sec - previous_time.tv_sec) * 1000 + (new_time.tv_usec - previous_time.tv_usec)/1000;
  return ms;
}



static void checkForChanges(void)
{
  if (requestedState->shutdown)
    exit(0);
  if (requestedState->xPos != currentState.xPos)
    {
      if (requestedState->xPos < currentState.xPos)
        currentState.xPos--;
      else
        currentState.xPos++;
      //printf("Moving x to %d\n",currentState.xPos);
      if (!moving)
        {
          moving = 1;
          lastMS = getMS();
        }
    }
  if (requestedState->yPos != currentState.yPos)
    {
      currentState.yPos = requestedState->yPos;
      //printf("Moving y to %d\n",currentState.yPos);
      if (!moving)
        {
          moving = 1;
          lastMS = getMS();
        }
    }
    if (requestedState->zPos != currentState.zPos)
    {
      if (requestedState->zPos < currentState.zPos)
        currentState.zPos--;
      else
        currentState.zPos++;
      //printf("Moving z to %d\n",currentState.zPos);
      if (!moving)
        {
          moving = 1;
          lastMS = getMS();
        }
    }
  if (requestedState->temp != currentState.temp)
    {
      if (requestedState->temp < currentState.temp)
        currentState.temp--;
      else
        currentState.temp++;
      moving = 1;
      printf("Moving temp to %d\n",currentState.temp);
    }
  if (requestedState->onOff != currentState.onOff)
    {
      currentState.onOff = requestedState->onOff;
      if (currentState.onOff == ON)
        printf("Turning water ON\n");
      else
        printf("Turning water OFF\n");
        moving = 1;
    }
  if (requestedState->mode != currentState.mode)
    {
      currentState.mode = requestedState->mode;
      moving = 1;
      switch (currentState.mode)
        {
        case SHOWER:
           printf("setting mode to SHOWER\n");
           break;
        case JET:
           printf("setting mode to JET\n");
           break;
        case RAIN:
           printf("setting mode to RAIN\n");
           break;
        case MASSAGE:
           printf("setting mode to MASSAGE\n");
           break;
        }
    }
}

#define DIST_PER_MS 0.05f

static void updatePos()
{
   if (!moving)
     return;
     int ms = getMS();
     int time = ms-lastMS;
     if (time < 1)
       return;
     lastMS = ms;
//     printf("updating pos time %d: %f vs %d\n",time,actualX,currentState.xPos);
    char stillMoving = 0;
    if (currentState.onOff == ON)
      stillMoving = 1;
   if (actualX != currentState.xPos)
     {
       if (actualX < currentState.xPos)
         {
            actualX += DIST_PER_MS * time;
            if (actualX >= currentState.xPos)
              actualX = currentState.xPos;
             else
               stillMoving = 1;
         }
       else
         {
            actualX -= DIST_PER_MS * time;
            if (actualX <= currentState.xPos)
              actualX = currentState.xPos;
             else
               stillMoving = 1;
         }
    }
   if (actualY != currentState.yPos)
     {
       if (actualY < currentState.yPos)
         {
            actualY += DIST_PER_MS * time;
            if (actualY >= currentState.yPos)
              actualY = currentState.yPos;
             else
               stillMoving = 1;
         }
       else
         {
            actualY -= DIST_PER_MS * time;
            if (actualY <= currentState.yPos)
              actualY = currentState.yPos;
             else
               stillMoving = 1;
         }
    }
   if (actualZ != currentState.zPos)
     {
       if (actualZ < currentState.zPos)
         {
            actualZ += DIST_PER_MS * time;
            if (actualZ >= currentState.zPos)
              actualZ = currentState.zPos;
             else
               stillMoving = 1;
         }
       else
         {
            actualZ -= DIST_PER_MS * time;
            if (actualZ <= currentState.zPos)
              actualZ = currentState.zPos;
             else
               stillMoving = 1;
         }
    }
//   printf("Moved to %f,%f,%f\n",actualX,actualY,actualZ);
   moving = stillMoving;  
   glutPostRedisplay();
}

static void idleFunc()
{
  checkForChanges();
  updatePos();
}


static void drawShowerHead()
{
  float barFront = actualZ+(HALF_BAR/2);
  float barBack = actualZ-(HALF_BAR/2);
  float barLeft = (-actualX)-(HALF_BAR/2);
  float barRight = (-actualX)+(HALF_BAR/2);
  float barTop = -BAR_THICKNESS;
  float barBottom = actualY+BAR_THICKNESS;
  
#define HEAD_WIDTH (BAR_THICKNESS*2)
#define HALF_HEAD (HEAD_WIDTH/2)
#define HEAD_HEIGHT (BAR_THICKNESS*1.5)

  glBegin(GL_QUADS);
    glColor3f(0.85f,0.85f,0.85f);  // the bar holding the shower head
    glVertex3f(barLeft,barBottom,barFront);  // front
    glVertex3f(barRight,barBottom,barFront);
    glVertex3f(barRight,barTop,barFront);
    glVertex3f(barLeft,barTop,barFront);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex3f(barLeft,barBottom,barBack);  // back
    glVertex3f(barRight,barBottom,barBack);
    glVertex3f(barRight,barTop,barBack);
    glVertex3f(barLeft,barTop,barBack);
    glVertex3f(barLeft,barBottom,barBack);  // outside
    glVertex3f(barLeft,barBottom,barFront);
    glVertex3f(barRight,barTop,barFront);
    glVertex3f(barLeft,-barTop,barBack);
    glVertex3f(barRight,barBottom,barBack);  // inside
    glVertex3f(barRight,barBottom,barFront);
    glVertex3f(barRight,barTop,barFront);
    glVertex3f(barRight,barTop,barBack);
  glEnd();
  
  glPushMatrix();
   glTranslatef((-actualX),actualY,actualZ);
   glRotatef(tilt,1,0,0);
  glBegin(GL_QUADS);
    glVertex3f(HALF_BAR,0,HALF_BAR);    // outside
    glVertex3f(HALF_BAR,0,-HALF_BAR);
    glVertex3f(HALF_HEAD,HEAD_HEIGHT,-HALF_HEAD);
    glVertex3f(HALF_HEAD,HEAD_HEIGHT,HALF_HEAD);
    
    glColor3f(0.7f,0.7f,0.7f);
    glVertex3f(-HALF_BAR,0,HALF_BAR);    // inside
    glVertex3f(-HALF_BAR,0,-HALF_BAR);
    glVertex3f(-HALF_HEAD,HEAD_HEIGHT,-HALF_HEAD);
    glVertex3f(-HALF_HEAD,HEAD_HEIGHT,HALF_HEAD);
    
    glColor3f(0.85f,0.85f,0.85f);
    glVertex3f(-HALF_BAR,0,HALF_BAR);    // front
    glVertex3f(HALF_BAR,0,HALF_BAR);
    glVertex3f(HALF_HEAD,HEAD_HEIGHT,HALF_HEAD);
    glVertex3f(-HALF_HEAD,HEAD_HEIGHT,HALF_HEAD);
    
    glColor3f(0.7f,0.7f,0.7f);
    glVertex3f(-HALF_BAR,0,-HALF_BAR);    // back
    glVertex3f(HALF_BAR,0,-HALF_BAR);
    glVertex3f(HALF_HEAD,HEAD_HEIGHT,-HALF_HEAD);
    glVertex3f(-HALF_HEAD,HEAD_HEIGHT,-HALF_HEAD);

  glEnd();
  glPopMatrix();
}

static void drawCrossBar()
{
   float barFront = actualZ+HALF_BAR;
   float barBack = barFront-BAR_THICKNESS;
   float barBottom = 0;
   float barTop = barBottom - BAR_THICKNESS;
   float barLeft = -50-BAR_THICKNESS;
   float barRight = 50+BAR_THICKNESS;
  glBegin(GL_QUADS);
    glColor3f(0.8f,0.8f,0.8f);
    //glColor3f(1,0,0);
    glVertex3f(barLeft,barBottom,barFront);  //front
    glVertex3f(barLeft,barTop,barFront);
    glVertex3f(barRight,barTop,barFront);
    glVertex3f(barRight,barBottom,barFront);

	//glColor3f(0,1,0);
    glVertex3f(barLeft,barBottom,barBack);  //back
    glVertex3f(barLeft,barTop,barBack);
    glVertex3f(barRight,barTop,barBack);
    glVertex3f(barRight,barBottom,barBack);

	//glColor3f(0,0,1);
    glVertex3f(barLeft,barBottom,barFront);      // bottom
    glVertex3f(barLeft,barBottom,barBack);
    glVertex3f(barRight,barBottom,barBack);
    glVertex3f(barRight,barBottom,barFront);

	//glColor3f(1,1,0);
    glVertex3f(barLeft,barTop,barFront);    // top
    glVertex3f(barLeft,barTop,barBack);
    glVertex3f(barRight,barTop,barBack);
    glVertex3f(barRight,barTop,barFront);
  glEnd();
}

static void drawEnclosure()
{
  glBegin(GL_QUADS);
    glColor3f(1,0.99,0.81);    // draw the part on the shower wall as cream
    glVertex3f(-50 - BAR_THICKNESS,-20,-2*BAR_THICKNESS);
    glVertex3f(-50 - BAR_THICKNESS,SHOWER_FLOOR,-2*BAR_THICKNESS);
    glVertex3f(50 + BAR_THICKNESS,SHOWER_FLOOR,-2*BAR_THICKNESS);
    glVertex3f(50 + BAR_THICKNESS,-20,-2*BAR_THICKNESS);
    
    glColor3f(1,0.99,0.81);    // draw the side wall as cream
    glVertex3f(-50 - BAR_THICKNESS,-20,-2*BAR_THICKNESS);
    glVertex3f(-50 - BAR_THICKNESS,SHOWER_FLOOR,-2*BAR_THICKNESS);
    glVertex3f(-50 - BAR_THICKNESS,SHOWER_FLOOR,SHOWER_BACK);
    glVertex3f(-50 - BAR_THICKNESS,-20,SHOWER_BACK);
    
	glColor3f(1,0.99,0.81);    // draw the back wall as cream
    glVertex3f(-50 - BAR_THICKNESS,-20,SHOWER_BACK);
    glVertex3f(-50 - BAR_THICKNESS,SHOWER_FLOOR,SHOWER_BACK);
    glVertex3f(50 + BAR_THICKNESS,SHOWER_FLOOR,SHOWER_BACK);
    glVertex3f(50 + BAR_THICKNESS,-20,SHOWER_BACK);
    
    glColor3f(0.8,0.8,0.8);  // the support structure
    
    glVertex3f(-50,0,-2*BAR_THICKNESS);  // inside
    glVertex3f(-50,0,SHOWER_BACK);
    glVertex3f(-50,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(-50,BAR_THICKNESS,-2*BAR_THICKNESS);
    
    glVertex3f(-50-BAR_THICKNESS,0,-2*BAR_THICKNESS);  // outside
    glVertex3f(-50-BAR_THICKNESS,0,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,BAR_THICKNESS,-2*BAR_THICKNESS);
    
    glVertex3f(-50,0,-2*BAR_THICKNESS);    // top
    glVertex3f(-50,0,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,0,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,0,-2*BAR_THICKNESS);
    
    glVertex3f(-50,BAR_THICKNESS,-2*BAR_THICKNESS);  // bottom
    glVertex3f(-50,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(-50-BAR_THICKNESS,BAR_THICKNESS,-2*BAR_THICKNESS);


	glColor3f(0.8,0.8,0.8);
    glVertex3f(50+BAR_THICKNESS,0,-2*BAR_THICKNESS);   // outside
    glVertex3f(50+BAR_THICKNESS,0,SHOWER_BACK);
    glVertex3f(50+BAR_THICKNESS,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(50+BAR_THICKNESS,BAR_THICKNESS,-2*BAR_THICKNESS);
    glVertex3f(50,0,-2*BAR_THICKNESS);   // inside
    glVertex3f(50,0,SHOWER_BACK);
    glVertex3f(50,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(50,BAR_THICKNESS,-2*BAR_THICKNESS);
    glVertex3f(50+BAR_THICKNESS,0,-2*BAR_THICKNESS);    // top
    glVertex3f(50+BAR_THICKNESS,0,SHOWER_BACK);
    glVertex3f(50,0,SHOWER_BACK);
    glVertex3f(50,0,-2*BAR_THICKNESS);
    glVertex3f(50+BAR_THICKNESS,BAR_THICKNESS,-2*BAR_THICKNESS);   // bottom
    glVertex3f(50+BAR_THICKNESS,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(50,BAR_THICKNESS,SHOWER_BACK);
    glVertex3f(50,BAR_THICKNESS,-2*BAR_THICKNESS);
   
glEnd();

}

static void drawWater()
{
  if (currentState.onOff == OFF)
    return;
    
  float bottomWidth = 80;
  float bottom = SHOWER_FLOOR-actualY;
  glPushMatrix();
   glTranslatef((-actualX),actualY,actualZ);
   glRotatef(tilt,1,0,0);
  glBegin(GL_TRIANGLES);
      glColor3f(0.8f,0.8f,1);
      glVertex3f(0,0,0);
      glVertex3f(0,bottom,bottomWidth/2);
      glVertex3f(0,bottom,-bottomWidth/2);
  glEnd();  
  glPopMatrix();
}

static void display()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   drawEnclosure();
   drawShowerHead();
   drawCrossBar();
   drawWater();
   
   glutSwapBuffers();
}

static void init()
{
  GLfloat light0_pos[4] = { 100,10,150,1};
  GLfloat light1_pos[4] = { 0,100,70,1};
  GLfloat light0_color[4] = { 1,1,1,1};
  GLfloat light1_color[4] = { 0.4,0.2,0.2,1};
  GLfloat ambient_color[4] = { 0.2,0.2,0.2,1};
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30,0.8,550,800);
  gluLookAt(610,120,300,0,50,100,0,-1,0);


  // add a light, enabling it first
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_color);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_color);
  glLightfv(GL_LIGHT0,GL_AMBIENT, ambient_color);
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
}

void dasaDisplay(int argc,char ** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
  glutInitWindowSize(1000,600);
  glutCreateWindow("DASA");
  glutIdleFunc(idleFunc);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
