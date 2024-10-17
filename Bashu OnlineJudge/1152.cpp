#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=10005;
const int M=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],f[N][M],p[N][M];
int Sqr(int x){return x*x;}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read(),Case=0;
	while(T--){
		n=read();m=read();
		memset(a,0,sizeof(a));
		memset(p,0,sizeof(p));
		memset(f,0x3f,sizeof(f));
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)f[i][1]=Sqr(a[1]-a[i]);
		for(int i=1;i<=n;i++){
			int t=min(i,m);
			for(int j=t;j>=2;j--){
				int l=p[i-1][j],r=p[i][j+1];
				if(!r)r=i-1;
				for(int k=l;k<=r;k++){
					if(f[i][j]>=f[k][j-1]+Sqr(a[k+1]-a[i])){
						f[i][j]=f[k][j-1]+Sqr(a[k+1]-a[i]);
						p[i][j]=k;
					}
				}
			}
		}
		printf("Case %d: %d\n",++Case,f[n][m]);
	}
	return 0;
}