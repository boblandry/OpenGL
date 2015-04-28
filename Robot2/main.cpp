#include <gl\glut.h>
#include <math.h>
#include <iostream>
#include "robot.h"
#include <stack>
#include <stdio.h>
using namespace std;
//保存点的xy坐标的结构体
struct point
{
	int x;
	int y;
};
GLubyte nowpixel[3];
GLubyte boundarypixel[3]={0,0,0};//黑色
GLubyte backpixel[3]={255,255,255};//白色
GLubyte setpixel[3];
void line_fill(int x,int y,int r,int g,int b)
{
	int sx,sy,xright,xleft,savex;
	//bool needfill=true;  
	stack<point> s1;
	point p1={x,y},temp_p;
	s1.push(p1);
	//setpixel[0]=r;setpixel[1]=g;setpixel[2]=b;
	while (!s1.empty()){
		temp_p=s1.top();
		s1.pop();
		sx=temp_p.x;
		sy=temp_p.y;
		//printf("%d %d\n",sx,sy);
		savex=temp_p.x;
		glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		//cout<<1<<endl;
		//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
		while(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2]){
			//if(nowpixel[0]!=255 && nowpixel[1]!=255 && nowpixel[2]!=255)
			//printf("1\n");
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			drawpoint(sx,sy,r,g,b);
			sx=sx+1;
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		}
		xright=sx-1;
		sx=savex-1;
		glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		while(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2]){
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			drawpoint(sx,sy,r,g,b);
			sx=sx-1;
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		}
		xleft=sx+1;sx=xright;sy=sy+1;
		//printf("\n");
		//上一行
		while(sx>=xleft){
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			if(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2] ){
			//&& nowpixel[0]!=r && nowpixel[1]!=g && nowpixel[2]!=b){
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
				point p={sx,sy};
				s1.push(p);
				//printf("找到一个点\n");
				break;
			}
			else{
				sx--;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			}
		}
		sy=sy-2;sx=xright;
		//下一行
		//printf("\n");
		while(sx>=xleft){
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			if(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2] ){
			//&& nowpixel[0]!=r && nowpixel[1]!=g && nowpixel[2]!=b){
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
				point p={sx,sy};
				s1.push(p);
				//printf("找到一个点\n");
				break;
			}	
			else{
				sx--;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			}
		}
	}
}
void line_fill1(int x,int y,int r,int g,int b)
{
	int sx,sy,xright,xleft,savex;
	//bool needfill=false;  
	stack<point> s1;
	point p1={x,y},temp_p;
	s1.push(p1);
	//setpixel[0]=r;setpixel[1]=g;setpixel[2]=b;
	while (!s1.empty()){
		temp_p=s1.top();
		s1.pop();
		sx=temp_p.x;
		sy=temp_p.y;
		//printf("%d %d\n",sx,sy);
		savex=temp_p.x;
		glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		//cout<<1<<endl;
		//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
		while(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2]){
			//if(nowpixel[0]!=255 && nowpixel[1]!=255 && nowpixel[2]!=255)
			//printf("1\n");
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			drawpoint(sx,sy,r,g,b);
			sx=sx+1;
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		}
		xright=sx-1;
		sx=savex-1;
		glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		while(nowpixel[0]!=boundarypixel[0] && nowpixel[1]!=boundarypixel[1] && nowpixel[2]!=boundarypixel[2]){
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			drawpoint(sx,sy,r,g,b);
			sx=sx-1;
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
		}
		xleft=sx+1;sx=xleft;sy=sy+1;
		//printf("\n");
		//上一行
		while(sx<=xright){
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			bool needfill=false;
			while(nowpixel[0]==backpixel[0] && nowpixel[1]==backpixel[1] && nowpixel[2]==backpixel[2]){
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
				needfill=true;
				sx++;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			}
			if(needfill){
				point p={sx-1,sy};
				s1.push(p);
				needfill=false;
			}
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			while(nowpixel[0]!=backpixel[0] && nowpixel[1]!=backpixel[1] && nowpixel[2]!=backpixel[2] && sx<=xright){
				sx++;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			}	
		}
		sy=sy-2;sx=xleft;
		//下一行
		//printf("\n");
		while(sx<=xright){
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
			bool needfill=false;
			while(nowpixel[0]==backpixel[0] && nowpixel[1]==backpixel[1] && nowpixel[2]==backpixel[2]){
				//printf("r=%d g=%d b=%d\n",nowpixel[0],nowpixel[1],nowpixel[2]);
				needfill=true;
				sx++;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			}
			if(needfill){
				point p={sx-1,sy};
				s1.push(p);
				needfill=false;
			}
			glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			while(nowpixel[0]!=backpixel[0] && nowpixel[1]!=backpixel[1] && nowpixel[2]!=backpixel[2] && sx<=xright){
				sx++;
				glReadPixels(sx,sy,1,1,GL_RGB,GL_UNSIGNED_BYTE,&nowpixel);
			}
				
		}
	}
}
void drawrobot(void)
{
	glClearColor(1.0,1.0,1.0,0);//将清空颜色设置为白色
	glClear(GL_COLOR_BUFFER_BIT);//将窗口背景设置为当前清空颜色
	glColor3f(0.0,0.0,0.0);
	//gluOrtho2D(-300.0, 300.0, -300.0, 300.0);//设定窗口左下角和右上角的xy坐标
	gluOrtho2D(0, 600.0,0, 600.0);
	glViewport(0,0,600,600);
	//dda(200,600,100,200);
	//midpointline(100,300,550,100);
	//bresenhamline(500,100,100,200);
	//pnarc1(150,300,300,3);
	//bresenhamarc(150,300,300,1);
	//画圆
	pnarc1(15,300,300,1);
	pnarc1(15,300,300,2);
	pnarc1(15,300,300,3);
	pnarc1(15,300,300,4);
	//画三角形
	midpointline(266,280,334,280);
	midpointline(266,280,300,340);
	midpointline(334,280,300,340);
	//画中心 圆角矩阵
	dda(400,360,400,240);
	dda(200,360,200,240);
	dda(220,380,380,380);
	dda(220,220,380,220);
	pnarc1(20,380,360,1);
	pnarc1(20,380,240,4);
	pnarc1(20,220,240,3);
	pnarc1(20,220,360,2);
	//画脖子
	dda(325,380,325,400);
	dda(275,380,275,400);
	//画头 圆角矩阵
	midpointline(240,400,360,400);
	dda(380,420,380,480);
	dda(220,420,220,480);
	midpointline(240,500,360,500);
	pnarc1(20,360,480,1);
	pnarc1(20,360,420,4);
	pnarc1(20,240,420,3);
	pnarc1(20,240,480,2);
	//画眼睛
	pnarc1(15,330,450,1);
	pnarc1(15,330,450,2);
	pnarc1(15,330,450,3);
	pnarc1(15,330,450,4);

	pnarc1(15,270,450,1);
	pnarc1(15,270,450,2);
	pnarc1(15,270,450,3);
	pnarc1(15,270,450,4);
	//画嘴巴
	bresenhamarc(20,300,435,6);
	bresenhamarc(20,300,435,7);
	//画天线
	dda(340,500,340,530);
	dda(260,500,260,530);
	//画右耳
	pnarc1(5,385,470,2);
	bresenhamline(385,475,395,475);
	pnarc1(5,395,470,1);
	bresenhamline(400,470,400,430);
	pnarc1(5,395,430,4);
	bresenhamline(385,425,395,425);
	pnarc1(5,385,430,3);
	//画左耳
	pnarc1(5,215,470,1);
	bresenhamline(215,475,205,475);
	pnarc1(5,205,470,2);
	bresenhamline(200,470,200,430);
	pnarc1(5,205,430,3);
	bresenhamline(205,425,215,425);
	pnarc1(5,215,430,4);
	//画右手
	bresenhamline(400,350,410,350);
	bresenhamline(400,330,410,330);
	bresenhamline(410,360,450,360);
	bresenhamline(410,290,450,290);
	bresenhamline(410,290,410,360);
	bresenhamline(450,290,450,360);

	bresenhamline(420,290,420,280);
	bresenhamline(440,290,440,280);

	bresenhamline(410,280,450,280);
	bresenhamline(410,280,410,230);
	bresenhamline(450,280,450,230);
	bresenhamline(410,230,450,230);
	pnarc1(10,430,220,1);
	pnarc1(10,430,220,2);
	pnarc1(10,430,220,3);
	pnarc1(10,430,220,4);
	//画左手
	bresenhamline(200,350,190,350);
	bresenhamline(200,330,190,330);
	bresenhamline(190,360,150,360);
	bresenhamline(190,290,150,290);
	bresenhamline(190,360,190,290);
	bresenhamline(150,360,150,290);

	bresenhamline(180,290,180,280);
	bresenhamline(160,290,160,280);

	bresenhamline(190,280,150,280);
	bresenhamline(190,280,190,230);
	bresenhamline(150,280,150,230);
	bresenhamline(190,230,150,230);
	pnarc1(10,170,220,1);
	pnarc1(10,170,220,2);
	pnarc1(10,170,220,3);
	pnarc1(10,170,220,4);
	//画右脚
	bresenhamline(330,220,330,210);
	bresenhamline(350,220,350,210);
	bresenhamline(330,210,350,210);
	pnarc1(10,330,200,2);
	pnarc1(10,350,200,1);
	bresenhamline(320,200,320,150);
	bresenhamline(360,200,360,150);
	pnarc1(10,330,150,3);
	pnarc1(10,350,150,4);
	bresenhamline(330,140,350,140);
	bresenhamline(330,140,330,130);
	bresenhamline(350,140,350,130);
	bresenhamline(315,130,365,130);
	bresenhamline(315,130,315,110);
	bresenhamline(365,130,365,110);
	bresenhamline(315,110,365,110);
	//画左脚
	bresenhamline(270,220,270,210);
	bresenhamline(250,220,250,210);
	bresenhamline(270,210,250,210);
	pnarc1(10,270,200,1);
	pnarc1(10,250,200,2);
	bresenhamline(239,200,239,150);
	bresenhamline(280,200,280,150);
	pnarc1(10,250,150,3);
	pnarc1(10,270,150,4);
	bresenhamline(250,140,270,140);
	bresenhamline(250,140,250,130);
	bresenhamline(270,140,270,130);
	bresenhamline(235,130,285,130);
	bresenhamline(235,130,235,110);
	bresenhamline(285,130,285,110);
	bresenhamline(235,110,285,110);
	
	
	glFlush();
	line_fill(300,295,255,0,0);//填充红色圆形
	line_fill(300,325,255,255,0);//填充黄色三角形

	line_fill1(240,300,153,153,153);//填充灰色肚子
	line_fill1(280,390,153,153,153);//脖子
	line_fill1(280,405,153,153,153);//脸
	line_fill1(170,220,153,153,153);//左右手
	line_fill1(430,220,153,153,153);
	line_fill1(260,215,153,153,153);//大腿
	line_fill1(340,215,153,153,153);
	line_fill1(260,135,153,153,153);//小腿
	line_fill1(340,135,153,153,153);
	line_fill1(170,285,153,153,153);//手肘
	line_fill1(430,285,153,153,153);
	line_fill1(195,340,153,153,153);//腋部
	line_fill1(405,340,153,153,153);

	line_fill1(215,470,73,73,73);//左右耳
	line_fill1(385,470,73,73,73);
	line_fill1(420,300,73,73,73);//上臂
	line_fill1(170,350,73,73,73);
	line_fill1(420,240,73,73,73);//小臂
	line_fill1(160,240,73,73,73);
	line_fill1(330,200,73,73,73);//膝盖
	line_fill1(270,200,73,73,73);
	line_fill1(320,120,73,73,73);//脚
	line_fill1(240,120,73,73,73);

	system("pause");
	glFlush();
}
int main(int argc,char *argv[])
{                                            
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("机器人");
	glutDisplayFunc(&drawrobot);
	//glutDisplayFunc(&move);
	//line_fill(300,300,255,255,0);
	glutMainLoop();
	return 0;
}