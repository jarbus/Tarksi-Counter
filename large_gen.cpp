#include <stdio.h>
#include <iostream>
#include <time.h>
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
/*int popcount64c(uint64_t x)
{
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}
*/
//places a 3x3 grid of 1s into the uint64_t
llint stamp(llint * board, llint row, llint col){
    llint VAR = 0;
    llint TOP=0;
    llint MIDDLE=0;
    llint BOTTOM=0;
    if(col==1|| col==8){
        VAR=3;
        if(col==8) col -=1;
        col -= 1;
    }
    else{
        VAR=7;
        col -= 2;
    }
    row = row-1;
    if(row>0)
        TOP = VAR << ((row-1)*8 + col);
    
    MIDDLE = VAR << (row*8 + col);

    if(row<7)
        BOTTOM = VAR << ((row+1)*8 + col);

    *board = *board | TOP | MIDDLE | BOTTOM;
    llint x=*board;
    x -= (*board >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
    return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
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
    space_count[0][0]=1;

    /* ERROR CHECKING FOR STAMP
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            stamp(&bit_board,i,j);
            cout<<i<<" "<<j<<endl;
            print_board(bit_board);
            bit_board=0;
        }
    }
    */
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            int count1 = stamp(&bit_board,i,j);
            space_count[1][count1]+=1;
            int bb1 = bit_board;
            //next loop

            for(int k=1; k<9; k++){
                for(int l=1;l<9;l++){
                    if((bit_board >> ((k-1)*8 + l-1)) & 1) continue;
                    int count2 = stamp(&bit_board,k,l);
                    space_count[2][count2]+=1;
                    int bb2 = bit_board;
                    //next loop

                    for(int m=1; m<9; m++){
                        for(int n=1;n<9;n++){
                            if((bit_board >> ((m-1)*8 + n-1)) & 1) continue;
                            int count3 = stamp(&bit_board,m,n);
                            space_count[3][count3]+=1;
                            int bb3 = bit_board;
                            //next loop

                            for(int o=1; o<9; o++){
                                for(int p=1;p<9;p++){
                                    if((bit_board >> ((o-1)*8 + p-1)) & 1) continue;
                                    int count4 = stamp(&bit_board,o,p);
                                    space_count[4][count4]+=1;
                                    int bb4 = bit_board;
                                    //next loop
                                    
                                    for(int q=1; q<9; q++){
                                        for(int r=1;r<9;r++){
                                            if((bit_board >> ((q-1)*8 + r-1)) & 1) continue;
                                            int count5 = stamp(&bit_board,q,r);
                                            space_count[5][count5]+=1;
                                            int bb5 = bit_board;
                                            //next loop
                                            bit_board = bb4;
                                        }
                                    }
                                    bit_board = bb3;
                                }
                            }
                            bit_board = bb2;
                    }
                }
                    bit_board = bb1;
                }
            }
            bit_board=0;
        }
    }




    // Formatting final chart
    cout << "  ";
    for(int i=0;i<65;i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i=0;i<12;i++){
        cout << i << "  " ;
        for(int j=0;j<64;j++){
            cout << space_count[i][j] << " ";
        }
        cout <<endl;
    }


}
