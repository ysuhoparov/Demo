#define MAIN
#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <bios.h>
#include <mem.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <graphics.h>
#include <time.h>

#include "kl.h"       // Location and Point class declarations
#include "key.h"

extern unsigned int k, pg, F, lPlan, FlPlan;
int topPage=0;
extern char *temp,old;

unsigned int ix=0, iy=1;
extern unsigned int plTop[];

extern char *fplan[];
extern char *tplan[]; //   { "Полировка","Шлифовка" };
menu M;


extern char far *plan;
extern char far *krd;
extern char far *kr;
extern char far *wbuf;
extern int ldFil( char *file, char *buf, unsigned int n);
extern int wrFil( char *file, char *buf, unsigned int n);
extern void contur();

extern union REGS reg;
extern int LoadScr( char *, int);
//extern int LoadBlock(char *,char *,int);
//extern int WriteBlock(char *,char *,int);
extern void day(void);
//extern void date(void);
//extern void times(void);
extern int getkey(void);
extern void save_win( int x, int y, int xend, int yend, char *buf);
extern void restore_win( int x, int y, int xend, int yend, char *buf);
extern void outtext(char *, unsigned char,unsigned char, unsigned char, unsigned char );
extern void rel();

extern char *conf;
char *passw="               ";

Conw::Conw()
{
Num=0;             // текущ. плита
pNumb=0;           // кол-во плит на конвейере
newNum=0;          // номер новой (последней) плиты на конвейере
pNum[0]=23;        // массив номеров плит, находящихся на конвейере
}

void Conw::SmallCon(int color) {
 x=348; y=320-16*(Num);
 setlinestyle(0,0,0);
 if( color==14) setcolor(15); else setcolor(0);
 line(x-6,y+2,x-6,y+10); line(x+22,y+2,x+22,y+10); rectangle(x-5,y,x+21,y+12);
 if( color==14) setcolor(4); else setcolor(0);
 sprintf(temp,"%2d",pNum[Num]); settextstyle(0,0,0);
 if (pNum[Num]<10) outtextxy(x-4,y+3,temp);
   else outtextxy(x,y+3,temp);      /* Num */
}

void Conw::drawConw(void) {
static int colrh[11] = { 2,3,9,5,6,15,14,13,12,11,10 };
for (j=0; j < pNumb; j++)
  { x=348; y=320-16*(j);  setlinestyle(0,0,0);
     for (i=1; i<=12; i++) { setcolor(colrh[i-1]); line(x-4,y+i,x+20,y+i); }
 if( j==Num) setcolor(15); else setcolor(0);
    line(x-6,y+2,x-6,y+10); line(x+22,y+2,x+22,y+10);
    rectangle(x-5,y,x+21,y+12);
 if( j==Num) setcolor(4); else setcolor(0);
    sprintf(temp,"%2d",pNum[j]); settextstyle(0,0,0);
    if (pNum[j]<10) outtextxy(x-4,y+3,temp);
    else outtextxy(x,y+3,temp);      /* Num */
   }
}

void Conw::newPl() {
  //if (pNum[0]==newNum) return;
  pNumb++; if (pNumb > 20)  pNumb=20;
  Num++; if (Num > 19) Num=19;
  for (j=pNumb; j > 0; j--) pNum[j]=pNum[j-1]; // передвинуть массив номеров плит
  pNum[0]=newNum; if(F<noDraw) drawConw(); //contur();  rel();
}

void Conw::delPl() {
 if (pNumb > 0) pNumb--;
 if (Num >= pNumb)  Num=pNumb-1;
  else for (j=Num; j <= pNumb; j++) pNum[j]=pNum[j+1]; // передвинуть массив номеров плит
 setfillstyle(1,8); bar(338,6,375,343);
 drawConw();  contur();  rel();
}

void Conw::plNum() {
  sprintf(temp," Плита N %2d ",pNum[Num]);  outtext(temp, 11,4, 0,2);
}



void ldPlan() {
 if (!ldFil(fplan[FlPlan],plan,0xffff)) {  M.Error(11+FlPlan);
  strcpy(plan,"  0    8   660   450  1234567  1234567  35  111111      44  ");
   *(plan+59)=0; *(plan+60)='Z';
 }
 outtext(tplan[FlPlan],12,1,2,64);
 unsigned int j=1;
  while(*(plan+j++) != 'Z') {
   if((*(plan+j) == 10)||(*(plan+j) == 13)) *(plan+j)=0;
   if(j%60==0) *(plan+j-1) = 0;
  }  lPlan=j/60;
} //void ldPlan

void typePlan() {
   setcolor(0);    settextstyle(0,0,0);
   for (int i= 0; i<=30; i++)
       if(*(plan+(topPage+i)*60)== 'Z') break;
        else {
          strcpy(temp,plan+(topPage+i)*60);
          *(temp+38)=*(temp+39)=*(temp+50)=*(temp+51)=32;
          outtextxy(16,45+i*10,temp); }
} //void typePlan()

int xBeg[10] = {14,48,92,138,188,260,332,364,428};
int xEnd[10] = {41,84,130,180,252,324,356,420,482};
int tBeg[10] = {16,56,96,144,192,264,336,368,432};
int tNumb[10] = {3,3,4,4,7,7,2,6,6};
//               2 7  12  18  24 32  42   46  54
void  Plan() {
unsigned int i,j; int pos=0; char *st=" _"; char *str="          "; char cr=0;
//char *msg5 = "N  Пpио- Размеp, mm    План    Выпол-   %   Оста-   Дата ";
//char *msg6 = "   pитетдлина шиpина    m      нено,m       ток,m   оконч";
    LoadScr("pg1.pak",1);
       setactivepage(1);    pg=1;
 outtext(tplan[FlPlan],12,1,2,64);
/*   setfillstyle(1,7);     bar(0,0,492,349);
   setcolor(0);       rectangle(4,4,490,345);
   //setfillstyle(1,1);     bar(495,1,634,345);
   rectangle(8,8,486,345); line(8,42,485,42);
   outtext(msg5, 7,7, 1,3);   outtext(msg6, 7,7, 2,3);
    line(44,8,44,345);         line(88,8,88,345);
    line(134,30,134,345);      line(184,8,184,345);
    line(256,8,256,345);       line(328,8,328,345);
    line(360,8,360,345);       line(432,8,432,345); */
   setcolor(0);    settextstyle(0,0,0);
   reg.x.ax=0x0501; int86(0x10,&reg,&reg); old--;
    setvisualpage(1);  typePlan();
   cr=14; pos=0;
   outtext(tplan[FlPlan],12,1,2,64);
   setcolor(cr);  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
     while (k!=F9)
 { day(); k=bioskey(1); if (k!=0) {  k=bioskey(0);
        switch(k)
   { case Enter :
     if (cr==14) { k=0; break; }
     if (pos) {
      for (i=tNumb[ix]; i>0; i--) { pos--;
        if (pos >= 0)
               *(plan+(topPage+iy)*60+tBeg[ix]/8+i-3) = str[pos];
         else  *(plan+(topPage+iy)*60+tBeg[ix]/8+i-3) = 32; }
   if (ix < 8) {
     setcolor(7);   setlinestyle(0,0,1);
     rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
     setfillstyle(1,7); bar(xBeg[ix]+1,45+iy*10,xEnd[ix]-1,52+iy*10);
     setcolor(cr);    ix++;
     rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
    case ESC:
   setfillstyle(1,7); bar(xBeg[ix]+1,45+iy*10,xEnd[ix]-1,52+iy*10);
           char *tem= (plan+(topPage+iy)*60);
          *(tem+38)=*(tem+39)=*(tem+50)=*(tem+51)=32;
          setcolor(0); outtextxy(16,45+iy*10,plan+(topPage+iy)*60);
   setcolor(cr); pos=0; }
         break;
    case BackSp :
   if (pos)
    { setfillstyle(1,7); str[--pos]=0;
     if( pos==tNumb[ix]-1 )
      bar(tBeg[ix]+(pos+1)*8,45+iy*10,tBeg[ix]+pos*8,52+iy*10);
     else
      bar(tBeg[ix]+(pos+2)*8,45+iy*10,tBeg[ix]+(pos)*8,52+iy*10);
                     outtextxy(pos*8+tBeg[ix],45+iy*10,"_"); }
         break;
    default :
    if(cr==4)
if ((pos < tNumb[ix]) & (((char)k =='*') | (((char)k > 43) & ((char)k < 58))))
     { str[pos]=(char)k;
       if( pos==tNumb[ix]-1 ) *(st+1)=0; else strcpy(st," _");
       if ( !pos )
       { setfillstyle(1,7); bar(xBeg[ix]+1,45+iy*10,xEnd[ix]-1,52+iy*10); }
       *st= (char)k;  setfillstyle(1,7);
       bar(tBeg[ix]+(pos+1)*8,45+iy*10,tBeg[ix]+pos*8,52+iy*10);
       outtextxy(pos*8+tBeg[ix],45+iy*10,st); pos++;  }
         break;
  case F2 :
    if (!wrFil(fplan[FlPlan],plan,lPlan*60+1)) M.Error(13);
      FlPlan^=1; ldPlan();
    topPage = 0;   iy=0;    setfillstyle(1,7);
    for (j= 0; j < 9; j++) bar(xBeg[j],43,xEnd[j],344);
    typePlan();
    cr=14; setcolor(cr); rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
         break;
  case F3 :
   char *wbuf=new char[42*4*4*14];
   save_win(10*8,11*14,52*8,14*14,wbuf);
   setfillstyle(1,10); bar(10*8,11*14,52*8-1,14*14);
   setcolor(11);      rectangle(10*8+4,11*14+3,52*8-5,14*14-3);
   outtext("Введите пароль  _", 13,10, 12,14);  outtext(" Esc", 1,10, 13,46);
    pos=0;
   while( k!=ESC & k!=Enter) {
      day();  k=bioskey(1);  if (k!=0) { k=bioskey(0);
        switch(k) {
     default    :
          temp[pos]=(char)k^0xaa;  outtext("*_", 13,10, 12,14+16+pos++);
                if (pos < 10)  break;
     case Enter :
         temp[pos]=0;  k=Enter;
          strcpy(conf+100,temp);
                    wrFil("config.k~_",conf,112);
     case BackSp:
        if (pos)  outtext("_ ", 13,10, 12,14+16+--pos);
         break;
}}} //    switch(k)  if (k!=0)  while
 restore_win(10*8,11*14,52*8,14*14,wbuf); delete(wbuf);
         break;  // end case F3:
  case F5 :
    if (cr==14) {  cr=4;  pos=0;
   setcolor(cr);  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
         break;
  case F6 :
    if ((cr==4)&(pos==0))
     { cr=14; setcolor(cr); rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
         break;
  case F8 :
    if(lPlan>1) {
      lPlan--;
        for(i=0; i+(topPage+iy)*60 < lPlan*60+3; i++ )
          *(plan+i+(iy+topPage)*60) = *(plan+i+(iy+1+topPage)*60);
      setfillstyle(1,7);
     for (j= 0; j < 9; j++) bar(xBeg[j],43,xEnd[j],344);
     typePlan();
     setcolor(cr); rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
    } //   if(lPlan) {
        break;
   case LeftKey :
   if ((ix > 0)&(!pos)) {
  setcolor(7);   setlinestyle(0,0,1);
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
  setcolor(cr);    ix--;
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
   case RightKey :
   if ((ix < 8)&(!pos)) {
  setcolor(7);   setlinestyle(0,0,1);
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
  setcolor(cr);    ix++;
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
   case UpKey :
   if ((iy > 0)&(!pos)) {
  setcolor(7);   setlinestyle(0,0,1);
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
  setcolor(cr);    iy--;
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
   case DnKey :
   if ((iy < 29)&(!pos)) {
    if (iy + topPage >= lPlan-1)
     if ( cr==14 ) break;
      else { for (i=0; i<60; i++)
            if (i>57) *(plan+(lPlan)*60+58)=0;
             else *(plan+(lPlan)*60+i)=' ';
    lPlan++;   *(plan+lPlan*60) = 'Z';  }
  setcolor(7);   setlinestyle(0,0,1);
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10);
  setcolor(cr);    iy++;
  rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
   case PgUpKey :
    if ((topPage-30 >= 0 ) & (!pos)) {
     topPage = topPage-30;   iy=0;
      setfillstyle(1,7);
     for (j= 0; j < 9; j++) bar(xBeg[j],43,xEnd[j],344);
     for (i= 0; i<=30; i++)
       if(*(plan+(topPage+i)*60)== 'Z') break;
        else { setcolor(0);  settextstyle(0,0,0);
         outtextxy(16,45+i*10,plan+(topPage+i)*60); }
     setcolor(cr);
     rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
   case PgDnKey :
    if ((topPage+30 < lPlan) & (!pos)) {
     topPage = topPage+30;    iy=0;
      setfillstyle(1,7);
     for (j= 0; j < 9; j++) bar(xBeg[j],43,xEnd[j],344);
     for (i= 0; i<=30; i++)
       if(*(plan+(topPage+i)*60)== 'Z') break;
        else { setcolor(0);  settextstyle(0,0,0);
         outtextxy(16,45+i*10,plan+(topPage+i)*60); }
     setcolor(cr);
     rectangle(xBeg[ix],43+iy*10,xEnd[ix],53+iy*10); }
        break;
} } } /*while, if, switch */
       setactivepage(0);   pg=0;
       reg.x.ax=0x0500;    int86(0x10,&reg,&reg);
       outtext(tplan[FlPlan],12,1,2,64);
       wrFil(fplan[FlPlan],plan,lPlan*60+1);
} // Plan

int passWord() {
  int f,pos;
      if ( (f=_open("config.k~_",O_RDONLY|O_DENYWRITE))== -1 ) {
        strcpy(passw,"?????"); strcpy(conf+100,passw); }
       else { lseek(f,-12,SEEK_END); _read(f,passw,10);
              _close(f); passw[10]=0;
       }
   char *wbuf=new char[42*4*4*14];
    save_win(10*8,11*14,52*8,14*14,wbuf);
   setfillstyle(1,10); bar(10*8,11*14,52*8-1,14*14);
   setcolor(11);      rectangle(10*8+4,11*14+3,52*8-5,14*14-3);
   outtext("Введите пароль  _", 13,10, 12,14);  outtext(" Esc", 1,10, 13,46);
    f=0; pos=0; k=0;
   while( k!=ESC & k!=Enter) {
      day();  k=bioskey(1);  if (k!=0) { k=bioskey(0);
        switch(k) {
     default    :
          temp[pos]=(char)k^0xaa;  outtext("*_", 13,10, 12,14+16+pos++);
                if (pos < 10)  break;
     case Enter :
         temp[pos]=0;  k=Enter;
        if (!strcmp(temp,passw)) f=1;
   //outtext(passw, 13,10, 13,30); outtext(temp, 13,10, 11,30); getche();
         break;
     case BackSp:
        if (pos)  outtext("_ ", 13,10, 12,14+16+--pos);
         break;
}}} //    switch(k) ; while
 restore_win(10*8,11*14,52*8,14*14,wbuf); delete(wbuf);
 return f;
} // int passWord()

