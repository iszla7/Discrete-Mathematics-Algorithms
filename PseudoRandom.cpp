#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Funkcja ma generowac ciag liczb pseudolosowych o dlugosci seqLength
// wg. algorytmu podanego na zajeciach.

string pseudorandomSeq(long a, long c, long modulus, long seed, int seqLength)
{
    string s="";//obiekt typu string do którego wpisuję kolejne elementy ciągu
    for(int i=0;i<seqLength;i++){//w każdej iteracji pętli tworzę nową liczbę za pomocą wzoru z notatek i dodaję do zwracanego obiektu typu string
        seed=(a*seed+c)%modulus;
        s.append(to_string(seed)+" ");
    }
    return s;
}
//ta funkcja "zwiększa losowość" biorąc tylko najmniej znaczące 15 bitów(ma to znaczenie tylko jak a i m są dość duże)
string morepseudorandomSeq(long a, long c, long modulus, long seed, int seqLength)
{
    string s="";
    long x=pow(2,15)-1;//liczba która w reprezentacji binarnej wygląda w ten sposób: 111111111111111.Czyli składa się z 15 jedynek.Korzystam z niej dla tego żeby wziąć 15 najmniej znaczących bitów z liczby
    for(int i=0;i<seqLength;i++){
        seed=(a*seed+c)%modulus;
        s.append(to_string(seed&x) + " ");//jedyne zmiany w porównaniu do funckji pseudorandomSeq następują tutaj(bo do stringa wpisuje tylko 15 najmniej znaczących bitów liczby)
    }
    return s;
}
int main()
{
    long a,c,modulus,seed;
    int l;//długość ciągu
    int n;//ilość zestawów danych
    cin>>n;
    ofstream f;
    f.open("wynik.txt");
    for(int i=0;i<n;i++) {
        cin >> a >> c >> modulus >> seed >> l;//wczytuje zestaw danych dla kolejnych ciągów
        f<<pseudorandomSeq(a, c, modulus, seed, l)<<endl;//generuje ciąg liczb pseudolosowych
        f<<morepseudorandomSeq(a, c, modulus, seed, l)<<endl;//te same liczby ale program zwraca tylko najmniej znaczące 15 bity dla każdej z liczb
    }
    f.close();
}
