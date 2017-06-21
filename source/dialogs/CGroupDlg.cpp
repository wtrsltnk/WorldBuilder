#include "CGroupDlg.h"

bool CGroupDlg::nieuw = true;
string CGroupDlg::m_sgr;
CGroup *CGroupDlg::m_gr = NULL;
CCommonDialogs *CGroupDlg::m_pCommonDlg = NULL;
CGroupManager *CGroupDlg::m_pGroupManager = NULL;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CGroupDlg::CGroupDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager )
{
	this->m_hOwner		= hOwner;
	this->m_hInstance	= hInstance;
	this->m_pGroupManager = pGroupManager;

	m_hWnd = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_GROUP ), m_hOwner, (DLGPROC)DlgProc );
	m_pCommonDlg = new CCommonDialogs( this->m_hInstance, this->m_hOwner);
}

CGroupDlg::~CGroupDlg( void )
{
	DestroyWindow( m_hWnd );
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CGroupDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    const char *result;
	switch(uMsg)
	{
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
  		case IDOK:
			if ( nieuw )
			{
				savedata( hDlg );
				m_pGroupManager->addGroup( m_gr );
			}
			else
			{
				savedata( hDlg );
			}
			SendMessage( GetParent( hDlg ), WM_UPDATE, 0, 0 );
  		case IDCANCEL:
			EndDialog( hDlg, IDCANCEL );
			break;
		case IDC_BUTTON_MAP:
			result = m_pCommonDlg->open( "Open Map file...", "Map Files\0*.map\0", "map" );
			if ( result != NULL )
			{
				SetDlgItemText( hDlg, IDC_EDIT_MAP, result );
			}
			break;
		case IDC_BUTTON_BASEDIR:
			result = m_pCommonDlg->folder( "Select the Base Directory" );
			if ( result != NULL )
			{
				SetDlgItemText( hDlg, IDC_EDIT_BASEDIR, result );
			}
			break;
		case IDC_BUTTON_GAMEDIR:
			result = m_pCommonDlg->open( "Open Game executable...", "Programs\0*.exe\0", "exe" );
			if ( result != NULL )
			{
				SetDlgItemText( hDlg, IDC_EDIT_GAMEDIR, result );
			}
			break;
		}
		break;
	}
	return FALSE;
}

void CGroupDlg::show( string group, bool nieuw )
{
	this->m_sgr = group;
	this->nieuw = nieuw;

	ShowWindow( m_hWnd, SW_SHOWNORMAL );
	SendMessage( GetDlgItem( m_hWnd, IDC_EDIT_NAME ), EM_SETREADONLY, !nieuw, 0 );

	clearData();
	if ( nieuw )
	{
		m_gr = new CGroup();
	}
	else
	{
		m_gr = m_pGroupManager->getGroup( group );
		showdata();
	}
}

void CGroupDlg::clearData( void )
{
	SetDlgItemText( m_hWnd, IDC_EDIT_NAME, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_MAP, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_BASEDIR, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_GAMENAME, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_GAMEDIR, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_WADDRIVE, "" );
}

void CGroupDlg::showdata( void )
{

	if ( m_gr != NULL )
	{
		SetDlgItemText( m_hWnd, IDC_EDIT_NAME, m_gr->getName().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, m_gr->getDescription().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_MAP, m_gr->getMapName().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_BASEDIR, m_gr->getBaseDir().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_GAMENAME, m_gr->getGameName().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_GAMEDIR, m_gr->getGameDir().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_WADDRIVE, m_gr->getWadDrive().c_str() );

		if ( m_gr->isGameRun() )
		{
			SendMessage( GetDlgItem( m_hWnd, IDC_CHECK_RUNGAME ), BM_SETCHECK, BST_CHECKED, 0 );
		}
		else
		{
			SendMessage( GetDlgItem( m_hWnd, IDC_CHECK_RUNGAME ), BM_SETCHECK, BST_UNCHECKED, 0 );
		}
	}
}

void CGroupDlg::savedata( HWND hDlg )
{
	char szBuff[255];

	if ( m_gr != NULL )
	{
		GetDlgItemText( hDlg, IDC_EDIT_NAME, szBuff, 255 );
		m_gr->setName( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_DESCRIPTION, szBuff, 255 );
		m_gr->setDescription( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_MAP, szBuff, 255 );
		m_gr->setMapName( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_BASEDIR, szBuff, 255 );
		m_gr->setBaseDir( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_GAMENAME, szBuff, 255 );
		m_gr->setGameName( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_GAMEDIR, szBuff, 255 );
		m_gr->setGameDir( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_WADDRIVE, szBuff, 255 );
		m_gr->setWadDrive( szBuff );

		m_gr->setGameRun( SendMessage( GetDlgItem( hDlg, IDC_CHECK_RUNGAME ), BM_GETCHECK, 0, 0 ) == BST_CHECKED );

	}
}

bool CGroupDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}

