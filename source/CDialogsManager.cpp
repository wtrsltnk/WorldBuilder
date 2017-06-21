#include "CDialogsManager.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CDialogsManager::CDialogsManager( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager )
{
	this->m_hInstance = hInstance;
	this->m_hOwner = hOwner;
	this->m_pGroupManager = pGroupManager;

	m_pGroupDlg = new CGroupDlg( m_hInstance, m_hOwner, this->m_pGroupManager );
	m_pToolDlg = new CToolDlg( m_hInstance, m_hOwner, this->m_pGroupManager );
	m_pCommandDlg = new CCommandDlg( m_hInstance, m_hOwner, this->m_pGroupManager );

	m_pNewDlg = new CNewDlg( m_hInstance, m_hOwner );
	m_pCommonDlg = new CCommonDialogs( m_hInstance, m_hOwner );
	m_pNewNameDlg = new CNewNameDlg( m_hInstance, m_hOwner );
}

CDialogsManager::~CDialogsManager( void )
{
	delete m_pGroupDlg;
	delete m_pToolDlg;
	delete m_pCommandDlg;

	delete m_pNewDlg;
	delete m_pCommonDlg;
	delete m_pNewNameDlg;
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

void CDialogsManager::setPointer( CGroupManager *pGroupManager )
{
	this->m_pGroupManager = pGroupManager;
}

void CDialogsManager::showGroup( string gr, bool nieuw )
{
	m_pGroupDlg->show( gr, nieuw );
}

void CDialogsManager::showTool( string gr, string tl, bool nieuw )
{
	m_pToolDlg->show( gr, tl, nieuw );
}

void CDialogsManager::showCommand( string gr, string tl, string cmd, bool nieuw )
{
	m_pCommandDlg->show( gr, tl, cmd, nieuw );
}

void CDialogsManager::showGameCommand( string gr, string cmd, bool nieuw )
{
	m_pCommandDlg->show( gr, "", cmd, nieuw );
}

void CDialogsManager::showNew( void )
{
	m_pNewDlg->show();
}

string CDialogsManager::showNewName( void )
{
	return m_pNewNameDlg->show();
}

bool CDialogsManager::isOpen( int type )
{
	switch ( type )
	{
	case 0:
		return m_pGroupDlg->isDlg();
		break;
	case 1:
		return m_pToolDlg->isDlg();
		break;
	case 2:
		return m_pCommandDlg->isDlg();
		break;
	default:
		return false;
		break;
	}
}

string CDialogsManager::getOpen( const char * title, const char *szFilter, const char *szDefExt )
{
	return m_pCommonDlg->open( title, szFilter, szDefExt );
}

string CDialogsManager::getSave( const char * title, const char *szFilter, const char *szDefExt )
{
	return m_pCommonDlg->save( title, szFilter, szDefExt );
}

string CDialogsManager::getFolder( const char * title )
{
	return m_pCommonDlg->folder( title );
}
