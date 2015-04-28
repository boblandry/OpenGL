#include <gl\glut.h>
#include <math.h>
#include <iostream>
#include <stack>
#include <stdio.h>

#define PI 3.1415926

int lineWidth=2;
int black[3]={0,0,0};
int grey[3]={173,173,173};
int yellow[3]={255,255,0};
int red[3]={255,0,0};
int darkgrey[3]={123,123,123};
int white[3]={255,255,255};

//画直线
void glLine(int x1,int y1,int x2,int y2){
    glBegin(GL_LINE_STRIP);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
}
//画三角形，传入三个点的坐标
void glTri(int x1,int y1,int x2,int y2,int x3,int y3,int MODE){
    glBegin(MODE);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}
//画矩形，传入的是左下角XY坐标和右上角XY坐标
void glRect(int leftX,int leftY,int rightX,int rightY,int MODE){
    glBegin(MODE);
	glVertex2d(leftX,leftY);
	glVertex2d(rightX,leftY);
	glVertex2d(rightX,rightY);
	glVertex2d(leftX,rightY);
	glEnd();
}
//画弧线，相对偏移量XY，开始的弧度，结束的弧度，半径
void glArc(double x,double y,double start_angle,double end_angle,double radius,int MODE)
{   
	glBegin(MODE);
	double delta_angle=PI/180;
	//画圆弧
	for (double i=start_angle;i<=end_angle;i+=delta_angle)
	{
		//绝对定位加三角函数值
		double vx=x+radius * cos(i);
		double vy=y+radius*sin(i);
		glVertex2d(vx,vy);
	}
	glEnd();
}
//画圆
void glCircle(double x, double y, double radius,int MODE)  
{  
    glArc(x,y,0,2*PI,radius,MODE);  
}  

//画圆角矩形，传入矩形宽高，角半径，矩形中心点坐标
void glRoundRec(int centerX,int centerY,int width,int height,float cirR,int MODE){
	float PI_HALF = PI/2;
	//划分程度,值越大画得越精细
	float divide=20.0;
	//圆角矩形的坐标
    float tx,ty; 
    glBegin(MODE);
	//四个象限不同的操作符
    int opX[4]={1,-1,-1,1};
    int opY[4]={1,1,-1,-1};
	//用来计数，从第一象限到第四象限
    float x=0;
	//x自增时加的值
	float part=1/divide;
	//计算内矩形宽高一半的数值
	int w=width/2-cirR;
	int h=height/2-cirR;
	//循环画线
    for(x=0;x<4;x+=part){
		//求出弧度
		float rad = PI_HALF*x;
		//计算坐标值
	    tx=cirR*cos(rad)+opX[(int)x]*w+centerX;
	    ty=cirR*sin(rad)+opY[(int)x]*h+centerY;
	    glVertex2f(tx,ty);
	}
   glEnd();
}


//画填充的三角形，传值为逆时针
void glFillTri(int x1,int y1,int x2,int y2,int x3,int y3,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glTri(x1,y1,x2,y2,x3,y3,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glTri(x1+lineWidth/2,y1+lineWidth/2,x2-lineWidth/2,y2+lineWidth/2,x3,y3-lineWidth/2,GL_POLYGON);
}

//画填充的圆角矩形
void glFillRoundRec(int centerX,int centerY,int width,int height,float cirR,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glRoundRec(centerX,centerY,width,height,cirR,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glRoundRec(centerX,centerY,width-lineWidth/2,height-lineWidth/2,cirR,GL_POLYGON);
}

//画填充的圆形
void glFillCircle(double x, double y, double radius,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glCircle(x,y,radius,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glCircle(x,y,radius-lineWidth/2,GL_POLYGON);
}

//画填充的矩形，传入左上角和右下角的坐标
void glFillRect(int leftX,int leftY,int rightX,int rightY,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glRect(leftX,leftY,rightX,rightY,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glRect(leftX+lineWidth/2,leftY-lineWidth/2,rightX-lineWidth/2,rightY+lineWidth/2,GL_POLYGON);
}
void drawrobot(void){
	glClearColor(1.0,1.0,1.0,0);//将清空颜色设置为白色
	glClear(GL_COLOR_BUFFER_BIT);//将窗口背景设置为当前清空颜色
	glColor3f(0.0,0.0,0.0);
	//gluOrtho2D(-300.0, 300.0, -300.0, 300.0);//设定窗口左下角和右上角的xy坐标
	gluOrtho2D(0, 600.0,0, 600.0);
	glViewport(0,0,600,600);
	//注意会覆盖
	glFillRoundRec(300,300,200,160,20,grey);//画中心圆角矩阵
	glFillTri(266,280,334,280,300,340,yellow);//画黄色三角形
	glFillCircle(300,300,10,red);//画红色圆形
	glFillRect(275,380,325,400,grey);//画脖子
	glLine(340,500,340,530);
	glLine(260,500,260,530);//画天线
	glFillRoundRec(300,450,160,100,20,grey);//画脸
	glFillCircle(330,450,12,white);
	glFillCircle(270,450,12,white);//画眼睛
	glArc(300,435,5*PI/4,7*PI/4,20,GL_LINE_STRIP);//画嘴
	glFillRoundRec(390,450,20,50,5,darkgrey);
	glFillRoundRec(210,450,20,50,5,darkgrey);//画耳朵
	//画右手
	glFillRect(400,330,410,350,grey);
	glFillRect(410,290,450,360,darkgrey);
	glFillRect(420,280,440,290,grey);
	glFillRect(410,230,450,280,darkgrey);
	glFillCircle(430,220,10,grey);
	//画左手
	glFillRect(190,330,200,350,grey);
	glFillRect(150,290,190,360,darkgrey);
	glFillRect(160,280,180,290,grey);
	glFillRect(150,230,190,280,darkgrey);
	glFillCircle(170,220,10,grey);
	//画右脚
	glFillRect(330,210,350,220,grey);
	glFillRoundRec(340,175,40,70,10,darkgrey);
	glFillRect(330,130,350,140,grey);
	glFillRect(315,110,365,130,darkgrey);
	//画左脚
	glFillRect(250,210,270,220,grey);
	glFillRoundRec(260,175,40,70,10,darkgrey);
	glFillRect(250,130,270,140,grey);
	glFillRect(235,110,285,130,darkgrey);

	glFlush();

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslated(50,0,0);
	glScaled(1.5,1.5,0);
	//glTranslated(50,100,0);
	//glRotatef(45,0,0,1);//绕Z轴旋转
	glFlush();
}
//窗口大小变化时调用的函数
void ChangeSize(GLsizei w,GLsizei h)  
{  
	//避免高度为0
    if(h==0) {  
        h=1;  
    }  
    //定义视口大小，宽高一致  
    glViewport(0,0,w,h);
	int half = 300;
	//重置坐标系统，使投影变换复位
    glMatrixMode(GL_PROJECTION); 
	//将当前的用户坐标系的原点移到了屏幕中心
    glLoadIdentity();  
   //定义正交视域体  
    if(w<h) {
		//如果高度大于宽度，则将高度视角扩大，图形显示居中
        //glOrtho(-half,half,-half*h/w,half*h/w,-half,half);
		gluOrtho2D(0,2*half,0,2*half*h/w);
    } else {
		//如果宽度大于高度，则将宽度视角扩大，图形显示居中
        //glOrtho(-half*w/h,half*w/h,-half,half,-half,half);
		gluOrtho2D(0,2*half*w/h,0,2*half);
    }   
}
int main(int argc,char *argv[])
{                                            
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("机器人");
	glutDisplayFunc(&drawrobot);
	glutReshapeFunc(ChangeSize); 
	//该函数让GLUT框架开始运行，所有设置的回调函数开始工作，直到用户终止程序为止
	glutMainLoop();
	return 0;
}