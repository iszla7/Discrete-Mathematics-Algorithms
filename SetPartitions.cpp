#include <iostream>
using namespace std;
/*The ff method generates

/*current partion is kept in 2D array
 tab[0][0] is used to keep number of subsets in current partition
 for 1<=i<=tab[0][0] tab[i][0] is used to keep number of elements in subset
other cells are used to keep elements of subsets
 */
void ff(int** tab,int n,int N)
{
    if(n-1==N){
        for(int i=1;i<=tab[0][0];i++){
            cout<<"{";
            for(int h=1;h<tab[i][0];h++)
                cout << tab[i][h] << ",";
            cout<<tab[i][tab[i][0]]<<"}";
        }
        cout<<endl;
        return;
    }

    tab[0][0]++;
    tab[tab[0][0]][0]++;
    tab[tab[0][0]][1]=n;
    ff(tab,n+1,N);

    tab[tab[0][0]][1]=0;
    tab[tab[0][0]][0]--;
    tab[0][0]--;

    for(int i=1;i<=tab[0][0];i++){
        tab[i][0]++;
        tab[i][tab[i][0]]=n;
        ff(tab,n+1,N);

        tab[i][tab[i][0]]=0;
        tab[i][0]--;
    }
}
int main(){
    int N;
    cin>>N;

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