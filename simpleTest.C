#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<string.h>
#include<math.h>
union REGS in , out;
//functions to start mouse
int initmouse() {
  in .x.ax = 0;
  int86(0X33, & in , & out);
  return (out.x.ax);
}
void showmouseptr() {
  in .x.ax = 1;
  int86(0X33, & in , & out);
}
int callmouse() {
  in .x.ax = 1;
  int86(51, & in , & out);
  return 1;
}
void mouseposi(int & xpos, int & ypos, int & click) {
  in .x.ax = 3;
  int86(51, & in , & out);
  click = out.x.bx;
  xpos = out.x.cx;
  ypos = out.x.dx;
}
int mousehide() {
  in .x.ax = 2;
  int86(51, & in , & out);
  return 1;
}
int main() {
  int gdriver = DETECT, gmode;
  int status;
  int i = 0;
  char str[30];
  clrscr();
  initgraph( & gdriver, & gmode, "c:\\turboc3\\bgi");
  outtextxy(100, 250, "When the red box turns green click as fast as possible");
  settextstyle(8, 0, 5);
  outtextxy(100, 150, "Reaction Time Test");
  delay(4000);
  cleardevice();
  //mouse pointer starter
  status = initmouse();
  if (status == 0)
    printf("Mouse support not available.\n");
  else
    showmouseptr();
  while (i < 5) {
    cleardevice();
    settextstyle(8, 0, 5);
    outtextxy(150, 150, "Wait for green");
    setbkcolor(4); //4:red
    //loop for click of mouse
    time_t endwait;
    time_t start = time(NULL);
    time_t seconds = 5; // end loop after this time has elapsed
    endwait = start + seconds;
    int x, y, cl = 0;
    int check = 0;
    int flag = 0;
    callmouse();
    do {
      check = 0;
      check = cl + 1;
      mouseposi(x, y, cl);
      start = time(NULL);
      if (cl == check) {
        cleardevice();
        setbkcolor(1); //1:blue
        settextstyle(8, 0, 5);
        outtextxy(225, 150, "Too soon");
        settextstyle(3, 0, 3);
        outtextxy(230, 250, "Wait for next try");
        i = i - 1;
        flag = 1;
      } } while (!kbhit() && start < endwait && flag == 0);
    if (flag != 1) {
      clock_t t;
      cl = 0;
      t = clock();
      cleardevice();
      settextstyle(8, 0, 5);
      setbkcolor(2); //2:green
      outtextxy(225, 150, "Click Now");
      do { check = 0;
        check = cl + 1;
        mouseposi(x, y, cl);
        start = time(NULL);
        if (cl == check) {
          cleardevice();
          setbkcolor(1); //1:blue
          t = clock() - t;
          double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
          sprintf(str, "%.4f", time_taken);
          strncat(str, "s", 2);
          settextstyle(8, 0, 5);
          outtextxy(250, 150, str);
          break; }
      } while (!kbhit());}
    delay(3000);
    i++;}
  settextstyle(3, 0, 3);
  outtextxy(220, 250, "Press any key to exit...");
  getch();
  return 0;
}
