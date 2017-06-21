#ifndef CNEWNAMEDLG_H
#define CNEWNAMEDLG_H

#include <windows.h>
#include <string>
using namespace std;

#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

#include "..\tools\CGroupManager.h"

class CNewNameDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
	static string		result;
public:
	CNewNameDlg( HINSTANCE, HWND );
	~CNewNameDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	string show( void );
	bool isDlg( void );
};

#endif
