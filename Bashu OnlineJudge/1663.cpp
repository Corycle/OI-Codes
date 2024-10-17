/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[5];
int n,m,S,Ans,fx[N],fy[N],sum[N][N];
inline int Sum(int sy,int ty,int sx,int tx){
	return sum[tx][ty]+sum[sx-1][sy-1]-sum[tx][sy-1]-sum[sx-1][ty];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=1001;
	for(int i=1;i<=n;i++){
		fx[i]=read()+1;fy[i]=read()+1;scanf("%s",s);
		sum[fx[i]][fy[i]]+=(s[0]=='H'?1:-n);
	}
	sort(fx+1,fx+n+1);sort(fy+1,fy+n+1);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}
	for(int l=1;l<=n;l++){
		for(int r=l;r<=n;r++){
			int lst=1;
			for(int i=1;i<=n;i++){
				int tmp=Sum(fy[l],fy[r],fx[lst],fx[i]);
				if(tmp<=0){lst=i+1;continue;}
				if(tmp>Ans){Ans=tmp;S=(fy[r]-fy[l])*(fx[i]-fx[lst]);}
				else if(tmp==Ans)S=min(S,(fy[r]-fy[l])*(fx[i]-fx[lst]));
			}
		}
	}
	printf("%d\n%d\n",Ans,S);
	return 0;
}
