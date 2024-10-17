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
const ll inf=1e18;
const int N=200005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll dis[N];
int n,m,K;
struct Node{
	int x,y;
	friend bool operator<(Node A,Node B){return A.x<B.x;}
}a[N];
struct ST{
	ll p1[N][M],p2[N][M];
	void Init(){
		sort(a+1,a+K+1);
		int k=(int)(log(K)/log(2));
		for(int i=1;i<=K;i++){
			p1[i][0]=a[i].y-dis[a[i].x];
			p2[i][0]=a[i].y+dis[a[i].x];
		}
		for(int j=1;j<=k;j++){
			for(int i=1;i+(1<<j)-1<=K;i++){
				p1[i][j]=min(p1[i][j-1],p1[i+(1<<(j-1))][j-1]);
				p2[i][j]=min(p2[i][j-1],p2[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int GetL(int x){Node tmp=(Node){x,0};return lower_bound(a+1,a+K+1,tmp)-a;}
	int GetR(int x){Node tmp=(Node){x,0};return upper_bound(a+1,a+K+1,tmp)-a-1;}
	ll Query1(int l,int r){
		if(l>r)swap(l,r);
		l=GetL(max(1,l));
		r=GetR(min(r,n));
		if(l>r)return inf;
		int k=(int)(log(r-l+1)/log(2));
		return min(p1[l][k],p1[r-(1<<k)+1][k]);
	}
	ll Query2(int l,int r){
		if(l>r)swap(l,r);
		l=GetL(max(1,l));
		r=GetR(min(r,n));
		if(l>r)return inf;
		int k=(int)(log(r-l+1)/log(2));
		return min(p2[l][k],p2[r-(1<<k)+1][k]);
	}
}st;
bool Check1(int x,int y){
	if(x==y)return true;
	ll t1=+dis[y]+st.Query1(2*y-x+1,y);
	ll t2=-dis[y]+st.Query2(y,x-1);
	ll Min=st.Query2(x,x)-dis[y];
	if(t1<=Min||t2<=Min)return false;
	if(2*y-x>=1)return (st.Query1(2*y-x,2*y-x)+dis[y]>Min);
	return true;
}
bool Check2(int x,int y){
	if(x==y)return true;
	ll t1=+dis[y]+st.Query1(x+1,y);
	ll t2=-dis[y]+st.Query2(y,2*y-x-1);
	ll Min=st.Query1(x,x)+dis[y];
	if(t1<=Min||t2<=Min)return false;
	if(2*y-x<=n)return (st.Query2(2*y-x,2*y-x)-dis[y]>=Min);
	return true;
}
int Query1(int x){
	int l=1,r=x,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check1(x,mid)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	return x-ans;
}
int Query2(int x){
	int l=x,r=n,ans=x;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check2(x,mid)){ans=mid;l=mid+1;}
		else r=mid-1;
	}
	return ans-x;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=2;i<=n;i++)dis[i]=dis[i-1]+read();
	while(m--){
		K=read();
		for(int i=1;i<=K;i++){a[i].x=read();a[i].y=read();}
		ll Ans=0;st.Init();
		for(int i=1;i<=K;i++){
			Ans+=Query1(a[i].x)+Query2(a[i].x)+1;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}