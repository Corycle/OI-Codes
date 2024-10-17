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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,f[N][N];
struct Node{int num,val;}P[N];
bool cmp(Node A,Node B){return A.num>B.num;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){P[i].num=read();P[i].val=read();}
	sort(P+1,P+n+1,cmp);memset(f,-0x3f,sizeof(f));f[0][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)f[i][j]=f[i-1][j];
		for(int j=1;j<=n;j++){
			int k=min(j-1+P[i].num,n);
			f[i][k]=max(f[i][k],f[i-1][j]+P[i].val);
			Ans=max(Ans,f[i][k]);
		}
	}
	printf("%d",Ans);
	return 0;
}
