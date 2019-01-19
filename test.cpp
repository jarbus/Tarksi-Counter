#include <gmp.h>
#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <math.h>

using namespace std;

void num_world_with_large(mpz_t lc, int num_l, int num_s)
{
	
}

void smaller_variants(mpz_t wc, int l, int n)
{
	mpz_bin_uiui(wc, l, n);
	/*
	num_world_small(int n, int location_count) 
	{	
		return binomial(location_count,n).multiply(TWO.pow(n));
	}
	*/
}

int main()
{

    //mpz_t test;
    //mpz_init(test);
    mpz_t ONE;
    mpz_init_set_str(ONE,"1",10);
    //mpz_add(test,ONE,test);
    
    mpz_t large_count, world_count, count, tmp;
    mpz_init(large_count);
    mpz_init(world_count);
    mpz_init(count);
    mpz_init(tmp);
    //Iterates over each number of possible objects in Tarski's world
    for(int n=0; n<=12; n++)
	{
        for(int l=0; l<=n; l++)
		{
            num_world_with_large(large_count, l, n-l);
            
            //Calculate how many different worlds are possible adding smaller piece
<<<<<<< HEAD
            smaller_variants(world_count);
            int two_power = pow(2,n-l);
            int three_power = pow(3,n);
            int nplusone = pow(n+1,6); 
=======
            smaller_variants(world_count, l, n);
            int two_power = pow(2, n-l);
>>>>>>> 4c6b1c0cca06ae02a85ccf5d092beef66fe602fc
            mpz_mul_si(tmp,tmp,two_power);
            mpz_mul(tmp,tmp,world_count);
            mpz_add(count,world_count,tmp);
        }
    }


    return 0;
}

