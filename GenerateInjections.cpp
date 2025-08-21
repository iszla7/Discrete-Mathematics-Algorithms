#include <iostream>
using namespace std;
int fact(int n){
    int fn=1;
    for(int i=2;i<=n;i++)
        fn*=i;
    return fn;
}
void nextpermutation(int n,int* tab){
    for(int i=0;i<n;i++)
        cout<<tab[i]<<" ";
    cout<<endl;
    int k,l;
    for(int i=0;i<n-1;i++){
        if(tab[i]<tab[i+1])
            k=i;
    }
    for(int i=k+1;i<n;i++){
        if(tab[i]>tab[k])
            l=i;
    }
    int a=tab[k];
    tab[k]=tab[l];
    tab[l]=a;
    for(int i=k+1;i<=(n-k)/2;i++) {
        a = tab[i];
        tab[i] =tab[n-i+k];
        tab[n-i+k]=a;
    }
}
void nextcomb(int N,int k,int* tab,int fn){
    //permutations
    int* tab1=new int[k];
    for(int g=0;g<k;g++){
        tab1[g]=tab[g];
    }
    for(int h=0;h<fn;h++) {
        nextpermutation(k, tab);
    }
    cout<<"---------"<<endl;
    for(int g=0;g<k;g++){
        tab[g]=tab1[g];
    }
    delete[] tab1;
    //new combination
    for(int i=k-1;i>=0;i--){
        if(tab[i]<N-k+i+1){
            tab[i]++;
            for(int j=i+1;j<k;j++)
                tab[j]=tab[j-1]+1;
            break;
        }
    }
}
int main(){
    int n,k;
    cin>>n>>k;
    if(k<n)
        cout<<"INJECTIVE MAP DOES NOT EXIST"<<endl;
    int fn=fact(n);
    int fk=fact(k);
    int fnk=fact(k-n);
    int komb=fk/(fn*fnk);
    int* tab=new int[k];
    for(int i=0;i<n;i++){
        tab[i]=i+1;
    }

    for(int i=0;i<komb;i++){
        nextcomb(k,n,tab,fn);
    }
    delete[] tab;
}
