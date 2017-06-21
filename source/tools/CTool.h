#ifndef CTOOL_H
#define CTOOL_H

#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
#include	"CCommand.h"
#include	"xmlparser.h"
#include "..\funclib.h"

class CTool
{
private:
	string				tlName;
	string				tlCall;
	string				tlDescription;
	bool				tlRun;
	vector <CCommand>	commands;

public:
	CTool( string, bool );			//name & run
	CTool( void );
	~CTool( void );

	////////////////////////////////////////////////////////
	//Savefunctions
	////////////////////////////////////////////////////////
    bool save( string );
    bool save( ofstream &, int );
    bool load( string );
    bool load( CXMLParser * );

	////////////////////////////////////////////////////////
	//Tool Functions
	////////////////////////////////////////////////////////
	bool addCommand( CCommand * );
	bool remCommand( string );
	CCommand *getCommand( string );
	CCommand *getCommand( int );
	int getCmdCount( void );

	string getName( void );
	void setName( string );

	string getCall( void );
	void setCall( string );

	string getDescription( void );
	void setDescription( string );

	bool isRun( void );
	void setRun( bool );

	////////////////////////////////////////////////////////
	//Command Functions
	////////////////////////////////////////////////////////
	string getCmdDescription( string );
	void setCmdDescription( string, string );

	string getCmdCall( string );
	void setCmdCall( string, string );

	string getCmdValue( string );
	void setCmdValue( string, string );

	int getCmdType( string );
	void setCmdType( string, int );
};
#endif
