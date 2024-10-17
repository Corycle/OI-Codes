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
ll Ans;
int n,m,a[N],L[N],R[N],vis[N];
struct Node{
	int val,id;
	friend bool operator<(Node A,Node B){return A.val>B.val;}
};
priority_queue<Node>q;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]=a[i+1]-a[i];n--;
	for(int i=1;i<=n;i++){L[i]=i-1;R[i]=i+1;q.push((Node){a[i],i});}
	a[0]=a[n+1]=inf;
	while(q.size()){
		int x=q.top().id;q.pop();
		if(vis[x])continue;
		Ans+=a[x];
		vis[L[x]]=vis[R[x]]=1;
		a[x]=a[L[x]]+a[R[x]]-a[x];
		q.push((Node){a[x],x});
		L[x]=L[L[x]];R[L[x]]=x;
		R[x]=R[R[x]];L[R[x]]=x;
		if(!(--m))break;
	}
	printf("%lld",Ans);
	return 0;
}