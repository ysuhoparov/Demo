//---------------------------------------------------------------------------

#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <IBTable.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImageList *ImageList2;
        TImageList *ImageList1;
        TMainMenu *MainMenu1;
        TMenuItem *NFile;
        TMenuItem *NReference;
        TMenuItem *NReport;
        TCoolBar *CoolBar1;
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TToolButton *ToolButton2;
        TToolButton *ToolButton7;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TToolButton *ToolButton6;
        TToolButton *ToolButton8;
        TDateTimePicker *TimePicker;
        TDateTimePicker *DatePicker;
        TEdit *Edit1;
        TStatusBar *StatusBar1;
        TMenuItem *Open1;
        TMenuItem *Close1;
        TMenuItem *Connect1;
        TMenuItem *Disconnect1;
        TMenuItem *Exit1;
        TMenuItem *Report11;
        TMenuItem *Report21;
        TMenuItem *Report31;
        TDataSource *DataSource1;
        TEdit *u1;
        TEdit *i1;
        TEdit *i2;
        TEdit *u2;
        TEdit *u3;
        TEdit *i3;
        TTimer *Timer1;
        TDBGrid *DBGrid1;
        TIBQuery *IBQSel;
        TIBQuery *IBQCommit;
        TShape *cmp1;
        TShape *crp1;
        TShape *cma1;
        TShape *cra1;
        TShape *Shape1;
        TMemo *Memo1;
        TPanel *Panel1;
        TEdit *r1;
        TEdit *r2;
        TEdit *r3;
        TIBQuery *IBQInsDt;
        TIBTable *IBTable1;
        TEdit *r0;
        TEdit *Edit2;
        TEdit *E3;
        TIBQuery *IBQIns;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TShape *cmp2;
        TShape *crp2;
        TShape *cra2;
        TShape *cma2;
        TShape *omp1;
        TShape *orp1;
        TShape *ora1;
        TShape *oma1;
        TShape *omp2;
        TShape *orp2;
        TShape *ora2;
        TShape *oma2;
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        AnsiString tOld;
        int tCount,trCount,r,t;
        unsigned char nu, Z, F,zw, flRgnOn[3][4];   //[Zone][nRgn]
        int ufiu[4];
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
