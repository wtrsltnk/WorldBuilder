#ifndef CGROUPMANAGER_H
#define CGROUPMANAGER_H

#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
#include "CGroup.h"
#include "..\funclib.h"

class CGroupManager
{
private:
	string				filename;
	vector <CGroup> groups;
public:
	CGroupManager( void );
	~CGroupManager( void );

	////////////////////////////////////////////////////////
	//Savefunctions
	////////////////////////////////////////////////////////
	bool load( string ) throw();
	bool save( void ) throw();
	bool save( string ) throw();

	////////////////////////////////////////////////////////
	//Manager Functions
	////////////////////////////////////////////////////////

	bool addGroup( CGroup * );
	bool remGroup( string );
	CGroup *getGroup( string );
	CGroup *getGroup( int );
	int getGroupCount( void );

	////////////////////////////////////////////////////////
	//Group Functions
	////////////////////////////////////////////////////////
	bool addGrGameCommand( string, CCommand * );
	bool remGrGameCommand( string, string );
	CCommand *getGrGameCommand( string, string );
	int getGrGameCmdCount( string );

	bool addGrTool( string, CTool * );
	bool remGrTool( string, string );
	CTool *getGrTool( string, string );
	int getGrToolCount( string );

	string getGrName( string );
	void setGrName( string, string );

	string getGrBaseDir( string );
	void setGrBaseDir( string, string );

	string getGrMapName( string );
	void setGrMapName( string, string );

	string getGrDescription( string );
	void setGrDescription( string, string );

	string getGrGameName( string );
	void setGrGameName( string, string );

	string getGrGameDir( string );
	void setGrGameDir( string, string );

	bool isGrGameRun( string );
	void setGrGameRun( string, bool );

	////////////////////////////////////////////////////////
	//Tool Functions
	////////////////////////////////////////////////////////
	bool addTlCommand( string, string, CCommand * );
	bool remTlCommand( string, string, string );
	CCommand *getTlCommand( string, string, string );
	int getTlCmdCount( string, string );

	string getTlName( string, string );
	void setTlName( string, string, string );

	string getTlDescription( string, string );
	void setTlDescription( string, string, string );

	bool isTlRun( string, string );
	void setTlRun( string, string, bool );

	////////////////////////////////////////////////////////
	//Command functions
	////////////////////////////////////////////////////////
	string getCmdDescription( string, string, string );
	void setCmdDescription( string, string, string, string );

	string getCmdCall( string, string, string );
	void setCmdCall( string, string, string, string );

	string getCmdValue( string, string, string );
	void setCmdValue( string, string, string, string );

	int getCmdType( string, string, string );
	void setCmdType( string, string, string, int );
};
#endif