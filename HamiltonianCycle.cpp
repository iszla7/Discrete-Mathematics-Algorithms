
#include <iostream>
#include <list>

using namespace std;

const int N = 8;
list <int> adj_list[N+1];

bool ALLOWED[N + 1];

int X[N + 1];                  // X[1..k] contains path X[1],X[2],...,X[k]

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
            if(ALLOWED[u]){
                X[k]=u;
                ALLOWED[u]=false;
                if(hamilton_cycle(k+1))
                    return true;
                ALLOWED[u]=true;
            }
        }
        return false;
    }
}



/* This function finds the example of Hamiltonian cycle starting
 in start_vertex or informs that such cycle does not exist*/

void find_hamilton_cycle(int start_vertex)
{
    for(int ii=1;ii<=N;ii++){
        ALLOWED[ii]=true;
    }
    ALLOWED[start_vertex]=false;
    X[1]=start_vertex;
    bool flag=hamilton_cycle(2);
    if(flag) {
        for (int i = 1;i<=N;i++){
            cout<<X[i]<<" ";
        }
        cout<<X[1]<<endl;
    }
    else{
        cout<<"HAMILTONIAN CYCLE DOES NOT EXIST"<<endl;
    }
}


int main()
{
    construct_graph();
    find_hamilton_cycle(4);
    return 0;
}