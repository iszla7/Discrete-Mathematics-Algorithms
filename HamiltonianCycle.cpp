
#include <iostream>
#include <list>

using namespace std;

const int N = 8;              // liczba wierzcholkow
list <int> adj_list[N+1];     // listy sasiedztwa. Wierzcholki NUMERUJEMY OD 1

bool DOPUSZCZALNE[N + 1];

int X[N + 1];                  // X[1..k] zawiera sciezke X[1],X[2],...,X[k]

void add_edge (int u,int v)
{
    adj_list[u].push_back(v);adj_list[v].push_back(u);
}


void construct_graph()
{
    add_edge(1, 4);add_edge(1, 5);add_edge(1, 7);add_edge(1, 8);
    add_edge(2, 3);add_edge(2, 4);add_edge(2, 5);add_edge(2, 6);add_edge(2, 7);
    add_edge(3, 8);
    add_edge(4, 7);add_edge(4, 8);
    add_edge(5, 6);add_edge(5, 8);
    add_edge(7, 8);
}


bool hamilton_cycle(int k)
{
    if(k==N+1){
        return find(adj_list[X[1]].begin(),adj_list[X[1]].end(),X[N])!=adj_list[X[1]].end();
    }
    else{
        for(int u:adj_list[X[k-1]]){
            if(DOPUSZCZALNE[u]){
                X[k]=u;
                DOPUSZCZALNE[u]=false;
                if(hamilton_cycle(k+1))
                    return true;
                DOPUSZCZALNE[u]=true;
            }
        }
        return false;
    }
}



// Ponizsza funcja wypisuje przykladowy cykl Hamiltona rozpoczynajacy
// sie od start_vertex lub informuje, ze takowego nie ma.

void find_hamilton_cycle(int start_vertex)
{
    for(int ii=1;ii<=N;ii++){
        DOPUSZCZALNE[ii]=true;
    }
    DOPUSZCZALNE[start_vertex]=false;
    X[1]=start_vertex;
    bool flag=hamilton_cycle(2);
    if(flag) {
        for (int i = 1;i<=N;i++){
            cout<<X[i]<<" ";
        }
        cout<<X[1]<<endl;
    }
    else{
        cout<<"NIE MA CYKLU HAMILTONA"<<endl;
    }
}


int main()
{
    construct_graph();
    find_hamilton_cycle(4);
    return 0;
}