#include <stdio.h>
#include <iostream>

using namespace std;
class board{
    public:
        bool b[8][8]; 
        //Constructor - initializes b to a 12x12 array of bool
        board(){
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    b[i][j] = 0;
                }
            }       
        }
        void stamp(int x, int y){
            //Bad input handling
            if(0>x || x>7 || y<0 || y>7){
                cerr << "Invalid matrix input!\n";
                return;
            }
            if(b[x][y]==1)
                return;
            b[x][y]=1;

            for(int i=-1; i <=1; i++){
                for(int j=-1;j<=1;j++){
                    if(x+i<0 || x+i > 7 || y+j < 0 || y+j > 7) continue;
                    b[x+i][y+i]=1;
                }
            }
             
        
        }




};

int main(){
    //space_count is n x m matrix s.t. n is number of large blocks and m is the amount of spaces it
    //has free
    //@return number of worlds that have m free spaces for l blocks
    int space_count[12][64];
    for(int i=0;i<13;i++){
        for(int j=0;j<64;j++){
            space_count[i][j] = 0;
        }
    }
    





}
