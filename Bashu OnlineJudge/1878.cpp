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
const int N=1e5+5;
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,num,f[N][M];
struct Node{int l,r;}P[N];
bool cmp(Node A,Node B){return A.l!=B.l?A.l<B.l:A.r>B.r;}
int Count(){
	int ans=0;
	for(int i=1,R=-1;i<=n;i++){
		ans+=P[i].r-max(R,P[i].l);
		R=P[i].r;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){P[i].l=read();P[i].r=read();}
	sort(P+1,P+n+1,cmp);
	for(int i=1,R=-1;i<=n;i++){
		if(P[i].r<=R){m--;continue;}
		P[++tot]=P[i];R=P[i].r;
	}
	n=tot;
	if(m<=0){printf("%d\n",Count());return 0;}
	for(int i=1;i<=n;i++){
		
	}
	return 0;
}
