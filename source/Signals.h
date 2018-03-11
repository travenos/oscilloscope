//---------------------------------------------------------------------------

#ifndef SignalsH
#define SignalsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSigForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSigForm(TComponent* Owner);
         void __fastcall sigType(int i);
};
//---------------------------------------------------------------------------
extern PACKAGE TSigForm *SigForm;
//---------------------------------------------------------------------------
#endif
