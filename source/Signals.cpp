//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Signals.h"
#include "OSC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSigForm *SigForm;
//---------------------------------------------------------------------------
__fastcall TSigForm::TSigForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSigForm::sigType(int i)
{
        switch(i)
        {
                case sigSIN:
                        OSCForm->LoadJPEGRes(Image1->Picture,"sin_jpg");
                        break;
                case sigAM:
                        OSCForm->LoadJPEGRes(Image1->Picture,"AM_jpg");
                        break;
                case sigFM:
                        OSCForm->LoadJPEGRes(Image1->Picture,"FM_jpg");
                        break;
                case sigPM:
                        OSCForm->LoadJPEGRes(Image1->Picture,"PM_jpg");
                        break;
                case sigIMP:
                        OSCForm->LoadJPEGRes(Image1->Picture,"IMP_jpg");
                        break;
                case sigP_IMP:
                        OSCForm->LoadJPEGRes(Image1->Picture,"P_IMP_jpg");
                        break;
                case sig2_IMP:
                        OSCForm->LoadJPEGRes(Image1->Picture,"2_IMP_jpg");
                        break;
        }
}
void __fastcall TSigForm::FormResize(TObject *Sender)
{
        Image1->Width=this->ClientWidth-18;
        Image1->Height=this->ClientHeight-20;
}
//---------------------------------------------------------------------------

