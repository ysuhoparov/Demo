#define v 20
#define g 20
#define noDraw 10  //  - F < 10 - перерисовывать конвейер
#define ePl  254 // ?- end of plato
#define eAr  253 // ¤- end of array
#define eAP  252 // №- end of array & plato
#define mk   0x3fff
#define nStep 50.0*1e3*17.2

// Конвейер шлифовки плит

class Conw {
unsigned int i,j,x,y;
friend Raskroy;
public:
int Num;             // Num - активная плита
int pNumb;           // кол-во плит на конвейере
int newNum,lastNum;  // номер новой (последней) плиты на конвейере
int pNum[21];        // массив номеров плит, находящихся на конвейере
Conw();
void SmallCon(int color);
void drawConw(void);
void newPl();
void delPl();
void plNum();
};

// Раскрой  плит
class Raskroy {
unsigned int Mrl[1000];
unsigned int Sv[100][100];
unsigned int Indx[40],xKr[30],yKr[30],sOsn[40],sDop[40],sNem[40],jD[40];
unsigned int Smxv;
unsigned int xDop, yDop,sDmx,ls;
unsigned int xi,yi,xj,yj,yk,yl,xNi,yNi,xNj,yNj,yNk,yNl,t;
unsigned int i,j,l,m,n,xn,yn,xr,yr,jd;
int xNr,yNr,yN1,maxY,I,J,Iy,xLeft,xRigh,xR;
unsigned int dx,dy;
unsigned int ImJ[1000],jS[1000],js,sPm[1000],IJ[1000]; // lPlan < 500 ???
struct ready {
unsigned int  date;  // YYmm mmdd dddh hhhh
unsigned int  xSize, ySize;
unsigned int  mern, nemern, pot, poh;
};
public:
float Svmax,sp,s,sd,sn,sv,sm,spI,sdI,snI,svI,siI,sjI,skI,slI,sp4,ltmp;
unsigned int xp[2000],yp[2000];
unsigned int xSize,ySize,q,iyI,jdI,tiI,tjI,tkI,tlI;
int prior,prI,qm;
Raskroy();
void raskroy();
void rect(unsigned int I,unsigned int J);
void razmP();
void pxSize(char d, int yR);
void pySize(int n);
void getSize(int lineNum);
void rez();
int  optRaskr();
double getValue(int index,unsigned int line);
void setValue(double value,int index,unsigned int line);
void changeValue();
void findAll();
void saveInfo();
};

// ******************* -- t.cpp -- ********************
#define InDay  0
#define InMon  1
#define InYear 2
#define InWrk  3
#define InPeriod 4
#define InInstall 5
#define AdInstall 6

#define sColor 0x4a
#define hColor 0x77

class menu {
public:
char *wbuf[20];
int scolor;
struct tm *tim;
int Period, CurentWin,Item[24];
menu();
void HideLine(int i);
void ShowLine(int i);
void Make(int i);
void delWin(int i);
void MKey(int d);
void MenuKey(int k);
void Exit();
void Error(int i);
};

// Загрузка информации о заводском плане

class loadInfo:public menu {
long beginArea;
unsigned int date,date_,Mdate;
int flRd;
struct Ready {
unsigned int  date;  // YYmm mmdd dddh hhhh
unsigned int  xSize, ySize;
unsigned int  mern, nemern, pot, poh;
};
struct Rdy {
unsigned int  date;  // YYmm mmdd dddh hhhh
unsigned int  xSize, ySize;
float mern, nemern, pot, poh;
};
public:
int Handle,J;
Ready *M;  // [20 Pl/hour * 20*8 Hour]
Rdy   *R;
int openDb();
int searchArea();
int makeDataBuf();
void savInfo();
//index 0-min 1-hour 2-wrk 3-day 4-mon 5-year
};



class report:public loadInfo {
void repMenu();
void repDraw();
public:
void periodMenu();
};

class install:public menu {
void showLine(int);
void showaLine(int);
void MKey(int);
char strb[8];
int pos,x,y,i,col,a;
public:
void installMenu();
void AdMenu();
void storeInPar();
};

// Получение данных из контроллера 
class channel {
void _exit_();
int rx;
public:
int cnt_int;
unsigned int buf_plato[16];
unsigned int buf_pult[10];
void _init_();
void interrupt _tint(...);
channel();
int initChannel();
};
