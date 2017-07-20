//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("vfwin.res");
USEFORM("mainfrm.cpp", MainForm);
USEFORM("dmm.cpp", DM); /* TDataModule: File Type */
USEUNIT("Unit1.cpp");
USEFORM("rgn.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TDM), &DM);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
