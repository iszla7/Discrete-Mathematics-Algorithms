#include <iostream>
#include <time.h>
#include <gmpxx.h>


using namespace std;
typedef mpz_class bigInteger;

/* PSEUDORANDOM NUMBERS */
gmp_randclass rr(gmp_randinit_default);

void initalize_random()
{
    rr.seed(time(NULL));
}

bigInteger randomInt(bigInteger a, bigInteger b)
{
    return a + rr.get_z_range(b-a+1);
}
bigInteger powermod(bigInteger M,bigInteger e,bigInteger N){
    bigInteger z=M%N;
    bigInteger m=e;
    bigInteger y(1);
    while(m>0){
        if(m%2==1){
            y=(y*z)%N;
        }
        m/=2;
        z=(z*z)%N;
    }
    return y;
}
bool fermat_test(bigInteger n, int no_of_trials)
{
    int i=1;
    while(i<=no_of_trials){
        bigInteger a=randomInt(bigInteger(2),n);
        if(powermod(a,n-1,n)!=bigInteger(1)) {
            cout<<a<<endl;
            return false;
        }
        i++;
    }
    return true;
}

int main()
{
    initalize_random();
    bigInteger a("22701801293785014193580405120204586741061235962766583907094021879215171483119139894870133091111044901683400949483846818299518041763507948922590774925466088171879259465921026597046700449819899096862039460017743094473811056991294128542891880855362707407670722593737772666973440977361243336397308051763091506836310795312607239520365290032105848839507981452307299417185715796297454995023505316040919859193718023307414880446217922800831766040938656344571034778553457121080530736394535923932651866030515041060966437313323672831539323500067937107541955437362433248361242525945868802353916766181532375855504886901432221349733");
    if(fermat_test(a,5))
        cout<<"is prime"<<endl;
    else
        cout<<"is not prime"<<endl;
}
