#include <iostream>
#include <list>
#include <vector>
#include <fstream>
using namespace std;
//MODEL MATEMATYCZNY
/*
Problem podany w zadaniu sprowadza się do problemu kolorowania wierzchołków grafa nieskierowanego oraz szukanie najwiekszego(względem ilości wierzchołków) podgrafu, który jest kliką.
Odpady identyfikuję jako wierzchołki grafu nieskierowanego,ten fakt,że odpady a i b nie mogą byc przewożone razem, identyfikuje jako to, że w grafie istenieje krawędż ab.
 Więc, problem znalezienia minimalnej liczby samochodów potrzebnych dla wywożenia odpadów sprowadza się do znalezienia liczby chromatycznej grafu,problem znalezienia przykładowego
 przydziału odpadów do samochodów sprowadza się do znalezienia przykładowego kolorowania grafu.
 Natomiast problem wyszukiwania rozmiaru oraz przykładu największego niebiezpiecznego układu sprowadza się do wyszukiwania rozmiaru oraz przykładu największego podgrafa zupenego.

 */
vector<int> maksymalny_niebiezpieczny_uklad;//wektor dla przechowywania maksymalnego niebiezpiecznego układu(kliki)
//funkcja do sprawdzenia czy można pokolorować podany wierzchołek podanym kolorem
bool CanBeColored(int color,int* colors,int k,const list<int>* adj_list){
    for(int u:adj_list[k]){//przechodzę po liście sąsiedztwa i sprawdzam czy jakiś wierzchołek sąsiedni z wierzchołkiem k ze zbioru {1,...,k-1} jest pokolorowany tym samym kolorem
        if(u<k&&colors[u]==color) {
            return false;
        }
    }
    return true;
}
//funckje z pliku do sprawdzenia czy da sie pokolorować graf
bool colorGraph(int k,int no_of_cols,int* colors,int N,const list<int>* adj_list){
    if(k==N+1)
        return true;
    for(int col=1;col<=no_of_cols;col++){
        if(CanBeColored(col,colors,k,adj_list)){
            colors[k] = col;
            if (colorGraph(k + 1, no_of_cols, colors, N, adj_list)) {
                return true;
            }
        }
    }
    return false;
}
bool isColorable(int no_of_cols,int* colors,int N,const list<int>* adj_list){
    colors[1]=1;
    for(int i=2;i<=N;i++){
        colors[i]=0;
    }
    return colorGraph(2,no_of_cols,colors,N,adj_list);
}
//=====================================================
//funckja sprawdzająca czy wierzchołek v tworzy klikę z już dodanymi do kliki wierzchołkami(sprawdzam tylko czy istnieją krawędzi między tym wierzchołkiem i już dodanymi wierżchołkami,bo skoro wywołuję funkcje rekurencyjnie to wiem że dodanę wcześniej wierzchołki tworzą klikę)
bool Check(int v,bool* klika,const list<int>* adj_list,int N){
    for(int i=1;i<N+1;i++){
        if(klika[i]&&find(adj_list[v].begin(),adj_list[v].end(),i)==adj_list[v].end())
            return false;
    }
    return true;
}
//ogólna idea poniższego algorytmu
/*
 skoro wierzchołki polączone krawędzią nie mogą byc pokolorowane tym samy kolorem więc jak dodaje do bieżacej kliki wierzchołek kolora i to już nie mogę dodać żadnego wierzchołku w tym samym kolorze.
 Więc w kazdym kroku rekurencyjnym przechodzę po wszystkich wierzchołkach w kolorze color i sprawdzam czy ten wierzchołek tworzy z już dodanymi wierzchołkami bieżacej kliki za pomocą pomocniczej funkcji Check.
 Dalej rekurencyjnie wywołuję funkcję dla koloru (color+1) i ilości wierzchołków (n+1) i sprawdzam czy otrzymany wynik jest większy niż rozmiar bieżącej kliki oraz czy udało się otrzymać coś większe niż bieżący maks.
 Spawdzam czy bieżąca klika ma rozmiar większy niż poprzednia maksymalna i jeśli tak jest to przepisuje tą klikę do specjalnego wektora.
 Oznaczam bieżacy wierzchołek jako false tym samym usuwając go z bieżacej kliki,żeby sprawdzić rozmiary klik tworzonych za pomocą innych wierzchołków w tym samym kolorze.
 Może też zajśc sytuacja taka że maksymalną klika zawiera naprzykład wierzchołki w kolorach 1,2,4,...Więc,na końcu funckji sprawdzam czy uzyskany już maks jest mniejszy niż
 suma ilości kolorów większych od bieżącego oraz ilości wierzchołków w bieżacej klicę(bo rozmiar maksymalnej kliki,który można uzyskać w wywołaniu funkcji dla ilości wierzchołków n i
 koloru (color+1), jest równa no_of_colors-(color+1)+1+n=no_of_colors-color+n,więc jesli max jest większy lub równy tej liczbie to nie ma sensu w tym wywołaniu)
 */
int FindMaxClique(int no_of_colors,int N,bool* clique,int color,int n,vector<vector<int>> coloring,const list<int>* adj_list){
    int M=0;
    if(color>no_of_colors)//baza rekurencji
        return 0;
    for(int j=0;j<coloring[color].size();j++){
        if(Check(coloring[color][j],clique,adj_list,N)) {
            clique[coloring[color][j]] = true;
            int m1=FindMaxClique(no_of_colors,N,clique,color+1,n+1,coloring,adj_list);
            m1=max(n+1,m1);
            M=max(M,m1);
            if(M>maksymalny_niebiezpieczny_uklad.size()){
                vector<int> v;
                for(int i=1;i<N+1;i++){
                    if(clique[i])
                        v.push_back(i);
                }
                maksymalny_niebiezpieczny_uklad=v;
            }
            clique[coloring[color][j]]=false;
        }
    }
    if(M<no_of_colors-color+n) {
        int m2 = FindMaxClique(no_of_colors, N, clique, color + 1, n, coloring, adj_list);
        M=max(M,m2);
    }
    return M;
}
int main() {
    //część, odpowiadająca za wczytywanie danych z pliku
    fstream f;
    f.open("dane.txt",ios::in);//otwieram plik w trybie wczytywania
    string s;
    if(f.is_open()) {//jesli plik sie otworzył to wczytuję dane z pliku i puszczam dla tych danych program
        getline(f, s);
        //wczytywanie liczby wierzchołków
        int N=0;
        for (char c : s){
            if (c >= '0' && c <= '9') {
                N = N * 10 + (c - '0');
            }
        }
        //--------------------
        //wczytywanie krawędzi
        list<int> adj_list[N + 1];
        while(getline(f, s)){
            int a=0;
            int b=0;
            string v1="";//odpowiada za wirzchołek v1 w krawędzi v1v2
            string v2="";//odpowiada za wirzchołek v2 w krawędzi v1v2
            for(int i=0;i<s.size();i++){
                if(s[i]==' '){
                    v1.append(s,0,i);
                    v2.append(s,i+1,s.size()+1);
                    break;
                }
            }
            for (char c : v1) {
                if (c >= '0' && c <= '9') {
                    a = a * 10 + (c - '0');
                }
            }
            for (char c : v2) {
                if (c >= '0' && c <= '9') {
                    b = b * 10 + (c - '0');
                }
            }
            //dodaję do list sąsiedztwa otrzymane wierzcholki
            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }
        f.close();//zamykam plik
        int* colors = new int[N + 1];//tablica do przechowywania kolorów wierzchołków
        vector <vector<int>> v;//wektor dwuwymiarowy dla przechowywania kolorowania(przyda sie póżniej)Każdy wiersz odpowiada koloru
        vector<int> vv;
        v.push_back(vv);
        for (int i = 1; i <= N; i++) {
            vector<int> vv;
            v.push_back(vv);//dodaje wierszy do tego momentu jak nie otrzymam dobre kolorowanie
            if (isColorable(i, colors, N, adj_list)){//sprawdzam czy da się pokolorować graf za pomocą i kolorów(0<=i<=N)
                //jeśli się da pokolorować to wypisuje pokolorowanie w odpowiedni sposób oraz przepisuje do wektora w ten sposób, że w wierszu i znajdują sie wierzchołki pokolorowane w kolor i
                for(int c=1;c<=i;c++){
                    cout<<"Samochód "<<c<<": ";
                    for(int i=1;i<=N;i++){
                        if(colors[i]==c) {
                            v[c].push_back(i);
                            cout << i <<" ";
                        }
                    }
                    cout<<endl;
                }
                //pomocnicza tablica typu bool do przechowywania bieżącego niebiezpiecznego układu w funkcji znajdz_klike
                bool* tab=new bool[N+1];
                for(int j=1;j<N+1;j++)
                    tab[j]=false;//ustawiam wszystkie wartości na false bo na początku biezący układ ma być pusty;
                cout<<"Maksymalny niebiezpieczny układ ma "<<FindMaxClique(i,N,tab, 1,0, v, adj_list)<<" elementy"<<endl;//drukuje ilość wierzchołków w maksymalnym niebizepiecznym układzie
                cout<<"Przykładowy taki układ: ";
                for(int k=0;k<maksymalny_niebiezpieczny_uklad.size();k++) {//drukuje przykładowy układ
                    cout <<maksymalny_niebiezpieczny_uklad[k]<< " ";
                }
                cout<<endl;
                delete[] tab;
                break;
            }
        }
        delete[] colors;
    }
}
