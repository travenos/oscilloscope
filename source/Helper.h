//---------------------------------------------------------------------------

#ifndef HelperH
#define HelperH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>

#include "about.h"
//---------------------------------------------------------------------------

class THelperForm : public TForm
{
__published:	// IDE-managed Components
        TCppWebBrowser *CppWebBrowser1;
        TButton *ButtonSearch;
        TListBox *ListBox1;
        TButton *Button1;
        TListBox *ListBox2;
        TLabel *Label1;
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ButtonSearchClick(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall ListBox2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        AnsiString folder;
        AnsiString file;
public:		// User declarations
        __fastcall THelperForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THelperForm *HelperForm;
//---------------------------------------------------------------------------
#endif
