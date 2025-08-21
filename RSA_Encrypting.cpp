#include <fstream>
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <cmath>
using bigInteger = mpz_class;
using namespace std;
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

vector<string> divide_str(string s,int K){
    int N=s.size();
    int j=0;
    vector<string> result;
    string res="";
    while(j<N){
        res+=s[j];
        j++;
        if(res.size()==K||j==N) {
            result.push_back(res);
            res="";
        }
    }
    return result;
}
int main(){

    string s="";
    string str="";
    fstream input;
    input.open("/Users/iszla/Discrete-Mathematics-Algorithms/input.txt");
    if(input.is_open()) {
        while (getline(input, str)) {
            s = s + str;
        }
    }
    input.close();
    //----------------------------------------------------
    int m=4;

    int k=5;
    int scope = pow(10,k);
    //-------------------
    //public key
    bigInteger N("1125907426181141");
    bigInteger e(65537);
    //-------------------
    vector <string> v=divide_str(s,m);
    ofstream encrypted_data;
    encrypted_data.open("/Users/iszla/Discrete-Mathematics-Algorithms/output.txt");
    for(int i=0;i<v.size();i++){
        string M="";
        for(int h=0;h<v[i].size();h++){
            if(v[i][h]=='A'){
                M+="10";
            }
            else if(v[i][h]=='B'){
                M+="11";
            }
            else if(v[i][h]=='C'){
                M+="12";
            }
            else if(v[i][h]=='D'){
                M+="13";
            }
            else if(v[i][h]=='E'){
                M+="14";
            }
            else if(v[i][h]=='F'){
                M+="15";
            }
            else if(v[i][h]=='G'){
                M+="16";
            }
            else if(v[i][h]=='H'){
                M+="17";
            }
            else if(v[i][h]=='I'){
                M+="18";
            }
            else if(v[i][h]=='J'){
                M+="19";
            }
            else if(v[i][h]=='K'){
                M+="20";
            }
            else if(v[i][h]=='L'){
                M+="21";
            }
            else if(v[i][h]=='M'){
                M+="22";
            }
            else if(v[i][h]=='N'){
                M+="23";
            }
            else if(v[i][h]=='O'){
                M+="24";
            }
            else if(v[i][h]=='P'){
                M+="25";
            }
            else if(v[i][h]=='Q'){
                M+="26";
            }
            else if(v[i][h]=='R'){
                M+="27";
            }
            else if(v[i][h]=='S'){
                M+="28";
            }
            else if(v[i][h]=='T'){
                M+="29";
            }
            else if(v[i][h]=='U'){
                M+="30";
            }
            else if(v[i][h]=='V'){
                M+="31";
            }
            else if(v[i][h]=='W'){
                M+="32";
            }
            else if(v[i][h]=='X'){
                M+="33";
            }
            else if(v[i][h]=='Y'){
                M+="34";
            }
            else if(v[i][h]=='Z'){
                M+="35";
            }
            else if(v[i][h]==' '){
                M+="36";
            }
        }
        bigInteger MM(M);
        int last_k_random_digits = rand() % scope;
        encrypted_data << powermod(MM,e,N) << last_k_random_digits << endl;
    }
    encrypted_data.close();
}

