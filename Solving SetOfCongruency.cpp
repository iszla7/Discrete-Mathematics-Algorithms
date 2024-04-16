#include <iostream>
#include <gmpxx.h>

using bigInteger = mpz_class;
using namespace std;

struct trojka{
    bigInteger d;
    bigInteger x;
    bigInteger y;
    trojka(bigInteger x1,bigInteger x2,bigInteger x3){d=x1;x=x2;y=x3;}
};
trojka odwrotny(bigInteger a,bigInteger b,bigInteger N){
    bigInteger x(0);
    trojka t(bigInteger(0),bigInteger(0),bigInteger(0));
    if(b==bigInteger(0))
        return trojka(bigInteger(a),bigInteger(1),bigInteger(0));
    else
        t=odwrotny(b,a%b,N);
    trojka tt(t.d,t.y,t.x-(a/b)*t.y);
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
        cout<<"BRAK ROZWIĄZAŃ"<<endl;
    else {
        bigInteger i(1);
        bigInteger a1=a/nwd;
        bigInteger b1=b/nwd;
        bigInteger n1=n/nwd;
        bigInteger x=((odwrotny(a1, n1, n1).x)*b1)%n1;
        cout<<x<<endl;
        while(i<nwd) {
            x=x+n1;
            cout << x << endl;
            i=i+1;
        }
    }

}
void crt(bigInteger a[], bigInteger n[], int k)
{
    bool flag=true;
    bigInteger nww(1);
    bigInteger nwwp(1);
    for(int i=0;i<k-1;i++){
        for(int j=i+1;j<k;j++){
            bigInteger d=gcd(n[i],n[j]);
            if((a[i]-a[j])%d!=bigInteger(0)){
                flag=false;
                break;
            }
            bigInteger pom=n[i]*n[j]/d;
            nww=pom*nwwp/gcd(pom,nwwp);
            nwwp=nww;
        }
        if(!flag)
            break;
    }
    if(!flag){
        cout<<"UKŁAD JEST SPRZECZNY"<<endl;
    }
    else{
        bigInteger* b=new bigInteger[k];
        bigInteger* y=new bigInteger[k];
        bigInteger m(0);
        for(int i=0;i<k;i++){
            b[i]=odwrotny((nww/n[i]),n[i],n[i]).x;
            y[i]=b[i]*(nww/n[i]);
            m=m+a[i]*y[i];
        }
        linsolve(1,m,nww);
    }
}

int main()
{
    const int k = 5;
    bigInteger a[k];
    bigInteger n[k];

    // Dane z zadania:

    a[0] = bigInteger("17");
    a[1] = bigInteger("15");
    a[2] = bigInteger("7");
    a[3] = bigInteger("5");
    a[4] = bigInteger("45");
    n[0] = bigInteger("13111");
    n[1] = bigInteger("225");
    n[2] = bigInteger("13");
    n[3] = bigInteger("19");
    n[4] = bigInteger("9999991");

    crt(a, n, k);
}
