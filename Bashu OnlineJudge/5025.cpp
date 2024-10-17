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
const ll inf=9e18;
const int N=10005;
const int M=805;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N][M],Ans=-inf;
int c[N],d[N],q1[N],q2[N];
int n,t,K,p,q,z,l1,r1,l2,r2,Now;
void Push(int pos){
	if(pos<0)return;
	if(d[pos]){
		while(l1<=r1&&f[pos][Now-1]>=f[q1[r1]][Now-1])r1--;
		q1[++r1]=pos;
	}
	else{
		while(l2<=r2&&f[pos][Now-1]>=f[q2[r2]][Now-1])r2--;
		q2[++r2]=pos;
	}
}
int main(){
//	freopen("journey.in","r",stdin);
//	freopen("journey.out","w",stdout);
	n=read();K=read();t=read();
	p=read();q=read();z=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)d[i]=(read()%t==0);
	memset(f,-0x3f,sizeof(f));
	f[0][0]=0;
	for(int j=1;j<=K;j++){
		Now=j;l1=1;r1=0;l2=1;r2=0;
		for(int i=1;i<=n;i++){
			while(l1<=r1&&q1[l1]<i-q)l1++;
			while(l2<=r2&&q2[l2]<i-q)l2++;
			Push(i-p);
			int dlt=d[i]?-z:0;
			if(l1<=r1)f[i][j]=max(f[i][j],f[q1[l1]][j-1]+c[i]+dlt);
			if(l2<=r2)f[i][j]=max(f[i][j],f[q2[l2]][j-1]+c[i]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int k=1;k<=K;k++){
			Ans=max(Ans,f[i][k]);
		}
	}
	printf("%lld",Ans);
	return 0;
}