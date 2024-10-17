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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],f[N],nxt[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int tmp=1;
	m=read();n=read();nxt[0]=-1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		int p=nxt[i-1];
		while(p!=-1&&a[p+1]!=a[i])p=nxt[p];
		nxt[i]=(p!=-1?p+1:0);
		tmp=1ll*tmp*m%Mod;
		f[i]=mod(f[nxt[i]]+tmp);
	}
	for(int i=1;i<=n;i++)printf("%d\n",f[i]);
	return 0;
}