/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const ll inf=9e18;
const int N=50005;
const int M=25;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m;
ll a[N],b[N],f[N][M];
ll ldis[N],lsum[N],lnum[N];
ll rdis[N],rsum[N],rnum[N];
inline ll Calc1(int l,int r){
	if(l>r)return 0;
	return rsum[l]-rsum[r]-rnum[r+1]*(rdis[l]-rdis[r]);
}
inline ll Calc2(int l,int r){
	if(l>r)return 0;
	return lsum[r]-lsum[l]-lnum[l-1]*(ldis[r]-ldis[l]);
}
inline ll Calc(int l,int mid,int r){
	return Calc1(l,mid)+Calc2(mid+1,r);
}
inline ll W(int l,int r){
	int ql=l,qr=r;
	ll Min=Calc(l,l,r);
	while(l+4<=r){
		int mid=(l+r)>>1;
		ll c1=Calc(ql,mid,qr);
		ll c2=Calc(ql,mid+1,qr);
		if(c1>c2)l=mid;else r=mid+1;
	}
	for(int i=l;i<=r;i++){
		Min=min(Min,Calc(ql,i,qr));
	}
	return Min;
}
inline void Divide(int ql,int qr,int p,int l,int r){
	int mid=(ql+qr)>>1,pos=0;f[mid][p]=inf;
	for(int i=l;i<=r;i++){
		ll tmp=f[i][p-1]+W(i,mid);
		if(f[mid][p]>tmp){
			f[mid][p]=tmp;
			pos=i;
		}
	}
	if(ql<mid)Divide(ql,mid-1,p,l,pos);
	if(qr>mid)Divide(mid+1,qr,p,pos,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		lnum[i]=lnum[i-1]+a[i];
		ldis[i]=ldis[i-1]+b[i-1];
		lsum[i]=lsum[i-1]+lnum[i-1]*b[i-1];
	}
	for(int i=n;i>=1;i--){
		rnum[i]=rnum[i+1]+a[i];
		rdis[i]=rdis[i+1]+b[i];
		rsum[i]=rsum[i+1]+rnum[i+1]*b[i];
	}
	for(int i=1;i<=n;i++)f[i][1]=lsum[i];
	for(int i=2;i<=m;i++)Divide(1,n,i,1,n);
	ll Ans=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			Ans=min(Ans,f[i][j]+rsum[i]);
		}
	}
	printf("%lld",Ans);
	return 0;
}