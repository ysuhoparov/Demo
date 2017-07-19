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
#include <time.h>
#include <graphics.h>

#include "kl.h"       // Location and class declarations
//unsigned char colF[8] = { 2,4,3,1,8,10,11,0};
extern void outtext(char *, unsigned char,unsigned char, unsigned char, unsigned char);
extern unsigned int k, pg, F, lPlan, FlPlan,topPage;
extern char far *temp;
extern char far *plan;
extern unsigned char kd[160];
extern unsigned char km[8];   /* ymin,xmax,ymax,xmin */
extern char cP;
extern Conw C;
extern int xBeg[],xEnd[],tBeg[],tNumb[];
extern int wrFil( char *file, char *buf, unsigned int n);
extern char *fplan[];
extern unsigned char inPar[]; // параметры настройки
extern char *Name[];
extern menu M;


Raskroy::Raskroy(){
prI=0;
dx=2; dy=4;
//xp[0]=10; yp[0]=101;
//Mrl[0]=0;
//Indx[0]=0; xKr[0]=0; yKr[0]=0;
//int Sv[100][100];
      //if (!(Sv[][] = new unsigned int [100][100])) {
      //  printf ("Insussufytion memory, reboot"); exit(0);}
//sOsn[0]=0; sDop[0]=0; sNem[0]=0;
}

void Raskroy::getSize(int lineNum)
{  for(int i=0; i < 10; i++)
    *(temp+i)=*(plan+lineNum*60+10+i) ;
   *(temp+4) = *(temp+10) = 0;
    if (*(temp+3) != '*') xSize = atoi(temp)+4;  else xSize =204;
    if (*(temp+9) != '*') ySize = atoi(temp+6)+4; else ySize =204;
   if (xSize < 204) xSize=204; if (ySize < 204) ySize=204;
}

void Raskroy::pxSize(char d,int yR)
{  int i = xKr[n+d]-xKr[n-1+d]-4, x, y;  yR++;
 // setcolor(colF[l & 7]);
 itoa(i,temp,10); setlinestyle(0,0,1);
   if (i > 99)
    { if (i > 250) { settextstyle(0,0,0); x=-11; y=13;
     bar(i/20+x+1+xKr[n-1+d]/10,J*2+v-y,i/20+x+23+xKr[n-1+d]/10,J*2+v+6-y);
                   }  else { settextstyle(0,1,0); x=6; y=29;
     bar(i/20+x-1+xKr[n-1+d]/10,J*2+v-y,i/20+x-9+xKr[n-1+d]/10,J*2+v+24-y);
                   }
      setcolor(14); line(xKr[n-1]/10,J*2+v-3,xKr[n]/10,J*2+v-3);
   }
    else  { settextstyle(0,0,0); x=10; y=23;
      if((xKr[n+d+1]-xKr[n-1+d+1]) <=250) y=40;
     bar(x+xKr[n-1+d]/10,J*2+v-y,x+16+xKr[n-1+d]/10,J*2+v+6-y);
     setcolor(14);
     line(xKr[n-1]/10,J*2+v-3,xKr[n]/10+24,J*2+v-3);}
     line(xKr[n]/10-3,J*2+v-1,xKr[n]/10+3,J*2+v-5);
     line(xKr[n-1]/10-3,J*2+v-1,xKr[n-1]/10+3,J*2+v-5);
   //setcolor(15);
 outtextxy(i/20+x+xKr[n-1+d]/10,J*2+v-y,temp);
}

void Raskroy::pySize(int n) {
int i = yKr[m-1]-yKr[m]-4, x, y, z;
  //setcolor(colF[l & 7]);
   itoa(i,temp,10); setlinestyle(0,0,1);
   if(( m <= yNr )||(F==4)) {
     if ((i > 300) & (m!=1)) { settextstyle(0,1,0); y=-12; x=5;
bar(xKr[n+1]/10-x-7,(i/2+yKr[m])*0.08+y+23,xKr[n+1]/10-x,(i/2+yKr[m])*0.08+y);
   }
      else { settextstyle(0,0,0); y=-4; x=29; if(m==1) y=-10;
bar(xKr[n+1]/10-x+23,(i/2+yKr[m])*0.08+y+7,xKr[n+1]/10-x,(i/2+yKr[m])*0.08+y);
      }
  setcolor(13);
  line(xKr[n+1]/10-3,yKr[m]*0.08,xKr[n+1]/10-3,yKr[m-1]*0.08);
  line(xKr[n+1]/10,yKr[m]*0.08+2,xKr[n+1]/10-6,yKr[m]*0.08-2);
  line(xKr[n+1]/10,yKr[m-1]*0.08+2,xKr[n+1]/10-6,yKr[m-1]*0.08-2);
  if ((m==1) && (F!=4)) i=140;
  outtextxy(xKr[n+1]/10-x,(i/2+yKr[m])*0.08+y,temp);
     }
  if (( m >yNr ) & ( n > 0 ) & (F!=4)) { settextstyle(0,1,0); y=2;
   if (i >=300) { y=-25-(i-300)/25; i=-1;}
       else if (i >=250) i=24;
          else if (i <= 99) i=18; else i=25;
  if (m<=1) { y=-45; i=-1; }
  bar(xKr[1]/10+3,yKr[m-1]*0.08+i,xKr[1]/10+15,yKr[m-1]*0.08+y);
  setcolor(13);
  line(xKr[1]/10+17,yKr[m]*0.08,xKr[1]/10+17,yKr[m-1]*0.08+i);
  line(xKr[1]/10+20,yKr[m]*0.08+2,xKr[1]/10+14,yKr[m]*0.08-2);
  line(xKr[1]/10+20,yKr[m-1]*0.08+2,xKr[1]/10+14,yKr[m-1]*0.08-2);
  outtextxy(xKr[1]/10+14,yKr[m-1]*0.08+y,temp);
}   }

void Raskroy::rect(unsigned int I,unsigned int J)
{   int i;
      for (xLeft=0, xRigh=250, i=I*2; i <= J*2; i+=2) {
        if (kd[i] > xLeft)  xLeft = kd[i];
        if (kd[i+1] < xRigh) xRigh = kd[i+1];
      }
   xRigh += inPar[0];  xLeft -= inPar[0]; // xLeft in см
}

void Raskroy::razmP() {
 int a = 14, b = 11, c = 20, d = 24;
  int x1= xLeft+g, x2= xRigh+g;      // 1 pixel = 10мм
  int y1= I*2+v, y2= J*2+v;          // 1 pixel = 12.5мм
 setcolor(0);                        // xLeft in 10мм, I - 25мм
 setlinestyle(0,0,1);
 line(x1,y2,x1,v+km[5]*4+a);
 line(x2,y2,x2,v+km[5]*4+a);
 line(x1,v+km[5]*4+b,x2,v+km[5]*4+b);  /* x */

 line(x1,v+km[5]*4+b,x1+5,v+km[5]*4+b-3);
 line(x1,v+km[5]*4+b,x1+5,v+km[5]*4+b+3);
 line(x2,v+km[5]*4+b,x2-5,v+km[5]*4+b-3);
 line(x2,v+km[5]*4+b,x2-5,v+km[5]*4+b+3);
 itoa((x2-x1)*10,temp,10);
 settextstyle(0,0,0);  setcolor(0);
 outtextxy(x1/2+x2/2-12,v+km[5]*4+1,temp);      /* X_Size */

 line(x2,y1,g+km[2]+d,y1);
 line(x2,y2,g+km[2]+d,y2);
 line(g+km[2]+c,y1,g+km[2]+c,y2);  // y

 line(g+km[2]+c,y1,g+km[2]+c+3,y1+3);
 line(g+km[2]+c,y1,g+km[2]+c-3,y1+3);
 line(g+km[2]+c,y2,g+km[2]+c+3,y2-3);
 line(g+km[2]+c,y2,g+km[2]+c-3,y2-3);
 itoa((y2-y1)*12.5,temp,10);
 settextstyle(0,1,1);  setcolor(0);
 outtextxy(g+km[2]+c-3,y2/2+y1/2-12,temp);        // y_Size
}

void Raskroy::raskroy() {
// g,xLeft - в см, v - 10см; xKr - в мм;   I - 1см, J - 5см
static unsigned int color[4]={2,4,8,11}, cm,cn,oldSize;
float stO,stD,stN;  // Стоимость основной, дополнительной, немерной плитки
 if(cP!=1) {
   for(i=0; i < 2*lPlan; i+=2) {
    getSize(i/2); yp[i+1]=xp[i]=xSize; xp[i+1]=yp[i]=ySize;
   }
   for (i=0; i<160; i+=2) if (kd[i] == 255) break;
   if((maxY=i-2) < 10) return;
   for (i=0; i < maxY/6; i++)                      //  All rectangle
    for (j=maxY/2; j > maxY/3; j--) {
      rect(i,j); Sv[i][j]=(xRigh - xLeft) * (j - i);
    }  // for j,i
   for (l=0; l < 20; l++) {                        // Find 20 Max rectangle
     for (Smxv=0, j=maxY/2; j > maxY/3; j--)
      for (i=0; i < maxY/6; i++)
       if (Sv[i][j] > Smxv) { Smxv=Sv[i][j]; I=i; J=j; } // for j,i,
     Indx[l]=I+(J << 8);
     if(!l)  Svmax=Sv[I][J];                       // max rectangle
     Sv[I][J]=0;                                   // zero Sv rectangle
   }                                               // for l
   if (F==5) findAll();
 }  // if(cP!=1)
 for(prior=0; prior < 4; prior++) {
   cn=color[prior]; cm=15-cn;
   if (F==5) Iy = jS[prior]/2;                             // Search prior
    else for(Iy=0; (Iy<lPlan-1)&(*(plan+Iy*60+7)!=prior+49); Iy++);
   for(i=0; i < 6; i++) *(temp+i)=*(plan+Iy*60+52+i) ;
   *(temp+6) = 0;   stO = atof(temp);  stN=stO/2; // Стоимость основной плитки
 if (F!=5) {
  for (l=0; l < 40; l+=2) {                      // View 20 Max rectangle
    I=Indx[l/2] & 255; J=Indx[l/2] >> 8;
    rect(I,J); I=I<<1; J=J<<1;
    for (i=0; i < 2; i++)  {
      xNr = (xRigh - xLeft)*10/xp[Iy*2+i];
      yNr = (J - I)*25/yp[Iy*2+i];
      sOsn[l+i] = ((xp[Iy*2+i]-4)*xNr/10)*((yp[Iy*2+i]-4)*yNr/10);
      xn = ((xRigh - xLeft)*10) % xp[Iy*2+i];
      yn = ((J - I)*25) % yp[Iy*2+i];
      if (F == 2) {               sNem[l+i]=0;
        if (xn >= 200) sNem[l+i] = xn/10 * ((yp[Iy*2+i]-4)*yNr/10);
        if (yn >= 200) sNem[l+i]+= yn/10 * ((xp[Iy*2+i]-4)*xNr/10);
      }
      if (F == 3) {
        for (xDop=0,j=0; j < 2*lPlan; j++)
         if ((xp[j] <= xn) & (xp[j] > xDop)) { jD[l+i]=j; xDop=xp[j]; }
        if (xDop > 0) { j=jD[l+i]; yDop=yp[j];
          yNr=(J - I)*25/yDop; sDop[l+i]=((xDop-4)/10)*((yDop-4)*yNr/10);
        }  else  sDop[l+i] = 0;
      }                     //  if( F ==3 )
  } }                                              // for i,l
  for (sDmx=1, l=0; l < 40; l++) {                // Searh opt rect whis 20
   if (F==2) { if (sOsn[l]+sNem[l]/inPar[2] > sDmx) {
                   sDmx=sOsn[l]+sNem[l]/inPar[2]; ls=l;}}
   if (F==3) { if (sOsn[l]+sDop[l]/inPar[3] > sDmx) {
                   sDmx=sOsn[l]+sDop[l]/inPar[3]; ls=l;}}
  }                                          // for (sDmx=1, l=0; l < 40; l++)
  I=Indx[ls/2] & 255; J=Indx[ls/2] >> 8;
 }    // if (F!=5)
 else { I=ImJ[prior] & 255; J=ImJ[prior] >> 8; ls=jS[prior]; }
  rect(I,J); I=I<<1; J=J<<1; setfillstyle(1,color[prior]);    // Draw
  if((F!=4)&(prior==prI)) { iyI=Iy;
     bar(xLeft+g,I*2+v,xRigh+g,J*2+v);
      setcolor(15);  setlinestyle(0,0,1); razmP();
       rectangle(xLeft+g,I*2+v,xRigh+g,J*2+v);
    if (((xRigh-xLeft) < oldSize)||(xRigh-xLeft-oldSize > inPar[1])) {
     sprintf(temp," Плиту N %2d задержать ",C.pNum[C.Num]);
     outtext(temp, cm,cn,23,4);
    }  oldSize=xRigh-xLeft;
  } //  if((F!=4)&(prior==prI))
    xSize=xp[Iy*2+ls%2]; ySize=yp[Iy*2+ls%2];
    xNi=xNr = (xRigh - xLeft)*10/xSize ;
    if ((xn=(xRigh-xLeft)*10 % xSize) == 0)  xNr--;
    xKr[xNr+1] = g*10+xRigh*10;
    setcolor(7);  setlinestyle(0,0,1);
    for (n=xNr; n > 0; n--) { xKr[n] = xKr[n+1]-xSize;
     if((F!=4)&(prior==prI)) line(xKr[n]/10,I*2+v+1,xKr[n]/10,J*2+v-1);
    }   // for n                                         // verticale X
    xKr[0] = g*10+xLeft*10;
   if(F==3) {
    sd=sDop[ls]; if (prior==prI)  sdI=sd/1e4;
    if (sd > 0) {
     for(i=0; i < 6; i++) *(temp+i)=*(plan+jd*60+52+i) ;
     *(temp+6) = 0;   stD = atof(temp);
     jd = jD[ls]; xr=xp[jd]; yr=yp[jd]; jd /= 2;
     xKr[0] = xKr[1] - xr;
     if(prior==prI) { line(xKr[0]/10,I*2+v+1,xKr[0]/10,J*2+v-1); jdI=jd;}
     yN1 = yNr = (J - I)*25/yr ;
     if ((J - I)*25 % yr == 0)  yNr--;
     yKr[0] = (v+J*2)*12.5; yKr[yNr+1] = (v+I*2)*12.5;
     for (m=1; m <= yNr+1; m++)  {  setcolor(7);     // horizontale Y1
        if (m <= yNr)   {   yKr[m] = yKr[0] - m*yr;
         if (prior==prI) line(xKr[0]/10+1,yKr[m]*0.08,xKr[1]/10-1,yKr[m]*0.08);
        }   //  if (m <= yNr)
        if ((prior==prI) & (m >= yNr)) pySize(0);
   }}}    // for m  if(F==3)
  yNi= yNr = (J - I)*25/ySize ;
  if((yn=(J - I)*25 % ySize) == 0) yNr--;
  yKr[0] = (v+J*2)*12.5; yKr[yNr+1] = (v+I*2)*12.5;
  for (m=1; m <= yNr+1; m++)  { setcolor(7);               // horizontale Y
   if (m <= yNr) { yKr[m] = yKr[0] - m*ySize;
      if (F==3)  i=1; else i=0;
      if((F!=4)&(prior==prI))
         line(xKr[i]/10+1,yKr[m]*0.08,g+xRigh-1,yKr[m]*0.08);
   }
   if ((m >= yNr) & (prior==prI) & (F!=4))  pySize(xNr);
  }    // for m
  if((F!=4)&(prior==prI)) for (n = 1; n <= xNr+1; n++) pxSize(0,yr);
  if(cP!=1) {
   sp=((xSize-4)*xNi/10)*((ySize-4)*yNi/10);
   if (F == 2)  sn = sNem[ls];
   sv = (xRigh - xLeft) * (J - I)*2.5;
   for(i=0, s=0; (i < 160)&(kd[i]!=255); i+=2) s += (kd[i+1]-kd[i])*5;
   sprintf(temp,"%.4f m¤",s/1e4); outtext(temp, 12,1,4,57);
   sprintf(temp,"%.3f %2.1f%%",Svmax*5/1e4,Svmax*500/s); outtext(temp,12,1,5,57);
   outtext("Цена",12,1,5,73);
   sprintf(temp,"%.3f %2.1f%%",sv/1e4,sv*100/s);
   sprintf(temp,"%3dx%3d %.3f %2.1f%% %8.f",xSize-4,ySize-4,sp/1e4,sp*100/s,sp*stO/1e4);
   outtext(temp, cm,cn,6+prior*3,49);
   if(F==2) {
    sprintf(temp,"***x%3d %.3f %2.1f%% %8.f",ySize-4,sn/1e4,sn*100/s,sn*stN/1e4);
    outtext(temp, cm,cn,7+prior*3,49);
    sprintf(temp,"S_сум = %.3f %2.1f%% %8.f",(sn+sp)/1e4,(sn+sp)*100/s,(sp*stO+sn*stN)/1e4);
    outtext(temp, cm,cn,8+prior*3,49);
   }
   if(F==3) {
    if(sd > 0)
     sprintf(temp,"%3dx%3d %.3f %2.1f%% %8.f",xr-4,yr-4,sd/1e4,sd*100/s,sd*stD/1e4);
    else      sprintf(temp,"Дополнительной нет          ");
    outtext(temp, cm,cn,7+prior*3,49);
    sprintf(temp,"S_сум = %.3f %2.1f%% %8.f",(sd+sp)/1e4,(sd+sp)*100/s,(sp*stO+sd*stD)/1e4);
    outtext(temp, cm,cn,8+prior*3,49);
   }
   if(F==5) {
    sprintf(temp,"                             ");
    outtext(temp, cm,cn,7+prior*3,49);
    sprintf(temp,"                             ");
    outtext(temp, cm,cn,8+prior*3,49);
   }
   if (!prior) { q=0; rez(); }
  } // if (cP!=1)
  if((F!=4)&(prior==prI)) { spI=sp; svI=sv; }
  if((F==2)&(prior==prI))   snI = sn;
  if((F==3)&(prior==prI))   sdI = sd;
 }  // for(prior=0; prior < 4; prior++)    */
 cP=0;
} // Raskroj

int Raskroy::optRaskr() {
register unsigned int i,j,k,l,m;
int x1,y1,x2,y2,xN1,xN2,yN1,yN2;
 if((yr=(J - I)*25) < 500) return(-1);
 xR=(xRigh-xLeft)*10; dy=dx*2;
 for(m=0,i=0; (i < lPlan*2) & (m<292); i++)
   for(k=i,x1=xp[i],y1=yp[i]; (k < lPlan*2); k++)                  // y1 ?
    if (xp[k]==x1)
     for(yN1=1; (yN1< yr/y1)&((y1!=yp[k])|(yN1==1)); yN1++)
      if(((yr-y1*yN1) >= yp[k]) & ((yr-y1*yN1)%yp[k] <= dy))       // y1 O'k
       for(j=i; (j < lPlan*2) & (m<292); j++)                      // x2 ?
        for(xN1=1,x2=xp[j],y2=yp[j]; (xN1<xR/x1)&((x2!=x1)|(xN1==1)); xN1++)
         if(((xR - x1*xN1) >= x2) & ((xR - x1*xN1) % x2 <= dx))    // x2 Ok
          for(l=0; (l < lPlan*2); l++ )                            // y2 ?
           if(xp[l]==x2)
            for(yN2=1; (yN2< yr/y2)&((y2!=yp[l])|(yN2==1)); yN2++)
             if(((yr-y2*yN2) >= yp[l]) & ((yr-y2*yN2)%yp[l] <= dy)) // y2
             { Mrl[m++]=i; Mrl[m++]=j; Mrl[m++]=k; Mrl[m++]=l;
                Mrl[m++]=xN1; Mrl[m++]=yN1;  Mrl[m++]=yN2;
//  printf("\n i=%d k=%d j=%d l=%d x1=%d x2=%d xSize=%d",i,k,j,l,xN1,x2,xp[l]);
//  getche();
             }
  return(m);
}

void Raskroy::rez() {   // Draw  4  barArea
   I=Indx[0] & 255; J=Indx[0] >> 8;
   rect(I,J); I=I<<1; J=J<<1; setfillstyle(1,1);
  if (F==4) {
  bar(xLeft+g,I*2+v,xRigh+g,J*2+v);
  setcolor(15);  setlinestyle(0,0,1);  razmP();
  rectangle(xLeft+g,I*2+v,xRigh+g,J*2+v); }
  if (q == 0) {
     for (qm=0,dx=2; (qm < 2)&(dx < 400); dx+=2+dx/5) 
       if((qm=optRaskr())==-1) return; }
  tiI=t=Mrl[q*7];   xi=xp[t]; yi=yp[t];                 // i
  tjI=t=Mrl[q*7+1];   xj=xp[t]; yj=yp[t];               // j
   //sprintf(temp,"%d   %d   %d   %d   %d   %d   %d     %d $",Mrl[q*7+0],Mrl[q*7+1],Mrl[q*7+2],Mrl[q*7+3],Mrl[q*7+4],Mrl[q*7+5],Mrl[q*7+6],q);
  sprintf(temp," x=%d y=%d n=%d N=%d  $",dx,dy,q,qm/7);
  outtext(temp, 6,1,0,15);
  xKr[0] = g*10+xLeft*10;
    xNi= Mrl[q*7+4];  xNj=(xR - xi*xNi)/xj;  xNr=xNi+xNj;
    setcolor(7);  setlinestyle(0,0,1);
    for (n=1; n <= xNi+xNj ; n++)  {                     // verticale X
     if (n <= xNi)  { xKr[n] = xKr[n-1] + xi;  ySize=yi; }
      else { xKr[n] = xKr[n-1] + xj;    ySize=yj; }
  if (F==4) {
      line(xKr[n]/10,I*2+v,xKr[n]/10,J*2+v);
    setcolor(15);
     /*if ((n==1)|(n >= xNr))*/   pxSize(0,ySize);
    setcolor(7);
  }} // if; for n
   setcolor(15); // n--; xKr[n] = g*10+xRigh*50; //n--;
    tkI=t=Mrl[q*7+2];   yk=yp[t];                          // k
    tlI=t=Mrl[q*7+3];   yl=yp[t];                          // l
    yNi= Mrl[q*7+5];  yNk=(yr - yi*yNi)/yk;
    yNj= Mrl[q*7+6];  yNl=(yr - yj*yNj)/yl;
   //sprintf(temp,"%d   %d   %d   %d   %d   %d   %d     %d $",xi,xj,yk,yl,xNi,yNk,yNl,q);
   // outtext(temp, 4,10,1,12);
   yKr[0] = (v+J*2)*12.5;
   setcolor(7);
  for (m=1; m <= yNi+yNk; m++)  {                   // horizontale Y
    if (m <= yNi)  yKr[m] = yKr[m-1] - yi;
      else  yKr[m] = yKr[m-1] - yk;
    if (F==4) { line(g+xLeft,yKr[m]*0.08,(xKr[0]+xNi*xi)/10,yKr[m]*0.08);
       if (((m == yNi) & (yi != yk)) | (m == yNi+yNk))
        pySize(xNi-1); setcolor(7);
  } }     // if for m
  for (m=1; m <= yNj+yNl; m++)  {                   // horizontale Y
     if (m <= yNj)  yKr[m] = yKr[m-1] - yj;
      else  yKr[m] = yKr[m-1] - yl;
    if (F==4) { line((xKr[0]+xNi*xi)/10,yKr[m]*0.08,g+xRigh,yKr[m]*0.08);
      if (((m == yNj) & (yj != yl)) | (m == yNl+yNj))
      pySize(xNi+xNj-1); setcolor(7);
  } }    // for m
  siI=(xi*xNi/10)*(yi*yNi/10);
  sjI=(xj*xNj/10)*(yj*yNj/10);
  skI=(xi*xNi/10)*(yk*yNk/10);
  slI=(xj*xNj/10)*(yl*yNl/10);
  sp4=siI+sjI+skI+slI;
  sprintf(temp,"S_4пл = %.3f %.1f%%",sp4/1e4,sp*100/s); outtext(temp, 14,1,19,49);
  sprintf(temp,"( %d x %d )",xi-4,yi-4); outtext(temp, 12,1,20,54);
  sprintf(temp,"( %d x %d )",xj-4,yj-4); outtext(temp, 12,1,21,54);
  sprintf(temp,"( %d x %d )",xi-4,yk-4); outtext(temp, 12,1,22,54);
  sprintf(temp,"( %d x %d )",xj-4,yl-4); outtext(temp, 12,1,23,54);
} //Rez()

double Raskroy::getValue(int index,unsigned int line) {
  for(int i=0; i <= tNumb[index]+index%2*2; i++)
// tBeg-positione in ecran, dans plan en 2 pos. bellow
    *(temp+i)=*(plan+line*60+tBeg[index]/8-2+i) ;
  *(temp+tNumb[index]+index%2*2) = 0;
return ((double)atof(temp));
}  // getValue(int index ...

void Raskroy::setValue(double value,int index,unsigned int line) {
  switch(index) {
    case 5 : sprintf(temp,"%9f",value);   break;   // all
    case 6 : sprintf(temp,"%3f",value);   break;   // %
    case 7 : sprintf(temp,"%8f",value);   break;   // nem
    } //   switch(index)
       for(int i=0; i < tNumb[index]+index%2*2; i++)
           *(plan+line*60+tBeg[index]/8-2+i) = *(temp+i);
} //  setValue()

void Raskroy::changeValue() {
 if(F<4) { setValue(getValue(5,iyI)+spI/1e4,5,iyI);     // osn
           setValue(getValue(5,iyI)/getValue(4,iyI)*100,6,iyI); }  // persent
 switch(F)   {
   case  2 :
        setValue(snI/1e4+getValue(7,iyI),7,iyI);            // nemern
   break;
   case  3 :
      setValue(getValue(5,jdI)+sdI/1e4,5,jdI);          // dop
      setValue(getValue(5,jdI)/getValue(4,jdI)*100,6,jdI);      // persent
   break;
   case  4 :
   //sprintf(temp,"%f %d",slI,tlI); outtext(temp, 12,1,21,12);
      setValue(getValue(5,tiI/2)+siI/1e4,5,tiI/2);          // i
      setValue(getValue(5,tiI/2)/getValue(4,tiI/2)*100,6,tiI/2); // persent
      setValue(getValue(5,tjI/2)+sjI/1e4,5,tjI/2);          // j
      setValue(getValue(5,tjI/2)/getValue(4,tjI/2)*100,6,tjI/2); // persent
      setValue(getValue(5,tkI/2)+skI/1e4,5,tkI/2);          // k
      setValue(getValue(5,tkI/2)/getValue(4,tkI/2)*100,6,tkI/2); // persent
      setValue(getValue(5,tlI/2)+slI/1e4,5,tlI/2);          // l
      setValue(getValue(5,tlI/2)/getValue(4,tlI/2)*100,6,tlI/2); // persent
   break;
  } //   switch(F)
 wrFil(fplan[FlPlan],plan,lPlan*60+1);
 //  strcpy(temp,plan+(topPage+24)*60);
 //  setcolor(12); settextstyle(0,0,0); outtextxy(16,45+24*10,temp);
}

void Raskroy::findAll() {
   for(i=0; i < lPlan*2; i++) {
     for (j=0; j < 20; j++) {         // View 20 Max rectangle
      I=Indx[j] & 255; J=Indx[j] >> 8;
      rect(I,J); I=I<<1; J=J<<1;
      xNr = (xRigh - xLeft)*10/xp[i]; yNr = (J - I)*25/yp[i];
      sOsn[j] = ((xp[i]-4)*xNr/10)*((yp[i] -4)*yNr/10);
     }
     for (sDmx=0,j=0; j < 20; j++) {  // max S
       if (sOsn[j] > sDmx) { sDmx = sOsn[j]; js=j; }
     }
     sPm[i]=sDmx; IJ[i]=Indx[js];                 // in size x,y
   }
   for(i=0; i < lPlan*2; i++) {              // Sort sPm[]
     for (sDmx=0,j=0; j < lPlan*2; j++)
       if (sPm[j] > sDmx) { sDmx=sPm[j]; js=j; }   // for j , MAX sPm[js]
     ImJ[i]=IJ[js]; jS[i]=js;   // Value for return
     sPm[js]=0;                                  // zero sPm rectangle
}  }

void Raskroy::saveInfo() {
static ready R;
int Handle;
 if((Handle=open(Name[FlPlan],O_CREAT|O_APPEND|O_WRONLY,S_IWRITE))==-1) {
   M.Error(7);  return; }
 time_t t=time(NULL); struct tm *tim=localtime(&t);
 R.date=(int)tim->tm_hour|(int)tim->tm_mday<<5|(int)tim->tm_mon<<10;
 R.nemern=0;
 if(F!=4) { getSize(iyI); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=spI; // osn
 if(F==2) { R.nemern=snI; R.pot=s-spI-snI; R.poh=svI-spI-snI; }
 if(F==3) { R.pot=s-spI-sdI; R.poh=svI-spI-sdI; }
 if(F==5) { R.pot=s-spI; R.poh=svI-spI; }
 _write(Handle,(char *)&R,sizeof(R));  }
 if((F==3)&(sdI>0)) {
   getSize(jdI); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=sdI;  // dop
   R.nemern=0; R.pot=0; R.poh=0;
   _write(Handle,(char *)&R,sizeof(R)); }
 if(F==4) {
   R.nemern=0; R.pot=s-sp4; R.poh=Svmax*5-sp4;
   getSize(tiI/2); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=siI;  // i
   _write(Handle,(char *)&R,sizeof(R));   R.pot=0; R.poh=0;
   getSize(tjI/2); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=sjI;  // j
   _write(Handle,(char *)&R,sizeof(R));
   getSize(tkI/2); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=skI;  // k
   _write(Handle,(char *)&R,sizeof(R));
   getSize(tlI/2); R.xSize=xSize-4; R.ySize=ySize-4; R.mern=slI;  // l
   _write(Handle,(char *)&R,sizeof(R)); }
 _close(Handle);
} // saveInfo()
