#include <fstream>
#include <iostream>
#include <gmpxx.h>
#include <vector>
#include <cmath>
using bigInteger = mpz_class;
using namespace std;
//funkcja obliczająca M^e mod N (gdzie M to przesyłana wiadomość, (N,e)-klucz publiczny)
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
//funkcja dzieląca tekst z tekstu wpisanego do s na bloki o dlugości co najwyzej k(ostatni może być krótszy) i zwraca wektor ,w którym każdy element odpowiada pewnemu bloku danych
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
    //część odpowiadająca za wczytywanie danych z pliku
    string s="";//string dla przechowywania tekstu z pliku
    string linia="";//pomoczniczy string żeby wczytywać kolejne linii z pliku
    fstream plik_wczytywanie_danych;
    plik_wczytywanie_danych.open("/Users/iszla/CLionProjects/dyskretna/input.txt");//otwieram plik
    if(plik_wczytywanie_danych.is_open()) {//jeśli plik się otworzył
        while (getline(plik_wczytywanie_danych, linia)) {//wczytuje kolejne linie
            s = s + linia;//dopisuje do calości
        }
    }
    plik_wczytywanie_danych.close();//zamykam plik
    //----------------------------------------------------
    int m=4;//dlugosc wczytywanych blokow
    //dane dla k ostatnich losowanych bitow
    int k=5;
    int zakres_losowania=pow(10,k);//pózniej będę losować za pomocą komendy rand()%zakres_losowania liczby 5-elementowe żeby dodawać na koniec linii
    //-------------------
    //klucz publiczny
    bigInteger N("1125907426181141");
    bigInteger e(65537);
    //-------------------
    vector <string> v=divide_str(s,m);//dziele wczytany tekst na bloki i wszystkie te bloki przechowuje w wektorze
    ofstream plik_zaszyfrowane_dane;
    plik_zaszyfrowane_dane.open("/Users/iszla/CLionProjects/dyskretna/output.txt");//otwieram plik do wypisywania danych zaszyfrowanych
    for(int i=0;i<v.size();i++){//dopóki wszystkie bloki nie zostaną zaszyfrowane
        string M="";//string do ktorego wpisuje ten blok w postaci liczby(każdej literze odpowiada pewna liczba)
        for(int h=0;h<v[i].size();h++){//w tej pętli przerabiam tekst na liczbę
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
        bigInteger MM(M);//tworze liczbe bigInteger z tego obiektu typu string w którym przepisany jest tekst w postaci liczby
        int ostatnie_k_losowanych_cyfr=rand() % zakres_losowania;//losuje k-cyfrową liczbę żeby dodac na koniec zaszyfrowanego bloku
        plik_zaszyfrowane_dane <<powermod(MM,e,N)<<ostatnie_k_losowanych_cyfr<<endl;//wypisuje do pliku zaszyfrowany za pomocą funkcji powermod blok(M^e  mod N) oraz k-elementową losową liczbę
    }
    plik_zaszyfrowane_dane.close();//zamykam plik
}

