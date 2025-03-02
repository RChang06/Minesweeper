#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <windows.h>
#include <string>

#include "Board.h"
#include "GameView.h"

// Forward declarations
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
GameView* globalGameView = nullptr;

class GamePanel
{
public:
    //This is just the functions called whenever a valid click is clicked
    // Calls upon the GameView class that handles the display
    void initialView(HWND hwnd)

    {
        if (!globalGameView){
            globalGameView = new GameView(hwnd);
        }
        globalGameView->initialBoard();

    }

    void processLeftClick(HWND hwnd, int index)
    {
        globalGameView->processLeftClick(index);
    }
    void processRightClick(HWND hwnd, int xPos, int yPos){
        globalGameView->processRightClick(xPos, yPos);
    }
    void processDoubleClick(HWND hwnd, int index){
        globalGameView->processDoubleClick(index);
    }
};

// Global instance of GamePanel
GamePanel gamePanel;

// Entry point of the application
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    srand(time(0));

    HWND hwnd;               // Handle for the window
    MSG messages;            // Message structure
    WNDCLASSEX wincl;        // Window class structure

    // Set up the window class
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = _T("CodeBlocksWindowsApp");
    wincl.lpfnWndProc = WindowProcedure; // Message handler
    wincl.style = CS_DBLCLKS;            // Catch double-clicks
    wincl.cbSize = sizeof(WNDCLASSEX);

    // Default icon and cursor
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;           // No menu
    wincl.cbClsExtra = 0;                // No extra class memory
    wincl.cbWndExtra = 0;                // No extra window memory
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND; // Default background color

    // Register the window class
    if (!RegisterClassEx(&wincl))
        return 0;

    // Create the window
    hwnd = CreateWindowEx(
        0,                          // Extended window style
        _T("CodeBlocksWindowsApp"), // Class name
        _T("KILL ME NOW PLZ"),      // Window title
        WS_OVERLAPPEDWINDOW,        // Window style
        CW_USEDEFAULT,              // Default horizontal position
        CW_USEDEFAULT,              // Default vertical position
        500,                        // Width
        500,                        // Height
        HWND_DESKTOP,               // Parent window
        NULL,                       // No menu
        hThisInstance,              // Instance handle
        NULL                        // No additional data
    );

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages); // Translate keyboard input
        DispatchMessage(&messages);  // Send messages to WindowProcedure
    }

    // Return the exit code
    return messages.wParam;
}

// Message handler for the window
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    //message is an integer value returned by the program when a certain type of click is pressed
    static DWORD lastClickTime = 0;
    //retrieve the x and y cordinates, and make it relative to window client rather than personal screen
    POINT pt = { LOWORD(lParam), HIWORD(lParam) };
    ScreenToClient(hwnd, &pt);
    
    //Integer 123 corresponds to right click, while the proper WM_RBUTTON DOWN is 516.
    // This is just a lazy hard code to solve that scenario
    if (message == 123 ){
        message = 516; 
    }
    
    //Issues commands to initialize depending what message is returned
    switch (message)
    {
    // set up the board if message is 1
    case WM_CREATE:
        gamePanel.initialView(hwnd); // Initialize the view
        break;
    
    //initialize the function processRightClick, when the user right clicks
    case WM_RBUTTONDOWN:

        gamePanel.processRightClick(hwnd, pt.x, pt.y);
        break;
    
    //double CLick    
   
    //trouble shooting ignore
    case WM_LBUTTONDBLCLK:
        std::cout<<"asdfa";
       
        break;

    // apparently double click message = 273 alligns with WM_COMMAND and not any of the other double clicks
    case WM_COMMAND: {
        DWORD currentTime = GetTickCount();
        if (currentTime - lastClickTime < GetDoubleClickTime()){
            std::cout<<"double click yaaaaa";
            gamePanel.processDoubleClick(hwnd, LOWORD(wParam));
        }

        else {
            gamePanel.processLeftClick(hwnd, LOWORD(wParam)); // Process commands
        }
        lastClickTime = currentTime;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0); // Exit the application
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam); // Default message handling
    }

    return 0;
}