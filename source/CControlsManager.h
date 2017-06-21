#ifndef CCONTROLSMANAGER_H
#define CCONTROLSMANAGER_H

#include <windows.h>
#include "..\resource\resource.h"
#include "controls\GUI.h"
#include "tools\CGroupManager.h"
#include <strstream>
#include <time.h>
using namespace std;

class CControlsManager
{
private:
	HINSTANCE				m_hInstance;
	HWND					m_hParent;
	CToolBar				*m_pToolBar;
	CStatusBar				*m_pStatusBar;
	CTreeView				*m_pTreeView;
	CReportView				*m_pReportView;
	CLabel					*m_pLabel;
	CGroupManager			*m_pGroupManager;
	int						nType, nRVType;
public:
	CControlsManager( HINSTANCE, HWND, CGroupManager *, int, int );
	~CControlsManager( void );

	void resize( WPARAM, LPARAM );
	void setPointer( CGroupManager *pGroupManager );

	void updateTreeView( void );
	void SelectGroup( string );
	void SelectTool( string, string );
	void SelectCommand( string, string, string );
	void TVSelectionChanged( void );
	void RVSelectionChanged( void );
	int getTVSelectedType( void );

	string getTVSelectedItem( void );
	string getRVSelectedItem( void );
	int getRVSelectedIndex( void );

	void timeChanged( void );
	void setTVinST( void );

	string getTVGroup( void );
	string getTVTool( void );
	string getTVCommand( void );
	HTREEITEM addItem( string, HTREEITEM, int );
};

#endif
