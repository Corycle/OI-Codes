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
const int N=10005;
const int M=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double f[N][M];
int n,m,cnt,vis[N],prime[N],ans[N],g[N][M];
void Prepare(){
	for(int i=2;i<M;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=1;i<N;i++){
		for(int j=1;j<=cnt&&prime[j]<=i;j++){
			f[i][j]=f[i][j-1];g[i][j]=0;
			for(int k=prime[j];k<=i;k*=prime[j]){
				double tmp=log(k);
				if(f[i][j]<f[i-k][j-1]+tmp){
					f[i][j]=f[i-k][j-1]+tmp;
					g[i][j]=k;
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();Prepare();
	while(Case--){
		n=read();m=0;
		int tmp=n,num=min(n,M-1);
		while(num>0){
			if(g[tmp][num])ans[++m]=g[tmp][num];
			tmp-=g[tmp][num];
			num--;
		}
		for(int i=1;i<=tmp;i++)ans[++m]=1;
		sort(ans+1,ans+m+1);
		tmp=1;
		for(int i=1;i<=m;i++){
			for(int j=1;j<ans[i];j++)printf("%d ",tmp+j);
			printf("%d ",tmp);
			tmp+=ans[i];
		}
		puts("");
	}
	return 0;
}
