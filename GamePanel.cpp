#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>
#include<iostream>

#include "Board.h"
#include "GameView.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
GameView* globalGameView = nullptr;
class GamePanel
{
    //    Board board;
public:
    //  GameView viewe;

    HWND button;  // variable for all the buttons
    HWND textBox; // variable for textbox
    char savedText[100];

    void initialView(HWND hwnd)
    {

        globalGameView = new GameView(hwnd);
        globalGameView->initialBoard();
    }

    /*  Make the class name into a global variable  */
    // TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

    int WINAPI WinMain(HINSTANCE hThisInstance,
                       HINSTANCE hPrevInstance,
                       LPSTR lpszArgument,
                       int nCmdShow)
    {
        HWND hwnd;        /* This is the handle for our window */
        MSG messages;     /* Here messages to the application are saved */
        WNDCLASSEX wincl; /* Data structure for the windowclass */

        // TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

        /* The Window structure */
        wincl.hInstance = hThisInstance;
        wincl.lpszClassName = _T("CodeBlocksWindowsApp");
        wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
        // wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        wincl.style = CS_DBLCLKS; /* Catch double-clicks */
        wincl.cbSize = sizeof(WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL; /* No menu */
        wincl.cbClsExtra = 0;      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

        /* Register the window class, and if it fails quit the program */
        if (!RegisterClassEx(&wincl))
            return 0;

        /* The class is registered, let's create the program*/
        hwnd = CreateWindowEx(
            0,                          /* Extended possibilites for variation */
            _T("CodeBlocksWindowsApp"), // szClassName,         /* Classname */
            _T("KILL ME NOW PLZ"),      /* Title Text */
            WS_OVERLAPPEDWINDOW,        /* default window */
            CW_USEDEFAULT,              /* Windows decides the position */
            CW_USEDEFAULT,              /* where the window ends up on the screen */
            500,                        /* The programs width */
            500,                        /* and height in pixels */
            HWND_DESKTOP,               /* The window is a child-window to desktop */
            NULL,                       /* No menu */
            hThisInstance,              /* Program Instance handler */
            NULL                        /* No Window Creation data */
        );

        /* Make the window visible on the screen */
        ShowWindow(hwnd, nCmdShow);

        /* Run the message loop. It will run until GetMessage() returns 0 */
        while (GetMessage(&messages, NULL, 0, 0))
        {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }

        /* The program return-value is 0 - The value that PostQuitMessage() gave */
        return messages.wParam;
    }

    /*  This function is called by the Windows function DispatchMessage()  */

    LRESULT CALLBACK WindowProcedure0000(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {

        switch (message) /* handle the messages */
        {
        case WM_CREATE:
            initialView(hwnd);
            break;

        case WM_COMMAND:

            //     LPCTSTR bb = TEXT("Test String");
            int buttonID = LOWORD(wParam);
            if(buttonID>=1 && buttonID <=64) {
                if (HIWORD(wParam) == BN_CLICKED){
                    std::cout<<"clicked";
                    globalGameView->leftClick(64/8, 64%8);
                }
            }
            std::cout<<"clicked";

            MessageBox(NULL, TEXT("Test String"), TEXT("Test String"), MB_OK);

        case WM_CTLCOLORBTN:
        {
            HDC hdcButton = (HDC)wParam;
            HWND hButton = (HWND)lParam;

            // Set background and text colors
            SetBkColor(hdcButton, RGB(255, 255, 0)); // Yellow background
            SetTextColor(hdcButton, RGB(0, 0, 0));   // Black text

            // Create a solid brush for the background
            static HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
            return (LRESULT)hBrush;
        }

        case WM_DESTROY:
            PostQuitMessage(0); /* send a WM_QUIT to the message queue */
            break;
        default: /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
        }

        return 0;
    }
};

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{

 GamePanel gamePanel;
   return gamePanel.WinMain(hThisInstance,
                             hPrevInstance,
                             lpszArgument,
                             nCmdShow);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
GamePanel gamePanel;
    return gamePanel.WindowProcedure0000(hwnd, message, wParam, lParam);
}