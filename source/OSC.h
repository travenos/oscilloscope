//---------------------------------------------------------------------------

#ifndef OSCH
#define OSCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>

#include "GeneratWindow.h"
#include "Helper.h"
#include <Menus.hpp>
#include "CSPIN.h"  
#include <fstream.h>
//---------------------------------------------------------------------------
class TOSCForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Screen;
        TImage *ImageChan1;
        TImage *ImageChan2;
        TImage *InvertImg;
        TButton *GeneratorI;
        TButton *GeneratorII;
        TButton *Button3;
        TTimer *Timer1;
        TImage *img1_1;
        TImage *img1_1_1;
        TImage *img1_1_2;
        TImage *img1_1_3;
        TImage *img1_2_3;
        TImage *img1_2_2;
        TImage *img1_2_1;
        TImage *img1_2;
        TImage *img2_1;
        TImage *img2_1_l;
        TScrollBar *Scroll2_1;
        TImage *img2_2;
        TImage *img2_2_l;
        TScrollBar *Scroll2_2;
        TImage *ImageBtn1_3;
        TImage *ImageBtn2_3;
        TImage *ImageBtn3_3;
        TImage *ImageBtn4_3;
        TImage *ImageBtn5_3;
        TImage *ImageLabels1;
        TScrollBar *Scroll4_1;
        TImage *img4_1_l;
        TImage *img4_1;
        TScrollBar *Scroll4_2;
        TImage *img4_2_l;
        TImage *img4_2;
        TImage *img12;
        TImage *img12_l;
        TScrollBar *Scroll12;
        TImage *img12_1;
        TImage *img12_3;
        TImage *ImagePwrBtn;
        TImage *ImagePwr;
        TScrollBar *Scroll11;
        TImage *img11_l;
        TImage *img11;
        TCheckBox *CheckBox9;
        TImage *ImageBtn1_9;
        TImage *ImageBtn10_9;
        TImage *ImageBtn2_9;
        TImage *ImageBtn3_9;
        TImage *ImageBtn4_9;
        TImage *ImageBtn5_9;
        TImage *ImageBtn6_9;
        TImage *ImageBtn7_9;
        TImage *ImageBtn8_9;
        TImage *ImageBtn9_9;
        TImage *ImageLabels2;
        TImage *img8;
        TImage *img8_l;
        TScrollBar *Scroll_8;
        TImage *img7;
        TImage *img7_l;
        TScrollBar *Scroll7;
        TSpeedButton *BtnTract1_down;
        TSpeedButton *BtnTract2_down;
        TSpeedButton *BtnTime_dwn;
        TSpeedButton *BtnTime_up;
        TSpeedButton *BtnTract1_up;
        TSpeedButton *BtnTract2_up;
        TEdit *FSync;
        TLabel *FSyncLabel;
        TImage *img12_lI;
        TImage *img12_lII;
        TScrollBar *Scroll12_III;
        TScrollBar *Scroll12_II;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ImageBtn1_3Click(TObject *Sender);
        void __fastcall ImageBtn2_3Click(TObject *Sender);
        void __fastcall ImageBtn3Cick(TObject *Sender);
        void __fastcall ImageBtn4_3Click(TObject *Sender);
        void __fastcall ImageBtn5_3Click(TObject *Sender);
        void __fastcall ImagePwrBtnClick(TObject *Sender);
        void __fastcall InvertImgClick(TObject *Sender);
        void __fastcall ImageBtn1_9Click(TObject *Sender);
        void __fastcall ImageBtn2_9Click(TObject *Sender);
        void __fastcall ImageBtn3_9Click(TObject *Sender);
        void __fastcall ImageBtn4_9Click(TObject *Sender);
        void __fastcall ImageBtn5_9Click(TObject *Sender);
        void __fastcall ImageBtn6_9Click(TObject *Sender);
        void __fastcall ImageBtn7_9Click(TObject *Sender);
        void __fastcall Scroll_8Change(TObject *Sender);
        void __fastcall img1_1_1Click(TObject *Sender);
        void __fastcall img1_1_2Click(TObject *Sender);
        void __fastcall img1_1_3Click(TObject *Sender);
        void __fastcall img1_2_1Click(TObject *Sender);
        void __fastcall img1_2_2Click(TObject *Sender);
        void __fastcall img1_2_3Click(TObject *Sender);
        void __fastcall Scroll2_1Change(TObject *Sender);
        void __fastcall Scroll2_2Change(TObject *Sender);
        void __fastcall Scroll4_1Change(TObject *Sender);
        void __fastcall img4_1_lClick(TObject *Sender);
        void __fastcall img4_2_lClick(TObject *Sender);
        void __fastcall Scroll4_2Change(TObject *Sender);
        void __fastcall Scroll7Change(TObject *Sender);
        void __fastcall img7_lClick(TObject *Sender);
        void __fastcall img11_lClick(TObject *Sender);
        void __fastcall Scroll11Change(TObject *Sender);
        void __fastcall Scroll12Change(TObject *Sender);
        void __fastcall CheckBox9MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall GeneratorIClick(TObject *Sender);
        void __fastcall GeneratorIIClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FSyncChange(TObject *Sender);
        void __fastcall BtnTract1_upClick(TObject *Sender);
        void __fastcall BtnTract1_downClick(TObject *Sender);
        void __fastcall BtnTract2_upClick(TObject *Sender);
        void __fastcall BtnTract2_downClick(TObject *Sender);
        void __fastcall BtnTime_upClick(TObject *Sender);
        void __fastcall BtnTime_dwnClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FSyncKeyPress(TObject *Sender, char &Key);
        void __fastcall Scroll12_IIChange(TObject *Sender);
        void __fastcall Scroll12_IIIChange(TObject *Sender);
private:	// User declarationsdouble kvnesh[2];//для дискретных переключателей напряжения 2-х каналов
        double kvnesh[2];//для дискретных переключателей напряжения 2-х каналов
        double kvnut[2];//для непрерывных переключателей напряжения 2-х каналов
        bool IsPwrOn;

        double Fs;//Частота синхронизации
        double Td; //Время задержки таймера
        double k[2];//Коэффициенты вертикальных масштабов
        double tR; //Длительность развёртки
        double tRvnut; //Делитель длительности развёртки
        double dt; //Время дискретизации
        unsigned short int kDT; //Множитель времени дискретизации
        int c[2];//Величины смещения нуля
        int ct;//Величина горизонтального смещения развёртки

        int SW; //Ширина экрана
        SignalParam param[2];     //Характеристики сигнала каналов

        double *Ut[2][2];  //Массивы со значениями сигналов для отрисовки

        double t; //время
        bool writingDown; //Производится ли запись отсчётов сигнала
        bool even; //Чётный или нечётный период развёртки
        int N; //Номер текущего отсчёта

        TTractForm *TractFormII;   //Окно генератора канала II
        THelperForm *Helper;

        //Настройки осциллографа
        short int inpMode[2];    //Переключатели ражимов входа (для элементов 1.1 и 1.2(значения 1, 2, 3))
        short int tractMode;   //Режим отображения каналов
        short int syncMode;   //Режим синхронизации
        bool syncFront;   //Фронт начала развёртки (true - передний, false - задний)
        bool invert; //Инвертирование сигнала канала II
        bool x10[2]; //для 4_1, 4_2//Усиление сигналов в 10 раз
        bool x02; //для 7 //Ускорение развёртки в 5 раз
        bool autoR; //Автоколебательная развёртка

        bool del6[2]; //Режим 6 ДЕЛ

        double startVal; //для 11//Значение, запускающее развёртку
        double fm[2]; //Прирост частоты при частотной модуляции
        double phasem[2]; //Текущий прирост фазы
        double ps[2];   //Постоянная составляющая
        double tLast; //Время завершения последней развёртки

        double oldU[2][2]; //Последние 2 значения входного сигнала фильтра
        double oldY[2][2]; //Последние 2 значения выходного сигнала фильтра

        //double realF[2];

        //Параметры цвета луча
        static const int hue=122;
        static const int saturation=89;
        int value;

        int lineWidth;      //Ширина луча
        int gridValue; //Яркость сетки

        double b;    //Коэффициенты ФВЧ
        double a[2];

        int dCh; //Делитель частоты

        Graphics::TBitmap *pic;

        AnsiString signalsFolder;     //Рабочий каталог

        int *positionsData;    //Массив с положениями окон

        //Методы
        void __fastcall clearData();
        void __fastcall signalCalc();
        void __fastcall signalDraw();
        void __fastcall XYDraw();
        void __fastcall drawGrid(int v);  //Нарисовать оранжевую сетку
        void __fastcall updatedt();  //Обновление величины шага
        void  __fastcall updateK();
        //Установление верхнего предела частоты, чтобы выполнялась т. Котельникова
        void __fastcall correctParam(bool tractN);
        void __fastcall paint(int i, int U, double ts);   //Непосредственное рисование на экране
        void __fastcall writeDown(double U, bool tractN);     //Запись сигнала в массив
        int __fastcall videoimp(double z, double T, double tau);
        double __fastcall triangleimp(double x, double Tf, double df);  //Треугольная функция

        //Определение значения сигнала в канале
        double __fastcall signal(bool tractN);

        double __fastcall filter(double u, bool tractN);

        //Перевод из HSV в RGB
        TColor __fastcall HSV2RGB(int i_hue,int sat,int val);

        void __fastcall readSettings(); //Считать настройки из файла
        void __fastcall writeSettings(); //Записать настройки в файл

public:		// User declarations

        vector<SignalParam> dataBase;
        __fastcall TOSCForm(TComponent* Owner);

        void __fastcall setConnection(bool tractN, bool enable);
        void __fastcall CloseHelper();

        void __fastcall LoadJPEGRes(TPicture *pic, AnsiString ResName);  //Загрузка JPEG из ресурса
        void __fastcall readDataBase();//Считать базу данных из файла
        void __fastcall extractDataBase(); //Извлечь из ресурсов встроенную базу данных
        void __fastcall writeDataBase();//Записать базу данных в файл
        void __fastcall writeDataBase(bool tractN);//Записать базу данных в файл
        
        void __fastcall signalCalcOnce(); //Рассчитать и вывести один период развёртки


};
//---------------------------------------------------------------------------
extern PACKAGE TOSCForm *OSCForm;
//---------------------------------------------------------------------------
#endif
