#include <iostream>
#include <gmpxx.h>
#include <chrono>
using namespace std;
using bigInteger = mpz_class;
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
int main()
{
    double tt;
    cin>>tt;
    chrono::time_point<chrono::system_clock> start, end;
    int n=0;
    bigInteger fp(0);
    bigInteger fi=1;
    while(true){
        start=chrono::system_clock::now();
        eGCD(fp,fi);
        end=chrono::system_clock::now();
        chrono::duration<double> d=end-start;
        if(d.count()>tt) {
            cout<<"F_"<<n-1<<" = "<<fp<<endl;
            cout<<"F_"<<n<<" = "<<fi<<endl;
            break;
        }
        bigInteger t=fi;
        fi=fp+fi;
        fp=t;
        n++;
    }
}
