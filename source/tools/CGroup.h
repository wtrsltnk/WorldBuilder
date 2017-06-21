#ifndef CGROUP_H
#define CGROUP_H

#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
#include	"CCommand.h"
#include	"CTool.h"
#include	"xmlparser.h"
#include "..\funclib.h"

class CGroup
{
private:
	string				grName;
	string				grBaseDir;
	string				grMapName;
	string				grDescription;
	string				grGameName;
	string				grGameDir;
	string				grWadDrive;
	vector <CCommand>	gameCommands;
	int					cmdCount;
	bool				grGameRun;
	vector <CTool>		tools;
	int					toolCount;

public:
	CGroup( string );				//name
	CGroup( void );
	~CGroup( void );

	////////////////////////////////////////////////////////
	//Savefunctions
	////////////////////////////////////////////////////////
    bool save( string );
    bool save( ofstream &, int );
    bool load( string );
    bool load( CXMLParser * );

	////////////////////////////////////////////////////////
	//Group Functions
	////////////////////////////////////////////////////////
	bool addGameCommand( CCommand * );
	bool remGameCommand( string );
	CCommand *getGameCommand( string );
	CCommand *getGameCommand( int );
	int getGameCmdCount( void );

	bool addTool( CTool * );
	bool remTool( string );
	CTool *getTool( string );
	CTool *getTool( int );

	int getToolCount( void );

	string getName( void );
	void setName( string );

	string getBaseDir( void );
	void setBaseDir( string );

	string getMapName( void );
	void setMapName( string );

	string getDescription( void );
	void setDescription( string );

	string getGameName( void );
	void setGameName( string );

	string getGameDir( void );
	void setGameDir( string );

	string getWadDrive( void );
	void setWadDrive( string );

	bool isGameRun( void );
	void setGameRun( bool );

	////////////////////////////////////////////////////////
	//Tool Functions
	////////////////////////////////////////////////////////
	bool addTlCommand( string, CCommand * );
	bool remTlCommand( string, string );
	CCommand *getTlCommand( string, string );
	int getTlCmdCount( string );

	string getTlName( string );
	void setTlName( string, string );

	string getTlCall( string );
	void setTlCall( string, string );

	string getTlDescription( string );
	void setTlDescription( string, string );

	bool isTlRun( string );
	void setTlRun( string, bool );

	////////////////////////////////////////////////////////
	//Command functions
	////////////////////////////////////////////////////////
	string getCmdDescription( string, string );
	void setCmdDescription( string, string, string );

	string getCmdCall( string, string );
	void setCmdCall( string, string, string );

	string getCmdValue( string, string );
	void setCmdValue( string, string, string );

	int getCmdType( string, string );
	void setCmdType( string, string, int );
};
#endif
