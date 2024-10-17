#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int g[1001][1001];
int main(){  
    int n,k;
    int i,j;
    cin>>n>>k;
    for(i=0;i<n;i++)
   		for(j=0;j<n;j++){
    		cin>>g[i][j];
			if(g[i][j]==-1)
    		g[i][j]=0x7f;
		}
	int sum,t;
	for(t=0;t<n;t++){
		for(i=0;i<n;i++)
			for(j=0;j<n;j++){
				if(t!=i&&i!=j&&t!=j&&g[i][t]!=0x7f&&g[t][j]!=0x7f&&g[i][t]+g[t][j]<g[i][j])
				g[i][j]=g[i][t]+g[t][j];
			}
	}
    for(i=0;i<n;i++)cout<<g[k][i]<<" ";
    return 0;  
}