
#include <vcl.h>
#pragma hdrstop

#include "mainfrm.h"
#include "dmm.h"
#pragma Packetage(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

#define FLTR 2
#define ZONE 4

TEdit * U[ZONE],* I[ZONE],* R[ZONE];
TShape * cmp[ZONE],* cma[ZONE],* crp[ZONE],* cra[ZONE];
TShape * omp[ZONE],* oma[ZONE],* orp[ZONE],* ora[ZONE];

int  t2=0, cnz=0, zone, dn=0;   		// Temporary

HANDLE hCom;
unsigned char fChan[256], chann[256], netPacket[128], chSumm;

int    iZn, fZn, flIn, nUi=0, wDog[ZONE];  	 // ZONE,count ui,FlagInpFile,watchDog
unsigned char flP[ZONE],flR[ZONE],flE[ZONE];  	 // flPacked, flr,  fle
unsigned char Phi[ZONE],rWE[ZONE],rErr[ZONE];   //
unsigned char iFlt[ZONE],uFlt[ZONE],nSpark[ZONE];   //

unsigned char flr,fle,ifl,ufl; 			//  When reading from the database, the tmp var/
Word  lHour, lMin, lSec, lMSec,rSec=1;
unsigned int  uiF[ZONE][10], rgnF, uitf;

int flRgnW[ZONE]={0,0,0};

unsigned char fOsc[32];

DWORD dwError, bytesRead=0,cnt, ch=0, cp=0, cs=0;       // cp- countPause
BOOL   bRb;AnsiString aChan;TDateTime dt, cdt;
int  d, j, ufui, rgn, eFilter, wDogTimer=0, jr=0;
AnsiString as, ds, tCur, lAstr;
unsigned int itst=0;

char *rMode[] = {"Авто","Иск.","Огp.","O.K.","К.З.","Х.Х.","Руч.","Стоп","    "};

//tInfo fInfo[FLTR][ZONE][];
// flr, fle, Phi, RgnEnable | rgnWork, rgnError, iInf, uInf, netSparc

/* Notation conventions
   ZONE, FLTR  - Const
   zone, fltr  - local variable
   myZone,myFilter (classMember) - member of class
   MyZone,MyFilter - Class
    Objects:
      ElFilter, InFile, VuCommand, FltrRgn, FltrAlimentation
      For each filter is an object. Number of objects - by number of filters
*/
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
  tOld="";
  tCount=0;
  ufiu[0]= ufiu[1]= ufiu[2]= ufiu[3]=0; zw=1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
  Close();
}
//--------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{

// Actions taken on time
   if(++wDogTimer > 100)  {   wDogTimer=0;    	// Сторож
     for (fZn=0; fZn<ZONE; fZn++){
       if (wDog[fZn]==0) {
         I[fZn]->Text= "";
         U[fZn]->Text= "";
         R[fZn]->Text= "";
         cmp1->Brush->Color=clBtnFace; crp1->Brush->Color=clBtnFace; // RGN "disable"

       }
       wDog[fZn]=0;    			// No accepted file
     }
   }

  if ((++trCount) > 25) { trCount=0;      		// RGN. Indication of mechanismsв
    for(j=0; j<2; j++) {
      if (rWE[j]&0x8)  {    //    Осад

         omp[j]->Visible^=1; orp[j]->Visible=omp[j]->Visible;
         oma[j]->Visible=!omp[j]->Visible; ora[j]->Visible=oma[j]->Visible;
      }
       else {
         omp[j]->Visible=True;  orp[j]->Visible=True;
         oma[j]->Visible=False; ora[j]->Visible=False;
      }
      if (rWE[j]&0x4)  {    //    Кор

         cmp[j]->Visible^=1; crp[j]->Visible=cmp[j]->Visible;
         cma[j]->Visible=!cmp[j]->Visible; cra[j]->Visible=cma[j]->Visible;
      }
       else {
         cmp[j]->Visible=True;  crp[j]->Visible=True;
         cma[j]->Visible=False; cra[j]->Visible=False;
      }
    }
  } // if ((++trCount) > 25)

   jr++;   // simple counter
   if (!(jr%100)) {
     r0->Text=AnsiString(jr);
     r0->Repaint();
   }

// Reciver

/* At the end of the packet Checking the checksum Buffering Raise the flag
Per second save in the database  */

// for (eFilter=0; eFilter<FLTR; eFilter++)   	// Check all filters

   bRb = ReadFile(hCom, &fChan, 2, &bytesRead, NULL) ;
   eFilter=0;  // COM0
   if (bytesRead > 0 ) { cnt=0;
      while (cnt <  bytesRead) {
        if (fChan[cnt]!=0xff) { cp=0;           		// !=pause
          netPacket[ch++]= fChan[cnt];
          aChan += IntToHex(fChan[cnt],1) + " ";     		// for view
        }
        else {
          aChan += AnsiString(".");
          if (!cp) { cp++; ch=0; // First pause
   // Class Net				
            for (j=0,chSumm=0; j<10; j++) chSumm+=netPacket[j];  // Net.CheckSumm
            if(chSumm==netPacket[10])  {                          	// Net.
              fZn = ( netPacket[0] >> 4) -1;			//To write to the database 
              wDog[fZn]=1;          	 // wDog
              flP[fZn] = netPacket[1];  	// fl1
              flR[fZn] = netPacket[2];  	// flr
              flE[fZn] = netPacket[3];  	// fle
              Phi[fZn] = netPacket[4]; 	 // phi
              rWE[fZn] = netPacket[5]; 	 // r Work/Еnable
              rErr[fZn] = netPacket[6];  	// rErr
              iFlt[fZn] = netPacket[7];  	// i
              uFlt[fZn] = netPacket[8];  	// u
              nSpark[fZn] = netPacket[9]; 	 // nSpark
              flIn = fZn+1;
        } } }  // else  if   if(chSumm)
        cnt++;
      }  //  while
   //    else { aChan += AnsiString("."); }
   }  // if(bytesRead > 0
   else SetFilePointer (hCom, 0, NULL, FILE_BEGIN) ;

   Memo1->Lines->Text = aChan;  	// for debug

  /*    Passage for all f
      If the number of passes> 10 - indication of the absence of communication
           Checking the command queue.
      Check the progress of the previous command.
      Put the command in the buffer.
  */

/*     D7	D6	D5	D4	D3	D2	D1	D0
0	s	S	s	s	r	r	r	r	Address field. 4-7-The address will be sent, 0-3 -The address is received, 0-BY, F-all1	rg	Rg	rg	rw	rw	rv	typ	file	The control field rg 0-Auto, 2-Sparc, 4-Огр, 6-ОК   8-КЗ,а-ХХ, с-Руч, е-Стоп
---	---	---	---	--	--	--	--	--     	 rw-№ Working fur. Regen. Rv-vibrator Short 1-full 2-information 3-VU
2									 Type-1 flr
3								        	fle
4								       	 Phi
5   re	re	re	re	rw	rw	rw	rw      		RgnEnable|RgnWork
6 2  							        		rgnError
7 3								  	Type-0 iInf
8 4									uInf
9 5									netSparc
a 6									CheckSumm
*/

//----------------Indication---------------------------------------------
  if (flIn>0 ) { flIn = 0;   	 // If a file is received
      I[fZn]->Text= AnsiString(iFlt[fZn]);
      U[fZn]->Text= AnsiString(uFlt[fZn]);
      R[fZn]->Text= AnsiString(rMode[flP[fZn]>>5]);
/*                              	// Reading from base, example. uitf - UIFx
   asm {
        mov eax,uitf
        mov fle,ah
        mov flr,al
        mov cl,16
        shr eax,cl
        mov ufl,ah
        mov ifl,al
       }
    E3->Text= AnsiString(uiF[iZn][0]);
    U[1]->Text= AnsiString(ufl);
    I[1]->Text= AnsiString(ifl);
*/

// RGN
    if ((rWE[fZn] & 0x80))  {  		 // Осад. разрешены?
       omp[fZn]->Brush->Color=clYellow; orp[fZn]->Brush->Color=clYellow;
       oma[fZn]->Brush->Color=clYellow; ora[fZn]->Brush->Color=clYellow;
       if ((rErr[fZn] & 0x80))  {
         omp[fZn]->Brush->Color=clRed; orp[fZn]->Brush->Color=clRed;
       }
    }
     else  {
       omp[fZn]->Brush->Color=clBtnFace; orp[fZn]->Brush->Color=clBtnFace;
    }
    if ((rWE[fZn] & 0x40))  {   		// Kop. разрешены?
       cmp[fZn]->Brush->Color=clYellow; crp[fZn]->Brush->Color=clYellow;
       cma[fZn]->Brush->Color=clYellow; cra[fZn]->Brush->Color=clYellow;
       if ((rErr[fZn] & 0x80))  {
         cmp[fZn]->Brush->Color=clRed; crp[fZn]->Brush->Color=clRed;
       }
    }
     else  {
       cmp[fZn]->Brush->Color=clBtnFace; crp[fZn]->Brush->Color=clBtnFace;
    }
  } // if (flIn>0 )
//------- Preparing to save to the database---------------------------------
    cdt=cdt.CurrentDateTime(); // Time
    if (DatePicker->Date!= cdt)  DatePicker->Date = cdt;
    if (TimePicker->Time!= cdt)  { TimePicker->Time = cdt;     // 1 sec
      for (iZn=0; iZn<ZONE; iZn++) {
         uiF[iZn][nUi]= 7777;
         if (wDog[iZn]) {				// Packing byte values into a word of 32 bits
           asm {
                mov ebx,iZn
                mov ah,uFlt[ebx]
                mov al,iFlt[ebx]
                mov cl,16
                shl eax,cl
                mov ah,flE[ebx]
                mov al,flR[ebx]
                mov uitf,eax
               }
           uiF[iZn][nUi]=uitf;
      } }
      if ((++nUi)>9) nUi=9;
      Edit2->Text= AnsiString(uiF[0][nUi]) ;  // Debug
    }  //if (TimePicker->Time!=

    DecodeTime(cdt, lHour, lMin, lSec, lMSec);
    if ((!(lSec%10))&& (lSec!=rSec))  {     		// Insert Data in dbase
//     for (iZn=0; iZn<ZONE; iZn++) {
         iZn=0;
      IBQIns->ParamByName("RECDATE")->Value = cdt.DateString();
      IBQIns->ParamByName("RECTIME")->Value = cdt.TimeString();
      IBQIns->ParamByName("ZONE")->Value = iZn;
      IBQIns->ParamByName("UIF0")->Value = uiF[iZn][0];
      IBQIns->ParamByName("UIF1")->Value = uiF[iZn][1];
      IBQIns->ParamByName("UIF2")->Value = uiF[iZn][2];
      IBQIns->ParamByName("UIF3")->Value = uiF[iZn][3];
      IBQIns->ParamByName("UIF4")->Value = uiF[iZn][4];
      IBQIns->ParamByName("UIF5")->Value = uiF[iZn][5];
      IBQIns->ParamByName("UIF6")->Value = uiF[iZn][6];
      IBQIns->ParamByName("UIF7")->Value = uiF[iZn][7];
      IBQIns->ParamByName("UIF8")->Value = uiF[iZn][8];
      IBQIns->ParamByName("UIF9")->Value = uiF[iZn][9];    // 10 sec
      rgnF=(rWE[iZn] + rErr[iZn]<<8)<<16 + Phi[iZn] + nSpark[iZn]<<8;
      IBQIns->ParamByName("RGN")->Value = rgnF;
      nUi=0;
      rSec = lSec;
      IBQIns->ExecSQL();
      //IBQCommit->ExecSQL();

    } // if (!(Sec%10)) if(lSec!=rSec)




}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
  //DM->Db->Connected=true;
  hCom = CreateFile(
           "filtb.chn",        		// address of name of the communications device
           GENERIC_READ,       	// access (read-write) mode
           0,                  		// share mode
           NULL,               		// address of security descriptor
           OPEN_EXISTING,     		 // how to create
           0,                  		// file attributes
           NULL                		// handle of file with attributes to copy
         );

     R[0]= r1;   R[1]= r2;    R[2]= r3;
     I[0]= i1;   I[1]= i2;    I[2]= i3;
     U[0]= u1;   U[1]= u2;    U[2]= u3;
     cmp[0]=cmp1; cma[0]=cma1; crp[0]=crp1; cra[0]=cra1;
     cmp[1]=cmp2; cma[1]=cma2; crp[1]=crp2; cra[1]=cra2;
     cmp[2]=cmp1; cma[2]=cma1; crp[2]=crp1; cra[2]=cra1;
     cmp[3]=cmp2; cma[3]=cma2; crp[3]=crp2; cra[3]=cra2;
     omp[0]=omp1; oma[0]=oma1; orp[0]=orp1; ora[0]=ora1;
     omp[1]=omp2; oma[1]=oma2; orp[1]=orp2; ora[1]=ora2;
     omp[2]=omp1; oma[2]=oma1; orp[2]=orp1; ora[2]=ora1;
     omp[3]=omp2; oma[3]=oma2; orp[3]=orp2; ora[3]=ora2;




}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   rWE[0]=0xff; rWE[1]=0xff; fZn=1;  flIn = 2;// On
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   rWE[1]=0xf0; fZn=1;  flIn = 2;    //Off
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button3Click(TObject *Sender)
{
   rWE[1]=0x0;  fZn=1;   flIn = 2;  //Off          // Disable
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button4Click(TObject *Sender)
{
   rErr[1]=0xff;  fZn=1;   flIn = 2;            //Err
}
//---------------------------------------------------------------------------



