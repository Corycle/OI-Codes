#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,P,Sr,Sb,Sg,tot;
int a[N],vis[N],sum[N],f[N][N][N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%P;
		tot=(tot*tot)%P;
		y>>=1;
	}
	return ans;
}
int Ask(){
	tot=0;
	memset(f,0,sizeof(f));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int p=i,len=0;
			while(!vis[p]){
				len++;
				vis[p]=1;
				p=a[p];
			}
			sum[++tot]=len;
		}
	}
	f[0][0][0]=1;
	for(int p=1;p<=tot;p++){
		for(int i=Sr;i>=0;i--){
			for(int j=Sb;j>=0;j--){
				for(int k=Sg;k>=0;k--){
					if(i>=sum[p])f[i][j][k]=(f[i][j][k]+f[i-sum[p]][j][k])%P;
					if(j>=sum[p])f[i][j][k]=(f[i][j][k]+f[i][j-sum[p]][k])%P;
					if(k>=sum[p])f[i][j][k]=(f[i][j][k]+f[i][j][k-sum[p]])%P;
				}
			}
		}
	}
	return f[Sr][Sb][Sg];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Sr=read();Sb=read();Sg=read();
	m=read();P=read();n=Sr+Sb+Sg;
	int ans=0,T=m;
	while(T--){
		for(int i=1;i<=n;i++)a[i]=read();
		ans=(ans+Ask())%P;
	}
	for(int i=1;i<=n;i++)a[i]=i;
	ans=(ans+Ask())%P;
	printf("%d",ans*Pow(m+1,P-2)%P);
	return 0;
}