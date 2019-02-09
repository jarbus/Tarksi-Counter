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

int main(){

    uint64_t bit_board = 0; //64 bit integer, could replace board class and have operations performed via bitwise operators

    //space_count is n x m matrix s.t. n is number of large blocks and m is the amount of spaces it
    //has free
    //@return number of worlds that have m free spaces for l blocks
    uint64_t space_count[13][65];
    for(uint64_t i=0;i<13;i++){
        for(uint64_t j=0;j<65;j++){
            space_count[i][j] = 0;
        }
    }
    space_count[0][0]=1;

/*
    // ERROR CHECKING FOR STAMP
    for(uint64_t i=0;i<64;i++){
        stamp(&bit_board,i);
        uint64_t bb = bit_board;
        for(uint64_t j=0;j<64;j++){
            if((bit_board >> j) & 1) continue;
            stamp(&bit_board,j);
            cout<<i<<endl;
            cout<<j<<endl;
            print_board(bit_board);
            bit_board=bb;
        }
        bit_board=0;
    }
*/


    uint64_t bb1, count1, bb2, count2, bb3, count3, bb4, count4, bb5, count5, bb6, count6, bb7, count7, bb8, count8, bb9, count9, bb10, count10, bb11, count11,bb12,count12;
    uint64_t i,j,k,l,m,n,o,p,q,r,s,t;
    for(i=0;i<64;i++){
        count1 = stamp(&bit_board,i);
        space_count[1][count1]+=1;
        bb1 = bit_board;
        //next loop

        for(k=i+1; k<64; k++){
            if((bit_board >> k) & 1) continue;
            count2 = stamp(&bit_board,k);
            space_count[2][count2]+=1;
            bb2 = bit_board;
            //next loop

            for(m=k+1; m<64; m++){
                if((bit_board >> m) & 1) continue;
                count3 = stamp(&bit_board,m);
                space_count[3][count3]+=1;
                bb3 = bit_board;
                //next loop

                for(o=m+1; o<64; o++){
                    if((bit_board >>o) & 1) continue;
                    count4 = stamp(&bit_board,o);
                    space_count[4][count4]+=1;
                    bb4 = bit_board;
                    //next loop

                    for(q=o+1; q<64; q++){
                        if((bit_board >> q) & 1) continue;
                        count5 = stamp(&bit_board,q);
                        space_count[5][count5]+=1;
                        bb5 = bit_board;
                        //next loop

                        for(s=q+1; s<64; s++){
                            if((bit_board >> s) & 1) continue;
                            count6 = stamp(&bit_board,s);
                            space_count[6][count6]+=1;
                            bb6 = bit_board;
                            //next loop

                            for(j=s+1; j<64; j++){
                                if((bit_board >> j) & 1) continue;
                                count7 = stamp(&bit_board,j);
                                space_count[7][count7]+=1;
                                bb7 = bit_board;
                                //next loop
                                for(l=j+1; l<64; l++){
                                    if((bit_board >> l) & 1) continue;
                                    count8 = stamp(&bit_board,l);
                                    space_count[8][count8]+=1;
                                    bb8 = bit_board;
                                    //next loop

                                    for(n=l+1; n<64; n++){
                                        if((bit_board >> n) & 1) continue;
                                        count9 = stamp(&bit_board,n);
                                        space_count[9][count9]+=1;
                                        bb9 = bit_board;
                                        //next loop
                                        for(p=n+1; p<64; p++){
                                            if((bit_board >> p) & 1) continue;
                                            count10 = stamp(&bit_board,p);
                                            space_count[10][count10]+=1;
                                            bb10 = bit_board;
                                            //next loop
                                            for(r=p+1; r<64; r++){
                                                if((bit_board >> r) & 1) continue;
                                                count11 = stamp(&bit_board,r);
                                                space_count[11][count11]+=1;
                                                bb11 = bit_board;
                                                //next loop
                                                for(t=r+1; t<64; t++){
                                                    if((bit_board >> t) & 1) continue;
                                                    count12 = stamp(&bit_board,t);
                                                    space_count[12][count12]+=1;
                                                    bit_board = bb11;
                                                }
                                                bit_board = bb10;
                                            }
                                            bit_board = bb9;
                                        }
                                        bit_board = bb8;
                                    }
                                    bit_board = bb7;
                                }
                                bit_board = bb6;
                            }
                            bit_board = bb5;
                        }
                        bit_board = bb4;
                    }
                    bit_board = bb3;
                }
                bit_board = bb2;
            }
            bit_board = bb1;
        }
        bit_board=0;
    }

    // Formatting final chart
    for(uint64_t i=0;i<13;i++){
        for(uint64_t j=0;j<65;j++){
            printf("%16" PRIu64,space_count[i][j]);
        }
        cout <<endl;
    }
}
