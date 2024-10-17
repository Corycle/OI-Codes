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
const int N=4005;
const int M=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,a[N],b[N],c[N],t[N],f[M][M][N],g[M][N],p1[M][M][N],p2[M][M][N],Ans[N];
void GetAns(int l,int r,int k){
//	cout<<l<<" "<<r<<" "<<k<<" "<<p1[l][r][k]<<" "<<p2[l][r][k]<<endl;
	int pos=p1[l][r][k];
	Ans[pos]=t[p2[l][r][k]];
	if(l<pos)GetAns(l,pos-1,p2[l][r][k]);
	if(r>pos)GetAns(pos+1,r,p2[l][r][k]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();b[i]=read();
		c[i]=read();t[++t[0]]=c[i];
	}
	sort(t+1,t+t[0]+1);tot=unique(t+1,t+t[0]+1)-t-1;
	for(int i=1;i<=m;i++)c[i]=lower_bound(t+1,t+tot+1,c[i])-t;
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++){
			memset(g,0,sizeof(g));
			for(int l=1;l<=m;l++){
				if(i<=a[l]&&b[l]<=j){
					for(int k=a[l];k<=b[l];k++)g[k][c[l]]++;
				}
			}
			for(int k=i;k<=j;k++){
				for(int l=tot;l>=1;l--)g[k][l]+=g[k][l+1];
			}
			for(int l=tot;l>=1;l--){
				for(int k=i;k<=j;k++){
					int dlt=f[i][k-1][l]+f[k+1][j][l]+g[k][l]*t[l];
					if(f[i][j][l]<=dlt){f[i][j][l]=dlt;p1[i][j][l]=k;p2[i][j][l]=l;}
				}
				if(f[i][j][l]<f[i][j][l+1]){
					f[i][j][l]=f[i][j][l+1];
					p1[i][j][l]=p1[i][j][l+1];
					p2[i][j][l]=p2[i][j][l+1];
				}
			}
		}
	}
	GetAns(1,n,1);
	printf("%d\n",f[1][n][1]);
	for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
	return 0;
}