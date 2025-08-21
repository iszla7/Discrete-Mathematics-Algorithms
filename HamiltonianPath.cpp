
 #include <iostream>
#include <list>

using namespace std;
const int N = 10;

list <int> adj_list[N+1];      // Vertices labels start from 1

bool ALLOWED[N + 1];

int X[N + 1];                  // X[1..k] contains path X[1],X[2],...,X[k]



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
            if(ALLOWED[u]){
                X[k]=u;
                ALLOWED[u]=false;
                if(hamilton_path(k+1))
                    return true;
                ALLOWED[u]=true;
            }
        }
        return false;
    }
}




/* This function finds Hamiltonian path starting
 in start_vertex or informs that such cycle does not exist*/

void find_hamilton_path(int start_vertex){
    for(int ii=1;ii<=N;ii++){
        ALLOWED[ii]=true;
    }
    ALLOWED[start_vertex]=false;
    X[1]=start_vertex;
    bool flag=hamilton_path(2);
    if(flag) {
        for (int i = 1;i<=N;i++){
            cout<<X[i]<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"HAMILTONIAN PATH DOES NOT EXIST"<<endl;
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
