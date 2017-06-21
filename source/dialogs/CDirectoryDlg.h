#ifndef CDIRECTORYDLG_H
#define CDIRECTORYDLG_H

#include <windows.h>
#include <string>
using namespace std;
 
#include "..\..\Resource\resource.h"
#include "..\custommsg.h"
#include "..\funclib.h"

#define BUFFER MAX_PATH 

class CDirectoryDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
	static string		result;
public:
	CDirectoryDlg( HINSTANCE, HWND );
	~CDirectoryDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	string show( void );
	bool isDlg( void );
};

#endif
