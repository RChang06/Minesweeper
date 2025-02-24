#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif // _UNICODE

typedef const TCHAR* LPCTSTR;


#include <windows.h> 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
 LPSTR lpCmdLine, int nCmdShow) 
{ 
    LPCTSTR bb = TEXT("Test String");
 MessageBox(NULL, bb, bb, MB_OK); 
 return 0; 
} 
