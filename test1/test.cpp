// DigitalDifferentialAnalyserLine.cpp : 定义控制台应用程序的入口点。   
  
//#include "stdafx.h"   
#include<stdlib.h>   
#include <GL/glut.h>   
  
/* initialization: */  
void myinit(void)  
{  
   
/* attributes */  
  
      glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */  
      glColor3f(1.0, 0.0, 0.0); /* draw in red */  
  
/* set up viewing: */  
/* 500 x 500 window with origin lower left */  
  
      glMatrixMode(GL_PROJECTION);  
      glLoadIdentity();  
      gluOrtho2D(0.0, 500.0, 0.0, 500.0);  
      glMatrixMode(GL_MODELVIEW);  
}  
  
void dda_line(int xa,int ya,int xb,int yb)  
{  
        GLfloat delta_x,delta_y,x,y;  
        int dx,dy,steps;  
        dx=xb-xa;  
        dy=yb-ya;  
        if(abs(dx)>abs(dy))  
                steps=abs(dx);  
        else  
                steps=abs(dy);  
        delta_x=(GLfloat)dx/(GLfloat)steps;  
        delta_y=(GLfloat)dy/(GLfloat)steps;  
        x=xa;  
        y=ya;  
        glClear(GL_COLOR_BUFFER_BIT);  
        glBegin(GL_POINTS);  
        glVertex3f(x,y,0);  
        for(int k=1;k<=steps;k++)  
        {  
                x+=delta_x;  
                y+=delta_y;  
                glBegin(GL_POINTS);  
                glVertex3f(x,y,0);   
                glEnd();  
        }  
          
}  
  
/* the display callback: */  
void display( void )  
{  
    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */  
  
    /*----------------------------------------*/  
    /*  viewport stuff                        */  
    /*----------------------------------------*/  
    /* set up a viewport in the screen window */  
    /* args to glViewport are left, bottom, width, height */  
    glViewport(0, 0, 500, 500);  
    /* NB: default viewport has same coords as in myinit, */  
    /* so this could be omitted: */  
  
      
    dda_line(200,200,2000,2000);  
  
    /* and flush that buffer to the screen */  
    glFlush();   
 }  
  
int main(int argc, char** argv)  
{  
  
/* Standard GLUT initialization */  
  
    glutInit(&argc,argv);  
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); /* default, not needed */  
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */  
    glutInitWindowPosition(0,0); /* place window top left on display */  
    glutCreateWindow("Digital Differential  Analyser  Line"); /* window title */  
    glutDisplayFunc(display); /* display callback invoked when window opened */  
     myinit(); /* set attributes */  
    glutMainLoop(); /* enter event loop */  
}  
