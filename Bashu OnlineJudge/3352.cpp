/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=10007;
const int N=1100;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,B,V,Sta;
int f[N],g[N],p[N],Ans[N];
int main(){
//	freopen("crypto.in","r",stdin);
//	freopen("crypto.out","w",stdout);
	n=read();B=read();
	m=read();V=read();
	Sta=(1<<B)-1;p[0]=1;
	for(int S=1;S<=Sta;S++){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int i=1;i<B;i++)if((S>>i)&1)f[i%m]++;
		for(int i=0;i<B;i++)if((S>>i)&1)g[i%m]++;
		ll k=n-1,len=1,tmp=B;
		while(k){
			if(k&1){
				memset(p,0,sizeof(p));
				for(int i=0;i<m;i++){
					for(int j=0;j<m;j++){
						p[(i*tmp%m+j)%m]+=f[i]*g[j]%Mod;
						p[(i*tmp%m+j)%m]%=Mod;
					}
				}
				for(int i=0;i<m;i++)f[i]=p[i];
			}
			k>>=1;
			memset(p,0,sizeof(p));
			for(int i=0;i<m;i++){
				for(int j=0;j<m;j++){
					p[(i*tmp%m+j)%m]+=g[i]*g[j]%Mod;
					p[(i*tmp%m+j)%m]%=Mod;
				}
			}
			for(int i=0;i<m;i++)g[i]=p[i];
			len<<=1;tmp=tmp*tmp%m;
		}
		Ans[S]=f[V];
	}
	for(int i=1;i<=Sta;i++){
		for(int j=(i-1)&i;j;j=(j-1)&i){
			Ans[i]=(Ans[i]-Ans[j]+Mod)%Mod;
		}
		for(int j=B-1;j>=0;j--){
			if((i>>j)&1)printf("%d",j);
		}
		printf(" %d\n",Ans[i]);
	}
	return 0;
}