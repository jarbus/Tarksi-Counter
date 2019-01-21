#include <stdio.h>
#include <iostream>
using namespace std;
const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

typedef uint64_t llint;
//literally stolen from https://en.wikipedia.org/wiki/Hamming_weight ty for the
//donation
//@return the number of 1 bits in uint64_t
int popcount64c(uint64_t x)
{
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}

//places a 3x3 grid of 1s into the uint64_t
void stamp(llint * board, llint row, llint col){
    llint VAR,TOP,MIDDLE,BOTTOM;
    if(col==1 || col==7){
        VAR=3;
    }
    else{
        VAR=7;
    }
    if(row>0)
        TOP = VAR << ((row-1)*8 + (col-1));
    
    MIDDLE = VAR << (row*8 + (col-1));

    if(row<7)
        BOTTOM = VAR << ((row+1)*8 + (col-1));
    *board = *board | TOP | MIDDLE | BOTTOM;
}

void print_board(llint board){
    for(short unsigned int i=0;i<8;i++){
        for(short unsigned int j=0;j<8;j++){
            cout << board%2;
            board = board>>1;
        }
        cout<<endl;
    }
}

int main(){
    
    llint bit_board = 0; //64 bit integer, could replace board class and have operations performed via bitwise operators

    //space_count is n x m matrix s.t. n is number of large blocks and m is the amount of spaces it
    //has free
    //@return number of worlds that have m free spaces for l blocks
    int space_count[12][64];
    for(int i=0;i<12;i++){
        for(int j=0;j<64;j++){
            space_count[i][j] = 0;
        }
    }
    
    llint boards [12];
    for(int i=0;i<12;i++){
        boards[i]=0;
    }
    stamp(&bit_board,0,1);
    print_board(bit_board);





}
