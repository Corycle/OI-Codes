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
const int M=1e5+5;
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,Sum;
int a[M],b[M],f[M],g[M],Ans[M];
struct Node{int c,v,t;}P[N],Q[M];
bool cmp(Node A,Node B){return A.t<B.t;}
void Update(int c,int v){for(int i=Sum;i>=v;i--)f[i]=min(f[i],f[i-v]+c);}
void Query(int c,int id){
	int l=1,r=top,pos=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(b[mid]<=c){pos=mid;l=mid+1;}
		else r=mid-1;
	}
	Ans[id]=a[pos];
}
int main(){
//	freopen("market.in","r",stdin);
//	freopen("market.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){P[i].c=read();P[i].v=read();P[i].t=read();Sum+=P[i].v;}
	for(int i=1;i<=m;i++){Q[i].t=read();Q[i].c=read();Q[i].v=i;}
	sort(P+1,P+n+1,cmp);
	sort(Q+1,Q+m+1,cmp);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int t=1,p=1,q=1;t<=n;t++){
		while(p<=n&&P[p].t<=t){Update(P[p].c,P[p].v);p++;}
		top=0;
		for(int i=0;i<=Sum;i++){
			while(top&&b[top]>=f[i])top--;
			top++;a[top]=i;b[top]=f[i];
		}
		while(q<=m&&Q[q].t<=t){Query(Q[q].c,Q[q].v);q++;}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}