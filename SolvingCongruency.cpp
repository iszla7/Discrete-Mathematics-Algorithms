#include <iostream>
#include <gmpxx.h>

using bigInteger = mpz_class;
using namespace std;

struct triple{
    bigInteger d;
    bigInteger x;
    bigInteger y;
    triple(bigInteger x1,bigInteger x2,bigInteger x3){d=x1;x=x2;y=x3;}
};
triple inverse(bigInteger a,bigInteger b,bigInteger N){
    bigInteger x(0);
    triple t(bigInteger(0),bigInteger(0),bigInteger(0));
    if(b==bigInteger(0))
        return triple(bigInteger(a),bigInteger(1),bigInteger(0));
    else
        t=inverse(b,a%b,N);
    triple tt(t.d,t.y,t.x-(a/b)*t.y);
    if(tt.x<bigInteger(0))
        tt.x+=N;
    return tt;
}
bigInteger gcd(bigInteger a,bigInteger b){
    bigInteger aa(0);
    if(b==bigInteger(0))
        return a;
    else
        aa=gcd(b,a%b);
    return aa;
}
void linsolve(const bigInteger& a, const bigInteger& b, const bigInteger& n)
{
    bigInteger nwd=gcd(a,n);
    if(b%nwd!=bigInteger(0))
        cout<<"SOLUTION DOES NOT EXIST"<<endl;
    else {
        bigInteger i(1);
        bigInteger a1=a/nwd;
        bigInteger b1=b/nwd;
        bigInteger n1=n/nwd;
        bigInteger x=((inverse(a1, n1, n1).x)*b1)%n1;
        cout<<x<<endl;
        while(i<nwd) {
            x=x+n1;
            cout << x << endl;
            i=i+1;
        }
    }

}
int main()
{
    linsolve(12,28,64);
}
