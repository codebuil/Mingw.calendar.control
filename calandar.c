#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 10000
#define MAX_BUFFER_SIZE 1024
#define lines 10
static HWND hStartEdit,hEndEdit,hButton,hButton2,thew,tthew[lines];
int xx = 2; // Define a posição horizontal
int yy = 2; // Define a posição vertical
 int nn,nnn;   
  static char startStr[1024], endStr[1024];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Temporizador");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    int iiii;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Este programa requer Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("button menu"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
        

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szBuffer[80];
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    char startStr[1025];
    time_t rawtime;
    struct tm *timeinfo;
    int iiii;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // Define a data para o primeiro dia do mês corrente
    tm->tm_mday = 1;

    // Normaliza a data
    mktime(tm);

    // Calcula o dia da semana (0 = domingo, 1 = segunda-feira, etc.)
    int d = tm->tm_wday;
   int mes = tm->tm_mon + 1;
   
    char buffer[MAX_BUFFER_SIZE];

    

    switch (message)
    {
        case WM_CREATE:
         // Obtém a data atual
    
       for(nn=0;nn<31;nn++){
        int nnn=40+(nn+1);
        sprintf(startStr,"%d",nn+1);
        if((nn+1)<=month[mes-1])tthew[nn] = CreateWindow("BUTTON", startStr, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            ((d+nn)-(((d+nn)/7)*7))*50+5,((d+nn)/7)*30+5, 50, 30,  hwnd, (HMENU)nnn, GetModuleHandle(NULL), NULL);
       }
                
                
            
        
        break;
        case WM_COMMAND:
            iiii=(int)(LOWORD(wParam));
            if(iiii>=40 && iiii<=40+35){
                iiii=iiii-40;
                sprintf(startStr,"%d",iiii);
                 SetWindowText(hwnd, startStr);
                 
                
            }
            
           
    break;   

    case WM_PAINT:
            
            hdc = BeginPaint(hwnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            break;
    

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
