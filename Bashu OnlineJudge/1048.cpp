#include<iostream>
#include<cstdio>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    int L,M;
    cin>>L>>M;
    int l[L+1];
    for(int i=0;i<L+1;i++)
    {   l[i]=1;}
    int a[M][2];
    for(int i=0;i<M;i++)
    {   for(int j=0;j<2;j++)
        {   cin>>a[i][j];}}
    for(int i=0;i<M;i++)
    {   for(int j=a[i][0];j<=a[i][1];j++)
        {   l[j]=0;}}
    int num=0;
    for(int i=0;i<L+1;i++)
    {   if(l[i]==1)num++;}
    cout<<num<<endl;
    return 0;
}