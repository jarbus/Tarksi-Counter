#include <gmp.h>
#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <math.h>
using namespace std;

void help_me_god(mpz_t lc, int l, int n){
}

void smaller_variants(mpz_t wc){
}

int main(){

    mpz_t test;
    mpz_init(test);
    mpz_t ONE;
    mpz_init_set_str(ONE,"1",10);
    mpz_add(test,ONE,test);
    
    mpz_t large_count, world_count, count, tmp;
    mpz_init(large_count);
    mpz_init(world_count);
    mpz_init(count);
    mpz_init(tmp);
    //Iterates over each number of possible objects in Tarski's world
    for(int n=0;n<=12;n++){
        for(int l=0;l<n;l++){
            help_me_god(large_count,l,n);
            
            //Calculate how many different worlds are possible adding smaller piece
            smaller_variants(world_count);
            int two_power = pow(2,n-l);
            int three_power = pow(3,n);
            int nplusone = pow(n+1,6); 
            mpz_mul_si(tmp,tmp,two_power);
            mpz_mul(tmp,tmp,world_count);
            mpz_add(tmp,world_count,tmp);
        }
    }


    return 0;
}

