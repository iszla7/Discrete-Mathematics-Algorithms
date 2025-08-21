#include <fstream>
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

bigInteger powermod(bigInteger M,bigInteger d,bigInteger N){
    bigInteger z=M%N;
    bigInteger m=d;
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
int main(){
    //public key
    bigInteger N("1125907426181141");
    bigInteger e(65537);
    //-------------------
    bigInteger p("1048583");
    bigInteger q("1073741827");
    bigInteger phiN=(p-1)*(q-1);
    //private key
    bigInteger d=inverse(e,phiN,phiN).x;
    //----------------------
    //data for decryption
    bigInteger encrypted_M1("58467865012426");
    bigInteger encrypted_M2("930815517522533");
    //------------------------
    bigInteger M1=powermod(encrypted_M1,d,N);
    bigInteger M2=powermod(encrypted_M2,d,N);
    ofstream decrypted_data;
    decrypted_data.open("/Users/iszla/Discrete-Mathematics-Algorithms/output.txt");
    string M="";
    while(M1>0){
        bigInteger m=M1%100;
        M1/=100;
        if(m==10){
            M='A'+M;
        }
        else if(m==11){
            M='B'+M;
        }
        else if(m==12){
            M='C'+M;
        }
        else if(m==13){
            M='D'+M;
        }
        else if(m==14){
            M='E'+M;
        }
        else if(m==15){
            M='F'+M;
        }
        else if(m==16){
            M='G'+M;
        }
        else if(m==17){
            M='H'+M;
        }
        else if(m==18){
            M='I'+M;
        }
        else if(m==19){
            M='J'+M;
        }
        else if(m==20){
            M='K'+M;
        }
        else if(m==21){
            M='L'+M;
        }
        else if(m==22){
            M='M'+M;
        }
        else if(m==23){
            M='N'+M;
        }
        else if(m==24){
            M='O'+M;
        }
        else if(m==25){
            M='P'+M;
        }
        else if(m==26){
            M='Q'+M;
        }
        else if(m==27){
            M='R'+M;
        }
        else if(m==28){
            M='S'+M;
        }
        else if(m==29){
            M='T'+M;
        }
        else if(m==30){
            M='U'+M;
        }
        else if(m==31){
            M='V'+M;
        }
        else if(m==32){
            M='W'+M;
        }
        else if(m==33){
            M='X'+M;
        }
        else if(m==34){
            M='Y'+M;
        }
        else if(m==35){
            M='Z'+M;
        }
        else if(m==36){
            M=' '+M;
        }
    }
    decrypted_data << M;
    M="";
    while(M2>0){
        bigInteger m=M2%100;
        M2/=100;
        if(m==10){
            M='A'+M;
        }
        else if(m==11){
            M='B'+M;
        }
        else if(m==12){
            M='C'+M;
        }
        else if(m==13){
            M='D'+M;
        }
        else if(m==14){
            M='E'+M;
        }
        else if(m==15){
            M='F'+M;
        }
        else if(m==16){
            M='G'+M;
        }
        else if(m==17){
            M='H'+M;
        }
        else if(m==18){
            M='I'+M;
        }
        else if(m==19){
            M='J'+M;
        }
        else if(m==20){
            M='K'+M;
        }
        else if(m==21){
            M='L'+M;
        }
        else if(m==22){
            M='M'+M;
        }
        else if(m==23){
            M='N'+M;
        }
        else if(m==24){
            M='O'+M;
        }
        else if(m==25){
            M='P'+M;
        }
        else if(m==26){
            M='Q'+M;
        }
        else if(m==27){
            M='R'+M;
        }
        else if(m==28){
            M='S'+M;
        }
        else if(m==29){
            M='T'+M;
        }
        else if(m==30){
            M='U'+M;
        }
        else if(m==31){
            M='V'+M;
        }
        else if(m==32){
            M='W'+M;
        }
        else if(m==33){
            M='X'+M;
        }
        else if(m==34){
            M='Y'+M;
        }
        else if(m==35){
            M='Z'+M;
        }
        else if(m==36){
            M=' '+M;
        }
    }
    decrypted_data << M << endl;
    decrypted_data.close();
}