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
const ll inf=0x3f3f3f3f;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Mina,Minb,K;
ll a[N][N],sum[N][N];
map<ll,bool>vis[N*N];
struct Node{ll x,y,fx,fy,sum;};
bool operator<(Node A,Node B){
	return A.sum>B.sum;
}
priority_queue<Node>q;
ll Sum(ll x,ll y,ll fx,ll fy){
	return sum[fx][fy]-sum[fx][y-1]-sum[x-1][fy]+sum[x-1][y-1];
}
Node Matrix(ll x,ll y,ll fx,ll fy){
	return (Node){x,y,fx,fy,Sum(x,y,fx,fy)};
}
ll id(ll x,ll y){return (x-1)*m+y;}
void Update(Node A){
	if(A.fx!=n){
		ll x=A.x,y=A.y,fx=A.fx+1,fy=A.fy;
		Node a=Matrix(x,y,fx,fy);
		if(!vis[id(x,y)][id(fx,fy)]){
			vis[id(x,y)][id(fx,fy)]=true;
			q.push(a);
		}
	}
	if(A.fy!=m){
		ll x=A.x,y=A.y,fx=A.fx,fy=A.fy+1;
		Node a=Matrix(x,y,fx,fy);
		if(!vis[id(x,y)][id(fx,fy)]){
			vis[id(x,y)][id(fx,fy)]=true;
			q.push(a);
		}
	}
}
int main(){
//	freopen("matrix.in","r",stdin);
//	freopen("matrix.out","w",stdout);
	n=read();m=read();
	Mina=read();Minb=read();K=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			a[i][j]=read();
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+a[i][j];
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			ll x=i+Mina-1,y=j+Minb-1;
			if(x>n||y>m)break;
			q.push(Matrix(i,j,x,y));
			vis[id(i,j)][id(x,y)]=true;
		}
	}
	Node Ans;
	while(K--){
		if(!q.size()){printf("-1");return 0;}
		Ans=q.top();q.pop();Update(Ans);
	}
	printf("%lld",Ans.sum);
	return 0;
}