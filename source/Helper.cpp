//---------------------------------------------------------------------------

#include <vcl.h>
#include "mshtmhst.h"
#include "mshtmcid.h"
#include "mshtml.h"

#pragma hdrstop

#include "Helper.h"
#include "OSC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"


#define HTMLID_FIND 1
THelperForm *HelperForm;
//---------------------------------------------------------------------------
__fastcall THelperForm::THelperForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THelperForm::FormResize(TObject *Sender)
{
        CppWebBrowser1->Width=this->ClientWidth - CppWebBrowser1->Left - 3;
        CppWebBrowser1->Height=this->ClientHeight - CppWebBrowser1->Top - 3;
}
//---------------------------------------------------------------------------
void __fastcall THelperForm::FormCreate(TObject *Sender)
{
        try       //Извлечение "странички" из ресурсов
        {
                folder=_wgetenv(L"APPDATA");
                folder+="\\osc";
                file=folder+"\\helper.mht";
                if (!DirectoryExists(folder))
                {
                        CreateDir(folder);
                }
                TResourceStream* helpRes;
                helpRes = new TResourceStream((int)HInstance, "helper_mht", "HTML");
                helpRes->SaveToFile(file);
                helpRes->Free();
        }
        catch(...)
        {
                ShowMessage("Ошибка запуска помощника");
                folder=GetCurrentDir();
        }
        AnsiString adr;
        adr=("mhtml:file://"+file+"#razdel0");
        WideString wadr(adr);
        CppWebBrowser1->Navigate(wadr.c_bstr());
        this->AutoSize=false;
}
//---------------------------------------------------------------------------
void __fastcall THelperForm::FormShow(TObject *Sender)
{
        Button1->SetFocus();
        CppWebBrowser1->SetFocus();
}
//---------------------------------------------------------------------------
//Поиск по документу
void __fastcall THelperForm::ButtonSearchClick(TObject *Sender)
{
        //Тут какой-то непонятный код, который я скопировал
        //Разбираться в API Internet Explorer'а у меня нет желания
    const GUID CGID_IWebBrowser =
        {0xed016940, 0xbd5b, 0x11cf,
        {0xba, 0x4e, 0x0, 0xc0, 0x4f, 0xd7, 0x08, 0x16}} ;
    LPDISPATCH lpDispatch = CppWebBrowser1->ControlInterface->get_Document();
    if(lpDispatch)
    {
        IOleCommandTarget* pcmd=NULL;
        if( SUCCEEDED(lpDispatch->QueryInterface(IID_IOleCommandTarget,(void**)&pcmd) ) )
        {
            pcmd->Exec(&CGID_IWebBrowser, HTMLID_FIND, 0, NULL, NULL);
            pcmd->Release();
        }
        lpDispatch->Release();
    }
}
//---------------------------------------------------------------------------

void __fastcall THelperForm::ListBox1Click(TObject *Sender)
{
        int count=ListBox1->ItemIndex;
        AnsiString adr;
        adr=("mhtml:file://"+file+"#razdel"+IntToStr(count));
        WideString wadr(adr); 
        ListBox1->ItemIndex=-1;

        CppWebBrowser1->SetFocus();
        CppWebBrowser1->Navigate(wadr.c_bstr());

}
//---------------------------------------------------------------------------

void __fastcall THelperForm::ListBox2Click(TObject *Sender)
{
        int count=ListBox2->ItemIndex;
        count+=3;
        AnsiString adr;
        adr=("mhtml:file://"+file+"#razdel"+IntToStr(count));
        WideString wadr(adr);
        ListBox2->ItemIndex=-1;

        CppWebBrowser1->SetFocus();
        CppWebBrowser1->Navigate(wadr.c_bstr());
}
//---------------------------------------------------------------------------


void __fastcall THelperForm::Button1Click(TObject *Sender)
{
        AboutBox->Show();        
}
//---------------------------------------------------------------------------

void __fastcall THelperForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        OSCForm->CloseHelper();
        //Можно убирать Помощник из памяти при закрытии. А можно и нет.
}
//---------------------------------------------------------------------------


