#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	
	//m_datas = new int*[m_rows]; //allocte the outer array
	
	/*
	for (int r = 0; r < m_rows; r++) { //allocate the inner arrays
		m_datas[r] = new int[m_cols];
	}

	*/
	for (int r = 0; r < m_rows; r++) {
		for (int c = 0; c < m_cols; c++) {
			m_datas[r][c] = 0; //initializing all records to 0
		}
	} 
} 

/*
History::~History() {
	for (int r = 0; r < m_rows; r++) {
		delete[](m_datas[r]);
	}

	delete[](m_datas);
} // is this okay ? to delete the int*s first then delete the int**
*/


bool History::record(int r, int c) {
	if (!(r <= m_rows && r >= 1 && c <= m_cols && c >= 1)) {
		return false;
	}
	else {
		m_datas[r-1][c-1]++;
		return true;
	}
}

void History::display() const {
	clearScreen();
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++) {
			if (m_datas[r][c] == 0) {
				cout << ".";
			}
			else if (m_datas[r][c] >= 1 && m_datas[r][c] <= 25) {
				char times = ('A' + (m_datas[r][c] - 1));
				cout << times;
			}
			else {
				cout << "Z";
			}
		}
		
		cout << endl;
	}
	cout << endl;
}