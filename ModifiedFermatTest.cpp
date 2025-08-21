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
void modified_fermat_test(bigInteger n, int no_of_trials) {
    int i = 1;
    while (i <= no_of_trials) {
        bigInteger a = randomInt(bigInteger(2), n);
        if (powermod(a, n - 1, n) != bigInteger(1)) {
            cout << "witness: \n" << a << "\n" << gcd(a, n) << endl;
        }
        i++;
    }
}
int main()
{
    initalize_random();
    bigInteger a("1590231231043178376951698401");
    modified_fermat_test(a,20);
}