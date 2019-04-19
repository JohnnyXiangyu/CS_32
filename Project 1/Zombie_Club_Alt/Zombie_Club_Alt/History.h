#ifndef HISTORY
#define HISTORY 1
#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
	//~History();
private:
	int m_rows;
	int m_cols;
	int m_datas[MAXROWS][MAXCOLS];
};

#endif // !HISTORY