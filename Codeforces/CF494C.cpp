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
const int M=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double f[M][M];
vector<int>G[N];
int n,m,a[N],p[N][20],fa[N];
struct Node{int l,r,Max;double p;}P[N];
bool cmp(Node A,Node B){
	int l1=A.r-A.l+1,l2=B.r-B.l+1;
	return l1!=l2?l1<l2:A.l<B.l;
}
void ST(){
	for(int i=1;i<=n;i++)p[i][0]=a[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)p[i][j]=max(p[i][j-1],p[i+(1<<(j-1))][j-1]);
	}
}
int Ask(int l,int r){
	int k=(int)(log(r-l+1)/log(2));
	return max(p[l][k],p[r-(1<<k)+1][k]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){P[i].l=read();P[i].r=read();scanf("%lf",&P[i].p);}
	P[++m]=(Node){1,n,0,0};sort(P+1,P+m+1,cmp);ST();
	for(int x=1;x<=m;x++){
		f[x][0]=1-P[x].p;
		P[x].Max=Ask(P[x].l,P[x].r);
		for(int y=1;y<x;y++){
			if(P[x].l<=P[y].l&&P[y].r<=P[x].r&&!fa[y]){
				fa[y]=x;G[x].push_back(y);
				f[x][0]*=f[y][P[x].Max-P[y].Max];
			}
		}
		for(int i=1;i<=m;i++){
			double p1=1,p2=1;
			for(auto y:G[x]){
				int dlt=P[x].Max-P[y].Max;
				p1*=f[y][min(m,i+dlt-1)];
				p2*=f[y][min(m,i+dlt)];
			}
			f[x][i]=P[x].p*p1+(1-P[x].p)*p2;
		}
	}
	double Ans=f[m][0]*P[m].Max;
	for(int i=1;i<=m;i++)Ans+=(f[m][i]-f[m][i-1])*(P[m].Max+i);
	printf("%.10lf\n",Ans);
	return 0;
}
