#ifndef CTOOLDLG_H
#define CTOOLDLG_H

#include <windows.h>
#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

#include "..\tools\CGroupManager.h"

class CToolDlg
{
private:
	HWND					m_hOwner;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;
	
	static bool				nieuw;
	static string			m_sgr;
	static string			m_stl;
	static CTool			*m_tl;
	static CGroupManager	*m_pGroupManager;
public:
	CToolDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager );
	~CToolDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show( string, string, bool );
	void clearData( void );
	void showdata( void );
	static void savedata( HWND );
	bool isDlg( void );
};

#endif
