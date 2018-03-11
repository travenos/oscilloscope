//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("GeneratWindow.cpp", TractForm);
USEFORM("Helper.cpp", HelperForm);
USEFORM("OSC.cpp", OSCForm);
USEFORM("about.cpp", AboutBox);
USEFORM("Signals.cpp", SigForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Осциллограф";
                 Application->CreateForm(__classid(TOSCForm), &OSCForm);
                 Application->CreateForm(__classid(TTractForm), &TractForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TSigForm), &SigForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
