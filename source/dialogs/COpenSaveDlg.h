#ifndef COPENSAVEDLG_H
#define COPENSAVEDLG_H

#include <windows.h>
#include <string>
using namespace std;

#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

class COpenSaveDlg
{
private:
	HWND				m_hOwner;
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

public:
	COpenSaveDlg( HINSTANCE, HWND );
	~COpenSaveDlg( void );

	string open( char *, char *, char * );
	string save( char *, char *, char * );
};

#endif
