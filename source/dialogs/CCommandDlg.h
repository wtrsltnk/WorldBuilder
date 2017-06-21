#ifndef CCOMMANDDLG_H
#define CCOMMANDDLG_H

#include <windows.h>
#include "..\..\Resource\resource.h"
#include "..\custommsg.h"

#include "..\tools\CGroupManager.h"

class CCommandDlg
{
private:
	HWND					m_hOwner;
	HWND					m_hWnd;
	HINSTANCE				m_hInstance;

	static string 			m_sgr, m_stl, m_scmd;
	static bool				nieuw;
	static CCommand			*m_cmd;
	static CGroupManager	*m_pGroupManager;
public:
	CCommandDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager );
	~CCommandDlg( void );
	static BOOL DlgProc( HWND, UINT, WPARAM, LPARAM );

	void show( string group, string tool, string command, bool );
	void clearData( void );
	void showdata( void );
	static void savedata( HWND );
	bool isDlg( void );
};

#endif
