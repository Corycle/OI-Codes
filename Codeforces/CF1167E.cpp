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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,a[N],s[N],L[N],R[N],f[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();f[m+1]=1;
	for(int i=1;i<=m;i++)L[i]=n+1;
	for(int i=1;i<=n;i++){a[i]=read();s[i]=max(s[i-1],a[i]);}
	for(int i=1;i<=n;i++){L[a[i]]=min(L[a[i]],i);R[a[i]]=max(R[a[i]],i);}
	for(int i=m,l=n+1;i>=1;i--){if(R[i]<l){l=min(l,L[i]);f[i]=f[i+1]+1;}else{l=-1;f[i]=f[i+1];}}
	for(int l=0,r=0;l<m;l++){if(r>L[l])break;r=max(r,R[l]);Ans+=f[max(l+2,s[r]+1)];}
	printf("%lld",Ans);
}
