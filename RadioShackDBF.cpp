/*	
	RadioShackDatabase.cpp
	(C)2006 Mark Horka
	http://www.antistatic.org
	
	This C++ class allows for reading from a Radio Shack "Scanner Loader"
	database (dBase III) file.

	Radio Shack Scanner Loader V1.0:
	http://support.radioshack.com/Download/software/200-0048.exe
	"Works with 200-0313, 200-0314, 200-0422, 200-0423, 200-0424 and 200-0514."

	For what it's worth, my ProLink application (available on my website)
	is many times better and easier	to use than the stock Scanner Loader.

		********************** NOTE ****************************
		*** The channels may not be in numerical order.      ***
		*** Use .GetChannel() to retrieve the channel number ***
		********************** NOTE ****************************
*/

/* for Microsoft Visual C++ only */
#include "stdafx.h"

#include <fstream>
#include "RadioShackDBF.h"

RadioShackDBF::RadioShackDBF()
{
	date = (char*)malloc(sizeof(char)*10);
}

RadioShackDBF::~RadioShackDBF()
{
	delete date;
}

/*
	bool Load(void)

	This function loads the file specified.
	Returns:
		-1	File does not exist
		0	File loaded successfully
		>1	Error loading file
			(Note: This means that the file is probably not in
			RadioShack's Scanner Loader DBF format, and is most
			likely a DBF in some other format, or is corrupt)
			1: file is not dBase III
			2: file is encrypted
*/

int RadioShackDBF::Load(string file)
{
	// TODO: fix this. not such a good idea i dont think.....
	fileName = file; // save the filename

	char byte;
	long longbyte;
	// max we will need is 44, but im doing Ceiling(Log2(N))
	// where N=44, just for good measure
	char CTYPE[64];
	string strTemp;
	DBEntry newEntry;
	int i;

	// TODO: fix this too:
	// WARNING: NO CHECKING TO SEE IF FILE EXISTS!!

	ifstream myFile(fileName.c_str(), ios::in | ios::binary);
	TRACE("File open.\n");
	// the first byte should be 0x03 
	// this is just a simple check
	myFile.read(&byte, 1);
	if (byte != 3)
		return 1; // error loading file
	
	// now it gets complicated... :)

	// the next byte is the year.. (from 1900)
	myFile.read(&byte, 1);	
	year = byte;
	// next is month
	myFile.read(&byte, 1);	
	month = byte;
	// then day
	myFile.read(&byte, 1);	
	day = byte;

	// next 4 are the number of records
	myFile.read((char*)&longbyte, 4);
	entries = longbyte;

	// for the purposes of this class, the next 7 bytes are useless
	// [2] num bytes in the header
	// [2] num bytes in the records
	// [3] reserved
	myFile.seekg(7, ios::cur);

	// the next flag is the encryption flag. if it is set, we assume the
	// database is encrypted (note, however, that this flag does not
	// itself encrypt the database, it simply signifies that it is so)
	// that being said, RS database isnt encrypted, so if this flag is
	// set we know something is wrong
	myFile.read(&byte, 1);
	if (byte == 1)
		return 2;

	// the next 16 are also unused by this class
	// see the format of dbase III for information
	myFile.seekg(16, ios::cur);

	myFile.read(&byte, 1); // read the "stop byte"
	while (byte != 0x0D) // 0x0D signals end of header
	{
		myFile.read(&byte, 1);
		// normally, we would read in all of the field information
		// from the header, however since we already know the RS
		// format, we can safely skip to the end
	}


	for (i = 0; i < entries; i++)
	{
		// if record is marked as deleted, dont import it
		myFile.read(&byte, 1);
		if 	(byte == '*')
			break;

		// 4 char for the bank (type C)
		myFile.read(CTYPE, 4);
		CTYPE[4] = '\0';
		newEntry._bank = CTYPE;
		
		// 4 char for the channel number (type N)
		myFile.read(CTYPE, 4);
		CTYPE[4] = '\0';
		newEntry._channel = atoi(CTYPE);

		// 15 char for the frequency [9 places] (type N)
		myFile.read(CTYPE, 15);
		CTYPE[15] = '\0';
		newEntry._frequency = CTYPE;

 		// 3 char for the mode (type C)
 		myFile.read(CTYPE, 3);
		CTYPE[3] = '\0';
		newEntry._mode = CTYPE;

		// 20 char for the class (type C)
		myFile.read(CTYPE, 20);
		CTYPE[20] = '\0';
		newEntry._class = CTYPE;

		// 44 char for the service (type C)
		myFile.read(CTYPE, 44);
		CTYPE[44] = '\0';
		newEntry._service = CTYPE;

		// 20 char for the alpha tag (type C)
		myFile.read(CTYPE, 20);
		CTYPE[20] = '\0';
		newEntry._alphatag = CTYPE;

		// 1 char for the bank lockout (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._banklockou = IsTrue(CTYPE[0]);		

		// 1 char for the channel lockout (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._channelloc = IsTrue(CTYPE[0]);

		// 1 char for the delay (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._delay = IsTrue(CTYPE[0]);

		// 10 char for the tone (type N)
		myFile.read(CTYPE, 10);
		CTYPE[10] = '\0';
		newEntry._tone = CTYPE;

		// 1 char for the use tone (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._usetone = IsTrue(CTYPE[0]);

		// 1 char for the attenuate (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._attenuate = IsTrue(CTYPE[0]);

		// 15 char for the step size [9 places] (type N)
		myFile.read(CTYPE, 15);
		CTYPE[15] = '\0';
		newEntry._stepsize = CTYPE;

		// 1 char for the tape (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._tape = IsTrue(CTYPE[0]);

		// 1 char for the select numb (type C)
		myFile.read(CTYPE, 3);
		CTYPE[3] = '\0';
		newEntry._selectnumb = CTYPE;		

		// 1 char for the select enab (type L)
		myFile.read(CTYPE, 1);
		CTYPE[1] = '\0';
		newEntry._selectenab = IsTrue(CTYPE[0]);
		
		db.Insert(newEntry);
	}	
	
	return 0;
}

const char* RadioShackDBF::GetDate()
{		
	sprintf(date, "%d/%d/%d", month, day, year+1900);
	return date;
}

long RadioShackDBF::NumRecords()
{			
	return entries;
}

DBEntry RadioShackDBF::GetRecord(int index)
{
	return db.GetEntry(index);
}

// IsTrue(char)
// helper function for determining if a char represents
// boolean true or false
bool RadioShackDBF::IsTrue(char c)
{ return (c == 'T' || c == 'Y' || c == 't' || c == 'y');
}
