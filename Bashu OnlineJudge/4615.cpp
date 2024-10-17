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
const int Mod=1e4;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],f[N],nxt[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read()%Mod;
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=2,j=0;i<=n;i++){
			while(j&&a[i]!=a[j+1])j=nxt[j];
			if(a[i]==a[j+1])j++;
			nxt[i]=j;
		}
		for(int i=1,tmp=1;i<=n;i++){
			tmp=tmp*m%Mod;
			f[i]=(f[nxt[i]]+tmp)%Mod;
		}
		printf("%04d\n",f[n]);
	}
	return 0;
}