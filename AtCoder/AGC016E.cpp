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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,A[M],B[M],vis[N],a[N][N],b[N],d[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){A[i]=read();B[i]=read();}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		vis[i]=1;b[i]=1;
		for(int j=m;j>=1;j--){
			if(vis[A[j]]&&vis[B[j]]){b[i]=0;break;}
			if(vis[A[j]]||vis[B[j]])vis[A[j]]=vis[B[j]]=1;
		}
		if(!b[i])continue;
		for(int j=1;j<=n;j++)a[i][j]=(vis[j]^1);
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i][j]&&a[j][i]&&b[i]&&b[j]){
				int flag=1;
				for(int k=1;k<=n;k++)if(!a[i][k]&&!a[j][k]){flag=0;break;}
				if(flag)Ans++;
			}
		}
	}
	printf("%d\n",Ans);
	return 0;
}
