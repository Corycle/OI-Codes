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
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,P;
ll Max,h[N],a[N],num[N];
struct Node{
	ll t;int id;
	friend bool operator<(Node A,Node B){return A.t>B.t;}
};
bool Check(ll x){
	priority_queue<Node>q;
	for(int i=1;i<=n;i++){
		num[i]=0;
		if(x-a[i]*m<h[i])q.push((Node){x/a[i],i});
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=K;j++){
			if(q.empty())break;
			Node A=q.top();q.pop();
			if(A.t<i)return false;
			num[A.id]++;
			if(x+num[A.id]*P-a[A.id]*m<h[A.id]){
				q.push((Node){(x+num[A.id]*P)/a[A.id],A.id});
			}
		}
	}
	return q.empty();
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();P=read();
	for(int i=1;i<=n;i++){
		h[i]=read();a[i]=read();
		Max=max(Max,h[i]+a[i]*m);
	}
	ll l=0,r=Max,ans=Max;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
