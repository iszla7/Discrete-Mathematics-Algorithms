#include <iostream>
using namespace std;
/*biezacy podzial przechowywuje w tablicy 2_wymiarowej
 w tab[0][0] jest przechowywana ilosc podzbiorow w biezacym podziale
 dla 1<=i<=tab[0][0] w tab[i][0] przechowywuje ilosc elementow w tym podzbiorze(kazdy wiersz odpowiada za podzbior podziala)
 w pozostalych komorkach wierzu przechowywane sa elementy podzbioru i
 */
void ff(int** tab,int n,int N){
    //jesli wszystkie liczby ze zbioru {1,...,N} zostaly dodane drukuje podzial i wychodze z rekurencji(baza rekurencji)
    if(n-1==N){//porownuje z n-1 z N bo zawsze przesylam w rekurencyjnych wywolaniach n+1(element do dodawania do podzialu) wiec skoro przypadek bazowy mam na poczatku funkcji jak dodam N do podzialu to przesle N+1
        for(int i=1;i<=tab[0][0];i++){//ilosc podzbiorow w tym podziale
            cout<<"{";
            for(int h=1;h<tab[i][0];h++)//ilosc elementow w podzbiorze
                cout << tab[i][h] << ",";
            cout<<tab[i][tab[i][0]]<<"}";
        }
        cout<<endl;
        return;//wychodze z rekurencji
    }
    //przypadek a
    //dodaje element n jako singleton do podzialu
    tab[0][0]++;//zwiekszam ilosc podzbiorow
    tab[tab[0][0]][0]++;//zwiekszam ilosc elementow w dodanym podzbiorze(bedzie 1 skoro dodaje singleton)
    tab[tab[0][0]][1]=n;//w wiersz odpowiadajacym dodanemu podzbiorowi wpisuje element singletona ktory dodalam
    ff(tab,n+1,N);//rekurencyjnie wywoluje funcje dalej zeby wygenerowalo mi podzial do konca
    //usuwam z podzialu dodany singleton zeby miec taki jak mialam przed ta czescia programu
    tab[tab[0][0]][1]=0;
    tab[tab[0][0]][0]--;
    tab[0][0]--;
    //przypadek b
    //dla kazdego podzbioru biezacego podzialu dodaje po kolei element n i puszczam rekurencyjnie funkcje zeby wygenerowac odpowiedni podzial do konca
    for(int i=1;i<=tab[0][0];i++){
        tab[i][0]++;//zwiekszam ilosc elementow w podzbiorze o 1
        tab[i][tab[i][0]]=n;//dodaje element na koniec podzbioru
        ff(tab,n+1,N);//rekurencyjne wywolanie funkcji
        //usuwam z podzbiora dodany element zeby w nastepnej iteracji element n nalezal !tylko! do jednego podzbioru
        tab[i][tab[i][0]]=0;
        tab[i][0]--;
    }
}
int main(){
    int N;
    cin>>N;
    //tablica do przechowywania podzialu
    int** TAB=new int*[N+1];
    for(int i=0;i<N+1;i++){
        TAB[i]=new int[N+2];
        for(int h=0;h<N+1;h++)
            TAB[i][h]=0;
    }
    ff(TAB,1,N);
    for(int i=0;i<N+1;i++)
        delete[] TAB[i];
    delete[] TAB;
}