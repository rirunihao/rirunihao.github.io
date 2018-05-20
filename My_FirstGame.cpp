#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>

typedef struct position
{
	int x;
	int y;
} posType;

#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)

void init(void);  // 初始化界面
void gamebegin(void);  //游戏开始界面
void gameplay(void);   //玩游戏的具体过程
void close(void);   //释放资源
void drawcursor(posType,COLORREF); //重绘光标
void drawtime(int);  //重绘时间
void drawscore(int); //重绘分数
void getsamecolorballs(posType,COLORREF); //获取同色小球
int isValid(posType cur,COLORREF cl); //判断是否合法
void ballsfall(); //小球下落

COLORREF colorArr[6]={RGB(200,0,0),RGB(0,200,0),RGB(0,0,200),
						RGB(200,200,0),RGB(200,0,200),RGB(0,200,200)};

posType cur; //当前光标所在位置
posType ballsArr[180]; //同色小球坐标
int index;  //同色小球的个数

void main()
{
	init();
	gamebegin();
	gameplay();
	close();
}

void init()
{
	initgraph(1000,700);
}

void gamebegin()
{
	//绘制边框
	setlinecolor(RGB(50,50,50));
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 10);
	rectangle(255,45,745,655);
	//绘制小球		
	setlinestyle(PS_SOLID);
	srand((unsigned) time(NULL));  //提供随机数种子
	for(int x=280;x<740;x+=40)
	{
		for(int y=70;y<650;y+=40)
		{
			COLORREF cl=colorArr[rand()%6];
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(x,y,18);
		}
	}
	//绘制光标
	cur.x=480;
	cur.y=390;
	drawcursor(cur,RGB(255,255,255));
	//绘制时间
	drawtime(30);
	//绘制分数
	drawscore(0);
}

void gameplay()
{
	int score=0;
	for(int i=299;i>-1;i--)
	{
		if(i%10==0)
		{
			drawtime(i/10);
		}
		if(KEY_DOWN(VK_UP)&&cur.y>70)
		{
			drawcursor(cur,RGB(0,0,0));
			cur.y-=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_DOWN)&&cur.y<630)
		{
			drawcursor(cur,RGB(0,0,0));
			cur.y+=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_LEFT)&&cur.x>280)
		{
			drawcursor(cur,RGB(0,0,0));
			cur.x-=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_RIGHT)&&cur.x<720)
		{
			drawcursor(cur,RGB(0,0,0));
			cur.x+=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_RETURN)||KEY_DOWN(VK_SPACE))
		{
			 //获得光标所在位置周围的同色小球坐标，存入数组，并记录个数
			 getsamecolorballs(cur,getpixel(cur.x,cur.y));

			 //将数组中元素依次置黑一段时间
			 if(index>1)
			 {
				 for(int k=0;k<index;k++)
				 {
					setlinecolor(RGB(0,0,0));
					setfillcolor(RGB(0,0,0));
					fillcircle(ballsArr[k].x,ballsArr[k].y,18);
				 }
				 Sleep(500);
				 //上方的小球下落
				 ballsfall();
				 //刷新分数
				 score+=index;
				 drawscore(score);
			 }
			 
			 index=0;			 
		}

		Sleep(100);
	}
	//游戏结束
	cleardevice();
	settextcolor(RGB(255,0,0));
	settextstyle(80, 0, _T("黑体"));
	outtextxy(300, 330, "Game Over");
	drawscore(score);
}

void close()
{
	getch();
	closegraph();
}

void drawcursor(posType cur,COLORREF cl)
{
	setlinecolor(cl);
	rectangle(cur.x-20,cur.y-20,cur.x+20,cur.y+20);
}

void drawtime(int sec)
{
	char str[30];
	settextcolor(RGB(255,255,0));
	settextstyle(25, 0, _T("黑体"));
	sprintf(str,"剩余时间：%2d s",sec);   
	outtextxy(30, 50, str);
}

void drawscore(int score)
{
	char str[30];
	settextcolor(RGB(255,0,0));
	settextstyle(25, 0, _T("黑体"));
	sprintf(str,"分数：%d",score);
	outtextxy(30, 600, str);
}

void getsamecolorballs(posType cur,COLORREF cl) //《数据结构》---迷宫求解
{
	ballsArr[index].x=cur.x;
	ballsArr[index].y=cur.y;
	index++;
	
	posType tmpPos;   
	for(int k=0;k<4;k++)
	{
		switch(k)
		{
			case 0:tmpPos.x=cur.x;tmpPos.y=cur.y-40;break; //上
			case 1:tmpPos.x=cur.x;tmpPos.y=cur.y+40;break; //下
			case 2:tmpPos.x=cur.x-40;tmpPos.y=cur.y;break; //左
			case 3:tmpPos.x=cur.x+40;tmpPos.y=cur.y;break; //右
		}

		if(isValid(tmpPos,cl))
		{
			getsamecolorballs(tmpPos,cl);
		}
	}
}

int isValid(posType cur,COLORREF cl)
{
	if(getpixel(cur.x,cur.y)!=cl)
	{
		return 0;
	}
	else
	{
		for(int i=0;i<index;i++)  //判断数组中之前是否已存在
		{
			if(cur.x==ballsArr[i].x&&cur.y==ballsArr[i].y)
			{
				return 0;
			}
		}
		return 1;
	}
}

void turn()
{
	int i,j;posType temp;
	for(j=0;j<index-1;j++)
	for(i=0;i<index-1-j;i++)
	{
		if(ballsArr[i].x>ballsArr[i+1].x)
		{
			temp=ballsArr[i];
			ballsArr[i]=ballsArr[i+1];
			ballsArr[i+1]=temp;
		}
		if(ballsArr[i].y>ballsArr[i+1].y)
		{
			temp=ballsArr[i];
			ballsArr[i]=ballsArr[i+1];
			ballsArr[i+1]=temp;
		}
	}
}

void ballsfall()
{
	turn();
	for(int i=0;i<index;i++)
	{
		for(int k=ballsArr[i].y;k>70;k-=40)
		{
			COLORREF cl=getpixel(ballsArr[i].x,k-40);
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(ballsArr[i].x,k,18);
		}
		COLORREF cl=colorArr[rand()%6];
		setlinecolor(cl);
		setfillcolor(cl);
		fillcircle(ballsArr[i].x,70,18);
	}
}
