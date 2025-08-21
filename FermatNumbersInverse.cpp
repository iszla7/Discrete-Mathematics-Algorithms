#include <iostream>
#include <gmpxx.h>
using namespace std;
using bigInteger = mpz_class;
//typedef mpz_class bigInteger;
class triple{
public:
    bigInteger d,x,y;
};
triple eGCD(bigInteger a,bigInteger b){
    triple t;
    if(b==0){
        triple ttt;
        ttt.d=a;
        ttt.x=bigInteger(1);
        ttt.y=bigInteger(0);
        return ttt;
    }
    else{
        t=eGCD(b,bigInteger(a%b));
    }
    triple tt;
    tt.d=t.d;
    tt.x=t.y;
    tt.y=t.x-a/b*t.y;
    return tt;
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
bigInteger inverse(bigInteger a,bigInteger n){
    triple t=eGCD(n,a);
    if(t.d!=bigInteger(1))
        return -1;
    else{
        if(t.y<0) {
            return t.y + bigInteger(n);
        }
        return t.y;
    }
}
int main() {
    int mm;
    cin >> mm;
    bigInteger m(mm);
    bigInteger i(0);
    bigInteger M(fastPower(bigInteger(2), fastPower(bigInteger(2), m)) + bigInteger(1));
    cout<<"F_"<<m<<" has "<< M.get_str().length() <<" digits"<< endl;
    while (i < m) {
        cout<<"Inverse F_"<<i<<" has ";
        bigInteger a1(fastPower(bigInteger(2), i));
        bigInteger fi(inverse(fastPower(bigInteger(2), a1) + bigInteger(1), M));
        cout << fi.get_str().length() <<" digits"<< endl;
        i++;
    }
}
