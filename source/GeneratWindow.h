//---------------------------------------------------------------------------

#ifndef GeneratWindowH
#define GeneratWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <math.h>
#include <vector.h>

#include "Signals.h"
//---------------------------------------------------------------------------
enum sigType{sigNONE=0, sigSIN, sigAM, sigFM, sigPM, sigIMP, sigP_IMP, sig2_IMP,
sigCONST};
struct SignalParam
{
        sigType type;   //Тип сигнала
        char Name[40]; //Имя сигнала
        double Uc;  //Амплитуда
        double fc;  //Частота несущей
        double fm;  //Частота модулирующего сигнала
        double m;   //Глубина модуляции
        double T;   //Период повторения импульсов
        double tau; //Длина импульса
        double tau2; //Длина второго импульса в пачке
        double tInt;  //Интервал между импульсами
        short int N;  //Количество импульсов в пачке
        double df;  //Диапазон изменения частоты
        double Tf;  //Период измененния частоты
        double Fi;  //Интервал между импульсами
        double fi0;  //Начальная фаза
};

class TTractForm : public TForm
{
__published:	// IDE-managed Components
        TComboBox *TypeChooserBox;
        TEdit *fcEdit;
        TEdit *UcEdit;
        TEdit *fmEdit;
        TEdit *mEdit;
        TLabel *fcLabel;
        TLabel *UcLabel;
        TLabel *mLabel;
        TLabel *fmLabel;
        TLabel *Label2;
        TEdit *TtEdit;
        TLabel *TtLabel;
        TEdit *tauEdit;
        TLabel *tauLabel1;
        TEdit *tIntEdit;
        TLabel *tIntLabel;
        TLabel *NLabel;
        TEdit *NEdit;
        TLabel *TfLabel;
        TEdit *TfEdit;
        TLabel *dfLabel;
        TEdit *dfEdit;
        TEdit *FiEdit;
        TLabel *FiLabel1;
        TEdit *fi0Edit;
        TLabel *fi0Label1;
        TLabel *fi0Label2;
        TLabel *fi0Label3;
        TLabel *tauLabel3;
        TLabel *tauLabel2;
        TLabel *FiLabel3;
        TLabel *FiLabel2;
        TLabel *NameLabel;
        TEdit *NameEdit;
        TButton *SaveBtn;
        TButton *InfBtn;
        TButton *DelBtn;
        TListBox *signalsList;
        TLabel *tau2Label3;
        TLabel *tau2Label2;
        TLabel *tau2Label1;
        TEdit *tau2Edit;
        void __fastcall TypeChooserBoxChange(TObject *Sender);
        void __fastcall UcEditChange(TObject *Sender);
        void __fastcall fcEditChange(TObject *Sender);
        void __fastcall fmEditChange(TObject *Sender);
        void __fastcall mEditChange(TObject *Sender);
        void __fastcall tauEditChange(TObject *Sender);
        void __fastcall TtEditChange(TObject *Sender);
        void __fastcall tIntEditChange(TObject *Sender);
        void __fastcall dfEditChange(TObject *Sender);
        void __fastcall FiEditChange(TObject *Sender);
        void __fastcall TfEditChange(TObject *Sender);
        void __fastcall NEditChange(TObject *Sender);
        void __fastcall fi0EditChange(TObject *Sender);
        void __fastcall InfBtnClick(TObject *Sender);
        void __fastcall UcEditKeyPress(TObject *Sender, char &Key);
        void __fastcall fcEditKeyPress(TObject *Sender, char &Key);
        void __fastcall fi0EditKeyPress(TObject *Sender, char &Key);
        void __fastcall FiEditKeyPress(TObject *Sender, char &Key);
        void __fastcall fmEditKeyPress(TObject *Sender, char &Key);
        void __fastcall mEditKeyPress(TObject *Sender, char &Key);
        void __fastcall NEditKeyPress(TObject *Sender, char &Key);
        void __fastcall tauEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TfEditKeyPress(TObject *Sender, char &Key);
        void __fastcall tIntEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TtEditKeyPress(TObject *Sender, char &Key);
        void __fastcall dfEditKeyPress(TObject *Sender, char &Key);
        void __fastcall SaveBtnClick(TObject *Sender);
        void __fastcall NameEditChange(TObject *Sender);
        void __fastcall signalsListClick(TObject *Sender);
        void __fastcall DelBtnClick(TObject *Sender);
        void __fastcall tau2EditChange(TObject *Sender);
        void __fastcall tau2EditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
        SignalParam signalParam;
        bool tractN;
        vector<SignalParam> *dataBase;
        bool connect;


        void __fastcall addNewSignal();
        void __fastcall updateSignal();
        void __fastcall dispSignalParam();
public:		// User declarations
        __fastcall TTractForm(TComponent* Owner);
        SignalParam __fastcall getSignalParam();
        int __fastcall getItemIndex();
        void __fastcall setTractN(bool tractN);
        void __fastcall readSignals();
        void __fastcall setSignalParam(SignalParam param);
        void __fastcall setItemIndex(int index);
        void __fastcall check(TEdit *Sender, char &Key, bool allowMinus);
};
//---------------------------------------------------------------------------
extern PACKAGE TTractForm *TractForm;
//---------------------------------------------------------------------------
#endif
