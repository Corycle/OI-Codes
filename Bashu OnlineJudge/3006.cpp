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
const int Mod=10007;
const int N=100005;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,blk,num;
int a[N],st[N],ed[N];
int pos[N],dlt1[N],dlt2[N];
inline void Reset(int x){
	for(register int i=st[x];i<=ed[x];i++){
		a[i]=(dlt1[x]+a[i]*dlt2[x]%Mod)%Mod;
	}
	dlt1[x]=0;dlt2[x]=1;
}
inline int Ask(int x){
	return (dlt1[pos[x]]+a[x]*dlt2[pos[x]]%Mod)%Mod;
}
inline void Add(int l,int r,int c){
	int x=pos[l],y=pos[r];Reset(x);Reset(y);
	if(x==y)for(register int i=l;i<=r;i++)a[i]=(a[i]+c)%Mod;
	else{
		for(register int i=l;i<=ed[x];i++)a[i]=(a[i]+c)%Mod;
		for(register int i=st[y];i<=r;i++)a[i]=(a[i]+c)%Mod;
		for(register int i=x+1;i<=y-1;i++)dlt1[i]=(dlt1[i]+c)%Mod;
	}
	Reset(x);Reset(y);
}
inline void Mul(int l,int r,int c){
	int x=pos[l],y=pos[r];Reset(x);Reset(y);
	if(x==y)for(register int i=l;i<=r;i++)a[i]=a[i]*c%Mod;
	else{
		for(register int i=l;i<=ed[x];i++)a[i]=a[i]*c%Mod;
		for(register int i=st[y];i<=r;i++)a[i]=a[i]*c%Mod;
		for(register int i=x+1;i<=y-1;i++){
			dlt1[i]=dlt1[i]*c%Mod;
			dlt2[i]=dlt2[i]*c%Mod;
		}
	}
	Reset(x);Reset(y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();blk=num=(int)(sqrt(n))/4;num=n/blk;
	for(register int i=1;i<=n;i++)a[i]=read()%Mod;
	for(register int i=1;i<=num;i++){st[i]=ed[i-1]+1;ed[i]=ed[i-1]+blk;}
	if(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=n;}
	for(register int i=1;i<=num;i++){
		dlt2[i]=1;
		for(register int j=st[i];j<=ed[i];j++){
			pos[j]=i;
		}
	}
	for(register int i=1;i<=n;i++){
		int op=read(),l=read(),r=read(),c=read();
		if(op==0)Add(l,r,c);
		if(op==1)Mul(l,r,c);
		if(op==2)printf("%d\n",Ask(r));
	}
	return 0;
}