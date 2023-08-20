/*
	The RadioShack Scanner Loader application uses a dBase III file format.
	For more information on dBase III: http://www.wotsit.org/download.asp?f=dbase
	It is unencrypted and contains 17 fields:

		FIELD 1: BANK type C located at 0 size 4 with 0 places
		FIELD 2: CHANNEL type N located at 0 size 4 with 0 places
		FIELD 3: FREQUENCY type N located at 0 size 15 with 9 places
		FIELD 4: MODE type C located at 0 size 3 with 0 places
		FIELD 5: CLASS type C located at 0 size 20 with 0 places
		FIELD 6: SERVICE type C located at 0 size 44 with 0 places
		FIELD 7: ALPHATAG type C located at 0 size 20 with 0 places
		FIELD 8: BANKLOCKOU type L located at 0 size 1 with 0 places
		FIELD 9: CHANNELLOC type L located at 0 size 1 with 0 places
		FIELD 10: DELAY type L located at 0 size 1 with 0 places
		FIELD 11: TONE type N located at 0 size 10 with 5 places
		FIELD 12: USETONE type L located at 0 size 1 with 0 places
		FIELD 13: ATTENUATE type L located at 0 size 1 with 0 places
		FIELD 14: STEPSIZE type N located at 0 size 15 with 9 places
		FIELD 15: TAPE type L located at 0 size 1 with 0 places
		FIELD 16: SELECTNUMB type N located at 0 size 3 with 0 places
		FIELD 17: SELECTENAB type L located at 0 size 1 with 0 places	
		
		The use of most of these fields is pretty obvious.
		For whatever reason, SERVICE and ALPHATAG seem to be reversed.
		SELECTENAB appears to hold a Priority Channel flag.

		Also, Scanner Loader 1.0 seems to only use a couple of these.
*/

/*	dbEntry
	A database entry sub-class, which stores all 17 fields.
	The variable names have been made identical to the field name.
	They are all private members. Public .GetX() functions were made only
	for the variables that ProLink requires, as the purpose for writing
	this class was for easy implementation of an import function.
	.GetX() and .SetX() functions should be trivial to add.
*/ 

#include <string>
#include <iostream>

using namespace std;

struct DBEntry
{
	string	_bank;
	int		_channel;
	string	_frequency;
	string	_mode;
	string	_class;
	string	_service;
	string	_alphatag;
	bool	_banklockou;
	bool	_channelloc;
	bool	_delay;
	string	_tone;
	bool	_usetone;
	bool	_attenuate;
	string	_stepsize;
	bool	_tape;
	string	_selectnumb;
	bool	_selectenab;
};

class DBNode
{
private:
	DBNode *next;
	friend class DBList;
public:
	DBEntry data;
	DBNode(DBEntry entry, DBNode *p = NULL)
	{	data = entry; next = p;	}
	string GetBank() { return data._bank; }
};

class DBList
{
protected:
	DBNode *head;
public:
	DBList();
	~DBList();
	void Insert(DBEntry entry);
	DBEntry GetEntry(int index);
};
