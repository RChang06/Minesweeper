#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <string>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND button;  // variable for all the buttons
HWND textBox; // variable for textbox
char savedText[100];

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("KILL ME NOW PLZ"), /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           500,                 /* The programs width */
           500,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
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

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        // creating textBox
        textBox = CreateWindow (TEXT("EDIT"),
                                TEXT(""),
                                WS_BORDER | WS_CHILD | WS_VISIBLE,
                                20,100,400,30,
                                hwnd, NULL, NULL, NULL);

        // creating buttons
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("0"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,410,130,20,
                             hwnd, (HMENU) 0, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("1"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,380,50,20,
                             hwnd, (HMENU) 1, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("2"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,380,50,20,
                             hwnd, (HMENU) 2, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("3"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,380,50,20,
                             hwnd, (HMENU) 3, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("4"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,350,50,20,
                             hwnd, (HMENU) 4, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("5"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,350,50,20,
                             hwnd, (HMENU) 5, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("6"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,350,50,20,
                             hwnd, (HMENU) 6, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("7"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             20,320,50,20,
                             hwnd, (HMENU) 7, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("8"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,320,50,20,
                             hwnd, (HMENU) 8, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("9"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,320,50,20,
                             hwnd, (HMENU) 9, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("("),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             100,290,50,20,
                             hwnd, (HMENU) 10, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT(")"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,290,50,20,
                             hwnd, (HMENU) 11, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("/"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,290,50,20,
                             hwnd, (HMENU) 12, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("x"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,320,50,20,
                             hwnd, (HMENU) 13, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("-"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,350,50,20,
                             hwnd, (HMENU) 14, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("+"),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             260,380,50,20,
                             hwnd, (HMENU) 15, NULL, NULL );
                             //break;
        button = CreateWindow (TEXT("BUTTON"),
                             TEXT("="),
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             180,410,130,20,
                             hwnd, (HMENU) 16, NULL, NULL );
                             break;

        case WM_COMMAND:

         //     LPCTSTR bb = TEXT("Test String");
 MessageBox(NULL, TEXT("Test String"), TEXT("Test String"), MB_OK); 
 
            switch (LOWORD(wParam))
            {
                case 0:
                    //code for button 0
                    ///::MessageBox(hwnd,"Button 0","was clicked",MB_OK);  // JUST CHECKED IF BUTTON WORKS



                case 1:
                    //code for button 1

                case 2:
                    //code for button 2

                case 3:
                    //code for button 3

                case 4:
                    //code for button 4

                case 5:
                    //code for button 5

                case 6:
                    //code for button 6

                case 7:
                    //code for button 7

                case 8:
                    //code for button 8

                case 9:
                    //code for button 9

                case 10:
                    //code for button 10 (

                case 11:
                    //code for button 11 )

                case 12:
                    //code for button 12 /

                case 13:
                    //code for button 13 x

                case 14:
                    //code for button 14 -

                case 15:
                    //code for button 15 +

                case 16:
                    //code for button 16 =

               return DefWindowProc (hwnd, message, wParam, lParam);
            }


        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}