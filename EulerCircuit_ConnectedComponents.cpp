#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

const int N = 18;
list<int> adj_list[N+1];

void add_edge (int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}

void construct_graph()
{
    add_edge(1, 2); add_edge(1, 6); add_edge(1, 7); add_edge(1, 17);
    add_edge(2, 3); add_edge(3, 4); add_edge(4, 5);
    add_edge(5, 6); add_edge(5, 13); add_edge(5, 17);
    add_edge(6, 7); add_edge(6, 16);
    add_edge(7, 8); add_edge(7, 15);
    add_edge(8, 9); add_edge(8, 10); add_edge(8, 12);
    add_edge(9, 11); add_edge(10, 11); add_edge(12, 14);add_edge(13, 17);
    add_edge(14, 15); add_edge(15, 16); add_edge(15, 18);
    add_edge(16, 17); add_edge(16, 18);
}
vector<int> euler_circuit(int start_vertex){
    stack<int> stack;
    vector<int> v;
    stack.push(start_vertex);
    while(!stack.empty()){
        start_vertex=stack.top();
        if(!adj_list[start_vertex].empty()){
            int u=adj_list[start_vertex].back();
            stack.push(u);
            adj_list[u].remove(start_vertex);
            adj_list[start_vertex].remove(u);
        }
        else {
            stack.pop();
            v.push_back(start_vertex);
        }
    }
    return v;
}
void connected_components_division(int start_vertex){
    vector<int> v=euler_circuit(start_vertex);
    stack<int> temp;
    bool tab[N+1];
    for(int i=1;i<N+1;i++)
        tab[i]=0;
    int length=v.size();
    for(int i=0;i<length;i++){
        start_vertex=v[i];
        if(tab[start_vertex]){
            cout<<start_vertex<<" ";
            while(temp.top()!=start_vertex){
                cout<<temp.top()<<" ";
                tab[temp.top()]=0;
                temp.pop();
            }
            cout<<start_vertex<<endl;
        }
        else{
            temp.push(start_vertex);
            tab[start_vertex]=1;
        }
    }
}
int main()
{
    construct_graph();
    connected_components_division(3);
    return 0;
}
