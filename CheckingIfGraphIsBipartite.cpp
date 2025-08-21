
#include <iostream>
#include <list>
#include <queue>
using namespace std;
const int N = 8;
list<int> adj_list[N+1];
int label[N+1];

void add_edge (int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

void construct_graph()
{
    add_edge(1, 2); add_edge(2 ,3);add_edge(3, 4);add_edge(4, 1);
    add_edge(7, 8); add_edge(8, 5);add_edge(5, 6);add_edge(6, 7);
    add_edge(4, 8); add_edge(1, 5);add_edge(2, 6);add_edge(3, 7);
}


void show_labels()
{
    for (int i=1; i<=N;++i)
        if (label[i] == 1)
            cout << i <<" ";

    cout << endl;

    for (int i=1;i<=N;++i)
        if (label[i] == 2)
            cout << i <<" ";
}

bool is_bipartite()
{
    for(int i=1;i<N+1;i++)
        label[i]=0;
    queue<int> q;
    int v=1;
    label[1]=1;
    q.push(v);
    while(!q.empty()){
        int u=q.back();
        q.pop();
        for(int vv:adj_list[u]){
            if (label[u]==label[vv]) {
                return false;
            }
            if(label[vv]==0){
                if(label[u]==1)
                    label[vv]=2;
                else
                    label[vv]=1;
                q.push(vv);
            }
        }
    }
    return true;
}


int main()
{
    construct_graph();

    if (is_bipartite())
    {
        cout << "Graph is bipartite. Group division: " << endl;
        show_labels();
    }
    else
        cout << "Graph is not bipartite.";

    return 0;
}
