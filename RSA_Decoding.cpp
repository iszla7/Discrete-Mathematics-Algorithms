#include <fstream>
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
//funkcja obliczająca M^d mod N (gdzie M to przesyłana wiadomość, (N,d)-klucz prywatny)
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
    //klucz publiczny
    bigInteger N("1125907426181141");
    bigInteger e(65537);
    //-------------------
    bigInteger p("1048583");
    bigInteger q("1073741827");
    bigInteger phiN=(p-1)*(q-1);
    //klucz prywatny
    bigInteger d=odwrotny(e,phiN,phiN).x;
    //----------------------
    //dane do deszyfrowania
    bigInteger zaszyfrowane_M1("58467865012426");
    bigInteger zaszyfrowane_M2("930815517522533");
    //------------------------
    bigInteger M1=powermod(zaszyfrowane_M1,d,N);
    bigInteger M2=powermod(zaszyfrowane_M2,d,N);
    ofstream plik_deszyfrowane_dane;
    plik_deszyfrowane_dane.open("/Users/iszla/CLionProjects/dyskretna/output.txt");//otwieram plik do wypisywania danych deszyfrowanych
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
    plik_deszyfrowane_dane<<M;
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
    plik_deszyfrowane_dane<<M<<endl;
    plik_deszyfrowane_dane.close();//zamykam plik
}