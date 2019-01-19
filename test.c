#include <gmp.h>
#include <stdio.h>

int main(){

mpz_t test;
mpz_init(test);
mpz_t FIVE;
mpz_init_set_str(FIVE,"5",10);
mpz_add(test,FIVE,test);
mpz_out_str(test);

return 0;
}

