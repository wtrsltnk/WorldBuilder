#ifndef CDIALOGSMANAGER_H
#define CDIALOGSMANAGER_H

#include <windows.h>
#include "..\resource\resource.h"
#include "tools\CGroupManager.h"
#include "dialogs\CCommandDlg.h"
#include "dialogs\CGroupDlg.h"
#include "dialogs\CToolDlg.h"
#include "dialogs\CNewDlg.h"
#include "dialogs\COpenSaveDlg.h"
#include "dialogs\CNewNameDlg.h"

class CDialogsManager
{
private:
	HINSTANCE				m_hInstance;
	HWND					m_hOwner;
	CGroupManager			*m_pGroupManager;
	CCommandDlg				*m_pCommandDlg;
	CGroupDlg				*m_pGroupDlg;
	CToolDlg				*m_pToolDlg;
	CNewDlg					*m_pNewDlg;
	CCommonDialogs			*m_pCommonDlg;
	CNewNameDlg				*m_pNewNameDlg;
public:
	CDialogsManager( HINSTANCE hInstance, HWND hParent, CGroupManager *pGroupManager );
	~CDialogsManager( void );

	void setPointer( CGroupManager *pGroupManager );

	void showGroup( string, bool );
	void showTool( string, string, bool );
	void showCommand( string, string, string, bool );
	void showGameCommand( string, string, bool );
	void showNew( void );
	string showNewName( void );
    string getOpen( const char *, const char *, const char * );
    string getSave( const char *, const char *, const char * );
    string getFolder( const char * title );
	bool isOpen( int );
};

#endif
