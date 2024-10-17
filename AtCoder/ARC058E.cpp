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
const int Mod=1e9+7;
const int M=(1<<17)+5;
const int N=42;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,x,y,z,Ans,Sta,Goal,f[N][M];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();x=read();y=read();z=read();
	Sta=(1<<(x+y+z))-1;
	Goal=(1<<(x+y+z-1))|(1<<(y+z-1))|(1<<(z-1));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int S=0;S<=Sta;S++){
			for(int k=1;k<=10;k++){
				int T=((S<<k)|(1<<(k-1)))&Sta;
				if((Goal|T)==T)continue;
				f[i][T]=mod(f[i][T]+f[i-1][S]);
			}
		}
	}
	Ans=1;
	for(int i=1;i<=n;i++)Ans=1ll*Ans*10%Mod;
	for(int S=0;S<=Sta;S++)Ans=mod(Ans-f[n][S]+Mod);
	printf("%d\n",Ans);
	return 0;
}
