#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

string pseudorandomSeq(long a, long c, long modulus, long seed, int seqLength)
{
    string s="";
    for(int i=0;i<seqLength;i++){
        seed=(a*seed+c)%modulus;
        s.append(to_string(seed)+" ");
    }
    return s;
}
//this function "boosts randomness" using only 15 bits(is important only if a and m are large)
string morepseudorandomSeq(long a, long c, long modulus, long seed, int seqLength)
{
    string s="";
    long x=pow(2,15)-1;
    for(int i=0;i<seqLength;i++){
        seed=(a*seed+c)%modulus;
        s.append(to_string(seed&x) + " ");
    }
    return s;
}
int main()
{
    long a,c,modulus,seed;
    int l;
    int n;
    cin >> n;
    ofstream f;
    f.open("wynik.txt");
    for(int i=0;i<n;i++) {
        cin >> a >> c >> modulus >> seed >> l;
        f<<pseudorandomSeq(a, c, modulus, seed, l)<<endl;
        f<<morepseudorandomSeq(a, c, modulus, seed, l)<<endl;
    }
    f.close();
}
