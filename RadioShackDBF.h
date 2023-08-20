
#include "DBList.h"

class RadioShackDBF
{
public:
	RadioShackDBF();
	~RadioShackDBF();
	
	int Load(string);
	float GetFrequency(int channel);
	const char* GetDate();
	long NumRecords();
	DBEntry GetRecord(int index);

private:
	bool IsTrue(char c);
	DBList db;
	long entries;
	string fileName;
	int day;
	int month;
	int year;
	char* date;
};
