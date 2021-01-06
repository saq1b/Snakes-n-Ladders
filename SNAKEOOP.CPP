#include <graphics.h>
#include <fstream.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
//#include <time.h>
const int fsize=1110;// btm=7;
int x=100, y=100, size=100, l[2][fsize], scr=-1, spd=11, dif;
void saveUser();
class food{
	static int fx, fy; // co-ord of food
	public:
	food(){}
	food(short, short);
	void rndm();
	void give_food();
//	void f(int);
};
int food::fx, food::fy;
void music()
{
  enum {c4=261,c4h=277,d4=294,d4h=311,e4=330,f4=349,f4h=370,g4=392,g4h=415,a4=440,a4h=466,b4=494,c5=523,c5h=554,d5=587,d5h=622,e5=659,f5=698,f5h=740,g5=784,g5h=831,a5=880,a5h=932,b5=988};
  int i=0;
  // Harry Potter
  int a[80]={b4,e5,g5,f5h,e5,b5,a5,f5h,e5,g5,f5h,d5h,f5h,b4,g4,b4,0};
  float t[100]={0.32967,0.549451,0.21978,0.384615,0.659341,0.384615,0.714286,0.934066,0.604396,0.164835,0.43956,0.714286,0.384615,0.714286,0.43956,0.7};
  st:

  {
    sound(a[i]);
    delay(t[i]*700);
    ++i;
  }
  if (a[i]==0){
    nosound();
    return;
//    exit(0);
  }
  goto st;
}
void food::give_food()
{
     ++scr;
     gotoxy(9,1); // Place to print score
     cout<<scr;
     if (scr%4==0)   // original value scr%10
	 spd--;          // Increase Speed (original line spd--)
     food(BLACK, 5); // remove previous
	if (spd<1)// || scr==20)  // default value scr 100
	{
//	   music();
	   gotoxy(10,10);
	   cout<<"You Win";
	   getch();
	   saveUser();
	   exit(0);
	}
     rndm();
     food(RED, 5); // give new
}
void food::rndm()
{
   randomize();
   fx=(rand()%620)+10;
   fy=(rand()%460)+10;
}
//                color     radius
void food::food(short fd, short rd)
{
   setcolor(fd);
   circle(fx,fy,rd);
   setfillstyle(1, fd);
   floodfill(fx,fy,fd);
}
void saveUser()
{
  char autograph[30];
  clearviewport();
  cout<<"We want your autograph ";
  cin.getline(autograph, 80);
  fstream ff("stars.txt", ios::out|ios::app);
  if (ff<0){
	cout<<"file == -1";
  }
  ff<<autograph<<endl;
  ff.close();
  ff.open("stars.txt", ios::in);
//  system("type stars.txt");
  ff.seekg(0);
  while(ff)
  {
    ff.getline(autograph,30);
    cout<<autograph<<endl;
  }
  ff.close();
  cout<<"\n\n\tYou're now one amongst our stars\n\tHit any key to exit";
  getch();
}
void f(int k,food o)	// navigation func
{
  static int arr_flr_pos=0;
  if (getpixel(x,y)==YELLOW)  // self bite
    {
      setcolor(RED);
      circle(x,y,4);
      circle(x,y,8);
      cout<<"	Misleaded - GAME OVER";
      delay(1000);
      getch();
      exit(0);
    }
    if (getpixel(x,y)==RED) // eat
    {
       o.give_food();
       sound(1000);
       delay(10);
       sound(2000);
       delay(10);
       nosound();
       // Elongate
       size+=10;
    }
    putpixel(x, y, YELLOW);
    putpixel(l[0][arr_flr_pos], l[1][arr_flr_pos], BLACK);
    l[0][arr_flr_pos]=x;  l[1][arr_flr_pos]=y;
    arr_flr_pos++;
    if (arr_flr_pos==size)
       arr_flr_pos=0;
    switch (k)
    {
      case 1 :
		--x;
		break;
      case 2 :
		--y;
		break;
      case 3 :
		++x;
		break;
      case 4 :
		++y;
		break;
    }
    if(x>640)
      x=0;
    if(x<0)
      x=640;
    if(y<0)
      y=480;
    if(y>480)
      y=0;
    delay(spd);
}
void WelcomeScreen()
{
    setcolor(YELLOW);
    int x=getmaxx()/2, y=getmaxy()/2;
//   line(10,10, 10,100);
    settextstyle(4,0,7);
    outtextxy(x-50,y-100,"Snake");
    settextstyle(1,0,2);
    setcolor(CYAN);
    outtextxy(100,y-30,"Instructions");
    setcolor(15);
    settextstyle(3,0,1);
    outtextxy(100,y,"Press Esc anytime to exit");
    outtextxy(100,y+30,"Score a 100 to win");
    for(int i=0; i<2*x; ++i)
    {
	putpixel(i, y-110, RED);
	putpixel(i, y+70, RED);
	delay(2);
    }
    i=y-110;
    int j=y+70;
    getch();
    while(i!=j)
    {
	setcolor(BLACK);
	line(0,i,2*x,i);
	++i;
	line(0,j,2*x,j);
	--j;
	setcolor(RED);
	line(0,i,2*x,i);
	line(0,j,2*x,j);
	delay(5);
    }
//    getch();
    music();
    setcolor(WHITE);
    clearviewport();
}
//union REGS i, o;
void main()
{
   clrscr();
   int gd = DETECT, gm, c;
   food _o;
   for (int j=0; j<size; j++)
   {
	l[0][j]=100;  // x co ord initial
	l[1][j]=j;    // y co ord
   }
   short p_k=4, prev=3;
   initgraph(&gd,&gm,"C:\\turboc3\\BGI");
   setcolor(WHITE);
   WelcomeScreen();
   line(0,0,0,480);      // Boundaries
   line(639,0,639,480);
   setcolor(14);
   line(100,0, 100,size-1); // Initial Snake Position
   cout<<"Score = "<<scr+1;
   _o.give_food();
   while(c!=27)
   {
    if (kbhit())  // when a key is pressed
    {
     c=getch();
    }
     if (c==72)  //119)    //w
	 p_k=2;
     if (c==75)//97)  //a
	 p_k=1;
     if (c==80)//115)  //s
	p_k=4;
     if (c==77)//100)  //d
	p_k=3;
     if( (p_k<3 && (p_k+2)==prev) )
       p_k+=2;
     else if( (p_k>2 && (p_k-2)==prev) )       // opp button
	p_k-=2;
     prev=p_k;
     f(p_k,_o);
   }
}