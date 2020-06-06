#include "Header.h"
HBITMAP BtmImg = NULL;
HBITMAP BtmImg2 = NULL;
BOOL CALLBACK LVDlg (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
        			BtmImg = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MyIcon2));
			if(BtmImg == NULL)
				MessageBox(hwnd, "Could not load An image!", "Error", MB_OK | MB_ICONEXCLAMATION);
            SetFocus(hwnd);
        return TRUE;
        case WM_PAINT:
		{
			BITMAP bm;
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(hwnd, &ps);

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, BtmImg);

			GetObject(BtmImg, sizeof(bm), &bm);

			BitBlt(hdc,132,7, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);

			EndPaint(hwnd, &ps);
		}
        break;
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {
            case IDC_LV1:
                Level=5;
            break;
            case IDC_LV2:
                Level=4;
            break;
            case IDC_LV3:
                Level=3;
            break;
            case IDC_BUTTONOK:
                EndDialog(hwnd,Level);
            break;
        }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}
BOOL CALLBACK AboutDlg (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:
        			BtmImg2 = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MyPic));
			if(BtmImg2 == NULL)
				MessageBox(hwnd, "Could not load An image!", "Error", MB_OK | MB_ICONEXCLAMATION);
            SetFocus(hwnd);
        return TRUE;
        case WM_CLOSE:
            EndDialog(hwnd,0);
        break;

        case WM_PAINT:
		{
			BITMAP bm;
			PAINTSTRUCT ps;

			HDC hdc = BeginPaint(hwnd, &ps);

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, BtmImg2);

			GetObject(BtmImg2, sizeof(bm), &bm);

			BitBlt(hdc,175,30,150,200, hdcMem,0,0, SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);

			EndPaint(hwnd, &ps);
		}
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_OK:
                EndDialog(hwnd,IDC_OK);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage (0);
        break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case Mstr:
                {
                        char T[4];
                        x=0;
                        while(x<9)
                        {
                                   y=0;
                                   while(y<9)
                                   {
                                       if(SDOK_NUMBERS2[x][y]==0)
                                       {
                                             GetWindowText(Hwnd[x][y],T,2);
                                             SDOK_NUMBERS2[x][y]=Char2Int(T[0]);
                                             if(SDOK_NUMBERS2[x][y]!=0)
                                             {
                                                 if(IsValidNumber(x,y,SDOK_NUMBERS2[x][y]))
                                                 {

                                                 }else
                                                 {
                                                     UnkownNumbers=1;

                                                        //MessageBox(hwnd,"Note:There is a number that you have entered is not correct:You Have  to start again or to reset the game.","Error",0);
                                                 }
                                                 EnableWindow(Hwnd[x][y],FALSE);
                                             }else
                                             {
                                                EnableWindow(Hwnd[x][y],TRUE);
                                             }
                                       }else
                                       {
                                            if(IsWindowEnabled(Hwnd[x][y])!=FALSE)
                                            {
                                                itoa(SDOK_NUMBERS2[x][y],T,10);
                                                SetWindowText(Hwnd[x][y],T);
                                                EnableWindow(Hwnd[x][y],FALSE);

                                            }
                                       }
                                        y++;
                                   }
                                   x++;
                        }
                        if(CheckCom())
                        {
                            EnableWindow(btnhwnd4,TRUE);
                            EnableWindow(btnhwnd3,FALSE);
                        }else
                        {
                            if(IsWindowEnabled(btnhwnd4)==TRUE)
                            {
                                EnableWindow(btnhwnd4,FALSE);
                                EnableMenuItem(GetMenu(hwnd),MITEM_CHECK,MF_DISABLED | MF_GRAYED);
                            }
                            if(IsWindowEnabled(btnhwnd3)==FALSE)
                            {
                                EnableWindow(btnhwnd3,TRUE);
                                EnableMenuItem(GetMenu(hwnd),MITEM_ADDone,MF_ENABLED);
                            }
                            if(IsWindowEnabled(btnhwnd2)==FALSE)
                            {
                                EnableWindow(btnhwnd2,TRUE);
                                EnableMenuItem(GetMenu(hwnd),MITEM_ReSet,MF_ENABLED);
                            }
                        }
                        if(IsWindowEnabled(btnhwnd3)==FALSE && !CheckCom())
                        {
                            EnableWindow(btnhwnd3,TRUE);
                            EnableMenuItem(GetMenu(hwnd),MITEM_ADDone,MF_ENABLED );
                        }

                }
                break;
                case BTN_CHECK:
                        if(UnkownNumbers==0 && CheckCom()==1)
                        {
                            if(HelpingOutCounter<=6)
                                       MessageBox(hwnd,"Smart Man Click,Try again","Good Work",0);
                                  else
                                       MessageBox(hwnd,"Smart Man,But You used  [Add one] Button more than 6 titmes","Good Work",0);
                        }
                        else if(UnkownNumbers==1 && CheckCom()==1)
                            MessageBox(hwnd,"Lazy Boy,Try again","^-^",0);
                        SetZero(SDOK_NUMBERS2);
                        SetZero(SDOK_NUMBERS3);
                break;
                case BTN_CLOSE:
                AnimateWindow(hwnd,500,0x00010000 | 0x00000002);
                   PostQuitMessage (0);
                break;
                case BTN_Help:
                    MessageBox(hwnd,"If you realy want My help Please contact me at:[MoroccanHackAttackx@hotmail.com]","Can U C Me",0);
                break;
                case MITEM_ABOUT:
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(101),hwnd,AboutDlg);
                break;
                case BTN_NewGame:
                {
                    GameStart=1;
                    Level=5;
                    UnkownNumbers=0;
                    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(LevelDlg),hwnd,LVDlg);
                    HelpingOutCounter=0;
                    SetNums();
                    SetKnownNumbers();
                    SendMessage(hwnd,WM_COMMAND,Mstr,0);

                }
                break;
                case 5:
                    PostMessage(hwnd,WM_COMMAND,Mstr,0);
                break;
                case BTN_ADDone:
                    HelpingOutCounter++;
                    AddNextOne();
                break;
                case BTN_ReSet:
                {
                    UnkownNumbers=0;
                     SetZero(NULL);
                   SetCurValue(SDOK_NUMBERS3);
                }
                break;
            }
        break;
        case WM_CLOSE:
            AnimateWindow(hwnd,500,0x00010000 | 0x00000002);
        break;
        case WM_CREATE:
        {
            int x,y;
            x=0;
            int j=0,j2=0;
            while(x<9)
            {
                y=0;
                j+=20;
                j2=0;
                if(x%3==0)j+=5;
                while(y<9)
                {
                    j2+=(j2==0?0:20);
                    if(y%3==0)j2+=5;
                    Hwnd[x][y]=CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|ES_NUMBER|ES_CENTER|WS_BORDER,j2,j,20,20,hwnd,5,GetModuleHandle(NULL),0);
                    y++;
                }
                x++;
            }
            CreateWindow("BUTTON","Exit",WS_CHILD|WS_VISIBLE|ES_CENTER,5,j+23,190,25,hwnd,BTN_CLOSE,0,0);
            btnhwnd2=CreateWindow("BUTTON","Reset",WS_CHILD|WS_DISABLED|WS_VISIBLE|ES_CENTER,j2+23,j-5,80,25,hwnd,BTN_ReSet,0,0);
            CreateWindow("BUTTON","NewGame",WS_CHILD|WS_VISIBLE|ES_CENTER,j2+23,j-30,80,25,hwnd,BTN_NewGame,0,0);
            CreateWindow("BUTTON","Help",WS_CHILD|WS_VISIBLE|ES_CENTER,j2+23,j-29-26,80,25,hwnd,BTN_Help,0,0);
            btnhwnd3=CreateWindow("BUTTON","Add one",WS_CHILD|WS_DISABLED|WS_VISIBLE|ES_CENTER,j2+23,j-29-26-25,80,25,hwnd,BTN_ADDone,0,0);
            btnhwnd4=CreateWindow("BUTTON","Check",WS_CHILD|WS_DISABLED|WS_VISIBLE|ES_CENTER,j2+23,j-29-26-25-25,80,25,hwnd,BTN_CHECK,0,0);
            AnimateWindow(hwnd,500,0x00020000 | 0x00000002);
            SetFocus(hwnd);
        }
        break;
        case WM_CTLCOLOREDIT:
        {
            SetTextColor((HDC)wParam,RGB(255,0,0));
            SetBkMode((HDC)wParam,1);
            return (LONG)CreateSolidBrush(RGB(0,255,0));
        }
        break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
