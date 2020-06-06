#define _WIN32_WINNT 0x0700
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
//Menu Conts
#define LevelDlg 599
#define IDC_LV1 897
#define IDC_LV2 898
#define IDC_LV3 899
#define IDC_BUTTONOK 900
#define IDC_IMAGE 1000

#define IDC_OK 1003
#define IDC_GROUPBOX1005 1005
#define IDC_GROUPBOX1006 1006

#define MyMenu 600
#define MITEM_Exit 601
#define MITEM_Help 602
#define MITEM_ReSet 603
#define MITEM_NewGame 604
#define MITEM_ADDone  605
#define MITEM_CHECK   606
#define MITEM_ABOUT   607
//Button Conts
#define BTN_CLOSE     MITEM_Exit
#define BTN_NewGame   MITEM_NewGame
#define BTN_ReSet     MITEM_ReSet
#define BTN_Help      MITEM_Help
#define BTN_ADDone     MITEM_ADDone
#define BTN_CHECK     MITEM_CHECK
#define MyIcon 895
#define MyIcon2 896
#define MyPic    10070

#define Mstr 986

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char szClassName[ ] = "HaSoudouko";

HWND Hwnd[9][9];
HWND btnhwnd;
HWND btnhwnd2,btnhwnd3,btnhwnd4;
HWND hwnd;
int SDOK_NUMBERS[9][9]={
			  {6,   5,   7,   	      1,   3,   8,		   4,   9,   2,},
			  {8,   2,   3, 		  9,   6,   4,		   7,   5,   1,},
			  {4,   1,   9, 		  2,   7,   5,		   6,   3,   8,},

			  {1,   6,   2, 		  5,   8,   9,		   3,   4,   7,},
			  {9,   3,   4, 		  7,   1,   6, 		   2,   8,   5,},
			  {5,   7,   8, 		  3,   4,   2, 		   1,   6,   9,},

			  {3,   4,   5, 		  8,   2,   7,		   9,   1,   6,},
			  {7,   8,   6, 		  4,   9,   1,		   5,   2,   3,},
			  {2,   9,   1, 		  6,   5,   3,		   8,   7,   4,}
		  };
int SDOK_NUMBERS2[9][9];
int SDOK_NUMBERS3[9][9];
int x,y;
int HelpingOutCounter=0;
int Level;
int UnkownNumbers=0;
int h=0;
int GameStart=0;
int Char2Int(char c)
{
    if(c>='1' && c<='9')
    {
     return c-'0';
    }
    return 0;
}

int Guese(int From,int To)
{
    srand(time(NULL)*rand());
    int R=rand()%To;
    return R>=From && R<=To?R:To-1;
}
int SetZero(int ar[9][9])
{
        int x=0;
        int y=0;
        while(x<9)
        {
            y=0;
            while(y<9)
            {
                if(ar!=NULL)
                 ar[x][y]=0;
                SetWindowText(Hwnd[x][y],"");
                 EnableWindow(Hwnd[x][y],TRUE);
                 y++;
            }
             x++;
        }
}
int AddNextOne()
 {
        int x=0;
        int y=0;
        while(x<9)
        {
            y=0;
            while(y<9)
            {
                if(SDOK_NUMBERS2[x][y]==0)
                {
                    if(!IsValidNumber(x,y,SDOK_NUMBERS[x][y]))UnkownNumbers=1;
                    SDOK_NUMBERS2[x][y]=SDOK_NUMBERS[x][y];
                    SendMessage(hwnd,WM_COMMAND,Mstr,0);
                    return 1;
                }
                 y++;
            }
             x++;
        }
 }
int SetKnownNumbers()
{
    SetZero(SDOK_NUMBERS2);
    SetZero(SDOK_NUMBERS3);
    int c1=0,c2=0,c3=0,k;
    int p=0;
    c1=0;
    while(c1<=6)
    {
        c2=0;
        while(c2<=6)
        {
            c3=0;
            p=Guese(2,Level);
            while(p>=0)
            {
                k=Guese(0,3);
                SDOK_NUMBERS2[c1+c3][c2+k]=SDOK_NUMBERS[c1+c3][c2+k];
                SDOK_NUMBERS3[c1+c3][c2+k]=SDOK_NUMBERS2[c1+c3][c2+k];
                c3++;
                if(c3==3)c3=0;
                p--;

            }
            c2+=3;
        }
        c1+=3;
    }

}

int SetNums()
{
                        int x=0;
                        int y=0;


                        y=0;
                        x=0;int k=0,l,ll;
                        while(k<9)
                        {
                         l=Guese(k,k+3);
                         ll=Guese(k,k+3);
                            x=0;
                             while(x<9)
                            {
                                    y=SDOK_NUMBERS[x][l];
                                    SDOK_NUMBERS[x][l]=SDOK_NUMBERS[x][ll];
                                    SDOK_NUMBERS[x][ll]=y;
                                x++;
                            }
                            x=0;
                            l=Guese(k,k+3);
                            ll=Guese(k,k+3);
                             while(x<9)
                            {
                                    y=SDOK_NUMBERS[l][x];
                                    SDOK_NUMBERS[l][x]=SDOK_NUMBERS[ll][x];
                                    SDOK_NUMBERS[ll][x]=y;
                                x++;
                            }
                            x=0;
                            l=Guese(k,k+3);
                            ll=Guese(k,k+3);
                             while(x<9)
                            {
                                    y=SDOK_NUMBERS[l][x];
                                    SDOK_NUMBERS[l][x]=SDOK_NUMBERS[ll][x];
                                    SDOK_NUMBERS[ll][x]=y;
                                x++;
                            }
                            k+=3;
                        }

                        k=0;
                        l=Guese(0,3);
                        ll=Guese(0,3);
                        l=l==0?l:l==1?3:6;
                        ll=ll==0?ll:ll==1?3:6;
                        int u,m;
                        while(k<9)
                        {
                            x=0;
                            while(x<9)
                            {
                                    y=SDOK_NUMBERS[x][l];
                                    SDOK_NUMBERS[x][l]=SDOK_NUMBERS[x][ll];
                                    SDOK_NUMBERS[x][ll]=y;
                                x++;

                            }
                            x=0;
                            while(x<9)
                            {
                                    y=SDOK_NUMBERS[l][x];
                                    SDOK_NUMBERS[l][x]=SDOK_NUMBERS[ll][x];
                                    SDOK_NUMBERS[ll][x]=y;
                                x++;

                            }
                            l++;ll++;
                            k+=3;
                       }
                       k=0;
                        while(k<9)
                        {
                         l=Guese(k,k+3);
                         ll=Guese(k,k+3);
                            x=0;
                             while(x<9)
                            {
                                    y=SDOK_NUMBERS[x][l];
                                    SDOK_NUMBERS[x][l]=SDOK_NUMBERS[x][ll];
                                    SDOK_NUMBERS[x][ll]=y;
                                x++;
                            }
                            x=0;
                            l=Guese(k,k+3);
                            ll=Guese(k,k+3);
                             while(x<9)
                            {
                                    y=SDOK_NUMBERS[l][x];
                                    SDOK_NUMBERS[l][x]=SDOK_NUMBERS[ll][x];
                                    SDOK_NUMBERS[ll][x]=y;
                                x++;
                            }
                            k+=3;
                        }

}
int CheckCom()
{
        int x=0;
        int y=0;
        int j=0;int jj=0;
        while(x<9)
        {
            y=0;
            while(y<9)
            {
               if(SDOK_NUMBERS2[x][y]!=0)
                      jj++;
                y++;
            }
             x++;
        }
        if(jj==81)
        {
            return 1;
        }
        return 0;
}


int SetCurValue(int SDOK[9][9])
{
                    int x=0;
                    int y;
                    while(x<9)
                    {
                        y=0;
                        while(y<9)
                        {
                            SDOK_NUMBERS2[x][y]=SDOK[x][y];
                            y++;
                        }
                        x++;
                    }
                    SendMessage(hwnd,WM_COMMAND,Mstr,0);
}

int IsValidNumber(int x,int y,int number)
{
    int xx,yy;
    xx=0;
    while(xx<9)
    {
        if(SDOK_NUMBERS2[xx][y]==number && xx!=x){
            return 0;
        }
        xx++;
    }
    yy=0;
    while(yy<9)
    {
        if(SDOK_NUMBERS2[x][yy]==number && yy!=y){
            return 0;
        }
        yy++;
    }
    xx=x<3?0:x<6?3:6;
    yy=y<3?0:y<6?3:6;
    int h=xx+3,j;

    while(xx<h)
    {
        yy=y<3?0:y<6?3:6;
       j=yy+3;
        while(yy<j)
        {
            if(SDOK_NUMBERS2[xx][yy]==number && (yy!=y && xx!=x)){
                return 0;
            }
            yy++;
        }
        xx++;
    }
    return 1;
}
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nFunsterStil)
{
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (GetModuleHandle(NULL),  MAKEINTRESOURCE(MyIcon));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL),  MAKEINTRESOURCE(MyIcon));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(MyMenu);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_HIGHLIGHT ;
    if (!RegisterClassEx (&wincl))
        return 0;
    hwnd = CreateWindowEx (0,szClassName, szClassName,WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,300, 300,HWND_DESKTOP,(HMENU)NULL,hThisInstance,NULL);
    ShowWindow (hwnd, nFunsterStil);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
