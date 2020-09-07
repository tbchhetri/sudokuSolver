#include <iostream>
#include <cstdint>
//git test
using namespace std;

uint16_t board[9][9];

const uint16_t
		 VALUE_MASK = 0x000f,
		 VALID_MASK = 0x1ff0,
		 IS_FILLED_IN = 0x8000,
		 IS_0_VALID = 0x2000;

int main(){
	char ch;
	
	cin >> ch;

	for (int r = 0; r <9; r++){
		for (int c = 0; c < 9; c++){
			if(ch == '.')
				board [r][c]=0;
			else 
				board[r][c] = IS_FILLED_IN | (ch - '0');//sub from 0 converts it into binary
		}
	}

	/*bool isValid(uint16_t cell, uint16_t i)
		return ((cell & (Is_0_VALID >> i ))!=0);

	void markInvalid (uint16_t &cell, int16_t i){
		cell = cell & ~(IS_0_VALID >> i)
		}*/	

	for (int r = 0; r <9; r++){
		for (int c = 0; c < 9; c++){
			cout << (board[r][c] & VALUE_MASK) << endl;}
	}
}
	
	
	
