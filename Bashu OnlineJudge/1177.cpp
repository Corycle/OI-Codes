#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,maxn;
double p[N][N],f[M][N];
int main(){
	n=read();maxn=1<<n;
	for(int i=0;i<maxn;i++){
		for(int j=0;j<maxn;j++){
			p[i][j]=read()/100.0;
		}
	}
	for(int i=0;i<maxn;i++)f[0][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<maxn;j++){
			for(int k=0;k<maxn;k++){
				if(((j>>(i-1))^1)==(k>>(i-1))){
					f[i][j]+=f[i-1][j]*f[i-1][k]*p[j][k];
				}
			}
		}
	}
	double ans=0;int Ans=-1;
	for(int i=0;i<maxn;i++){
		if(f[n][i]>ans){
			ans=f[n][i];
			Ans=i+1;
		}
	}
	printf("%d",Ans);
	return 0;
}