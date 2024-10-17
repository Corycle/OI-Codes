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
const int M=35;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char op[10];
int n,m,a[N],b[N],f[M][2],val[M][2];
int DFS(int x,int flag){
	if(x<0)return 0;
	if(f[x][flag]!=-1)return f[x][flag];
	int k=(flag?(m>>x)&1:1);
	for(int i=0;i<=k;i++){
		f[x][flag]=max(f[x][flag],DFS(x-1,flag&(i==k))+val[x][i]);
	}
	return f[x][flag];
}
int Solve(int m){
	memset(f,-1,sizeof(f));
	for(int i=0;i<=30;i++){
		val[i][1]=1<<i;
		for(int j=1;j<=n;j++){
			int x=b[j]&(1<<i);
			val[i][0]=(a[j]==1?val[i][0]&x:(a[j]==2?val[i][0]|x:val[i][0]^x));
			val[i][1]=(a[j]==1?val[i][1]&x:(a[j]==2?val[i][1]|x:val[i][1]^x));
		}
	}
	return DFS(30,1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",op);
		a[i]=(op[0]=='A'?1:(op[0]=='O'?2:3));
		b[i]=read();
	}
	printf("%d",Solve(m));
	return 0;
}