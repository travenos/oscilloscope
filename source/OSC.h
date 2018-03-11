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
private:	// User declarationsdouble kvnesh[2];//��� ���������� �������������� ���������� 2-� �������
        double kvnesh[2];//��� ���������� �������������� ���������� 2-� �������
        double kvnut[2];//��� ����������� �������������� ���������� 2-� �������
        bool IsPwrOn;

        double Fs;//������� �������������
        double Td; //����� �������� �������
        double k[2];//������������ ������������ ���������
        double tR; //������������ ��������
        double tRvnut; //�������� ������������ ��������
        double dt; //����� �������������
        unsigned short int kDT; //��������� ������� �������������
        int c[2];//�������� �������� ����
        int ct;//�������� ��������������� �������� ��������

        int SW; //������ ������
        SignalParam param[2];     //�������������� ������� �������

        double *Ut[2][2];  //������� �� ���������� �������� ��� ���������

        double t; //�����
        bool writingDown; //������������ �� ������ �������� �������
        bool even; //׸���� ��� �������� ������ ��������
        int N; //����� �������� �������

        TTractForm *TractFormII;   //���� ���������� ������ II
        THelperForm *Helper;

        //��������� ������������
        short int inpMode[2];    //������������� ������� ����� (��� ��������� 1.1 � 1.2(�������� 1, 2, 3))
        short int tractMode;   //����� ����������� �������
        short int syncMode;   //����� �������������
        bool syncFront;   //����� ������ �������� (true - ��������, false - ������)
        bool invert; //�������������� ������� ������ II
        bool x10[2]; //��� 4_1, 4_2//�������� �������� � 10 ���
        bool x02; //��� 7 //��������� �������� � 5 ���
        bool autoR; //����������������� ��������

        bool del6[2]; //����� 6 ���

        double startVal; //��� 11//��������, ����������� ��������
        double fm[2]; //������� ������� ��� ��������� ���������
        double phasem[2]; //������� ������� ����
        double ps[2];   //���������� ������������
        double tLast; //����� ���������� ��������� ��������

        double oldU[2][2]; //��������� 2 �������� �������� ������� �������
        double oldY[2][2]; //��������� 2 �������� ��������� ������� �������

        //double realF[2];

        //��������� ����� ����
        static const int hue=122;
        static const int saturation=89;
        int value;

        int lineWidth;      //������ ����
        int gridValue; //������� �����

        double b;    //������������ ���
        double a[2];

        int dCh; //�������� �������

        Graphics::TBitmap *pic;

        AnsiString signalsFolder;     //������� �������

        int *positionsData;    //������ � ����������� ����

        //������
        void __fastcall clearData();
        void __fastcall signalCalc();
        void __fastcall signalDraw();
        void __fastcall XYDraw();
        void __fastcall drawGrid(int v);  //���������� ��������� �����
        void __fastcall updatedt();  //���������� �������� ����
        void  __fastcall updateK();
        //������������ �������� ������� �������, ����� ����������� �. ������������
        void __fastcall correctParam(bool tractN);
        void __fastcall paint(int i, int U, double ts);   //���������������� ��������� �� ������
        void __fastcall writeDown(double U, bool tractN);     //������ ������� � ������
        int __fastcall videoimp(double z, double T, double tau);
        double __fastcall triangleimp(double x, double Tf, double df);  //����������� �������

        //����������� �������� ������� � ������
        double __fastcall signal(bool tractN);

        double __fastcall filter(double u, bool tractN);

        //������� �� HSV � RGB
        TColor __fastcall HSV2RGB(int i_hue,int sat,int val);

        void __fastcall readSettings(); //������� ��������� �� �����
        void __fastcall writeSettings(); //�������� ��������� � ����

public:		// User declarations

        vector<SignalParam> dataBase;
        __fastcall TOSCForm(TComponent* Owner);

        void __fastcall setConnection(bool tractN, bool enable);
        void __fastcall CloseHelper();

        void __fastcall LoadJPEGRes(TPicture *pic, AnsiString ResName);  //�������� JPEG �� �������
        void __fastcall readDataBase();//������� ���� ������ �� �����
        void __fastcall extractDataBase(); //������� �� �������� ���������� ���� ������
        void __fastcall writeDataBase();//�������� ���� ������ � ����
        void __fastcall writeDataBase(bool tractN);//�������� ���� ������ � ����
        
        void __fastcall signalCalcOnce(); //���������� � ������� ���� ������ ��������


};
//---------------------------------------------------------------------------
extern PACKAGE TOSCForm *OSCForm;
//---------------------------------------------------------------------------
#endif
