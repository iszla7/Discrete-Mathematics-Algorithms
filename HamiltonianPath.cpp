
 #include <iostream>
#include <list>

using namespace std;
const int N = 10;              // liczba wierzcholkow

list <int> adj_list[N+1];      // listy sasiedztwa. Wierzcholki NUMERUJEMY OD 1

bool DOPUSZCZALNE[N + 1];

int X[N + 1];                  // X[1..k] zawiera sciezke X[1],X[2],...,X[k]



void add_edge (int u,int v)
{
    adj_list[u].push_back(v);adj_list[v].push_back(u);
}


void construct_graph()
{
    add_edge(1, 2);add_edge(1, 5);add_edge(1, 6);
    add_edge(2, 3);add_edge(2, 7);
    add_edge(3, 4);add_edge(3, 8);
    add_edge(4, 5);add_edge(4, 9);
    add_edge(5, 10);
    add_edge(6, 8);add_edge(6, 9);
    add_edge(7, 9); add_edge(7, 10);
    add_edge(8, 10);
}
bool hamilton_path(int k)
{
    if(k==N+1){
        return true;
    }
    else{
        for(int u:adj_list[X[k-1]]){
            if(DOPUSZCZALNE[u]){
                X[k]=u;
                DOPUSZCZALNE[u]=false;
                if(hamilton_path(k+1))
                    return true;
                DOPUSZCZALNE[u]=true;
            }
        }
        return false;
    }
}




// Ponizsza funkcja powinna wypisywac na standardowe
// wyjscie sciezke Hamiltona rozpoczynajaca sie w wierzcholku
// start_vertex badź informować, że takowej nie ma.

void find_hamilton_path(int start_vertex)
{
        for(int ii=1;ii<=N;ii++){
            DOPUSZCZALNE[ii]=true;
        }
        DOPUSZCZALNE[start_vertex]=false;
        X[1]=start_vertex;
        bool flag=hamilton_path(2);
        if(flag) {
            for (int i = 1;i<=N;i++){
                cout<<X[i]<<" ";
            }
            cout<<endl;
        }
        else{
            cout<<"NIE MA ŚCIEŻKI HAMILTONA"<<endl;
        }
}
int main()
{
    construct_graph();
    for(int i=1;i<=N;i++){
        find_hamilton_path(i);
    }
    return 0;
}
