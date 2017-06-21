#include "CMainFrame.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CMainFrame::CMainFrame()
{
	GetAppPath( GetCommandLine(), m_pAppPath );
	_getcwd( this->appPath, MAX_PATH );

	this->m_strDataname		 = this->appPath;
	this->m_strBatchname	 = this->appPath;

	strcat( const_cast <char*>(this->m_strDataname.c_str()), "\\groups.xml" );
	strcat( const_cast <char*>(this->m_strBatchname.c_str()), "\\wb.bat" );


	this->m_dwCreationFlags  = 0L;
	this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW;
	this->m_dwExWindowStyle	 = WS_EX_WINDOWEDGE;
	this->m_dwCreationFlags  = SW_SHOW;
	this->m_PosX			 = CW_USEDEFAULT;	
	this->m_PosY			 = CW_USEDEFAULT;	
	this->m_dwCreationWidth  = CW_USEDEFAULT;
	this->m_dwCreationHeight = CW_USEDEFAULT;
	this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW);
	this->m_hIcon			 = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_WRENCH));
	this->m_strWindowTitle	 = "WorldBuilder";
	this->m_hMenu			 = LoadMenu(m_hInstance, MAKEINTRESOURCE(IDR_MENU));
	this->m_bChange			 = false;
}


CMainFrame::~CMainFrame()
{
	delete m_pControlsManager;
	m_pControlsManager = NULL;
	delete m_pDialogsManager;
	m_pDialogsManager = NULL;
	delete m_pGroupManager;
	m_pGroupManager = NULL;
	delete m_pCompileManager;
	m_pCompileManager = NULL;
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

LRESULT CMainFrame::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMTVKEYDOWN info;
	RECT Rect;
	char szBuffer[ 255 ];
	bool nieuw = false;
	UINT uResult;
	string result;
	string newgroup;
	string newtool;
	strstream strs;

	CGroup *gr;
	CTool *tl;
	CCommand *cmd;

	switch ( uMsg )
	{


// CREATE MESSAGE
	case WM_CREATE:
		m_pGroupManager = new CGroupManager();
		m_pDialogsManager = new CDialogsManager( m_hInstance, m_hWnd, m_pGroupManager );
		m_pControlsManager = new CControlsManager( m_hInstance, m_hWnd, m_pGroupManager, m_nWidth, m_nHeight );
		m_pCompileManager = new CCompileManager( m_hInstance, m_hWnd );

		SetTimer( m_hWnd, ID_TIME, 55, NULL );
		break;



// DESTROY MESSAGE
	case WM_DESTROY:
		break;



// CLOSE MESSAGE
	case WM_CLOSE:
		if ( this->m_bChange )
		{
			LoadString( m_hInstance, IDS_QUIT_SAVE, szBuffer, 255 );
			uResult = msgConfirm( szBuffer, m_hWnd );
			switch ( uResult )
			{
			case IDYES:
				result = m_pDialogsManager->getSave( "Save GroupManager file...", "XML Files\0*.xml\0", "xml" );
				if ( strcmp(result.c_str(), "") != 0 )
				{
					try
					{
						m_pGroupManager->save( result );
						this->m_bChange = false;
					}
					catch ( char *error )
					{
						msgError( error, m_hWnd );
					}
				}
				else
					return FALSE;
			case IDNO:
				break;
			case IDCANCEL:
				return FALSE;
			}
		}
		break;



// SIZE MESSAGE
	case WM_SIZE:
		m_pControlsManager->resize( wParam, lParam );
		GetWindowRect( m_hWnd, &Rect );
		this->m_nX = Rect.left;
		this->m_nY = Rect.top;
		this->m_nWidth = Rect.right - Rect.left;
		this->m_nHeight = Rect.bottom - Rect.top;
		break;



// COMMAND MESSAGE
	case WM_COMMAND:
		switch ( LOWORD(wParam) )
		{

	// LOAD FILE
		case IDM_FILE_LOAD:
			result = m_pDialogsManager->getOpen( "Open GroupManager file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				delete m_pGroupManager;
				m_pGroupManager = new CGroupManager();
				m_pControlsManager->setPointer( m_pGroupManager );
				m_pDialogsManager->setPointer( m_pGroupManager );
				try
				{
					m_pGroupManager->load( result );
					this->m_bChange = false;
				}
				catch( char *error )
				{
					msgError( error, m_hWnd );
				}
				m_pControlsManager->updateTreeView();
				m_pControlsManager->TVSelectionChanged();
			}
			break;



	// SAVE FILE
		case IDM_FILE_SAVE:
			result = m_pDialogsManager->getSave( "Save GroupManager file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				try
				{
					m_pGroupManager->save( result );
					this->m_bChange = false;
				}
				catch ( char *error )
				{
					msgError( error, m_hWnd );
				}
			}
			break;



	// CLOSE FILE
		case IDM_FILE_CLOSE:
			if ( this->m_bChange )
			{
				LoadString( m_hInstance, IDS_QUIT_SAVE, szBuffer, 255 );
				uResult = msgConfirm( szBuffer, m_hWnd );
				switch ( uResult )
				{
				case IDYES:
					try
					{
						m_pGroupManager->save( "groups.xml" );
						this->m_bChange = false;
					}
					catch ( char *error )
					{
						msgError( error, m_hWnd );
						break;
					}
				case IDNO:
					if ( m_pGroupManager != NULL )
					{
						delete m_pGroupManager;
						m_pGroupManager = NULL;
						this->m_bChange = false;
					}
					m_pControlsManager->updateTreeView();
					m_pControlsManager->TVSelectionChanged();
					break;
				case IDCANCEL:
					break;
				}
			}
			else
			{
				if ( m_pGroupManager != NULL )
				{
					delete m_pGroupManager;
					m_pGroupManager = NULL;
					this->m_bChange = false;
				}
				m_pControlsManager->updateTreeView();
				m_pControlsManager->TVSelectionChanged();
			}
			break;



	// IMPORT DEFAULT HALF-LIFE GROUP
		case IDM_FILE_IMPORT_DEFHL:
			gr = new CGroup();
			try
			{
				gr->load( "defaults\\half-life.xml" );
			}
			catch ( char *error )
			{
				msgError( error, m_hWnd );
				break;
			}
			result = m_pDialogsManager->showNewName();
			if ( strcmp( result.c_str(), "" ) != 0 )
			{
				gr->setName( result );
				m_pGroupManager->addGroup( gr );
				m_pControlsManager->updateTreeView();
				m_pControlsManager->TVSelectionChanged();
			}
			break;



	// IMPORT GROUP
		case IDM_FILE_IMPORT_GROUP:
			result = m_pDialogsManager->getOpen( "Open Group file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				gr = new CGroup();
				try
				{
					gr->load( result );
					this->m_bChange = true;
				}
				catch( char *error )
				{
					msgError( error, m_hWnd );
				}
				result = m_pDialogsManager->showNewName();
				if ( strcmp( result.c_str(), "" ) )
				{
					gr->setName( result );
					m_pGroupManager->addGroup( gr );
					m_pControlsManager->updateTreeView();
					m_pControlsManager->TVSelectionChanged();
				}
			}
			break;



	// IMPORT TOOL
		case IDM_FILE_IMPORT_TOOL:
			result = m_pDialogsManager->getOpen( "Open Tool file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				if ( 
					strcmp( m_pControlsManager->getTVGroup().c_str(), "")
					)
				{
					tl = new CTool();
					try
					{
						tl->load( result );
						this->m_bChange = true;
					}
					catch( char *error )
					{
						msgError( error, m_hWnd );
					}
					result = m_pDialogsManager->showNewName();
					if ( strcmp( result.c_str(), "" ) )
					{
						m_pGroupManager->addGrTool( m_pControlsManager->getTVGroup(), tl );
						m_pControlsManager->updateTreeView();
						m_pControlsManager->TVSelectionChanged();
					}
				}
				else
				{
					LoadString( m_hInstance, IDS_NOTOOLLOAD, szBuffer, 255 );
					msgError( szBuffer, m_hWnd );
				}
			}
			break;



	// IMPORT COMMAND
		case IDM_FILE_IMPORT_COMMAND:
			result = m_pDialogsManager->getOpen( "Open Command file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				if ( 
					strcmp( m_pControlsManager->getTVGroup().c_str(), "") &&
					strcmp( m_pControlsManager->getTVTool().c_str(), "")
					)
				{
					cmd = new CCommand();
					try
					{
						cmd->load( result );
						this->m_bChange = true;
					}
					catch( char *error )
					{
						msgError( error, m_hWnd );
					}
					result = m_pDialogsManager->showNewName();
					if ( strcmp( result.c_str(), "" ) )
					{
						m_pGroupManager->addTlCommand( m_pControlsManager->getTVGroup(), m_pControlsManager->getTVTool(), cmd );
						m_pControlsManager->updateTreeView();
						m_pControlsManager->TVSelectionChanged();
					}
				}
				else
				{
					LoadString( m_hInstance, IDS_NOCOMMANDLOAD, szBuffer, 255 );
					msgError( szBuffer, m_hWnd );
				}
			}
			break;



	// EXPORT GROUP
		case IDM_FILE_EXPORT_GROUP:
			result = m_pDialogsManager->getSave( "Save Group file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				if ( strcmp(m_pControlsManager->getTVGroup().c_str(), "") != 0 )
				{
					m_pGroupManager->getGroup( 
						m_pControlsManager->getTVGroup() )
						->save( result );
				}
				else
				{
					LoadString( m_hInstance, IDS_NOGROUPSAVE, szBuffer, 255 );
					msgError( szBuffer, m_hWnd );
				}
			}
			break;



	// EXPORT TOOL
		case IDM_FILE_EXPORT_TOOL:
			result = m_pDialogsManager->getSave( "Save Tool file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				if (
					( strcmp(m_pControlsManager->getTVGroup().c_str(), "") != 0 ) &&
					( strcmp(m_pControlsManager->getTVTool().c_str(), "") != 0 ) 
					)
				{
					m_pGroupManager->getGrTool( 
						m_pControlsManager->getTVGroup(), 
						m_pControlsManager->getTVTool() )
						->save( result );
				}
				else
				{
					LoadString( m_hInstance, IDS_NOTOOLSAVE, szBuffer, 255 );
					msgError( szBuffer, m_hWnd );
				}
			}
			break;



	// EXPORT COMMAND
		case IDM_FILE_EXPORT_COMMAND:
			result = m_pDialogsManager->getSave( "Save Command file...", "XML Files\0*.xml\0", "xml" );
			if ( strcmp(result.c_str(), "") != 0 )
			{
				if (
					( strcmp(m_pControlsManager->getTVGroup().c_str(), "") != 0 ) &&
					( strcmp(m_pControlsManager->getTVTool().c_str(), "") != 0 ) &&
					( strcmp(m_pControlsManager->getTVCommand().c_str(), "") != 0 ) 
					)
				{
					m_pGroupManager->getTlCommand( 
						m_pControlsManager->getTVGroup(), 
						m_pControlsManager->getTVTool(), 
						m_pControlsManager->getTVCommand() )
						->save( result );
				}
				else
				{
					LoadString( m_hInstance, IDS_NOCOMMANDSAVE, szBuffer, 255 );
					msgError( szBuffer, m_hWnd );
				}
			}
			break;



	// EXIT PROGRAM
		case IDM_FILE_EXIT:
			SendMessage( m_hWnd, WM_CLOSE, 0, 0 );
			break;



	// BUILD MAP
		case IDM_BUILD_MAP:
			if ( strcmp( m_pControlsManager->getTVGroup().c_str(), "" ) != 0 )
			{
				m_pCompileManager->buildBatch( this->m_strBatchname, m_pGroupManager->getGroup( m_pControlsManager->getTVGroup() ) );
				m_pCompileManager->startBatch( this->m_strBatchname );
			}
			else
			{
				LoadString( m_hInstance, IDS_NOGROUPSEL, szBuffer, 255 );
				msgError( szBuffer, m_hWnd );
			}
			break;



	// BUILD BATCH FILE
		case IDM_BUILD_BATCH:
			if ( strcmp( m_pControlsManager->getTVGroup().c_str(), "" ) != 0 )
			{
				if ( m_pCompileManager->buildBatch( this->m_strBatchname, m_pGroupManager->getGroup( m_pControlsManager->getTVGroup() ) ))
				{
					LoadString( m_hInstance, IDS_BATCHCREATED, szBuffer, 255 );
					msgNotify( szBuffer, hWnd );
				}
			}
			else
			{
				LoadString( m_hInstance, IDS_NOGROUPSEL, szBuffer, 255 );
				msgError( szBuffer, m_hWnd );
			}
			break;



	// START GAME
		case IDM_BUILD_STARTGAME:
			if ( strcmp( m_pControlsManager->getTVGroup().c_str(), "" ) != 0 )
			{
				m_pCompileManager->startGame( m_pGroupManager->getGroup( m_pControlsManager->getTVGroup() ) );
			}
			else
			{
				LoadString( m_hInstance, IDS_NOGROUPSEL, szBuffer, 255 );
				msgError( szBuffer, m_hWnd );
			}
			break;



	// NEW GROUP/TOOL/COMMAND
		case IDM_EDIT_NEW:
			if ( m_pControlsManager->getTVSelectedType() >= 0 )
				m_pDialogsManager->showNew();
			else
				SendMessage( hWnd, WM_NEW_ITEM, (WPARAM)NEW_TYPE_GR, 0 );
			break;



	// EDIT SELECTED GROUP/TOOL/COMMAND
		case IDM_EDIT_EDIT:
			switch ( m_pControlsManager->getTVSelectedType() )
			{
			case 0:
				m_pDialogsManager->showGroup( const_cast <char*>(m_pControlsManager->getTVGroup().c_str())
					, false );
				break;
			case 1:
				m_pDialogsManager->showTool( const_cast <char*>(m_pControlsManager->getTVGroup().c_str()),
					const_cast <char*>(m_pControlsManager->getTVTool().c_str())
					, false );
				break;
			case 2:
				m_pDialogsManager->showCommand( const_cast <char*>(m_pControlsManager->getTVGroup().c_str()),
					const_cast <char*>(m_pControlsManager->getTVTool().c_str()),
					const_cast <char*>(m_pControlsManager->getTVCommand().c_str()), false );
				break;
			case 3:
				break;
			}
			break;



	// DELETE SELECTED GROUP/TOOL/COMMAND
		case IDM_EDIT_DEL:
			LoadString( m_hInstance, IDS_CONFIRM, szBuffer, 255 );
			if ( msgConfirm( szBuffer, m_hWnd ) )
			{
				switch ( m_pControlsManager->getTVSelectedType() )
				{
				case 0:
					m_pGroupManager
						->remGroup( m_pControlsManager->getTVGroup() );
					break;
				case 1:
					m_pGroupManager
						->getGroup( m_pControlsManager->getTVGroup() )
						->remTool( m_pControlsManager->getTVTool() );
					break;
				case 2:
					m_pGroupManager
						->getGrTool( m_pControlsManager ->getTVGroup(), m_pControlsManager->getTVTool() )
						->remCommand( m_pControlsManager->getTVCommand() );
					break;
				case 3:
					m_pGroupManager
						->getGroup( m_pControlsManager->getTVGroup() )
						->remGameCommand( m_pControlsManager->getRVSelectedItem() );
					break;
				}
			m_pControlsManager->updateTreeView();
			m_pControlsManager->TVSelectionChanged();
			this->m_bChange = true;
			}
			break;



	// OPEN HELP FILE
		case IDM_HELP_INDEX:
			
			break;



	// OPEN ABOUT BOX
		case IDM_HELP_ABOUT:
			DialogBox( m_hInstance, MAKEINTRESOURCE(IDD_ABOUT), m_hWnd, (DLGPROC)AboutProc );
			break;
		}
		break;



// NOTIFY MESSAGE 
	case WM_NOTIFY:
		switch ( ((LPNMHDR)lParam)->idFrom )
		{

			
	// TREEVIEW
		case IDC_TREEVIEW:
			switch ( ((LPNMHDR)lParam)->code )
			{
			case TVN_SELCHANGED:
				m_pControlsManager->TVSelectionChanged();
				m_pControlsManager->setTVinST();
				break;
			case TVN_KEYDOWN:
				info = ((LPNMTVKEYDOWN)lParam);
				if ( info->wVKey == VK_F2 )
				{
					SendMessage( m_hWnd, WM_COMMAND, LOWORD(IDM_EDIT_EDIT), 0 );
				}
				else if ( info->wVKey == VK_DELETE )
				{
					SendMessage( m_hWnd, WM_COMMAND, LOWORD(IDM_EDIT_DEL), 0 );
				}
				break;
			}
			break;



	// REPORTVIEW
		case IDC_REPORTVIEW:
			switch ( ((LPNMHDR)lParam)->code )
			{
			case LVN_ITEMACTIVATE:
				switch ( m_pControlsManager->getTVSelectedType() )
				{
				case 0:
					if  ( 
						m_pControlsManager->getRVSelectedIndex() 
						>=
						m_pGroupManager->getGroup( m_pControlsManager->getTVGroup() )->getToolCount()
						)
					{
						m_pDialogsManager->showGameCommand( const_cast <char*>(m_pControlsManager->getTVGroup().c_str()), const_cast <char*>(m_pControlsManager->getRVSelectedItem().c_str()), false );
					}
					else
					{
						m_pDialogsManager->showTool( const_cast <char*>(m_pControlsManager->getTVGroup().c_str()), const_cast <char*>(m_pControlsManager->getRVSelectedItem().c_str()), false );
					}
					break;
				case 1:
					m_pDialogsManager->showCommand( const_cast <char*>(m_pControlsManager->getTVGroup().c_str()), const_cast <char*>(m_pControlsManager->getTVTool().c_str()), const_cast <char*>(m_pControlsManager->getRVSelectedItem().c_str()), false );
					break;
				}
				break;




			case LVN_KEYDOWN:
				info = ((LPNMTVKEYDOWN)lParam);
				if ( info->wVKey == VK_DELETE )
				{
					LoadString( m_hInstance, IDS_CONFIRM, szBuffer, 255 );
					if ( msgConfirm( szBuffer, m_hWnd ) )
					{
						if ( 
							m_pControlsManager->getRVSelectedIndex() 
							>=
							m_pGroupManager->getGroup( m_pControlsManager->getTVGroup() )->getToolCount()
							)
						{
							m_pGroupManager
								->getGroup( m_pControlsManager->getTVGroup() )
								->remGameCommand( m_pControlsManager->getRVSelectedItem() );
						}
						else
						{
							m_pGroupManager
								->getGroup( m_pControlsManager->getTVGroup() )
								->remTool(  m_pControlsManager->getRVSelectedItem() );
						}
					}
					m_pControlsManager->updateTreeView();
				m_pControlsManager->TVSelectionChanged();
				}
				break;
			}
			break;
		}
		return FALSE;



// UPDATE MESSAGE
	case WM_UPDATE:
		m_pControlsManager->updateTreeView();
		m_pControlsManager->TVSelectionChanged();
		this->m_bChange = true;
		break;



// NEWITEM MESSAGE
	case WM_NEW_ITEM:
		newgroup = m_pControlsManager->getTVGroup();
		newtool = m_pControlsManager->getTVTool();
		switch ( wParam )
		{
		case NEW_TYPE_GR:
			m_pDialogsManager->showGroup( "", true );
			break;
		case NEW_TYPE_TL:
			m_pDialogsManager->showTool( newgroup, "", true );
			break;
		case NEW_TYPE_CMD:
			switch ( m_pControlsManager->getTVSelectedType() )
			{
			case 0:
				m_pDialogsManager->showGameCommand( newgroup, "", true );
				break;
			case 1:
			case 2:
				m_pDialogsManager->showCommand( newgroup, newtool, "", true );
				break;
			}
			break;
		}
		break;



// DLGERROR MESSAGE
	case WM_DLGERROR:
		switch ( wParam )
		{
		case 1:
			LoadString( m_hInstance, IDS_DLG_NONAME, szBuffer, 255 );
			msgError( szBuffer, m_hWnd );
			break;
		}
		break;



// TIMER MESSAGE
	case WM_TIMER:
		switch ( wParam )
		{
		case ID_TIME:
			m_pControlsManager->timeChanged();
			break;
		}
		break;
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CMainFrame::AboutProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg )
	{
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
  		case IDCLOSE:
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog( hDlg, IDCANCEL );
		break;
	}
	return FALSE;
}

char *CMainFrame::GetParameters( char *cmdline )
{
	char *result;
	int cmdlen;

	cmdlen = strlen(cmdline);

	if ( cmdline[cmdlen-1] == '\"' )
	{
		for ( int i = cmdlen-2; i >= 0; i-- )
		{
			if ( cmdline[i] == '\"' )
			{
				if ( i == 0 )
					return NULL;
				result = new char[cmdlen-i-2];
                int j;
                for ( j = 1; j < cmdlen - i - 1; j++ )
				{
					result[j-1] = cmdline[j+i];
				}
				result[j-1] = '\0';
				return result;
			}
		}
	}
	return NULL;
}

void CMainFrame::GetAppPath( char *cmdline, char *dest )
{
	int cmdlen;
	int i, j, k;

	cmdlen = strlen(cmdline);

	if ( cmdline[0] == '\"' )
	{
		for ( i = 1; i < cmdlen; i++ )
		{
			if ( cmdline[i] == '\"' )
			{
				for ( j = 0; j < i; j++ )
				{
					dest[j] = cmdline[j+1];
				}
				for ( k = j; k > 0; k-- )
				{
					if ( dest[k] == '\\' )
					{
						dest[k] = '\0';
						return;
					}
				}
			}
		}
	}
}
