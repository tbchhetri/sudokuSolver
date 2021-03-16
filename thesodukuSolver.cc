//
//  thesodukuSolver.cc
//  sudokuSolver
//
//  Created by Tek Chhetri on 3/18/20.
//  Copyright © 2020 Tek Chhetri. All rights reserved.
//

#include <iostream>
#include <cstdint>
#include <string>
#include "stack.h"
//#include "simpleStack.h"

using namespace std;

uint16_t board[9][9];

const uint16_t
         VALUE_MASK = 0x000f, // for cout'ng board
         VALID_MASK = 0x1ff0, // for accessing all valid choices for the board
        IS_FILLED_IN = 0x8000,
        IS_0_VALID = 0x2000;

Stack<int> myStack;

//*************************************************************************
bool isValid(uint16_t cell, uint16_t i){
        return ((cell & (IS_0_VALID >> i ))!=0);
}

void markInvalid (uint16_t &cell, int16_t i){
        cell = cell & ~(IS_0_VALID >> i);
        }
//*************************************************************************
int countBits(unsigned int n){
  int count = 0;
  while (n != 0){
    count++;
    n &= n - 1;
    }
  return count;
}

//*************************************************************************
void showBits(uint16_t n) {
  for (int i = 15; i >= 0; i--)
    if (n & (1 << i))
      cout << "1";
    else
      cout <<"0";

    cout << endl;
}

//*************************************************************************
bool findBest (uint16_t board[][9], Stack<int>& myStack){
//1 Marking cells as valid choices
    int digit;
   for (int i = 0; i <9; i++){
          for (int j = 0; j < 9; j++){
               if((board[i][j] & IS_FILLED_IN) == 0){
                   board[i][j] = VALID_MASK;
                 }
          }
    }
    //2.0 remove invalid choices
    //2.1 Invalid in row
        for (int i = 0; i <9; i++){
                 for (int j = 0; j < 9; j++){
                     if((board[i][j] & IS_FILLED_IN) != 0){
                         digit = (board[i][j] & VALUE_MASK);
                         for (int r = 0; r < 9; r++){
                             if((board[i][r] & IS_FILLED_IN) == 0){
                                 markInvalid(board[i][r],digit);
                             }
                         }
                     
    //2.2 Invalid in column
                         for (int c = 0; c < 9; c++){
                            if((board[c][j] & IS_FILLED_IN) == 0){
                                 markInvalid(board[c][j],digit);
                            }
                         }
    //2.3 Invalid in Square
                    int x=3*(i/3), y=3*(j/3);
                         for(int r = 0; r < 3; r++){
                             for (int c = 0; c < 3; c++){
                                 if(((board[x+r][y+c]) & IS_FILLED_IN ) == 0){
                                     markInvalid(board[x+r][y+c],digit);
                                 }
                             }
                         }
                      }
                     }
        }
//    cout << " The Board: ";
    for (int i = 0; i <9; i++){
        for (int j = 0; j < 9; j++){
//            showBits(board[i][j]);
        }
 //       cout << endl;
    }
    
//finding the best values
    int low = 10;
    int iBest = 0, jBest = 0, count1 = 0;
    string temp1 , temp2;
    
    for (int i = 0; i <9; i++){
        for (int j = 0; j < 9; j++){
            if((board[i][j] & IS_FILLED_IN) == 0){
                count1 = countBits(board[i][j]) ;
                if(count1 < low){
                    low = count1;
                    iBest = i;
                    jBest = j;
                 }
                }
            }
  //      cout << endl;
        }
//          cout << " Best " << " ( " << iBest << " , " << jBest << " ) ";
//        cout << endl;
    if (low == 10){
        return false;
    }
    
    // Mark best cell as filled in
    board[iBest][jBest] = board[iBest][jBest] | IS_FILLED_IN;
 //   showBits(board[iBest][jBest]);

  //  int cell = 0;
    
  //  cell = iBest *9 + jBest;
    myStack.push(iBest *9 + jBest);
    
    return true;
}

//*************************************************************************

int main(){
    char ch;
    
    cout << " Enter the puzzle " << endl;

    for (int r = 0; r <9; r++){
        for (int c = 0; c < 9; c++){
            cin >> ch;
            if(ch == '.')
                board [r][c]=0;
            else
                board[r][c] = IS_FILLED_IN | (ch - '0');//sub from 0 converts it into int and " | " to conv to binary
//            cout << (board[r][c] & VALUE_MASK);//value mask converts board value back to int
                                        //just use value mask to unmask and know the int value
        }
        cout << endl;
    }

////The main algorithm
    bool notError = findBest(board, myStack);
    while(notError){
        int i,j;
        
        i = myStack.peek()/9;
        j = myStack.peek()%9;
        
        bool temp4 = false;
        if((board[i][j] &~ IS_FILLED_IN) != 0){
            int temp3 = 1;
            while(temp3 <= 9){
                if( isValid(board[i][j], temp3 )){
                    board[i][j] = board[i][j] &~ VALUE_MASK;
                    board[i][j] = temp3 | board[i][j];
                    markInvalid(board[i][j],temp3);
                    temp4 = true;
                    break;
                }
                temp3++;
            }
        }
            if( !temp4){
                board[i][j] = board[i][j] &~ IS_FILLED_IN;
                myStack.pop();
                
                if(myStack.isEmpty()){
                    cout << " No sol " << endl;
                    return 0;
                }
                continue;
            }
        
        notError = findBest(board, myStack);
        if( !notError){
            break;
        }
    }
    cout << "*BEHOLD YOUR SOLUTION*" << endl;
     for (int i = 0; i <9; i++){
         if(i%3 == 0 && (i != 0 )){
             cout << "----|-----|-----" << endl;
         }
         for (int j = 0; j < 9; j++){
             if(j%3 == 0 && j != 0){
                 cout << " | " ;
             }
     cout << (board[i][j] & VALUE_MASK);
         }
         cout << endl;
     }
    
    
    return 0;
}//end main

