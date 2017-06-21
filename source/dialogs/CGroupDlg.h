#ifndef CGROUPDLG_H
#define CGROUPDLG_H

#include <windows.h>
#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

#include "..\tools\CGroupManager.h"
#include "..\controls\CCommonDialogs.h"

class CGroupDlg
{
private:
	HWND					m_hOwner;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;

	static string			m_sgr;
	static bool				nieuw;
	static CGroup			*m_gr;
	static CCommonDialogs	*m_pCommonDlg;
	static CGroupManager	*m_pGroupManager;
public:
	CGroupDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager );
	~CGroupDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show( string, bool );
	void clearData( void );
	void showdata( void );
	static void savedata( HWND );
	bool isDlg( void );
};

#endif
