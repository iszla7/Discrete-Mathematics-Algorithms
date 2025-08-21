#include <iostream>
#include <list>
#include <vector>
#include <fstream>
using namespace std;
//MATHEMATICAL MODEL
/*
The problem given in the task boils down to the problem of coloring the vertices of an undirected graph
and finding the largest (in terms of number of vertices) subgraph that is a clique.
The waste items are identified as vertices of an undirected graph. The fact that wastes a and b cannot be transported together
means that there is an edge between a and b in the graph.
Therefore, the problem of finding the minimum number of trucks needed to remove the waste reduces to finding the chromatic number of the graph.
The problem of finding an example allocation of waste to trucks becomes the problem of finding an example graph coloring.
The problem of finding the size and an example of the largest dangerous configuration becomes the problem of finding the size
and an example of the largest complete subgraph (clique).
*/

vector<int> maximum_clique;//vector for storing the maximal dangerous configuration (clique)
//Function to check whether a vertex can be colored with a given color

bool CanBeColored(int color,int* colors,int k,const list<int>* adj_list){
    for(int u:adj_list[k]){ //go through the adjacency list and check whether any adjacent vertex (from 1,...,k-1) is already colored with the same color
        if(u<k&&colors[u]==color) {
            return false;
        }
    }
    return true;
}
//Function to check if the graph can be colored

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

//Function that checks whether vertex v creates a clique with already added vertices
//(only checking whether edges exist between this vertex and already added ones,
//because recursive calls guarantee that previously added vertices form a clique)
bool Check(int v,bool* clique,const list<int>* adj_list,int N){
    for(int i=1;i<N+1;i++){
        if(clique[i] && find(adj_list[v].begin(),adj_list[v].end(),i) == adj_list[v].end())
            return false;
    }
    return true;
}

//General idea of the below algorithm
/*
Since vertices connected by an edge cannot be colored with the same color, when I add a vertex of color i to the current clique,
I can no longer add any other vertex of the same color.
So in each recursive step, I go through all vertices of the current color and check whether the vertex forms a clique
with already added vertices using the helper function Check.
Then I recursively call the function for color+1 and number of vertices n+1 and check whether the obtained result is greater than the current maximum.
I check whether the current clique is larger than the previously found maximum clique, and if it is, I save it into a special vector.
I mark the current vertex as false to remove it from the current clique, in order to check sizes of cliques formed by other vertices of the same color.
It might also happen that the maximum clique contains, for example, vertices with colors 1,2,4,...
So, at the end of the function I check whether the already found maximum is smaller than the sum of remaining colors
and the number of vertices in the current clique
(because the maximum size of a clique obtainable in the function call for number of vertices n and color+1 is
no_of_colors - color + n, so if max is already >= this, further recursion doesn't make sense)
*/
int FindMaxClique(int no_of_colors,int N,bool* clique,int color,int n,vector<vector<int>> coloring,const list<int>* adj_list){
    int M=0;
    if(color>no_of_colors)
        return 0;
    for(int j=0;j<coloring[color].size();j++){
        if(Check(coloring[color][j],clique,adj_list,N)) {
            clique[coloring[color][j]] = true;
            int m1=FindMaxClique(no_of_colors,N,clique,color+1,n+1,coloring,adj_list);
            m1=max(n+1,m1);
            M=max(M,m1);
            if(M>maximum_clique.size()){
                vector<int> v;
                for(int i=1;i<N+1;i++){
                    if(clique[i])
                        v.push_back(i);
                }
                maximum_clique=v;
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

    fstream f;
    f.open("/Users/iszla/Discrete-Mathematics-Algorithms/data.txt,ios::in);
    string s;
    if(f.is_open()) {
        getline(f, s);

        int N=0;
        for (char c : s){
            if (c >= '0' && c <= '9') {
                N = N * 10 + (c - '0');
            }
        }

        list<int> adj_list[N + 1];
        while(getline(f, s)){
            int a=0;
            int b=0;
            string v1="";
            string v2="";
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

            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }
        f.close();
        int* colors = new int[N + 1];
        vector <vector<int>> v;
        vector<int> vv;
        v.push_back(vv);
        for (int i = 1; i <= N; i++) {
            vector<int> vv;
            v.push_back(vv);//add rows until a proper coloring is found
            if (isColorable(i, colors, N, adj_list)){//check if the graph can be colored with i colors (0 <= i <= N)
                //if it can be colored, print the coloring and store it in the vector so that row i contains all vertices colored with color i
                for(int c=1;c<=i;c++){
                    cout << c << ": ";
                    for(int i=1;i<=N;i++){
                        if(colors[i]==c) {
                            v[c].push_back(i);
                            cout << i <<" ";
                        }
                    }
                    cout << endl;
                }

                bool* tab=new bool[N+1];
                for(int j=1;j<N+1;j++)
                    tab[j]=false;
                cout<<"Maximum clique has "<<FindMaxClique(i,N,tab, 1,0, v, adj_list)<<" vertices"<<endl;
                cout<<"Example of such clique: ";
                for(int k=0;k<maximum_clique.size();k++) {
                    cout <<maximum_clique[k]<< " ";
                }
                cout<<endl;
                delete[] tab;
                break;
            }
        }
        delete[] colors;
    }
}
