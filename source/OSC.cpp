//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "OSC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

#define alphaConst1 0.01570796
#define alphaConst2 0.0235619449
#define penWidth 2 //Ширина риски непрерывных ручек
TOSCForm *OSCForm;
//---------------------------------------------------------------------------
__fastcall TOSCForm::TOSCForm(TComponent* Owner)
        : TForm(Owner)
{
        //Инициализация полей
        value=230;
        lineWidth=3;

        positionsData=NULL;
        Fs=FSync->Text.ToDouble();   //Период синхронизации
        inpMode[0] = 1;//по умолчанию для 1.1 и 1.2
        inpMode[1] = 1;  //Переключатели ражимов входа
        kvnesh[0] = 0.5;  //по умолчанию для 2.1 и 2.2
        kvnesh[1] = 0.5;
        kvnut[0] = 1;  //по умолчанию для 2.1 и 2.2
        kvnut[1] = 1;
        updateK();
        del6[0] = false;      //Режим 6 дел.
        del6[1] = false;
        tractMode = 2;     //по умолчанию для 3 //Режим отображения каналов
        IsPwrOn = false;  //питание выключено
        //Инвертирование сигнала канала II
        invert = false;    //вытянута - неинвертируется (почему тогда true???)
        syncMode = 0;     //вытянута     //Режим синхронизации
        syncFront = true; //нажата верхнаяя     //Фронт начала развёртки (true - передний, false - задний)
        x10[0] = false;   //вытянута
        x10[1] = false;   //Усиление сигналов в 10 раз
        c[0] = -Screen->Height/2;  //Смещение нуля канала I
        c[1] = -Screen->Height/2;  //Смещение нуля канала II
        x02 = false;//вдавлена
        ct = -Screen->Width/2;   //Величина горизонтального смещения развёртки
        startVal = -2;//для 11
        autoR = true;

        tR=0.010; //Время развёртки
        tRvnut=1;

        phasem[0]=0;
        phasem[1]=0;
        memset(&param,0,sizeof(param));
        memset(&oldY,0,sizeof(oldY));
        memset(&oldU,0,sizeof(oldU));

        //ct=0;//Величина горизонтального смещения развёртки
        t=0;
        kDT=1; //Множитель времени дискретизации
        tLast=0;
        fm[0]=0;
        fm[1]=0;

        dCh=0;

        Helper=NULL;

        signalsFolder=_wgetenv(L"APPDATA");
        signalsFolder+="\\osc";

        readDataBase();

        //Загрузка изображений из ресурсов
        LoadJPEGRes(img1_1->Picture,"1_1_1_2_1_jpg");
        LoadJPEGRes(img1_2->Picture,"1_1_1_2_1_jpg");
        LoadJPEGRes(img2_1->Picture,"2_1_2_2_0_5v_jpg");
        LoadJPEGRes(img2_2->Picture,"2_1_2_2_0_5v_jpg");
        LoadJPEGRes(img4_1->Picture,"4_1_4_2_unpressed_jpg");
        LoadJPEGRes(img4_2->Picture,"4_1_4_2_unpressed_jpg");
        LoadJPEGRes(ImageLabels1->Picture,"Labels1_jpg");
        LoadJPEGRes(ImageChan2->Picture,"chan2_JPG");
        LoadJPEGRes(InvertImg->Picture,"invert_btn_pressed_jpg");
        LoadJPEGRes(img7->Picture,"7_pressed_jpg");
        LoadJPEGRes(img11->Picture,"11_pressed_jpg");
        LoadJPEGRes(img8->Picture,"8_1ms_jpg");
        LoadJPEGRes(ImagePwr->Picture,"power_off_jpg");
        LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_3->Picture,"pressed_button_jpg");
        LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn6_9->Picture,"pressed_button_jpg");
        LoadJPEGRes(ImageBtn7_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn8_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn9_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn10_9->Picture,"unpressed_button_jpg");


}
//---------------------------------------------------------------------------
int i[3] = {2, 2, 11};//массив счетчиков переключателей (первые два для элементов 2.1, 2.2, третий для элемента 8)
//ПЕРЕКЛЮЧАТЕЛИ НАПРЯЖЕНИЙ
String Images_2[12] = {"2_1_2_2_2v_jpg", "2_1_2_2_1v_jpg", "2_1_2_2_0_5v_jpg", "2_1_2_2_0_2v_jpg",
"2_1_2_2_0_1v_jpg", "2_1_2_2_50mv_jpg", "2_1_2_2_20mv_jpg", "2_1_2_2_10mv_jpg",
"2_1_2_2_5mv_jpg", "2_1_2_2_2mv_jpg", "2_1_2_2_1mv_jpg", "2_1_2_2_xv_jpg"};            //массив имен картинок переключателя
double Voltage[12] = {2, 1, 0.5, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005, 0.002, 0.001, 0.01}; //массив значений напряжений(0 - спец.значение)

int HorizV[12] = {50, 48, 47, 47, 48, 50, 52, 54, 55, 55, 54, 52};
int VerticV[12] = {75, 75, 73, 70, 68, 67, 67, 68, 70, 72, 74, 75};

//ПЕРЕКЛЮЧАТЕЛЬ ВРЕМЕНИ РАЗВЕРТКИ
String Images_8[22] = {"8_5s_jpg", "8_2s_jpg", "8_1s_jpg", "8_0_5s_jpg",
"8_0_2s_jpg", "8_0_1s_jpg", "8_50ms_jpg", "8_20ms_jpg",
"8_10ms_jpg", "8_5ms_jpg", "8_2ms_jpg", "8_1ms_jpg", "8_0_5ms_jpg",
"8_0_2ms_jpg", "8_0_1ms_jpg", "8_50mks_jpg", "8_20mks_jpg", "8_10mks_jpg",
"8_5mks_jpg", "8_2mks_jpg", "8_1mks_jpg", "8_0_5mks_jpg"};                               //массив имен картинок переключателя
double Times[22] = {50, 20, 10, 5, 2, 1, 0.5, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005, 0.002, 0.001,
0.0005, 0.0002, 0.0001, 0.00005, 0.00002, 0.00001, 0.000005};

int HorizT[22]={80, 81, 81, 81, 80, 80, 80, 79, 78, 78, 78, 77, 77, 76, 76, 77,
77, 77, 77, 78, 79, 80};
int VerticT[22]={81, 82, 82, 84, 85, 86, 86, 86, 86, 86, 85, 85, 84, 83, 83, 82,
81, 81, 81, 80, 80, 80};                    //массив значений времен

double x0, y0, r, alpha, xn, yn;


//---------------------------------------------------------------------------
void __fastcall TOSCForm::FormShow(TObject *Sender)
{
        Scroll2_1->Position = 200;
        Scroll_8->Position = 200;
        Scroll2_2->Position = 200;
        Scroll4_1->Position = 150;
        Scroll4_2->Position = 50;
        Scroll7->Position = 100;
        Scroll11->Position = 102;
        Scroll12->Position=55;
        Scroll12_II->Position=133;
        Scroll12_III->Position=0;

        this->DoubleBuffered = true;

        TractFormII=new TTractForm(this);
        TractFormII->setTractN(1);
        SW=Screen->Width;
        Ut[0][0]=new double[SW+1];
        Ut[0][1]=new double[SW+1];
        Ut[1][0]=new double[SW+1];
        Ut[1][1]=new double[SW+1];

        clearData();

        writingDown=false;
        even=false;
        dt=tR/(SW+1); //Время дискретизации

        pic=new Graphics::TBitmap();
        pic->PixelFormat=pf24bit;
        pic->Width=SW;
        pic->Height=Screen->Height;

        pic->Canvas->Brush->Color=(TColor)RGB(126, 124, 111);
        pic->Canvas->FillRect(TRect(0,0,Screen->Width,Screen->Height));
        drawGrid(0);

        Screen->BringToFront();
        Screen->Picture->Bitmap=pic;

        readSettings();
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImageBtn1_3Click(TObject *Sender)
{
        if(tractMode == 1)
        {
                LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
                tractMode = 0;
        }
        else
        {
                LoadJPEGRes(ImageBtn1_3->Picture,"pressed_button_jpg");
                tractMode = 1;
        }
        LoadJPEGRes(ImageBtn2_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
        signalCalcOnce();
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImageBtn2_3Click(TObject *Sender)
{
        if(tractMode == 2)
        {
                LoadJPEGRes(ImageBtn2_3->Picture,"unpressed_button_jpg");
                tractMode = 0;
        }
        else
        {
                tractMode = 2;
                LoadJPEGRes(ImageBtn2_3->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
        signalCalcOnce();
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImageBtn3Cick(TObject *Sender)
{
        if(tractMode == 3)
        {
                LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
                tractMode = 0;
        }
        else
        {
                tractMode = 3;
                LoadJPEGRes(ImageBtn3_3->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
        signalCalcOnce();
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImageBtn4_3Click(TObject *Sender)
{
        if(tractMode == 4)
        {
                LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
                tractMode = 0;
        }
        else
        {
                tractMode = 4;
                LoadJPEGRes(ImageBtn4_3->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
        signalCalcOnce();

}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImageBtn5_3Click(TObject *Sender)
{
        if(tractMode == 5)
        {
                LoadJPEGRes(ImageBtn5_3->Picture,"unpressed_button_jpg");
                tractMode = 0;
        }
        else
        {
                tractMode = 5;
                LoadJPEGRes(ImageBtn5_3->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_3->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_3->Picture,"unpressed_button_jpg");
        signalCalcOnce();
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::ImagePwrBtnClick(TObject *Sender)
{
        pic->Canvas->Pen->Width = 1 + Scroll12->Position*0.06;

        //Дальше код логики
        //Очистка массивов
        N=0;
        memset(&oldY,0,sizeof(oldY));
        memset(&oldU,0,sizeof(oldU));

        clearData();

        tLast=0;
        if(IsPwrOn)
        {
                LoadJPEGRes(ImagePwr->Picture, "power_off_jpg");
                IsPwrOn = false;
                Timer1->Enabled=false; pic->Canvas->FillRect(TRect(0,0,Screen->Width,Screen->Height));
                drawGrid(0);
                Screen->Picture->Bitmap=pic;
        }
        else
        {
                LoadJPEGRes(ImagePwr->Picture, "power_on_jpg");
                IsPwrOn = true;
                if (syncMode!=0)
                {
                    drawGrid(gridValue);
                    Timer1->Enabled=true;
                }
                else
                {
                        signalCalcOnce();
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::InvertImgClick(TObject *Sender)
{
        if(invert)
        {
                LoadJPEGRes(InvertImg->Picture, "invert_btn_pressed_jpg");
                invert = false;
        }
        else
        {
                LoadJPEGRes(InvertImg->Picture, "invert_btn_unpressed_jpg");
                invert = true;
        }

        signalCalcOnce();
}
//---------------------------------------------------------------------------



void __fastcall TOSCForm::ImageBtn1_9Click(TObject *Sender)
{
        if (syncMode==0)
        {
                clearData();
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        if(syncMode == 1)
        {
                LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
                syncMode = 6;
        }
        else
        {
                syncMode = 1;
                LoadJPEGRes(ImageBtn1_9->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg"); 
        CheckBox9->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn2_9Click(TObject *Sender)
{
        if (syncMode==0)
        {
                clearData();
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        if(syncMode == 2)
        {
                LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
                syncMode = 6;
        }
        else
        {
                syncMode = 2;
                LoadJPEGRes(ImageBtn2_9->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
        CheckBox9->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn3_9Click(TObject *Sender)
{
        if (syncMode==0)
        {
                clearData();
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        if(syncMode == 3)
        {
                LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
                syncMode = 6;
        }
        else
        {
                syncMode = 3;
                LoadJPEGRes(ImageBtn3_9->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
        CheckBox9->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn4_9Click(TObject *Sender)
{
        if (syncMode==0)
        {
                clearData();
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        if(syncMode == 4)
        {
                LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
                syncMode = 6;
        }
        else
        {
                syncMode = 4;
                LoadJPEGRes(ImageBtn4_9->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
        CheckBox9->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn5_9Click(TObject *Sender)
{
        if (syncMode==0)
        {
                clearData();
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        if(syncMode == 5)
        {
                LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
                syncMode = 6;
        }
        else
        {
                syncMode = 5;
                LoadJPEGRes(ImageBtn5_9->Picture,"pressed_button_jpg");
        }
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        CheckBox9->Checked = false;
}
//---------------------------------------------------------------------------



//----------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn6_9Click(TObject *Sender)
{
        syncFront = true;
        LoadJPEGRes(ImageBtn6_9->Picture,"pressed_button_jpg");
        LoadJPEGRes(ImageBtn7_9->Picture,"unpressed_button_jpg");
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::ImageBtn7_9Click(TObject *Sender)
{
        syncFront = false;
        LoadJPEGRes(ImageBtn6_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn7_9->Picture,"pressed_button_jpg");
}
//---------------------------------------------------------------------------


void __fastcall TOSCForm::Scroll_8Change(TObject *Sender)
{
        x0 = 20; y0 = 20; r = 20;
        alpha = Scroll_8->Position*alphaConst2;
        xn = x0 - r*cos(alpha-M_PI/4);
        yn = y0 - r*sin(alpha-M_PI/4);
        img8_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white2_bmp");
        img8_l->Picture->Bitmap->TransparentColor=clWhite;
        img8_l->Canvas->Pen->Color = clGreen;
        img8_l->Canvas->Pen->Width = penWidth;
        img8_l->Canvas->MoveTo(x0, y0);
        img8_l->Canvas->LineTo(xn, yn);
        tRvnut = 1+(200-Scroll_8->Position)*0.0075;
        updatedt();

        signalCalcOnce();
}
//---------------------------------------------------------------------------



void __fastcall TOSCForm::img1_1_1Click(TObject *Sender)
{
        LoadJPEGRes(img1_1->Picture,"1_1_1_2_1_jpg");
        inpMode[0] = 1;
        memset(&oldY[0],0,sizeof(oldY[0]));
        memset(&oldU[0],0,sizeof(oldU[0]));

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img1_1_2Click(TObject *Sender)
{
        LoadJPEGRes(img1_1->Picture,"1_1_1_2_2_jpg");
        inpMode[0] = 2;
        memset(&oldY[0],0,sizeof(oldY[0]));
        memset(&oldU[0],0,sizeof(oldU[0]));

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img1_1_3Click(TObject *Sender)
{
        LoadJPEGRes(img1_1->Picture,"1_1_1_2_3_jpg");
        inpMode[0] = 3;
        
        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img1_2_1Click(TObject *Sender)
{
        LoadJPEGRes(img1_2->Picture,"1_1_1_2_1_jpg");
        inpMode[1] = 1;
        memset(&oldY[1],0,sizeof(oldY[1]));
        memset(&oldU[1],0,sizeof(oldU[1]));
        
        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img1_2_2Click(TObject *Sender)
{
        LoadJPEGRes(img1_2->Picture,"1_1_1_2_2_jpg");
        inpMode[1] = 2;
        memset(&oldY[1],0,sizeof(oldY[1]));
        memset(&oldU[1],0,sizeof(oldU[1]));

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img1_2_3Click(TObject *Sender)
{
        LoadJPEGRes(img1_2->Picture,"1_1_1_2_3_jpg");
        inpMode[1] = 3;

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll2_1Change(TObject *Sender)
{
        x0 = 20; y0 = 20; r = 20;
        alpha = Scroll2_1->Position*alphaConst2;
        xn = x0 - r*cos(alpha-M_PI/4);
        yn = y0 - r*sin(alpha-M_PI/4);
        img2_1_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white2_bmp");
        img2_1_l->Picture->Bitmap->TransparentColor=clWhite;
        img2_1_l->Canvas->Pen->Color = clGreen;
        img2_1_l->Canvas->Pen->Width = penWidth;
        img2_1_l->Canvas->MoveTo(x0, y0);
        img2_1_l->Canvas->LineTo(xn, yn);
        kvnut[0] = 1+(200-Scroll2_1->Position)*0.0075;
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll2_2Change(TObject *Sender)
{
        x0 = 20; y0 = 20; r = 20;
        alpha = Scroll2_2->Position*alphaConst2;
        xn = x0 - r*cos(alpha-M_PI/4);
        yn = y0 - r*sin(alpha-M_PI/4);
        img2_2_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white2_bmp");
        img2_2_l->Picture->Bitmap->TransparentColor=clWhite;
        img2_2_l->Canvas->Pen->Color = clGreen;
        img2_2_l->Canvas->Pen->Width = penWidth;
        img2_2_l->Canvas->MoveTo(x0, y0);
        img2_2_l->Canvas->LineTo(xn, yn);
        kvnut[1] = 1+(200-Scroll2_2->Position)*0.0075;
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------


void __fastcall TOSCForm::Scroll4_1Change(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll4_1->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img4_1_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img4_1_l->Picture->Bitmap->TransparentColor=clWhite;
        img4_1_l->Canvas->Pen->Color = clGreen;
        img4_1_l->Canvas->Pen->Width = penWidth;
        img4_1_l->Canvas->MoveTo(x0, y0);
        img4_1_l->Canvas->LineTo(xn, yn);
        c[0] = -Screen->Height/2 + Scroll4_1->Position*0.005*Screen->Height;

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img4_1_lClick(TObject *Sender)
{
        if(!x10[0])
        {
                LoadJPEGRes(img4_1->Picture,"4_1_4_2_pressed_jpg");
                img4_1_l->Left = 279;
                x10[0] = true;
        }
        else
        {
                LoadJPEGRes(img4_1->Picture,"4_1_4_2_unpressed_jpg");
                img4_1_l->Left = 285;
                x10[0] = false;
        }

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img4_2_lClick(TObject *Sender)
{
        if(!x10[1])
        {
                LoadJPEGRes(img4_2->Picture,"4_1_4_2_pressed_jpg");
                img4_2_l->Left = 151;
                x10[1] = true;
        }
        else
        {
                LoadJPEGRes(img4_2->Picture,"4_1_4_2_unpressed_jpg");
                img4_2_l->Left = 157;
                x10[1] = false;
        }

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll4_2Change(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll4_2->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img4_2_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img4_2_l->Picture->Bitmap->TransparentColor=clWhite;
        img4_2_l->Canvas->Pen->Color = clGreen;
        img4_2_l->Canvas->Pen->Width = penWidth;
        img4_2_l->Canvas->MoveTo(x0, y0);
        img4_2_l->Canvas->LineTo(xn, yn);
        c[1] = -Screen->Height/2 + Scroll4_2->Position*0.005*Screen->Height;
        
        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll7Change(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll7->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img7_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img7_l->Picture->Bitmap->TransparentColor=clWhite;
        img7_l->Canvas->Pen->Color = clGreen;
        img7_l->Canvas->Pen->Width = penWidth;
        img7_l->Canvas->MoveTo(x0, y0);
        img7_l->Canvas->LineTo(xn, yn);
        ct = -Screen->Width + Scroll7->Position*0.01*Screen->Width;

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img7_lClick(TObject *Sender)
{
        if(!x02)
        {
                LoadJPEGRes(img7->Picture,"7_unpressed_jpg");
                img7_l->Left = 891;
                x02 = true;
        }
        else
        {
                LoadJPEGRes(img7->Picture,"7_pressed_jpg");
                img7_l->Left = 887;
                x02 = false;
        }

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::img11_lClick(TObject *Sender)
{
        if(autoR)
        {
                LoadJPEGRes(img11->Picture,"11_unpressed_jpg");
                img11_l->Left = 894;
                autoR = false;
        }
        else
        {
                LoadJPEGRes(img11->Picture,"11_pressed_jpg");
                img11_l->Left = 890;
                autoR = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll11Change(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll11->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img11_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img11_l->Picture->Bitmap->TransparentColor=clWhite;
        img11_l->Canvas->Pen->Color = clGreen;
        img11_l->Canvas->Pen->Width = penWidth;
        img11_l->Canvas->MoveTo(x0, y0);
        img11_l->Canvas->LineTo(xn, yn);
        startVal = -2 + Scroll11->Position*0.02;
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll12Change(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll12->Position*0.0314;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img12_l->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img12_l->Picture->Bitmap->TransparentColor=clWhite;
        img12_l->Canvas->Pen->Color = clGreen;
        img12_l->Canvas->Pen->Width = penWidth;
        img12_l->Canvas->MoveTo(x0, y0);
        img12_l->Canvas->LineTo(xn, yn);
        lineWidth = 1 + Scroll12->Position*0.06;

        signalCalcOnce();
}

void __fastcall TOSCForm::Scroll12_IIChange(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll12_II->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img12_lI->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img12_lI->Picture->Bitmap->TransparentColor=clWhite;
        img12_lI->Canvas->Pen->Color = clGreen;
        img12_lI->Canvas->Pen->Width = penWidth;
        img12_lI->Canvas->MoveTo(x0, y0);
        img12_lI->Canvas->LineTo(xn, yn);
        this->value = 180 + Scroll12_II->Position*0.375;

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Scroll12_IIIChange(TObject *Sender)
{
        x0 = 12.5; y0 = 12.5; r = 12.5;
        alpha = Scroll12_III->Position*alphaConst1;
        xn = x0 - r*cos(alpha);
        yn = y0 - r*sin(alpha);
        img12_lII->Picture->Bitmap->LoadFromResourceName((int)HInstance,"white_bmp");
        img12_lII->Picture->Bitmap->TransparentColor=clWhite;
        img12_lII->Canvas->Pen->Color = clGreen;
        img12_lII->Canvas->Pen->Width = penWidth;
        img12_lII->Canvas->MoveTo(x0, y0);
        img12_lII->Canvas->LineTo(xn, yn);
        this->gridValue = Scroll12_III->Position;

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTract1_upClick(TObject *Sender)
{
        if(i[0] == 11)
                i[0] = -1;
        i[0]++;
        kvnesh[0] = Voltage[i[0]];
        if(i[0] == 11)
                del6[0] = true;
        else
                del6[0] = false;
        LoadJPEGRes(img2_1->Picture,Images_2[i[0]]);
        img2_1_l->Top=img2_1->Top+VerticV[i[0]];
        img2_1_l->Left=img2_1->Left+HorizV[i[0]];
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTract1_downClick(TObject *Sender)
{
        if(i[0] == 0)
                i[0] = 12;
        i[0]--;
        kvnesh[0] = Voltage[i[0]];
        if(i[0] == 11)
                del6[0] = true;
        else
                del6[0] = false;
        LoadJPEGRes(img2_1->Picture,Images_2[i[0]]);
        img2_1_l->Top=img2_1->Top+VerticV[i[0]];
        img2_1_l->Left=img2_1->Left+HorizV[i[0]];
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTract2_upClick(TObject *Sender)
{
        if(i[1] == 11)
                i[1] = -1;
        i[1]++;
        kvnesh[1] = Voltage[i[1]];
        if(i[1] == 11)
                del6[1] = true;
        else
                del6[1] = false;
        LoadJPEGRes(img2_2->Picture,Images_2[i[1]]);
        img2_2_l->Top=img2_2->Top+VerticV[i[1]];
        img2_2_l->Left=img2_2->Left+HorizV[i[1]];
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTract2_downClick(TObject *Sender)
{
        if(i[1] == 0)
                i[1] = 12;
        i[1]--;
        kvnesh[1] = Voltage[i[1]];
        if(i[1] == 11)
                del6[1] = true;
        else
                del6[1] = false;
        LoadJPEGRes(img2_2->Picture,Images_2[i[1]]);
        img2_2_l->Top=img2_2->Top+VerticV[i[1]];
        img2_2_l->Left=img2_2->Left+HorizV[i[1]];
        updateK();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTime_upClick(TObject *Sender)
{
        if(i[2] == 21)
                i[2] = -1;
        i[2]++;
        tR = Times[i[2]];
        LoadJPEGRes(img8->Picture,Images_8[i[2]]);
        img8_l->Top=img8->Top+VerticT[i[2]];
        img8_l->Left=img8->Left+HorizT[i[2]];
        updatedt();
        

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::BtnTime_dwnClick(TObject *Sender)
{
        if(i[2] == 0)
                i[2] = 22;
        i[2]--;
        tR = Times[i[2]];
        LoadJPEGRes(img8->Picture,Images_8[i[2]]);
        img8_l->Top=img8->Top+VerticT[i[2]];
        img8_l->Left=img8->Left+HorizT[i[2]];
        updatedt();

        signalCalcOnce();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::CheckBox9MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if(syncMode == 0)
        {
                CheckBox9->Checked = false;
                clearData();
                syncMode = 6;
                if (IsPwrOn)
                {
                        Timer1->Enabled=true;
                }
        }
        else
        {
                syncMode = 0;
                CheckBox9->Checked = true;
                Timer1->Enabled=false;
                signalCalcOnce();
        }
        LoadJPEGRes(ImageBtn1_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn2_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn3_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn4_9->Picture,"unpressed_button_jpg");
        LoadJPEGRes(ImageBtn5_9->Picture,"unpressed_button_jpg");
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::FSyncChange(TObject *Sender)
{
      try
      {
        Fs=FSync->Text.ToDouble();
      }
      catch (...)
      {
        Fs=0;
      }
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::GeneratorIClick(TObject *Sender)
{
        TractForm->Caption="Входной сигнал канала I";
        TractForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::GeneratorIIClick(TObject *Sender)
{
        TractFormII->Caption="Входной сигнал канала II";
        TractFormII->Show();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::Button3Click(TObject *Sender)
{
        if (Helper==NULL){
                Helper=new THelperForm(this);
        }
        Helper->Show();
}

//---------------------------------------------------------------------------
void __fastcall TOSCForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        if (Helper!=NULL){
                Helper->Free();
        }

        writeSettings();
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::FormResize(TObject *Sender)
{
        if (positionsData!=NULL)
        {
                this->Left=positionsData[0];
                this->Top=positionsData[1];
                TractForm->Left=positionsData[2];
                TractForm->Top=positionsData[3];
                TractFormII->Left=positionsData[4];
                TractFormII->Top=positionsData[5];
                delete [] positionsData;
                positionsData=NULL;
        }
        else
        {
                TractForm->Top=this->Top-TractForm->Height;
                if (TractForm->Top<0)
                        TractForm->Top=0;
                TractFormII->Top=TractForm->Top;
                TractForm->Left=this->Left;
                TractFormII->Left=TractForm->Left+TractForm->Width+20;
        }
}
//---------------------------------------------------------------------------

void __fastcall TOSCForm::FSyncKeyPress(TObject *Sender, char &Key)
{
        TractForm->check((TEdit*)Sender, Key, false);
}

//---------------------------------------------------------------------------


//Создание нового кадра
void __fastcall TOSCForm::Timer1Timer(TObject *Sender)
{
        Timer1->Interval=40;
        Td=Timer1->Interval/1000.0;
        dCh+=Timer1->Interval;
        if (dCh>100)
        {
                dCh=0;pic->Canvas->FillRect(TRect(0,0,Screen->Width,Screen->Height));
                drawGrid(gridValue);
        }
        if (param[0].type!=3)
                fm[0]=0;         //Обнуление добавочной частоты
        if (param[1].type!=3)
                fm[1]=0;         //Обнуление добавочной частоты
        param[0]=TractForm->getSignalParam();
        param[1]=TractFormII->getSignalParam();

        correctParam(0);
        correctParam(1);        
        
        updatedt();     //Обновление величины шага

        signalCalc(); //Вычисление следующих значений сигналов в каналах
        Screen->Picture->Bitmap=pic;
}
//---------------------------------------------------------------------------


//Методы, не связанные с событиями

//Установление верхнего предела частоты, чтобы выполнялась т. Котельникова
void __fastcall TOSCForm::correctParam(bool tractN)
{
        //realF[tractN]=param[tractN].fc;
        if (del6[tractN])
        {
                param[tractN].type=sigSIN;
                param[tractN].fc=1000;
                if (!x10[tractN])
                        param[tractN].Uc=0.03;
                else
                        param[tractN].Uc=0.3;
        }
        if (syncMode==5){
              return;
        }
        if (param[tractN].type<=sigPM && param[tractN].fc>1/(4.0*kDT*dt))
        {
                param[tractN].fc=1/(4.0*kDT*dt);
        }
        if (param[tractN].type==sigAM && param[tractN].fm>1/(8.0*kDT*dt))
        {
                param[tractN].fm=0;    //1/(4.0*kDT*dt);
        }
        if (param[tractN].type>=sigIMP)
        {
                double T=param[tractN].T;
                double tau2=param[tractN].tau2;
                int Ni=param[tractN].N;
                if (T<=0)
                {
                        return;
                }
                if (param[tractN].T<2*kDT*dt)
                {
                   param[tractN].T=2*kDT*dt;
                   if (param[tractN].tau>0)
                   {
                        param[tractN].tau2=0;
                   }
                   if (param[tractN].N>1)
                   {
                        param[tractN].N=1;
                   }
                }
                if (param[tractN].type==sigP_IMP)
                {
                        if (param[tractN].tau>=param[tractN].tInt && param[tractN].tau*Ni>=T)
                        {
                                param[tractN].tau=param[tractN].T;
                                return;
                        }
                }
                if (param[tractN].type==sig2_IMP)
                {
                        double tOst=(T-param[tractN].tInt)*0.999999;
                        if (param[tractN].tau>=param[tractN].tInt && tau2>=tOst)
                        {
                                param[tractN].tau=param[tractN].T;
                                return;
                        }
                }
                param[tractN].tau*=param[tractN].T/T;
                if (param[tractN].tau<kDT*dt && param[tractN].tau>0)
                {
                   param[tractN].tau=kDT*dt;
                }
                if (param[tractN].tau2<kDT*dt && param[tractN].tau2>0
                        && T==param[tractN].T)
                {
                   param[tractN].tau2=kDT*dt;
                }
        }
}


//Изменение частоты дискретизации
void __fastcall TOSCForm::updatedt()
{
        dt=tR/(SW+1)*tRvnut;
        if (x02)
                dt*=0.2;
        //Для режима X-Y
        if (syncMode==5)
        {
                if (param[0].fc<=param[1].fc && tractMode!=1)
                {
                        if  (param[1].fc!=0)
                                dt=2/(param[1].fc*(SW+1));
                }
                else
                {
                        if  (param[0].fc!=0)
                                dt=2/(param[0].fc*(SW+1));
                }
        }
        if (dt<0.000000074 && syncMode!=0)    //Подстройка множителя шага дискретизации
        {
                kDT=int(0.000000074/dt);
                if (kDT==0)
                        kDT=1;
        }
        else
        {
                kDT=1;
        }

        //Вычисление коэффициентов ФВЧ
        double TD=dt*kDT;
        const double ba=1;
        const double aa[3]={246.7401, 22.2144, 1};
        double TD2=TD*TD;
        double a0=aa[0]+aa[1]/TD+aa[2]/TD2;
        b=ba/(TD2*a0);
        a[1]=aa[2]/(TD2*a0);
        a[0]=-2*a[1]-aa[1]/(TD*a0);
}

void  __fastcall TOSCForm::updateK(){
        k[0] = 1/8.0*Screen->Height/kvnesh[0]/kvnut[0];
        k[1] = 1/8.0*Screen->Height/kvnesh[1]/kvnut[1];
}

//ФВЧ
double __fastcall TOSCForm::filter(double u, bool tractN)
{
       double minued=b*(u-2*oldU[tractN][0]+oldU[tractN][1]);
       double subtrahend=a[1]*oldY[tractN][1]+a[0]*oldY[tractN][0];
       double y=minued-subtrahend;
       oldY[tractN][1]=oldY[tractN][0];
       oldY[tractN][0]=y;
       oldU[tractN][1]=oldU[tractN][0];
       oldU[tractN][0]=u;
       return y;
}

void __fastcall TOSCForm::signalDraw()     //Отрисовка сигналов в соответствии с выбранным режимом
{
       pic->Canvas->Pen->Color=HSV2RGB(hue,saturation,value);
       pic->Canvas->Pen->Width=lineWidth;

       if (Scroll12_II->Position==0) //Если яркость нулевая, ничего не рисуется
               return;
       if (syncMode==5)    //Режим X-Y
       {
               XYDraw();
               return;
       }
       int start=ct;
       if (start<0)
                start=0;
       if (start>SW)
                start=SW;
       int stop=SW+ct;
       if (stop<0)
                stop=0;
       if (stop>SW)
                stop=SW;

       switch (tractMode)
       {
                case 1:       //Отрисовка только канала I
                {
                        pic->Canvas->MoveTo(start, Screen->Height/2-Ut[0][0][start]);
                        int i;
                        for (i=start+kDT; i<=stop; i+=kDT)
                        {
                                paint(i,Ut[0][0][i],Ut[0][1][i]);
                        }
                        if (stop==SW)
                        {
                                paint(SW,Ut[0][0][SW],Ut[0][1][SW]);
                        }
                }
                break;
                case 2:   //Отрисовка каналов I и II одновременно
                case 4:
                {
                        pic->Canvas->MoveTo(start, Screen->Height/2-Ut[0][0][start]);
                        for (int i=start+kDT; i<=stop; i+=kDT)
                        {
                                paint(i,Ut[0][0][i],Ut[0][1][i]);

                        }
                        if (stop==SW)
                        {
                                paint(SW,Ut[0][0][SW],Ut[0][1][SW]);
                        }
                        pic->Canvas->MoveTo(start, Screen->Height/2-Ut[1][0][start]);
                        for (int i=start+kDT; i<=stop; i+=kDT)
                        {
                                paint(i,Ut[1][0][i],Ut[1][1][i]);
                        }
                        if (stop==SW)
                        {
                                paint(SW,Ut[1][0][SW],Ut[1][1][SW]);
                        }
                }
                break;
                case 3:   //Отрисовка суммы сигналов каналов I и II
                {
                        double U;
                        double st=Ut[0][0][start]+Ut[1][0][start];
                        pic->Canvas->MoveTo(start, Screen->Height/2-st);
                        for (int i=start+kDT; i<=stop; i+=kDT)
                        {
                                U=Ut[0][0][i]+Ut[1][0][i];
                                paint(i,U,Ut[0][1][i]);
                        }
                        if (stop==SW)
                        {
                                U=Ut[0][0][SW]+Ut[1][0][SW];
                                paint(SW,U,Ut[0][1][SW]);
                        }
                }
                break;
                case 5:   //Отрисовка только канала II
                {
                               pic->Canvas->MoveTo(start, Screen->Height/2-Ut[1][0][start]);
                                for (int i=start+kDT; i<=stop; i+=kDT)
                                {
                                        paint(i,Ut[1][0][i],Ut[1][1][i]);
                                }
                                if (stop==SW)
                                {
                                        paint(SW,Ut[1][0][SW],Ut[1][1][SW]);
                                }
                }
                break;
       }
}
//---------------------------------------------------------------------------
//Отрисовка сигналов при подаче канала I на горизонтальную катушку
void __fastcall TOSCForm::XYDraw()
{
       switch (tractMode)
       {
                case 1:       //На вертикальной катушке канал I
                {
                        pic->Canvas->MoveTo(SW/2+Ut[0][0][0]-c[0],Screen->Height/2-Ut[0][0][0]+ct);
                        int i;
                        for (i=0; i<=SW; i+=kDT)
                        {
                                paint(SW/2+Ut[0][0][i]-c[0],Ut[0][0][i]-ct,Ut[0][1][i]);
                        }
                }
                break;
                case 2:   //На вертикальной катушке каналы I и II одновременно
                case 4:
                {
                        pic->Canvas->MoveTo(SW/2+Ut[0][0][0]-c[0],Screen->Height/2-Ut[0][0][0]+ct);
                        int i;
                        for (i=0; i<=SW; i+=kDT)
                        {
                                paint(SW/2+Ut[0][0][i]-c[0],Ut[0][0][i]-ct,Ut[0][1][i]);
                        }
                        pic->Canvas->MoveTo(SW/2+Ut[0][0][0]-c[0],Screen->Height/2-Ut[1][0][0]);
                        for (i=0; i<=SW; i+=kDT)
                        {
                                paint(SW/2+Ut[0][0][i]-c[0],Ut[1][0][i],Ut[1][1][i]);
                        }
                }
                break;
                case 3:   //На вертикальной катушке сумма сигналов каналов I и II
                {
                        pic->Canvas->MoveTo(SW/2+Ut[0][0][0]-c[0],Screen->Height/2-Ut[0][0][0]-Ut[1][0][0]+ct);
                        int i;
                        for (i=0; i<=SW; i+=kDT)
                        {
                                paint(SW/2+Ut[0][0][i]-c[0],Ut[0][0][i]+Ut[1][0][i]-ct,Ut[0][1][i]);
                        }
                }
                break;
                case 5:   //На вертикальной катушке канал II
                {
                        pic->Canvas->MoveTo(SW/2+Ut[0][0][0]-c[0],Screen->Height/2-Ut[1][0][0]);
                        int i;
                        for (i=0; i<=SW; i+=kDT)
                        {
                                paint(SW/2+Ut[0][0][i]-c[0],Ut[1][0][i],Ut[1][1][i]);
                        }
                }
                break;
        }
}

//---------------------------------------------------------------------------
void __fastcall TOSCForm::paint(int i, int U, double ts)
{
       double lightTime=0.1;
       if (lightTime<dt)
                lightTime=dt+0.01;
       if ((t-ts)<=lightTime && t>=ts || syncMode==0)
                pic->Canvas->LineTo(i,Screen->Height/2-U);
       else
                pic->Canvas->MoveTo(i,Screen->Height/2-U);
}

void __fastcall TOSCForm::signalCalc()      //Вычисление значений сигнала
{
       bool U2sync;
       int randn; //Случайное число от 0 до 9
       const double dTR=0.000166; //Макс. шаг, при котором полностью заполнен экран
       double tEnd=t+Td;
       int iDraw=0; //Счётчик отрисовок
       static  double U1=0;
       static double U2=0; //Текущие значения напряжений каналов
       double U1old, U2old; //Предыдущие значения напряжений каналов
       static double U3=0;
       double U3old; //Напряжение сигнала внешней синхронизации
       randomize();
       //Случаи, когда необходимо переключить синхронизацию на канал ||
       U2sync=param[0].fc==0 || param[0].type==sigNONE || param[0].type==sigCONST || inpMode[0]==2 || (param[0].fc<=100 && autoR);
       if (param[0].type==sigIMP || param[0].type==sigP_IMP || param[0].type==sig2_IMP)
       {
               if (param[0].tau==0 || param[0].T==0)
                        U2sync=true;
               if ((startVal+ps[0])<0 && (param[0].Uc-ps[0])>=0)
                        U2sync=true;
               if ((startVal+ps[0])>0 && (param[0].Uc-ps[0])<=0)
                        U2sync=true;
               if (fabs(param[0].Uc-ps[0])<=fabs(startVal))
                        U2sync=true;
               if (param[0].tau>=param[0].T)
                        U2sync=true;
               if (param[0].type==sigP_IMP)
                {
                        if(param[0].tInt-param[0].tau<=0)
                                if((param[0].tau-param[0].tInt)*(param[0].N-1)+param[0].tau>=param[0].T)
                                        U2sync=true;
                        if (param[0].N<=0)
                                U2sync=true;
                }
                if (param[0].type==sig2_IMP)
                {
                        if(param[0].tInt-param[0].tau<=0)
                                if(param[0].tau2>=param[0].T-param[0].tInt)
                                        U2sync=true;
                        if (param[0].tau==0 && param[0].tau2==0 )
                                U2sync=true;
                }
       }
       else
       {
                U2sync=U2sync || fabs(param[0].Uc)<=startVal || -fabs(param[0].Uc)>=startVal;
       }
       while (true)
       {
                while(t<tEnd)
                {
                        U1old=U1;
                        U2old=U2;
                        U1=signal(0);      //Сигнал канала I
                        U2=signal(1);      //Сигнал канала II
                        if (syncMode==5) //Режим X-Y
                                writingDown=true;
                        if ((syncMode==3 || syncMode==4) && Fs!=0)
                        {
                                U3old=U3;
                                U3=videoimp(t,1/Fs,1/(2*Fs)); //Величина сигнала внешней синхронизации
                        }

                        if (autoR) //Если автоколебательная развёртка
                        {
                                if (t-tLast>0.01) //Через 0,01 с запуск развёртки, если не было синхр.
                                {
                                        writingDown=true;
                                }
                        }
                        if (!writingDown)           //Ожидание начала развёртки
                        {
                                if (syncMode==1 || (syncMode==2 && !U2sync))   //Внутренняя синхронизация по первому каналу
                                {
                                        if (syncFront)
                                        {
                                                if (U1>startVal && U1old<=startVal) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                        else
                                        {
                                                if (U1<startVal && U1old>=startVal) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                }
                                if (syncMode==2 && U2sync) //Синхронизация по первому каналу невозможна
                                {
                                        if (syncFront)
                                        {
                                                if (U2>startVal && U2old<=startVal) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                        else
                                        {
                                                if (U2<startVal && U2old>=startVal) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                }
                                if (syncMode==3 || syncMode==4)
                                {
                                        if (syncFront)
                                        {
                                                if (U3>=1 && U3old<1) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                        else
                                        {
                                                if (U3<1 && U3old>=1) //Запуск развёртки
                                                {
                                                        writingDown=true;
                                                }
                                        }
                                }
                        }

                        double kDTtemp=kDT;
                        if (writingDown)        //Запись текущих значений сигналов
                        {
                                if (tractMode==4)    //Если отображение каналов осуществляется через период
                                {
                                        if (even)
                                                writeDown(U1,0);
                                        else
                                                writeDown(U2,1);
                                }
                                else
                                {
                                        writeDown(U1,0);
                                        writeDown(U2,1);
                                }
                                int Nold=N;
                                N+=kDT;
                                if (kDT>1 && N+ct>SW && Nold+ct<SW)
                                {
                                        kDTtemp=SW-Nold-ct;
                                        N=SW-ct;
                                }
                                if (N>=SW+1) //Завершение развёртки
                                {
                                        N=0;
                                        writingDown=false;
                                        even=!even;
                                        tLast=t;
                                        if (dt<=dTR)
                                        {
                                                randn=rand()%10;
                                                if (iDraw==0 || (randn>=8 && iDraw<=3))
                                                {
                                                        signalDraw();
                                                        ++iDraw;
                                                }
                                        }
                                }
                        }
                        t+=dt*kDTtemp;
                }
                if (dt>dTR || !writingDown)
                {
                        signalDraw();
                        break;
                }
                else
                {
                        double tAdd=dt*(SW+1-N);
                        tEnd+=tAdd;
                        Td+=tAdd;
                        Timer1->Interval=int(Td*1000);
                }
       }
}

//---------------------------------------------------------------------------
void __fastcall TOSCForm::writeDown(double U, bool tractN)     //Запись сигнала в массив
{
        U*=k[tractN];
        if (x10[tractN])
                U/=10;
        if (tractN==1 && invert)
                U=-U;
        int pos;
        if (syncMode==5)       //Только для режима X-Y
        {
                pos=N;
                if (tractN==0)
                        U+=ct;
                U+=c[tractN];
        }
        else
        {
                int ctm=ct;
                if (ct<0)
                        ctm=ct-ct%kDT;
                pos=N+ctm;
                U+=c[tractN];
        }
        if (pos>=0 && pos<=SW)
        {
                Ut[tractN][0][pos]=U;
                Ut[tractN][1][pos]=t;
        }
}
//---------------------------------------------------------------------------
void __fastcall TOSCForm::signalCalcOnce()      //Вычисление значений сигнала за 1 период
{
       if (syncMode!=0 || !IsPwrOn)
                return;
       pic->Canvas->FillRect(TRect(0,0,Screen->Width,Screen->Height));
       drawGrid(gridValue);
       fm[0]=0;         //Обнуление добавочной частоты
       fm[1]=0;         //Обнуление добавочной частоты
       param[0]=TractForm->getSignalParam();
       param[1]=TractFormII->getSignalParam();

       clearData();
       correctParam(0);
       correctParam(1);

       updatedt();     //Обновление величины шага
       t=0;
       tLast=0;
       N=0;
       memset(&oldY,0,sizeof(oldY));
       memset(&oldU,0,sizeof(oldU));

       while(true)
       {
                writeDown(signal(0),0);
                writeDown(signal(1),1);
                N++;
                t+=dt;
                if (N>=SW+1) //Завершение развёртки
                {
                        t=0;
                        fm[0]=0;
                        fm[1]=0;
                        phasem[0]=0;
                        phasem[1]=0;
                        N=0;
                        signalDraw();
                        break;
                }
       }
       Screen->Picture->Bitmap=pic;
}
//---------------------------------------------------------------------------
//Определение значения сигнала в канале
double __fastcall TOSCForm::signal(bool tractN)
{
     double U=0;
     if (del6[tractN])     //Калибровочный режим
     {
         U=0.6*videoimp(t,0.001,0.0005)-0.3;
         if (!x10[tractN])
         {
                U=U*0.1;
         }
         return U;
     }
     if  (inpMode[tractN]==2)     //Если вход подключён к земле
        return 0;
     switch(param[tractN].type)
     {
        case sigNONE: //Нет сигнала
        {
                U=0;
        }
        break;
        case sigSIN: //Синусоида
        {
                U=param[tractN].Uc*sin(2*M_PI*param[tractN].fc*t+param[tractN].fi0);
        }
        break;
        case sigAM: //Амплитудная модуляция
        {
                double Um;   //Величина огибающей
                if (param[tractN].fm==0)
                        Um=1;
                else
                        Um=(1+param[tractN].m*sin(2*M_PI*param[tractN].fm*t))/(1+param[tractN].m);
                U=Um*param[tractN].Uc*sin(2*M_PI*param[tractN].fc*t);
        }
        break;
        case sigFM: //Частотная модуляция
        {
                fm[tractN]+=triangleimp(t,param[tractN].Tf,param[tractN].df);
                U=param[tractN].Uc*sin(2*M_PI*(param[tractN].fc*t+dt*kDT*fm[tractN]));
        }
        break;
        case sigPM: //Фазовая модуляция
        {
                if (param[tractN].Tf>0)
                {
                        if (int(t/param[tractN].Tf)>int((t-dt*kDT)/param[tractN].Tf))
                        {
                                phasem[tractN]+=param[tractN].Fi;
                                if (phasem[tractN]>2*M_PI)
                                {
                                        phasem[tractN]-=2*M_PI;
                                }
                        }
                }
                U=param[tractN].Uc*sin(2*M_PI*param[tractN].fc*t+phasem[tractN]);
        }
        break;
        case sigIMP: //Одиночные импульсы
        {
                U=param[tractN].Uc*videoimp(t,param[tractN].T,param[tractN].tau);
        }
        break;
        case sigP_IMP: //Пачка импульсов
        {
                U=0;
                for (int i=0;i<=param[tractN].N-1;++i)
                {
                        U+=param[tractN].Uc*videoimp(t-param[tractN].tInt*i,param[tractN].T,param[tractN].tau);
                }
                if (fabs(U)>fabs(param[tractN].Uc))
                         U=param[tractN].Uc;
        }
        break;
        case sig2_IMP: //Пара импульсов
        {
                U=0;
                U+=param[tractN].Uc*videoimp(t,param[tractN].T,param[tractN].tau);
                U+=param[tractN].Uc*videoimp(t-param[tractN].tInt,param[tractN].T,param[tractN].tau2);
                if (fabs(U)>fabs(param[tractN].Uc))
                         U=param[tractN].Uc;
        }
        break;
        case sigCONST: //Постоянное напряжение
        {
                U=param[tractN].Uc;
        }
        break;
     }
     if  (inpMode[tractN]==3)
     {
        double Uf=filter(U, tractN);
        ps[tractN]=U-Uf;
        return Uf;
     }
     return U;
}
//---------------------------------------------------------------------------
int __fastcall TOSCForm::videoimp(double x, double T, double tau)  //Видеоимпульс
{
     if (T!=0)
     {
        while (x<0)
                x+=T;
        int N=x/T;
        x-=N*T;
        return (x<tau)?1:0;
     }
     else
        return 0;
}
//---------------------------------------------------------------------------
double __fastcall TOSCForm::triangleimp(double x, double Tf, double df)  //Треугольный импульс
{
     while (x<0)
        x+=Tf;
     if (Tf!=0)
     {
        int N=x/Tf;
        x-=N*Tf;
        double K;   //Тангенс угла наклона линии нарастания частоты
        double B;
        if (x<=Tf/2)
        {
                K=4*df/Tf;
                B=-df;
        }
        else
        {
                K=-4*df/Tf;
                B=3*df;
        }
        return K*x+B;
     }
     else
        return 0;
}

//---------------------------------------------------------------------------
//Подключение проводов к гнёздам в случае подачи сигнала
void __fastcall TOSCForm::setConnection(bool tractN, bool enable)
{
//tractN - номер канала. false - канал I, true - канал II
//enable - подключить проводок или убрать его. true - подключить, false - убрать
        if(!tractN && enable)
                LoadJPEGRes(ImageLabels1->Picture,"Labels1_wire_jpg");        if(!tractN && !enable)                LoadJPEGRes(ImageLabels1->Picture,"Labels1_jpg");        if(tractN && enable)                LoadJPEGRes(ImageChan2->Picture,"chan2_wire_jpg");        if(tractN && !enable)                LoadJPEGRes(ImageChan2->Picture,"chan2_JPG");
}

//Перевод цвета из HSV в RGB
TColor __fastcall TOSCForm::HSV2RGB(int i_hue,int sat,int val)
{
    int r,g,b,ii;
    double fr, hue;
    unsigned int c1, c2, c3;
    if (!sat)
      r = g = b = val;
    else
    {
        while (i_hue >= 360)
        i_hue -= 360;
        hue = i_hue;
        ii = (int)(hue /= 60.0);
        fr = hue - ii;
        c1 = (val * (255 - sat)) / 255;
        c2 = (val * (255 - sat * fr)) / 255;
        c3 = (val * (255 - sat * (1.0 - fr))) / 255;
        switch (ii)
        {
            case 0: r = val; g = c3; b = c1; break;
            case 1: r = c2; g = val; b = c1; break;
            case 2: r = c1; g = val; b = c3; break;
            case 3: r = c1; g = c2; b = val; break;
            case 4: r = c3; g = c1; b = val; break;
            case 5: r = val; g = c1; b = c2; break;
        }
    }
    return (TColor)RGB(r,g,b);
}

//Нарисовать сетку
void __fastcall TOSCForm::drawGrid(int v)
{
     static const int h=32;
     static const int s=209;
     static const int gridStepL=SW/10; //Ширина большого деления
     static const int gridStepS=gridStepL/10; //Ширина малого деления
     static const int gridDivLeng=10; //Длина риски

     static const int sv=(pic->Height-gridDivLeng)/2;
     static const int fv=sv+gridDivLeng;
     static const int sh=(pic->Width-gridDivLeng)/2;
     static const int fh=sh+gridDivLeng;
     static const int mid=gridStepS*5;
     
     pic->Canvas->Pen->Width=2;
     pic->Canvas->Pen->Color=HSV2RGB(h,s,v); //Задаём цвет
     //Рисуем вертикальные линии
     for (int i=0; i<=pic->Width; i+=gridStepL)
     {
         pic->Canvas->MoveTo(i,0);
         pic->Canvas->LineTo(i,pic->Height-1);
         if (i>=pic->Width)
         {
                break;
         }
         //Рисуем шкалу
         for (int j=i+gridStepS; j<i+gridStepL; j+=gridStepS)
         {
                //Середина деления
                if (j==i+mid)
                {
                        pic->Canvas->MoveTo(j,sv-2);
                        pic->Canvas->LineTo(j,fv+2);
                }
                else
                {
                        pic->Canvas->MoveTo(j,sv);
                        pic->Canvas->LineTo(j,fv);
                }
         }
     }
     //Рисуем горизонтальные линии
     for (int i=0; i<=pic->Height; i+=gridStepL)
     {
         pic->Canvas->MoveTo(0,i);
         pic->Canvas->LineTo(pic->Width-1,i);
         if (i>=pic->Height)
         {
                break;
         }
         //Рисуем решётку
         for (int j=i+gridStepS; j<i+gridStepL; j+=gridStepS)
         {
                //Середина деления
                if (j==i+mid)
                {
                        pic->Canvas->MoveTo(sh-2,j);
                        pic->Canvas->LineTo(fh+2,j);
                        pic->Canvas->LineTo(sh-2,j);
                }
                else
                {
                        pic->Canvas->MoveTo(sh,j);
                        pic->Canvas->LineTo(fh,j);
                        pic->Canvas->LineTo(sh,j);
                }
         }
     }
}

void __fastcall TOSCForm::CloseHelper()
{
        if (Helper!=NULL){
                Helper->Free();
                Helper=NULL;
        }
}

//---------------------------------------------------------------------------
//Загрузка JPEG из ресурса
void __fastcall TOSCForm::LoadJPEGRes(TPicture *pic, AnsiString ResName)
{
  TResourceStream *Stream;
  Stream = new TResourceStream((int)HInstance, ResName, "JPEG");
  TJPEGImage *img;
  img=new TJPEGImage;
  try
  {
        img->LoadFromStream(Stream);
  }
  catch(...)
  {
        img->Free();
        ShowMessage("Ресурс не найден!");
        return;
  }
  Stream->Free();
  pic->Bitmap->Assign(img);
  img->Free();
}

//Считать базу данных из файла
void __fastcall TOSCForm::readDataBase()
{
      AnsiString signalsFile=signalsFolder+"\\signals.obf";
      if (!FileExists(signalsFile))
      {
            extractDataBase();
      }
      ifstream fi;
      fi.open(signalsFile.c_str(),ios::binary|ios::in);
      SignalParam signal;
      dataBase.clear();
      while (!fi.eof())
      {
        fi.read((char*)&signal,sizeof(signal));
        if (!fi.eof())
                dataBase.push_back(signal);
      }
      fi.close();
}

//Извлечь из ресурсов встроенную базу данных
void __fastcall TOSCForm::extractDataBase()
{
                if (!DirectoryExists(signalsFolder))
                {
                        CreateDir(signalsFolder);
                }
                TResourceStream* Res;
                Res = new TResourceStream((int)HInstance, "signals_obf", "HTML");
                Res->SaveToFile(signalsFolder+"\\signals.obf");
                Res->Free();
}

//Записать базу данных в файл
void __fastcall TOSCForm::writeDataBase()
{
      if (!DirectoryExists(signalsFolder))
      {
            CreateDir(signalsFolder);
      }
      AnsiString signalsFile=signalsFolder+"\\signals.obf";
      ofstream fo;
      fo.open(signalsFile.c_str(),ios::binary|ios::out);
      for (vector<SignalParam>::iterator it=dataBase.begin(); it!=dataBase.end();++it)
      {
        fo.write((char*)it,sizeof((*it)));
      }
      fo.close();
}

void __fastcall TOSCForm::writeDataBase(bool tractN)
{
      writeDataBase();
      if (tractN==0)
      {
        TractFormII->readSignals();
      }
      else
      {
        TractForm->readSignals();
      }
}

//Записать текущие настройки в файл
void __fastcall TOSCForm::writeSettings()
{
        if (!DirectoryExists(signalsFolder))
        {
                CreateDir(signalsFolder);
        }

        fstream f;
        AnsiString fileName = signalsFolder + "\\settings.obf";
        f.open(fileName.c_str(), ios::binary | ios::out);
        f.write((char *) &i, sizeof(i));
        int scrollData[8];
        scrollData[0]=Scroll2_1->Position;
        scrollData[1]=Scroll2_2->Position;
        scrollData[2]=Scroll4_1->Position;
        scrollData[3]=Scroll4_2->Position;
        scrollData[4]=Scroll_8->Position;
        scrollData[5]=Scroll7->Position;
        scrollData[6]=Scroll11->Position;
        scrollData[7]=Scroll12->Position;
        f.write((char *) &scrollData, sizeof(scrollData));
        bool pressedData[5];
        pressedData[0]=x10[0];
        pressedData[1]=x10[1];
        pressedData[2]=invert;
        pressedData[3]=x02;
        pressedData[4]= autoR;
        f.write((char *) &pressedData, sizeof(pressedData));
        f.write((char *) &syncFront, sizeof(syncFront));
        int buttonsData[4];
        buttonsData[0]=tractMode;
        buttonsData[1]=syncMode;
        buttonsData[2]=inpMode[0];
        buttonsData[3]=inpMode[1];
        f.write((char *) &buttonsData, sizeof(buttonsData));
        if (positionsData==NULL)
                positionsData=new int[6];
        positionsData[0]=this->Left;
        positionsData[1]=this->Top;
        positionsData[2]=TractForm->Left;
        positionsData[3]=TractForm->Top;
        positionsData[4]=TractFormII->Left;
        positionsData[5]=TractFormII->Top;
        f.write((char *) positionsData, sizeof(*positionsData)*6);
        delete [] positionsData;
        positionsData=NULL;
        param[0]=TractForm->getSignalParam();
        param[1]=TractFormII->getSignalParam();
        f.write((char *) &param, sizeof(param));
        f.write((char *) &Fs, sizeof(Fs));
        int libNumbers[2];
        libNumbers[0]=TractForm->getItemIndex();
        libNumbers[1]=TractFormII->getItemIndex();
        f.write((char *) &libNumbers, sizeof(libNumbers));

        int scrollData2[2];
        scrollData2[0]=Scroll12_II->Position;
        scrollData2[1]=Scroll12_III->Position;
        f.write((char *) &scrollData2, sizeof(scrollData2));
        f.close();
}

//Считать настройки из файла
void __fastcall TOSCForm::readSettings()
{
        AnsiString settingsFile= signalsFolder + "\\settings.obf";
        if (!FileExists(settingsFile))
        {
            return;
        }
        ifstream f;
        f.open(settingsFile.c_str(),ios::binary|ios::in);
        f.read((char *) &i, sizeof(i));
        i[0]--;
        BtnTract1_upClick(NULL);
        i[1]--;
        BtnTract2_upClick(NULL);
        i[2]--;
        BtnTime_upClick(NULL);
        int scrollData[8];
        f.read((char *) &scrollData, sizeof(scrollData));
        Scroll2_1->Position=scrollData[0];
        Scroll2_2->Position=scrollData[1];
        Scroll4_1->Position=scrollData[2];
        Scroll4_2->Position=scrollData[3];
        Scroll_8->Position=scrollData[4];
        Scroll7->Position=scrollData[5];
        Scroll11->Position=scrollData[6];
        Scroll12->Position=scrollData[7];
        bool pressedData[5];
        f.read((char *) &pressedData, sizeof(pressedData));
        x10[0]=!pressedData[0];
        img4_1_lClick(NULL);
        x10[1]=!pressedData[1];
        img4_2_lClick(NULL);
        invert=!pressedData[2];
        InvertImgClick(NULL);
        x02=!pressedData[3];
        img7_lClick(NULL);
        autoR=!pressedData[4];
        img11_lClick(NULL);
        f.read((char *) &syncFront, sizeof(syncFront));
        if (syncFront)
        {
                LoadJPEGRes(ImageBtn6_9->Picture,"pressed_button_jpg");
                LoadJPEGRes(ImageBtn7_9->Picture,"unpressed_button_jpg");
        }
        else
        {
                LoadJPEGRes(ImageBtn7_9->Picture,"pressed_button_jpg");
                LoadJPEGRes(ImageBtn6_9->Picture,"unpressed_button_jpg");
        }

        int buttonsData[4];
        f.read((char *) &buttonsData, sizeof(buttonsData));
        tractMode=buttonsData[0];
        TImage *Buttons[5];
        Buttons[0]=ImageBtn1_3;
        Buttons[1]=ImageBtn2_3;
        Buttons[2]=ImageBtn3_3;
        Buttons[3]=ImageBtn4_3;
        Buttons[4]=ImageBtn5_3;
        for (int j=0; j<=4; j++)
        {
                if (j==tractMode-1)
                {
                        LoadJPEGRes(Buttons[j]->Picture,"pressed_button_jpg");
                }
                else
                {
                        LoadJPEGRes(Buttons[j]->Picture,"unpressed_button_jpg");
                }
        }

        syncMode=buttonsData[1];
        Buttons[0]=ImageBtn1_9;
        Buttons[1]=ImageBtn2_9;
        Buttons[2]=ImageBtn3_9;
        Buttons[3]=ImageBtn4_9;
        Buttons[4]=ImageBtn5_9;
        for (int j=0; j<=4; j++)
        {
                if (j==syncMode-1)
                {
                        LoadJPEGRes(Buttons[j]->Picture,"pressed_button_jpg");
                        CheckBox9->Checked=false;
                }
                else
                {
                        LoadJPEGRes(Buttons[j]->Picture,"unpressed_button_jpg");
                }
        }
        if (syncMode==0)
        {
                CheckBox9->Checked=true;
        }
        else
        {
                CheckBox9->Checked=false;
        }

        inpMode[0]=buttonsData[2];
        inpMode[1]=buttonsData[3];
        AnsiString ResNames[3]={"1_1_1_2_1_jpg", "1_1_1_2_2_jpg", "1_1_1_2_3_jpg"};
        LoadJPEGRes(img1_1->Picture,ResNames[inpMode[0]-1]);
        LoadJPEGRes(img1_2->Picture,ResNames[inpMode[1]-1]);

        positionsData=new int[6];
        f.read((char *) positionsData, sizeof(*positionsData)*6);

        f.read((char *) &param, sizeof(param));
        TractForm->setSignalParam(param[0]);
        TractFormII->setSignalParam(param[1]);
        f.read((char *) &Fs, sizeof(Fs));
        FSync->Text=FloatToStr(Fs);
        int libNumbers[2];
        f.read((char *) &libNumbers, sizeof(libNumbers));
        TractForm->setItemIndex(libNumbers[0]);
        TractFormII->setItemIndex(libNumbers[1]);

        int scrollData2[2];
        f.read((char *) &scrollData2, sizeof(scrollData2));
        Scroll12_II->Position=scrollData2[0];
        Scroll12_III->Position=scrollData2[1];
        f.close();
}

//Очистка записанных данных
void __fastcall TOSCForm::clearData()
{
                t=-9;  //Любое относительно большое отрицательное число
                N=0;
                while (N<=SW)
                {
                        writeDown(0,0);
                        writeDown(0,1);
                        N++;
                }
                N=0;
                t=0;
}

