//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                                                  
#include "GeneratWindow.h"
#include "OSC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTractForm *TractForm;
//---------------------------------------------------------------------------
__fastcall TTractForm::TTractForm(TComponent* Owner)
        : TForm(Owner)
{
        memset(&signalParam,0,sizeof(signalParam));
        dataBase=&OSCForm->dataBase;
        tractN=false;

        signalsList->ItemIndex=0;
        readSignals();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::TypeChooserBoxChange(TObject *Sender)
{
        signalParam.type=TypeChooserBox->ItemIndex;
        connect=true;   //Выбран ли сигнал
        switch(signalParam.type)
        {
                case sigNONE:       //Нет сигнала
                {
                        UcEdit->Visible=false;
                        UcLabel->Visible=false;
                        fcEdit->Visible=false;
                        fcLabel->Visible=false;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        memset(&signalParam,0,sizeof(signalParam)); //обнуление параметров
                        InfBtn->Enabled=false;
                        connect=false;
                        break;
                }
                case sigSIN:           //Синусоида
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=true;
                        fcLabel->Visible=true;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=true;
                        fi0Label1->Visible=true;
                        fi0Label2->Visible=true;
                        fi0Label3->Visible=true;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);    //Запись данных из полей ввода
                        fcEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigAM:            //Амплитудная модуляция
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=true;
                        fcLabel->Visible=true;
                        fmEdit->Visible=true;
                        fmLabel->Visible=true;
                        mEdit->Visible=true;
                        mLabel->Visible=true;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        fcEditChange(NULL);
                        fmEditChange(NULL);
                        mEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigFM:           //Частотная модуляция
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=true;
                        fcLabel->Visible=true;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=true;
                        dfLabel->Visible=true;
                        TfEdit->Visible=true;
                        TfLabel->Visible=true;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        fcEditChange(NULL);
                        TfEditChange(NULL);
                        dfEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigPM:         //Фазовая модуляция
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=true;
                        fcLabel->Visible=true;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false; 
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=true;
                        TfLabel->Visible=true;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=true;
                        FiLabel1->Visible=true;
                        FiLabel2->Visible=true;
                        FiLabel3->Visible=true;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        fcEditChange(NULL);
                        TfEditChange(NULL);
                        FiEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigIMP:      //Одиночные прямоугольные импульсы
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=false;
                        fcLabel->Visible=false;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        tauEdit->Visible=true;
                        tauLabel1->Visible=true;
                        tauLabel2->Visible=true;
                        tauLabel3->Visible=true;
                        TtEdit->Visible=true;
                        TtLabel->Visible=true;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        tauEditChange(NULL);
                        TtEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigP_IMP:            //Пачка прямоугольных импульсов
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=false;
                        fcLabel->Visible=false;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        tauEdit->Visible=true;
                        tauLabel1->Visible=true;
                        tauLabel2->Visible=true;
                        tauLabel3->Visible=true;
                        TtEdit->Visible=true;
                        TtLabel->Visible=true;
                        tIntEdit->Visible=true;
                        tIntLabel->Visible=true;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=true;
                        NLabel->Visible=true;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        tauEditChange(NULL);
                        TtEditChange(NULL);
                        tIntEditChange(NULL);
                        NEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sig2_IMP:            //Пара прямоугольных импульсов
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=false;
                        fcLabel->Visible=false;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        tauEdit->Visible=true;
                        tauLabel1->Visible=true;
                        tauLabel2->Visible=true;
                        tauLabel3->Visible=true;
                        TtEdit->Visible=true;
                        TtLabel->Visible=true;
                        tIntEdit->Visible=true;
                        tIntLabel->Visible=true;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=true;
                        tau2Label1->Visible=true;
                        tau2Label2->Visible=true;
                        tau2Label3->Visible=true;
                        UcEditChange(NULL);
                        tauEditChange(NULL);
                        tau2EditChange(NULL);
                        TtEditChange(NULL);
                        tIntEditChange(NULL);
                        InfBtn->Enabled=true;
                        break;
                }
                case sigCONST:       //Постоянное напряжение
                {
                        UcEdit->Visible=true;
                        UcLabel->Visible=true;
                        fcEdit->Visible=false;
                        fcLabel->Visible=false;
                        fmEdit->Visible=false;
                        fmLabel->Visible=false;
                        mEdit->Visible=false;
                        mLabel->Visible=false;
                        TtEdit->Visible=false;
                        TtLabel->Visible=false;
                        tauEdit->Visible=false;
                        tauLabel1->Visible=false;
                        tauLabel2->Visible=false;
                        tauLabel3->Visible=false;
                        tIntEdit->Visible=false;
                        tIntLabel->Visible=false;
                        dfEdit->Visible=false;
                        dfLabel->Visible=false;
                        TfEdit->Visible=false;
                        TfLabel->Visible=false;
                        NEdit->Visible=false;
                        NLabel->Visible=false;
                        FiEdit->Visible=false;
                        FiLabel1->Visible=false;
                        FiLabel2->Visible=false;
                        FiLabel3->Visible=false;
                        fi0Edit->Visible=false;
                        fi0Label1->Visible=false;
                        fi0Label2->Visible=false;
                        fi0Label3->Visible=false;
                        tau2Edit->Visible=false;
                        tau2Label1->Visible=false;
                        tau2Label2->Visible=false;
                        tau2Label3->Visible=false;
                        UcEditChange(NULL);
                        InfBtn->Enabled=false;
                        break;
                }

        }
        OSCForm->setConnection(tractN,connect);
        OSCForm->signalCalcOnce();
}

SignalParam __fastcall TTractForm::getSignalParam()
{
     return signalParam;
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::UcEditChange(TObject *Sender)
{
     try
     {
        signalParam.Uc=UcEdit->Text.ToDouble();
        if (fabs(signalParam.Uc)>250)
        {
               signalParam.Uc=signalParam.Uc>0?250:-250;
               UcEdit->Text=FloatToStr(signalParam.Uc);
               UcEdit->SelStart=UcEdit->Text.Length();
        }
     }
     catch(...)
     {
        signalParam.Uc=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::fcEditChange(TObject *Sender)
{
     if (!fcEdit->Visible)
        return;
     try
     {
        signalParam.fc=fcEdit->Text.ToDouble();
        if (signalParam.fc>2000000)
        {
               signalParam.fc=2000000;   //Максимальная частота - 2 МГц
               fcEdit->Text="2000000";
               fcEdit->SelStart=fcEdit->Text.Length();
        }
     }
     catch(...)
     {
        signalParam.fc=0;
     }
     if (signalParam.fc!=0)
     {
        signalParam.T=1/signalParam.fc;
     }
     else
     {
        signalParam.T=0;
     }
     TtEdit->Text=FloatToStr(signalParam.T*1000);
     dfEditChange(NULL);
     tauEditChange(NULL);
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::fmEditChange(TObject *Sender)
{
     try
     {
        signalParam.fm=fmEdit->Text.ToDouble();
     }
     catch(...)
     {
        signalParam.fm=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::mEditChange(TObject *Sender)
{
     try
     {
        signalParam.m=mEdit->Text.ToDouble();
        if (signalParam.m>1)
        {
               signalParam.m=1;
               mEdit->Text="1";
               mEdit->SelStart=mEdit->Text.Length();
        }
     }
     catch(...)
     {
        signalParam.m=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------


void __fastcall TTractForm::tauEditChange(TObject *Sender)
{
     try
     {
        signalParam.tau=tauEdit->Text.ToDouble()/1000;
        signalParam.fm=fmEdit->Text.ToDouble();
        /*if (signalParam.tau>signalParam.T)
        {
               signalParam.tau=signalParam.T;
               tauEdit->Text=TtEdit->Text;
               tauEdit->SelStart=tauEdit->Text.Length();
        }*/
     }
     catch(...)
     {
        signalParam.tau=0;
     }
     //tIntEditChange(NULL);
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::TtEditChange(TObject *Sender)
{
     if (!TtEdit->Visible)
        return;
     try
     {
        signalParam.T=TtEdit->Text.ToDouble()/1000;
        if (signalParam.T<0.0000005 && signalParam.T!=0)
        {
               signalParam.T=0.0000005;
               TtEdit->Text=FloatToStr(signalParam.T*1000);
               TtEdit->SelStart=TtEdit->Text.Length();
        }
     }
     catch(...)
     {
        signalParam.T=0;
     }
     if (signalParam.T!=0)
     {
        signalParam.fc=1/signalParam.T;
     }
     else
     {
        signalParam.fc=0;
     }
     fcEdit->Text=FloatToStr(signalParam.fc);
     tauEditChange(NULL);
     dfEditChange(NULL);
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::tIntEditChange(TObject *Sender)
{
     try
     {
        signalParam.tInt=tIntEdit->Text.ToDouble()/1000;
        /*if (signalParam.tInt>signalParam.T)
        {
               signalParam.tInt=signalParam.T;
               tIntEdit->Text=TtEdit->Text;
               tIntEdit->SelStart=tIntEdit->Text.Length();
        }
        if (signalParam.tInt<signalParam.tau)
        {
               signalParam.tInt=signalParam.tau;
               tIntEdit->Text=tauEdit->Text;
               tIntEdit->SelStart=tIntEdit->Text.Length();
        } */
     }
     catch(...)
     {
        signalParam.tInt=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------


void __fastcall TTractForm::dfEditChange(TObject *Sender)
{
     try
     {
        signalParam.df=dfEdit->Text.ToDouble();
        /*if (signalParam.df>signalParam.fc)
        {
               signalParam.df=signalParam.fc;
               dfEdit->Text=fcEdit->Text;
               dfEdit->SelStart=dfEdit->Text.Length();
        }*/
     }
     catch(...)
     {
        signalParam.df=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::FiEditChange(TObject *Sender)
{
     try
     {
        signalParam.Fi=FiEdit->Text.ToDouble()*M_PI/180;
     }
     catch(...)
     {
        signalParam.Fi=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::TfEditChange(TObject *Sender)
{
     try
     {
        signalParam.Tf=TfEdit->Text.ToDouble()/1000;
     }
     catch(...)
     {
        signalParam.Tf=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::NEditChange(TObject *Sender)
{
     try
     {
        signalParam.N=NEdit->Text.ToInt();
        int max;
        max=signalParam.T/signalParam.tInt;
        if (signalParam.N>max)
        {
                NEdit->Text=IntToStr(max);
                NEdit->SelStart=NEdit->Text.Length();
        }
        
     }
     catch(...)
     {
        signalParam.N=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------


void __fastcall TTractForm::fi0EditChange(TObject *Sender)
{
     try
     {
        signalParam.fi0=fi0Edit->Text.ToDouble()*M_PI/180;
     }
     catch(...)
     {
        signalParam.fi0=0;
     }
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::NameEditChange(TObject *Sender)
{
      if (NameEdit->Text.Length()>39)
      {
                NameEdit->Text=NameEdit->Text.SubString(1,39);
                NameEdit->SelStart=NameEdit->Text.Length();
      }
      strcpy(signalParam.Name,NameEdit->Text.c_str());
      SaveBtn->Enabled=!NameEdit->Text.IsEmpty();
}
//---------------------------------------------------------------------------


void __fastcall TTractForm::InfBtnClick(TObject *Sender)
{
        SigForm->sigType(signalParam.type);
        SigForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTractForm::check(TEdit *Sender, char &Key, bool allowMinus)
{
        if ((Key >= '0') && (Key<='9'))  //цифра
                return;
         //Обработка десятичного разделителя
         if ((Key=='.') ||(Key==','))
         {
                Key=DecimalSeparator;
                if (Sender->Text.Pos(DecimalSeparator)!=0)
                        Key=0;
                return;
         }
         if (Key==VK_BACK)
                return;
         if (Key=='-' && allowMinus)
         {
                if (Sender->Text.Pos('-')!=0 || Sender->SelStart!=0)
                        Key=0;
                return;
         }
         Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TTractForm::UcEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, true);
}
//---------------------------------------------------------------------------


void __fastcall TTractForm::fcEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::fi0EditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, true);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::FiEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, true);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::fmEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::mEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::NEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
     if (Key==DecimalSeparator)
        Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::tauEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::TfEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::tIntEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::TtEditKeyPress(TObject *Sender, char &Key)
{
     check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::dfEditKeyPress(TObject *Sender, char &Key)
{
        check((TEdit*)Sender, Key,false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::setTractN(bool tractN)
{
        this->tractN=tractN;
}

//---------------------------------------------------------------------------
void __fastcall TTractForm::signalsListClick(TObject *Sender)
{
        if (signalsList->ItemIndex==0)
        {
                NameEdit->Text="";
                DelBtn->Enabled=false;
                return;
        }
        DelBtn->Enabled=true;
        vector<SignalParam>::iterator it=dataBase->begin()+signalsList->ItemIndex-1;
        signalParam=(*it);
        dispSignalParam();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::setSignalParam(SignalParam param)
{
        signalParam=param;
        dispSignalParam();
}

//---------------------------------------------------------------------------
void __fastcall TTractForm::dispSignalParam()
{
        TypeChooserBox->ItemIndex=signalParam.type;

        NameEdit->Text=signalParam.Name;
        switch(signalParam.type)
        {
                case sigNONE:
                        break;
                case sigSIN:           //Синусоида
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        fi0Edit->Text=FloatToStr(signalParam.fi0*180/M_PI); 
                        fcEdit->Text=FloatToStr(signalParam.fc);
                        break;
                }
                case sigAM:            //Амплитудная модуляция
                {
                        fmEdit->Text=FloatToStr(signalParam.fm);
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        mEdit->Text=FloatToStr(signalParam.m);   
                        fcEdit->Text=FloatToStr(signalParam.fc);
                        break;
                }
                case sigFM:           //Частотная модуляция
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        dfEdit->Text=FloatToStr(signalParam.df);
                        TfEdit->Text=FloatToStr(signalParam.Tf*1000);
                        fcEdit->Text=FloatToStr(signalParam.fc);
                        break;
                }
                case sigPM:         //Фазовая модуляция
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        FiEdit->Text=FloatToStr(signalParam.Fi*180/M_PI);
                        TfEdit->Text=FloatToStr(signalParam.Tf*1000);    
                        fcEdit->Text=FloatToStr(signalParam.fc);
                        break;
                }
                case sigIMP:      //Одиночные прямоугольные импульсы
                {                                                      
                        tauEdit->Text=FloatToStr(signalParam.tau*1000);
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        TtEdit->Text=FloatToStr(signalParam.T*1000);
                        break;
                }
                case sigP_IMP:            //Пачка прямоугольных импульсов
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        tauEdit->Text=FloatToStr(signalParam.tau*1000);
                        tIntEdit->Text=FloatToStr(signalParam.tInt*1000);
                        TtEdit->Text=FloatToStr(signalParam.T*1000);
                        NEdit->Text=IntToStr(signalParam.N);
                        break;
                }
                case sig2_IMP:            //Пара прямоугольных импульсов
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        tauEdit->Text=FloatToStr(signalParam.tau*1000);
                        tIntEdit->Text=FloatToStr(signalParam.tInt*1000);
                        tau2Edit->Text=FloatToStr(signalParam.tau2*1000); 
                        TtEdit->Text=FloatToStr(signalParam.T*1000);
                        break;
                }
                case sigCONST:            //Постоянное напряжение
                {
                        UcEdit->Text=FloatToStr(signalParam.Uc);
                        break;
                }
        } 
        TypeChooserBoxChange(this);
}

//---------------------------------------------------------------------------
void __fastcall TTractForm::SaveBtnClick(TObject *Sender)
{
        if (signalsList->ItemIndex==0)
        {
                addNewSignal();
        }
        else
        {       if (MessageBox(this->Handle,"Вы уверены, что хотите изменить параметры сигнала?",
        "Предупреждение",MB_YESNO|MB_ICONQUESTION) == IDYES)
                {
                        updateSignal();
                }
        }
        signalsListClick(this);
}
//---------------------------------------------------------------------------
//Добавить новый сигнал в базу данных
void __fastcall TTractForm::addNewSignal()
{
     dataBase->push_back(signalParam);
     OSCForm->writeDataBase(tractN);
     readSignals();
     signalsList->ItemIndex=dataBase->size();
}

//Обновить сигнал в базе данных
void __fastcall TTractForm::updateSignal()
{
     int i=signalsList->ItemIndex-1;
     (*dataBase)[i]=signalParam;
     OSCForm->writeDataBase(tractN);
     readSignals();
     signalsList->ItemIndex=i+1;
}

//Считать список сигналов из базы данных
void __fastcall TTractForm::readSignals()
{
      int pos=signalsList->ItemIndex;
      signalsList->Clear();
      signalsList->Items->Add("Новый сигнал");
      for (vector<SignalParam>::iterator it=dataBase->begin(); it!=dataBase->end();++it)
      {
        signalsList->Items->Add((*it).Name);
      }
      if (pos<=signalsList->Count-1)
      {
           signalsList->ItemIndex=pos;
      }
      else
      {
           signalsList->ItemIndex=0;
      }
      signalsListClick(this);
}
void __fastcall TTractForm::DelBtnClick(TObject *Sender)
{
        if (MessageBox(this->Handle,"Вы уверены, что хотите удалить данный сигнал?",
        "Предупреждение",MB_YESNO|MB_ICONQUESTION) == IDNO)
                return;
        int i=signalsList->ItemIndex-1;
        if(i<0)
                return;
        dataBase->erase(dataBase->begin()+i);
        OSCForm->writeDataBase(tractN);
        readSignals();
        signalsList->ItemIndex=0;
        signalsListClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::tau2EditChange(TObject *Sender)
{
        try
     {
        signalParam.tau2=tau2Edit->Text.ToDouble()/1000;
     }
     catch(...)
     {
        signalParam.tau2=0;
     }
     
     OSCForm->signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::tau2EditKeyPress(TObject *Sender, char &Key)
{
        check((TEdit*)Sender, Key, false);
}
//---------------------------------------------------------------------------

void __fastcall TTractForm::setItemIndex(int index)
{
        if (index<signalsList->Items->Count)
        {
                signalsList->ItemIndex=index;
                if (index!=0)
                {
                        DelBtn->Enabled=true;
                }
        }
}

int __fastcall TTractForm::getItemIndex()
{
        return signalsList->ItemIndex;

}
