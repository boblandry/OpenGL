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

//��ֱ��
void glLine(int x1,int y1,int x2,int y2){
    glBegin(GL_LINE_STRIP);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glEnd();
}
//�������Σ����������������
void glTri(int x1,int y1,int x2,int y2,int x3,int y3,int MODE){
    glBegin(MODE);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}
//�����Σ�����������½�XY��������Ͻ�XY����
void glRect(int leftX,int leftY,int rightX,int rightY,int MODE){
    glBegin(MODE);
	glVertex2d(leftX,leftY);
	glVertex2d(rightX,leftY);
	glVertex2d(rightX,rightY);
	glVertex2d(leftX,rightY);
	glEnd();
}
//�����ߣ����ƫ����XY����ʼ�Ļ��ȣ������Ļ��ȣ��뾶
void glArc(double x,double y,double start_angle,double end_angle,double radius,int MODE)
{   
	glBegin(MODE);
	double delta_angle=PI/180;
	//��Բ��
	for (double i=start_angle;i<=end_angle;i+=delta_angle)
	{
		//���Զ�λ�����Ǻ���ֵ
		double vx=x+radius * cos(i);
		double vy=y+radius*sin(i);
		glVertex2d(vx,vy);
	}
	glEnd();
}
//��Բ
void glCircle(double x, double y, double radius,int MODE)  
{  
    glArc(x,y,0,2*PI,radius,MODE);  
}  

//��Բ�Ǿ��Σ�������ο�ߣ��ǰ뾶���������ĵ�����
void glRoundRec(int centerX,int centerY,int width,int height,float cirR,int MODE){
	float PI_HALF = PI/2;
	//���̶ֳ�,ֵԽ�󻭵�Խ��ϸ
	float divide=20.0;
	//Բ�Ǿ��ε�����
    float tx,ty; 
    glBegin(MODE);
	//�ĸ����޲�ͬ�Ĳ�����
    int opX[4]={1,-1,-1,1};
    int opY[4]={1,1,-1,-1};
	//�����������ӵ�һ���޵���������
    float x=0;
	//x����ʱ�ӵ�ֵ
	float part=1/divide;
	//�����ھ��ο��һ�����ֵ
	int w=width/2-cirR;
	int h=height/2-cirR;
	//ѭ������
    for(x=0;x<4;x+=part){
		//�������
		float rad = PI_HALF*x;
		//��������ֵ
	    tx=cirR*cos(rad)+opX[(int)x]*w+centerX;
	    ty=cirR*sin(rad)+opY[(int)x]*h+centerY;
	    glVertex2f(tx,ty);
	}
   glEnd();
}


//�����������Σ���ֵΪ��ʱ��
void glFillTri(int x1,int y1,int x2,int y2,int x3,int y3,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glTri(x1,y1,x2,y2,x3,y3,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glTri(x1+lineWidth/2,y1+lineWidth/2,x2-lineWidth/2,y2+lineWidth/2,x3,y3-lineWidth/2,GL_POLYGON);
}

//������Բ�Ǿ���
void glFillRoundRec(int centerX,int centerY,int width,int height,float cirR,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glRoundRec(centerX,centerY,width,height,cirR,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glRoundRec(centerX,centerY,width-lineWidth/2,height-lineWidth/2,cirR,GL_POLYGON);
}

//������Բ��
void glFillCircle(double x, double y, double radius,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glCircle(x,y,radius,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glCircle(x,y,radius-lineWidth/2,GL_POLYGON);
}

//�����ľ��Σ��������ϽǺ����½ǵ�����
void glFillRect(int leftX,int leftY,int rightX,int rightY,int color[3]){
	glColor3ub(black[0],black[1],black[2]);
	glRect(leftX,leftY,rightX,rightY,GL_LINE_LOOP);
	glColor3ub(color[0],color[1],color[2]);
	glRect(leftX+lineWidth/2,leftY-lineWidth/2,rightX-lineWidth/2,rightY+lineWidth/2,GL_POLYGON);
}
void drawrobot(void){
	glClearColor(1.0,1.0,1.0,0);//�������ɫ����Ϊ��ɫ
	glClear(GL_COLOR_BUFFER_BIT);//�����ڱ�������Ϊ��ǰ�����ɫ
	glColor3f(0.0,0.0,0.0);
	//gluOrtho2D(-300.0, 300.0, -300.0, 300.0);//�趨�������½Ǻ����Ͻǵ�xy����
	gluOrtho2D(0, 600.0,0, 600.0);
	glViewport(0,0,600,600);
	//ע��Ḳ��
	glFillRoundRec(300,300,200,160,20,grey);//������Բ�Ǿ���
	glFillTri(266,280,334,280,300,340,yellow);//����ɫ������
	glFillCircle(300,300,10,red);//����ɫԲ��
	glFillRect(275,380,325,400,grey);//������
	glLine(340,500,340,530);
	glLine(260,500,260,530);//������
	glFillRoundRec(300,450,160,100,20,grey);//����
	glFillCircle(330,450,12,white);
	glFillCircle(270,450,12,white);//���۾�
	glArc(300,435,5*PI/4,7*PI/4,20,GL_LINE_STRIP);//����
	glFillRoundRec(390,450,20,50,5,darkgrey);
	glFillRoundRec(210,450,20,50,5,darkgrey);//������
	//������
	glFillRect(400,330,410,350,grey);
	glFillRect(410,290,450,360,darkgrey);
	glFillRect(420,280,440,290,grey);
	glFillRect(410,230,450,280,darkgrey);
	glFillCircle(430,220,10,grey);
	//������
	glFillRect(190,330,200,350,grey);
	glFillRect(150,290,190,360,darkgrey);
	glFillRect(160,280,180,290,grey);
	glFillRect(150,230,190,280,darkgrey);
	glFillCircle(170,220,10,grey);
	//���ҽ�
	glFillRect(330,210,350,220,grey);
	glFillRoundRec(340,175,40,70,10,darkgrey);
	glFillRect(330,130,350,140,grey);
	glFillRect(315,110,365,130,darkgrey);
	//�����
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
	//glRotatef(45,0,0,1);//��Z����ת
	glFlush();
}
//���ڴ�С�仯ʱ���õĺ���
void ChangeSize(GLsizei w,GLsizei h)  
{  
	//����߶�Ϊ0
    if(h==0) {  
        h=1;  
    }  
    //�����ӿڴ�С�����һ��  
    glViewport(0,0,w,h);
	int half = 300;
	//��������ϵͳ��ʹͶӰ�任��λ
    glMatrixMode(GL_PROJECTION); 
	//����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ����
    glLoadIdentity();  
   //��������������  
    if(w<h) {
		//����߶ȴ��ڿ�ȣ��򽫸߶��ӽ�����ͼ����ʾ����
        //glOrtho(-half,half,-half*h/w,half*h/w,-half,half);
		gluOrtho2D(0,2*half,0,2*half*h/w);
    } else {
		//�����ȴ��ڸ߶ȣ��򽫿���ӽ�����ͼ����ʾ����
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
	glutCreateWindow("������");
	glutDisplayFunc(&drawrobot);
	glutReshapeFunc(ChangeSize); 
	//�ú�����GLUT��ܿ�ʼ���У��������õĻص�������ʼ������ֱ���û���ֹ����Ϊֹ
	glutMainLoop();
	return 0;
}