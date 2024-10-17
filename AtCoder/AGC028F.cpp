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
const int N=1505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,tot,a[N][N],R[N][N],sum[N][N],Min[2][N][N],Max[2][N][N];
int main(){
//	freopen("cell.in","r",stdin);
//	freopen("cell.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			a[i][j]=(s[j]=='#'?0:s[j]-'0');
		}
	}
	int t=0;
	for(int i=n;i>=1;i--){
		t^=1;
		for(int j=n;j>=1;j--){
			if(!a[i][j])continue;
			R[i][j]=max(i,max(R[i][j+1],R[i+1][j]));
			sum[i][j]=sum[i][j+1]+sum[i+1][j]+a[i][j];
			Min[t][j][i]=j;
			for(int k=i+1;k<=R[i+1][j];k++)Min[t][j][k]=Min[t^1][j][k];
			for(int k=max(i,R[i+1][j])+1;k<=R[i][j+1];k++)Min[t][j][k]=Min[t][j+1][k];
			Max[t][j][i]=j;
			for(int k=i;k<=R[i][j+1];k++)Max[t][j][k]=Max[t][j+1][k];
			for(int k=max(i,R[i][j+1])+1;k<=R[i+1][j];k++)Max[t][j][k]=Max[t^1][j][k];
			int d=i+1,r=min(R[i][j+1],R[i+1][j]);
			while(d<=r){
				if(Max[t^1][j][d]>=Min[t][j+1][d]){
					sum[i][j]-=sum[d][Min[t][j+1][d]];
					d=R[d][Min[t][j+1][d]];
				}
				d++;
			}
			Ans+=1ll*a[i][j]*(sum[i][j]-a[i][j]);
		}
	}
	printf("%lld",Ans);
	return 0;
}
