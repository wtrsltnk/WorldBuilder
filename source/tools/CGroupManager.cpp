#include "CGroupManager.h"
#include "XMLParser.h"


////////////////////////////////////////////////////////
//CONSTRUCTOR / DESCRUCTOR
////////////////////////////////////////////////////////
CGroupManager::CGroupManager( void )
{
	this->filename = "";
}

CGroupManager::~CGroupManager( void )
{
}

////////////////////////////////////////////////////////
//Savefunctions
////////////////////////////////////////////////////////
bool CGroupManager::load( string filename ) throw()
{
	CXMLParser xml;
	CGroup *gr;
	
	this->filename = filename;

	try
	{
		xml.SetXmlFile( const_cast <char *> (filename.c_str()) );
	}
	catch ( char * error )
	{
		throw( error );
		return false;
	}

	xml.GetNextElement();
	xml.GetNextElement();
	xml.GetNextElement();

	if ( strcmp( xml.GetElementName(), "<WorldBuilder>" ) != 0 )
	{
		throw( "Wrong File" );
		return false;
	}

	xml.GetNextElement();
	while ( stricmp( xml.GetElementName(), "</WorldBuilder>" ) != 0 )
	{
		gr = new CGroup();
		gr->load( &xml );
		this->addGroup( gr );
		xml.GetNextElement();
	}
	return true;
}

bool CGroupManager::save( void ) throw()
{
	int i;
	ofstream output;



// CONTROLE
	if ( groups.empty() )
	{
		throw( "No groups to save !\n" );
		return false;
	}

	if ( stricmp(filename.c_str(), "") == 0 )
	{
		throw( "No file name specified !\n" );
		return false;
	}

	output.open((const char *)filename.c_str());
	if (output.fail())
	{
		throw( "Couldn't open this file\n" );
		return false;
	}



// SCHRIJVEN
	output << "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
		<< "<!-- WorldBuilder Data Storage File -->\n";

	output << "<WorldBuilder>\n";

	for ( i = 0; i < this->getGroupCount(); i++ )
		this->getGroup( i )->save( output, 1 );

	output << "</WorldBuilder>\n";




	output.close();
	return true;
}

bool CGroupManager::save( string filename ) throw()
{
	bool result;
	try
	{
		this->filename = filename;
		result = save();
	}
	catch( char *error )
	{
		throw( error );
		return false;
	}
	return result;
}

////////////////////////////////////////////////////////
//Manager Functions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CGroupManager::addGroup( CGroup *group )
{
	if ( group != NULL )
		groups.push_back( *group );
	else
		return false;
	return true;
}

bool CGroupManager::remGroup( string name )
{
	if ( !groups.empty() )
	{
		for ( int i = 0; i < groups.size(); i++ )
			if ( strcmp( const_cast <char *> (groups[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				groups.erase( groups.begin() + i );
				return true;
			}
	}
	return false;
}

CGroup *CGroupManager::getGroup( string name )
{
	if ( !groups.empty() )
	{
		for ( int i = 0; i < groups.size(); i++ )
		{
			if ( strcmp( const_cast <char *> (groups[ i ].getName().c_str()), const_cast <char *> (name.c_str()) ) == 0 )
			{
				return &groups[ i ];
			}
		}
	}
	return NULL;
}

CGroup *CGroupManager::getGroup( int index )
{
	if ( !groups.empty()  )
	{
		return &groups[ index ];
	}
	return NULL;
}

int CGroupManager::getGroupCount( void )
{
	return groups.size();
}

////////////////////////////////////////////////////////
//Group Functions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CGroupManager::addGrGameCommand( string grName, CCommand *cmd )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->addGameCommand( cmd );
	return false;
}

bool CGroupManager::remGrGameCommand( string grName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->remGameCommand( name );
	return false;
}

CCommand *CGroupManager::getGrGameCommand( string grName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getGameCommand( name );
	return NULL;
}

int CGroupManager::getGrGameCmdCount( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getGameCmdCount();
	return 0;
}

bool CGroupManager::addGrTool( string grName, CTool *tool )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->addTool( tool );
	return false;
}

bool CGroupManager::remGrTool( string grName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->remTool( name );
	return false;
}

CTool *CGroupManager::getGrTool( string grName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getTool( name );
	return NULL;
}

int CGroupManager::getGrToolCount( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getToolCount();
	return 0;
}

//////////////////////
//GET/SET Functions
//////////////////////
string CGroupManager::getGrName( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getName();
	return "No Name:";
}

void CGroupManager::setGrName( string grName, string name )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setName( name );
}

string CGroupManager::getGrBaseDir( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getBaseDir();
	return "No Base Dir:";
}

void CGroupManager::setGrBaseDir( string grName, string basedir )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setBaseDir( basedir );
}

string CGroupManager::getGrMapName( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getMapName();
	return "No Map Name:";
}

void CGroupManager::setGrMapName( string grName, string mapname )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setMapName( mapname );
}

string CGroupManager::getGrDescription( string grName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getDescription();
	return "No Description:";
}
	
void CGroupManager::setGrDescription( string grName, string description )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setDescription( description );
}

string CGroupManager::getGrGameName( string grName )
{
	
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getGameName();
	return "No Game Name:";
}
	
void CGroupManager::setGrGameName( string grName, string gamename )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setGameName( gamename );
}

string CGroupManager::getGrGameDir( string grName )
{
	
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getGameDir();
	return "No Game Dir:";
}
	
void CGroupManager::setGrGameDir( string grName, string gamedir )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setGameDir( gamedir );
}

bool CGroupManager::isGrGameRun( string grName )
{
	
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->isGameRun();
	return false;
}

void CGroupManager::setGrGameRun( string grName, bool run )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setGameRun( run );
}



////////////////////////////////////////////////////////
//Tool Functions
////////////////////////////////////////////////////////

//////////////////////
//VECTOR Functions
//////////////////////
bool CGroupManager::addTlCommand( string grName, string tlName, CCommand *cmd )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->addTlCommand( tlName, cmd );
	return false;
}

bool CGroupManager::remTlCommand( string grName, string tlName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->remTlCommand( tlName, name );
	return false;
}

CCommand *CGroupManager::getTlCommand( string grName, string tlName, string name )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getTlCommand( tlName, name );
	return NULL;
}

int CGroupManager::getTlCmdCount( string grName, string tlName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getTlCmdCount( tlName );
	return 0;
}

//////////////////////
//GET/SET Functions
//////////////////////
string CGroupManager::getTlName( string grName, string tlName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getTlName( tlName );
	return "No Name:";
}

void CGroupManager::setTlName( string grName, string tlName, string name )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setTlName( tlName, name );
}

string CGroupManager::getTlDescription( string grName, string tlName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getTlDescription( tlName );
	return "NoDescription:";
}
	
void CGroupManager::setTlDescription( string grName, string tlName, string description )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setTlDescription( tlName, description );
}

bool CGroupManager::isTlRun( string grName, string tlName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->isTlRun( tlName );
	return false;
}

void CGroupManager::setTlRun( string grName, string tlName, bool run )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setTlRun( tlName, run );
}


////////////////////////////////////////////////////////
//Command Functions
////////////////////////////////////////////////////////

//////////////////////
//GET/SET Functions
//////////////////////
string CGroupManager::getCmdDescription( string grName, string tlName, string cmdName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getCmdDescription( tlName, cmdName );
	return "No Description:";
}

void CGroupManager::setCmdDescription( string grName, string tlName, string cmdName, string description )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setCmdDescription( tlName, cmdName, description );
}

string CGroupManager::getCmdCall( string grName, string tlName, string cmdName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getCmdCall( tlName, cmdName );
	return "No Call:";
}

void CGroupManager::setCmdCall( string grName, string tlName, string cmdName, string call )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setCmdCall( tlName, cmdName, call );
}

string CGroupManager::getCmdValue( string grName, string tlName, string cmdName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getCmdValue( tlName, cmdName );
	return "No Value:";
}

void CGroupManager::setCmdValue( string grName, string tlName, string cmdName, string value )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setCmdValue( tlName, cmdName, value );
}


int CGroupManager::getCmdType( string grName, string tlName, string cmdName )
{
	if ( getGroup( grName ) != NULL )
		return getGroup( grName )->getCmdType( tlName, cmdName );
	return -1;
}

void CGroupManager::setCmdType( string grName, string tlName, string cmdName, int type )
{
	if ( getGroup( grName ) != NULL )
		getGroup( grName )->setCmdType( tlName, cmdName, type );
}