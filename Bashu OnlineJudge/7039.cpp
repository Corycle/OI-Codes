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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],b[N],F[N];
int n,m,cnt,p[N],fa[N],Fa[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Node{
	int x;ll a,b;
	friend bool operator<(Node A,Node B){
		return A.b*B.a<B.b*A.a;
	}
};
priority_queue<Node>q;
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=2;i<=n;i++)Fa[i]=read();
	for(int i=1;i<=n;i++){a[i]=read();b[i]=read();q.push((Node){i,a[i],b[i]});}
	while(q.size()){
		Node A=q.top();q.pop();int x=A.x;
		if(x==1||a[x]!=A.a||b[x]!=A.b)continue;
		int y=Find(Fa[x]);
		F[y]+=F[x]+b[y]*a[x];
		a[y]+=a[x];b[y]+=b[x];fa[x]=y;
		q.push((Node){y,a[y],b[y]});
	}
	printf("%lld\n",F[1]);
	return 0;
}