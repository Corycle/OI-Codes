/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int N=155;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,t,Ans,Max;
int a[N],f[N][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		Max=max(Max,a[i]+1);
	}
	for(int L=0;L<=Max;L++){
		for(int R=L;R<=Max;R++){
			f[n+1][L][R]=1;
		}
	}
	for(int i=n;i>=1;i--){
		for(int L=0;L<=Max;L++){
			for(int R=L;R<=Max;R++){
				for(int x=max(L,1);x<=min(R,a[i]);x++){
					if(x==L||x==R)f[i][L][R]=mod(f[i][L][R]+f[i+1][x][x]);
					else{
						f[i][L][R]=mod(f[i][L][R]+f[i+1][L][x]);
						f[i][L][R]=mod(f[i][L][R]+f[i+1][x][R]);
						f[i][L][R]=mod(f[i][L][R]-f[i+1][x][x]+Mod);
					}
				}
			}
		}
	}
	printf("%d",f[1][0][Max]);
	return 0;
}