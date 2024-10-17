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
const int N=500005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,L,R,Pos[N][M];
ll Ans,sum[N],Min[N][M];
struct Node{
	int l,r,pos,t;ll ans;
	friend bool operator<(Node A,Node B){
		return A.ans<B.ans;
	}
};
priority_queue<Node>q;
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=0;i<=n;i++){Min[i][0]=sum[i];Pos[i][0]=i;}
	for(int j=1;j<=k;j++){
		for(int i=0;i+(1<<j)-1<=n;i++){
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
			Pos[i][j]=(Min[i][j]==Min[i][j-1]?Pos[i][j-1]:Pos[i+(1<<(j-1))][j-1]);
		}
	}
}
int Query(int l,int r){
	int k=(int)(log(r-l+1)/log(2));
	return (Min[l][k]<Min[r-(1<<k)+1][k]?Pos[l][k]:Pos[r-(1<<k)+1][k]);
}
void Push(int l,int r,int t){
	int pos=Query(l,r);
	ll ans=sum[t]-sum[pos];
	q.push((Node){l,r,pos,t,ans});
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();L=read();R=read();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+read();
	ST();
	for(int i=L;i<=n;i++){
		int l=max(i-R,0);
		int r=max(i-L,0);
		Push(l,r,i);
	}
	while(K--){
		Node A=q.top();q.pop();Ans+=A.ans;
		if(A.l<A.pos)Push(A.l,A.pos-1,A.t);
		if(A.r>A.pos)Push(A.pos+1,A.r,A.t);
	}
	printf("%lld",Ans);
	return 0;
}