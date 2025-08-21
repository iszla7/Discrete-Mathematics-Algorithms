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
bigInteger fastPower(bigInteger a,bigInteger n){
    bigInteger z=a;
    bigInteger y(1);
    bigInteger m=n;
    while(m>0){
        if(m%2==1)
            y=y*z;
        m/=2;
        z=z*z;
    }
    return y;
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
//MILLERA_RABINA TEST
bool PrimeTest(bigInteger n,int no_of_trials){
    bigInteger r(0);
    bigInteger nn=n-1;
    while(nn%2==0){
        r++;
        nn=nn/2;
    }
    bigInteger s=nn;
    while(no_of_trials>0) {
        bigInteger a = randomInt(bigInteger(2), n - 1);
        bigInteger x = powermod(a, s, n);
        if (x % n == bigInteger(1) || x % n == bigInteger(n - 1))
            return true;
        bigInteger i(1);
        while (i <= r - 1) {
            x = powermod(x, bigInteger(2), n);
            if (x % n == bigInteger( n - 1))
                return true;
            i++;
        }
        no_of_trials--;
    }
    return false;
}

int main()
{
    initalize_random();
    for(int i=1;i<=15;i++){
        bigInteger F(fastPower(bigInteger(2), fastPower(bigInteger(2), i)) + bigInteger(1));
        if(PrimeTest(F,15))
            cout<<"F_"<<i<<" can be prime"<<endl;
        else
            cout<<"F_"<<i<<" is not prime"<<endl;
    }
}