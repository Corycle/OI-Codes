/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
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
ll sum[N];
struct Node{
	int l,r;ll d;
	friend bool operator<(Node A,Node B){
		return A.d<B.d;
	}
};
priority_queue<Node>q;
unordered_map<int,int>vis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+read();
	}
	vis[1][n]=1;
	q.push((Node){1,n,sum[n]});
	while(m--){
		Node A=q.top();q.pop();
		printf("%lld ",A.d);
		int l=A.l,r=A.r;
		if(!vis[l][r-1]){
			vis[l][r-1]=1;
			q.push((Node){l,r-1,sum[r-1]-sum[l-1]});
		}
		if(!vis[l+1][r]){
			vis[l+1][r]=1;
			q.push((Node){l+1,r,sum[r]-sum[l]});
		}
	}
	return 0;
}