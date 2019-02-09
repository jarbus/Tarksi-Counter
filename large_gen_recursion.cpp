#include <stdio.h>
#include <iostream>
#include <time.h>
#include <inttypes.h>

using namespace std;

const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...


//places a 3x3 grid of 1s into the uint64_t
uint64_t stamp(uint64_t * board, uint64_t spot){
    uint64_t VAR,TOP,BOTTOM;
    uint64_t row = spot/8;
    uint64_t col = spot%8;
    if(col==0|| col==7){
        VAR=3;
        if(col==7) col -=1;
    }
    else{
        VAR=7;
        col -= 1;
    }
    if(row>0)
        TOP = VAR << ((row-1)*8 + col);
    else
        TOP = 0;

    uint64_t MIDDLE = VAR << (row*8 + col);

    if(row<7)
        BOTTOM = VAR << ((row+1)*8 + col);
    else
        BOTTOM = 0;

    *board = *board | TOP | MIDDLE | BOTTOM;
    uint64_t x=*board;
    x -= (*board >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
    return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

void print_board(uint64_t board){
    for(short unsigned int i=0;i<8;i++){
        for(short unsigned int j=0;j<8;j++){
            cout << board%2;
            board = board>>1;
        }
        cout<<endl;
    }
}

void count_worlds(uint64_t** table, int depth, uint64_t board, int k) {
    if(depth >= 12) return;
    uint64_t count;
    uint64_t copy = board;
    for(int i = k+1; i < 64; i++) {
        if((board>>i)&1) continue;
        count = stamp(&board,i);
        table[depth][count]+=1;
        count_worlds(table,depth+1,board,i);
        board = copy;
    }
}

int main(){

    uint64_t bit_board = 0; //64 bit integer, could replace board class and have operations performed via bitwise operators

    //space_count is n x m matrix s.t. n is number of large blocks and m is the amount of spaces it
    //has free
    //@return number of worlds that have m free spaces for l blocks
    uint64_t** space_count;//[13][65];
    space_count = new uint64_t*[13];
    for(int i = 0; i < 13; i++) {
        space_count[i] = new uint64_t[65];
    }

    for(uint64_t i=0;i<13;i++){
        for(uint64_t j=0;j<65;j++){
            space_count[i][j] = 0;
        }
    }
    count_worlds(space_count,0,0,-1);

    // Formatting final chart
    for(uint64_t i=0;i<13;i++){
        for(uint64_t j=0;j<65;j++){
            printf("%16" PRIu64,space_count[i][j]);
        }
        cout <<endl;
    }

    for(int i = 0; i < 13; i++) {
        delete [] space_count[i];
    }
    delete [] space_count;

} 
