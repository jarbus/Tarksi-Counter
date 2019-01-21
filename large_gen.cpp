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
    llint VAR,TOP,BOTTOM;
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
    
    llint MIDDLE = VAR << (row*8 + col);

    if(row<7)
        BOTTOM = VAR << ((row+1)*8 + col);
    else
        BOTTOM = 0;

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
    llint space_count[12][64];
    for(llint i=0;i<12;i++){
        for(llint j=0;j<64;j++){
            space_count[i][j] = 0;
        }
    }
    space_count[0][0]=1;

    // ERROR CHECKING FOR STAMP
    /*for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            stamp(&bit_board,i,j);
            cout<<i<<" "<<j<<endl;
            print_board(bit_board);
            bit_board=0;
        }
    }*/
    
    llint bb1, count1, bb2, count2, bb3, count3, bb4, count4, bb5, count5, bb6, count6;
    llint i,j,k,l,m,n,o,p,q,r,s,t;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            count1 = stamp(&bit_board,i,j);
            space_count[1][count1]+=1;
            bb1 = bit_board;
            //next loop

            for(k=0; k<8; k++){
                for(l=0;l<8;l++){
                    if((bit_board >> (k*8 + l)) & 1) continue;
                    count2 = stamp(&bit_board,k,l);
                    space_count[2][count2]+=1;
                    bb2 = bit_board;
                    //next loop

                    for(m=0; m<8; m++){
                        for(n=0;n<8;n++){
                            if((bit_board >> (m*8 + n)) & 1) continue;
                            count3 = stamp(&bit_board,m,n);
                            space_count[3][count3]+=1;
                            bb3 = bit_board;
                            //next loop

                            for(o=0; o<8; o++){
                                for(p=0;p<8;p++){
                                    if((bit_board >>(o*8 + p)) & 1) continue;
                                    count4 = stamp(&bit_board,o,p);
                                    space_count[4][count4]+=1;
                                    bb4 = bit_board;
                                    //next loop

                                    for(q=0; q<8; q++){
                                        for(r=0;r<8;r++){
                                            if((bit_board >> (q*8 + r)) & 1) continue;
                                            count5 = stamp(&bit_board,q,r);
                                            space_count[5][count5]+=1;
                                            bb5 = bit_board;
                                            //next loop

                                            for(s=0; s<8; s++){
                                                for(t=0;t<8;t++){
                                                    if((bit_board >> (s*8 + t)) & 1) continue;
                                                    count6 = stamp(&bit_board,s,t);
                                                    space_count[6][count6]+=1;
                                                    bb6 = bit_board;
                                                    //next loop

                                                    bit_board = bb5;
                                                }
                                            }
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
    for(llint i=0;i<65;i++){
        printf("%8" PRIu64,i);
    }
    cout << endl;
    for(llint i=0;i<12;i++){
        cout << i << "  " ;
        for(llint j=0;j<64;j++){
            printf("%8" PRIu64,space_count[i][j]);
        }
        cout <<endl;
    }


}
