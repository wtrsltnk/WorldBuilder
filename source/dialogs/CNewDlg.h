#ifndef CNEWDLG_H
#define CNEWDLG_H

#include <windows.h>
#include <string>
using namespace std;

#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

class CNewDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

public:
	CNewDlg( HINSTANCE, HWND );
	~CNewDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show( void );
	bool isDlg( void );
};

#endif
