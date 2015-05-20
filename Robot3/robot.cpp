#include <gl\glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define PI 3.1415926
/* 每个图形最多的顶点数 */
#define MAX_VERTEX 10
/* 画的图形最多的个数 */
#define MAX_PLOY 10
/* 窗口长宽的一半 */
int halfWidth, halfHeight;
/* 绘制多边形的起始标志，0是开始绘制，1是结束绘制，初始为-1 */
int	drawStatus	= -1;
int	moveNum		= -1;
/* 定义点击点的x,y*/
int clickX, clickY;
/* 多边形结构体 */
struct polygon {
	/* 顶点坐标 */
	int	x[MAX_VERTEX];
	int	y[MAX_VERTEX];
	/* 定义第几个顶点 */
	int	verNum;
	GLubyte color[3];
};
/* 各种颜色 */
GLubyte border[3] = { 0, 0, 0 };
GLubyte grey[3] = { 195, 195, 195 };
GLubyte yellow[3] = { 255, 243, 0 };
GLubyte red[3] = { 237, 28, 36 };
GLubyte darkGrey[3] = { 126, 126, 126 };
GLubyte white[3] = { 255, 255, 255 };
GLubyte startBtn[3] = { 10, 10, 10 };
GLubyte endBtn[3] = { 20, 20, 20 };
GLubyte delBtn[3] = { 30, 30, 30 };
GLubyte moveBtn[3] = { 40, 40, 40 };
GLubyte storeBtn[3] = {50, 50, 50};
GLubyte loadBtn[3] = {55, 55, 55};
/* 当前颜色 */
GLubyte nowColor[3] = { 0, 0, 0 };
/* 声明多边形数组 */
polygon polygons[MAX_PLOY];
/* 记录画了几个多边形 */
int con = 0;

int min(int a,int b){
	if(a<b)
		return a;
	else
		return b;
}

int max(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}
/* 保存所有的图形 */
void savePolygons()
{
	FILE *fp;
	int i;
	if ((fp = fopen("shapes.txt", "w")) == NULL)
	{
		printf("不能打开文件!");
		return;
	}
	/* 保存一共多少个图形 */
	fprintf(fp, "%d", con);
	fprintf(fp, "\n");
	for (i = 0; i < con; i++){
		/* 保存颜色值 */
		fprintf(fp, "%d %d %d ", polygons[i].color[0], polygons[i].color[1], polygons[i].color[2]);
		/* 保存顶点数量 */
		fprintf(fp, "%d ", polygons[i].verNum);
		/* 保存顶点坐标 */
		for (int j = 0; j < polygons[i].verNum; j++)
			fprintf(fp, "%d ", polygons[i].x[j]);
		for (int m = 0; m < polygons[i].verNum; m++)
			fprintf(fp, "%d ", polygons[i].y[m]);
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("保存成功。\n");
}

/* 读取存档 */
void readPolygons()
{
	FILE *fp;
	int i;
	if ((fp = fopen("shapes.txt", "r")) == NULL)
	{
		printf("不能打开文件!");
		return;
	}
	fscanf(fp, "%d", &con);
	printf("count%d",con);
	fscanf(fp, "\n");
	for (i = 0; i < con; i++){
		/* 读取颜色值 */
		fscanf(fp, "%d %d %d ", &polygons[i].color[0], &polygons[i].color[1], &polygons[i].color[2]);
		/* 读取顶点数量 */
		fscanf(fp, "%d ", &polygons[i].verNum);
		/* 读取顶点坐标 */
		for (int j = 0; j < polygons[i].verNum; j++)
			fscanf(fp, "%d ", &polygons[i].x[j]);
		for (int k = 0; k < polygons[i].verNum; k++)
			fscanf(fp, "%d ", &polygons[i].y[k]);
		fscanf(fp, "\n");
	}
	fclose(fp);
	printf("读取成功。\n");

}

/* 绘制多边形 */
void glPolygons()
{
	if ( con >= 0 )
	{
		for ( int i = 0; i <= con; i++ )
		{
			/* 取到这个多边形 */
			polygon poly = polygons[i];
			/* 画封闭线 */
			glBegin( GL_LINE_LOOP );
			int num = poly.verNum;
			printf( "num:%d\n", num );
			for ( int j = 0; j < num; j++ )
			{
				glColor3ub( poly.color[0], poly.color[1], poly.color[2] );
				glVertex2d( poly.x[j] - halfWidth, halfHeight - poly.y[j] );
				printf( "polyx:%d,polyy:%d", poly.x[j], poly.y[j] );
			}
			/* 结束画线 */
			glEnd();
			/* 刷新 */
			glFlush();
		}
	}
}


/* 绘制填充的圆形 */
void glColorCircle( int x, int y, int R, GLubyte color[3] )
{
	/* 开始绘制曲线 */
	glBegin( GL_POLYGON );
	/* 设置颜色 */
	glColor3ub( color[0], color[1], color[2] );
	/* 每次画增加的弧度 */
	double delta_angle = PI / 180;
	/* 画圆弧 */
	for ( double i = 0; i <= 2 * PI; i += delta_angle )
	{
		/* 绝对定位加三角函数值 */
		double	vx	= x + R * cos( i );
		double	vy	= y + R*sin( i );
		glVertex2d( vx, vy );
	}
	/* 结束绘画 */
	glEnd();
	glFlush();
}


/* 画矩形，传入的是左下角XY坐标和右上角XY坐标 */
void glRect( int leftX, int leftY, int rightX, int rightY )
{
	/* 画封闭曲线 */
	glBegin( GL_LINE_LOOP );
	/* 左下角 */
	glVertex2d( leftX, leftY );
	/* 右下角 */
	glVertex2d( rightX, leftY );
	/* 右上角 */
	glVertex2d( rightX, rightY );
	/* 左上角 */
	glVertex2d( leftX, rightY );
	/* 结束画线 */
	glEnd();
}


/* 画圆角矩形，传入矩形宽高，角半径，矩形中心点坐标 */
void glRoundRec( int centerX, int centerY, int width, int height, float cirR )
{
	/* 二分之PI，一个象限的角度 */
	float PI_HALF = PI / 2;
	/* 划分程度,值越大画得越精细 */
	float divide = 20.0;
	/* 圆角矩形的坐标 */
	float tx, ty;
	/* 画封闭曲线 */
	glBegin( GL_LINE_LOOP );
	/* 四个象限不同的操作符 */
	int	opX[4]	= { 1, -1, -1, 1 };
	int	opY[4]	= { 1, 1, -1, -1 };
	/* 用来计数，从第一象限到第四象限 */
	float x = 0;
	/* x自增时加的值 */
	float part = 1 / divide;
	/* 计算内矩形宽高一半的数值 */
	int	w	= width / 2 - cirR;
	int	h	= height / 2 - cirR;
	/* 循环画线 */
	for ( x = 0; x < 4; x += part )
	{
		/* 求出弧度 */
		float rad = PI_HALF * x;
		/* 计算坐标值 */
		tx	= cirR * cos( rad ) + opX[(int) x] * w + centerX;
		ty	= cirR * sin( rad ) + opY[(int) x] * h + centerY;
		/*传入坐标画线 */
		glVertex2f( tx, ty );
	}
	/* 结束画线 */
	glEnd();
}


/* 画弧线，相对偏移量XY，开始的弧度，结束的弧度，半径 */
void glArc( double x, double y, double start_angle, double end_angle, double radius )
{
	/* 开始绘制曲线 */
	glBegin( GL_LINE_STRIP );
	/* 每次画增加的弧度 */
	double delta_angle = PI / 180;
	/* 画圆弧 */
	for ( double i = start_angle; i <= end_angle; i += delta_angle )
	{
		/* 绝对定位加三角函数值 */
		double	vx	= x + radius * cos( i );
		double	vy	= y + radius*sin( i );
		glVertex2d( vx, vy );
	}
	/* 结束绘画 */
	glEnd();
}


/* 画圆 */
void glCircle( double x, double y, double radius )
{
	/* 画全圆 */
	glArc( x, y, 0, 2 * PI, radius );
}


/* 画三角形，传入三个点的坐标 */
void glTri( int x1, int y1, int x2, int y2, int x3, int y3 )
{
	/* 画封闭线 */
	glBegin( GL_LINE_LOOP );
	/* 一点 */
	glVertex2d( x1, y1 );
	/* 二点 */
	glVertex2d( x2, y2 );
	/*三点 */
	glVertex2d( x3, y3 );
	/* 结束画线 */
	glEnd();
}


/* 画线，传入两点坐标 */
void glLine( int x1, int y1, int x2, int y2 )
{
	/* 画封闭线 */
	glBegin( GL_LINE_STRIP );
	/* 一点 */
	glVertex2d( x1, y1 );
	/* 二点 */
	glVertex2d( x2, y2 );
	/* 结束画线 */
	glEnd();
}


/* 函数用来画图 */
void display( void )
{
	/* GL_COLOR_BUFFER_BIT表示清除颜色 */
	glClear( GL_COLOR_BUFFER_BIT );
	/* 设置画线颜色 */
	glColor3f( 0.5, 0.5, 0.5 );
	/* 画点大小 */
	glPointSize( 2 );
	/* 画圆角矩形，大肚子 */
	glRoundRec( 0, 0, 146, 120, 15 );
	/* 画圆，中间小圈 */
	glCircle( 0, 0, 10 );
	/* 画矩形，脖子 */
	glRect( -25, 60, 25, 76 );
	/* 画圆角矩形，大脸 */
	glRoundRec( 0, 113, 128, 74, 10 );
	/* 两个眼睛 */
	glCircle( -30, 111, 10 );
	glCircle( 30, 111, 10 );
	/* 两条天线 */
	glLine( -35, 150, -35, 173 );
	glLine( 35, 150, 35, 173 );
	/* 圆角矩形，两个耳朵 */
	glRoundRec( 81, 115, 20, 34, 5 );
	glRoundRec( -81, 115, 20, 34, 5 );
	/* 圆弧，画嘴 */
	glArc( 0, 133, 11 * PI / 8, 13 * PI / 8, 45 );
	/* 画三角，肚子里的三角 */
	glTri( -30, -15, 30, -15, 0, 28 );
	/* 画矩形，胳膊连接处 */
	glRect( -81, 43, -73, 25 );
	glRect( 81, 43, 73, 25 );
	/* 画矩形，上臂 */
	glRect( -108, 45, -81, 0 );
	glRect( 108, 45, 81, 0 );
	/* 画矩形，中臂 */
	glRect( -101, 0, -88, -4 );
	glRect( 101, 0, 88, -4 );
	/* 画矩形，下臂 */
	glRect( -108, -4, -81, -37 );
	glRect( 108, -4, 81, -37 );
	/* 画圆形，手掌 */
	glCircle( -95, -47, 10 );
	glCircle( 95, -47, 10 );

	/* 绘制取色盘 */
	glColorCircle( -280, 280, 10, red );
	glColorCircle( -250, 280, 10, yellow );
	glColorCircle( -220, 280, 10, grey );
	glColorCircle( -180, 280, 10, nowColor );
	glColorCircle( 250, 280, 10, startBtn );
	glColorCircle( 280, 280, 10, endBtn );
	glColorCircle( 220, 280, 10, delBtn );
	glColorCircle( 190, 280, 10, moveBtn );
	glColorCircle( 160, 280, 10, storeBtn );
	glColorCircle( 130, 280, 10, loadBtn );

	/* 保证前面的OpenGL命令立即执行，而不是让它们在缓冲区中等待 */
	/* 绘制多边形 */
	glPolygons();
	glFlush();
}


/* 窗口大小变化时调用的函数 */
void ChangeSize( GLsizei w, GLsizei h )
{
	/* 避免高度为0 */
	if ( h == 0 )
	{
		h = 1;
	}
	/* 定义视口大小，宽高一致 */
	glViewport( 0, 0, w, h );
	int half = 300;
	/* 定义宽高的一半 */
	halfHeight	= 300;
	halfWidth	= 300;
	/* 重置坐标系统，使投影变换复位 */
	glMatrixMode( GL_PROJECTION );
	/* 将当前的用户坐标系的原点移到了屏幕中心 */
	glLoadIdentity();
	/* 定义正交视域体 */
	if ( w < h )
	{
		/* 如果高度大于宽度，则将高度视角扩大，图形显示居中 */
		glOrtho( -half, half, -half * h / w, half * h / w, -half, half );
	} else {
		/* 如果宽度大于高度，则将宽度视角扩大，图形显示居中 */
		glOrtho( -half * w / h, half * w / h, -half, half, -half, half );
	}
}


/* 判断两个颜色是否相等 */
bool sameColor( GLubyte color1[3], GLubyte color2[3] )
{
	if ( color1[0] - color2[0] < 5 && color1[1] - color2[1] < 5 && color1[2] - color2[1] < 5 )
	{
		return(true);
	} else {
		return(false);
	}
}


/* 画点 */
void glPoints( int x, int y )
{
	glBegin( GL_POINTS );
	/* 点直接设置为黑色 */
	glColor3ub( 0, 0, 0 );
	glVertex2d( x - halfWidth, halfHeight - y );
	glEnd();
	glFlush();
}


/* 判断一个点是否在多边形内部 */
bool pointInPoly( polygon poly, int x, int y )
{
	int nCross = 0;
	for ( int i = 0; i < poly.verNum; i++ )
	{
		int	p1x	= poly.x[i];
		int	p1y	= poly.y[i];
		int	p2x	= poly.x[(i + 1) % poly.verNum];
		int	p2y	= poly.y[(i + 1) % poly.verNum];
		/* 平行或在延长线上，忽略 */
		if ( p1y == p2y || y < min( p1y, p2y ) || y > max( p1y, p2y ) )
		{
			continue;
		}
		/* 计算交点横坐标 */
		double m = (double) (y - p1y) * (double) (p2x - p1x) / (double) (p2y - p1y) + p1x;
		if ( m > x )
			nCross++;
	}
	return(nCross % 2 == 1);
}


/* 移动多边形 */
void movePoly( int x, int y )
{
	/* 取到要移动的图形 */
	int verNum = polygons[moveNum].verNum;
	printf( "verNum%d,x%d,y%d,clickX%d,clickY%d\n", verNum, x, y, clickX, clickY );
	for ( int i = 0; i < verNum; i++ )
	{
		polygons[moveNum].x[i]	+= (x - clickX);
		polygons[moveNum].y[i]	+= (y - clickY);
		printf( "polyx%d\n", polygons[moveNum].x[i] );
	}
	/* 移动完毕之后重新记录当前的点 */
	clickX	= x;
	clickY	= y;
	/* 重新绘制 */
	glutPostRedisplay();
}


/* 删除多边形 */
void removePoly( int index )
{
	if ( index > con )
	{
		printf( "Out Of Index\n" );
	}
	for ( int i = index; i < con; i++ )
	{
		polygons[i] = polygons[i + 1];
	}
	con--;
}


/* 删除多边形 */
void deletePoly( int x, int y )
{
	int delenum = -1;
	for ( int i = 0; i < con; i++ )
	{
		if ( pointInPoly( polygons[i], x, y ) )
		{
			delenum = i;
		}
	}
	if ( delenum != -1 )
	{
		removePoly( delenum );
	}
	/* 重新绘制 */
	glutPostRedisplay();
}


/* 鼠标点击事件 */
void mouseClick( int btn, int state, int x, int y )
{
	/* 赋值全局变量 */
	clickX	= x;
	clickY	= y;
	/* 选项卡的分界范围 */
	int	optionHeight	= 40;
	int	optionWidth	= 250;
	if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		/* 如果在颜色选项卡中点击 */
		if ( y < optionHeight && x < optionWidth )
		{
			glReadPixels( x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &nowColor );
			/* 设置绘图颜色并显示当前取色板颜色 */
			glColorCircle( -180, 280, 10, nowColor );
			/* 如果点击的是右侧选项按钮 */
		}else if ( y < optionHeight && x > optionWidth )
		{
			/* 取当前的点 */
			GLubyte color[3];
			glReadPixels( x, 2 * halfHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color );
			/* 如果点击了开始绘制的按钮 */
			if ( sameColor( color, startBtn ) )
			{
				drawStatus = 0;
				/* 开始画一个图形，顶点个数置零 */
				polygons[con].verNum = 0;
				/* 如果点击了结束绘制的按钮 */
			} else if ( sameColor( color, endBtn ) )
			{
				glutPostRedisplay();
				/* 画的图形个数加一 */
				con++;
			} else if ( sameColor( color, delBtn ) )
			{
				/* 删除时设置drawStatus为2 */
				drawStatus = 2;
			} else if ( sameColor( color, moveBtn ) )
			{
				/* 移动时设置drawStatus为3 */
				drawStatus = 3;
			} else if ( sameColor( color, storeBtn ) )
			{
				/* 存盘时设置drawStatus为4 */
				drawStatus = 4;
				glutPostRedisplay();
				savePolygons();
			} else if ( sameColor( color, loadBtn ) )
			{
				/* 读盘时设置drawStatus为5 */
				drawStatus = 5;
				readPolygons();
				glutPostRedisplay();
			}

			/* 如果点击的是下方的绘图页面 */
		}else{
			/* 如果当前是正在取点状态 */
			if ( drawStatus == 0 )
			{
				/* 保存每个点，然后该图形顶点个数加一 */
				polygons[con].x[polygons[con].verNum]	= x;
				polygons[con].y[polygons[con].verNum]	= y;
				/* 画点 */
				glPoints( x, y );
				/* 设置当前颜色RGB，如果取色有变动，以最后的取色为准 */
				polygons[con].color[0]	= nowColor[0];
				polygons[con].color[1]	= nowColor[1];
				polygons[con].color[2]	= nowColor[2];
				polygons[con].verNum++;
			}else if ( drawStatus == 2 )
			{
				/* 删除图形 */
				deletePoly( x, y );
			} else if ( drawStatus == 3 )
			{
				moveNum = -1;
				for ( int i = 0; i < con; i++ )
				{
					if ( pointInPoly( polygons[i], x, y ) )
					{
						moveNum = i;
					}
				}
			}
		}
	}
}


/* 鼠标移动事件 */
void mouseMove( int x, int y )
{
	if ( drawStatus == 3 && moveNum != -1 )
	{
		printf( "move x:%d,y:%dmoveNum:%d\n", x, y, moveNum );
		movePoly( x, y );
	}
}


/*程序入口 */
int main( int argc, char *argv[] )
{
	/* 对GLUT进行初始化，并处理所有的命令行参数 */
	glutInit( &argc, argv );
	/* 指定RGB颜色模式和单缓冲窗口 */
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	/* 定义窗口的位置 */
	glutInitWindowPosition( 100, 100 );
	/* 定义窗口的大小 */
	glutInitWindowSize( 600, 600 );
	/* 创建窗口，同时为之命名 */
	glutCreateWindow( "OpenGL" );
	/* 设置窗口清除颜色为白色 */
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	/* 参数为一个函数，绘图时这个函数就会被调用 */
	glutDisplayFunc( &display );
	/* 参数为一个函数，当窗口大小改变时会被调用 */
	glutReshapeFunc( ChangeSize );
	/*鼠标点击事件，鼠标点击或者松开时调用 */
	glutMouseFunc( mouseClick );
	/*鼠标移动事件，鼠标按下并移动时调用 */
	glutMotionFunc( mouseMove );
	/* 该函数让GLUT框架开始运行，所有设置的回调函数开始工作，直到用户终止程序为止 */
	glutMainLoop();
	/*程序返回 */
	return(0);
}