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
const int Mod=1e9+7;
const int N=5005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Q,a[N],b[M][N],rk[N],tmp[N],Ans[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=m;i++)rk[i]=i;
	for(int i=1;i<=n;i++){
		int tot=0;
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[j]=b[i][j]=s[j]-'0';
		for(int j=1;j<=m;j++)if(a[rk[j]]==0)tmp[++tot]=rk[j];
		for(int j=1;j<=m;j++)if(a[rk[j]]==1)tmp[++tot]=rk[j];
		for(int j=1;j<=m;j++)rk[j]=tmp[j];
	}
	for(int j=1;j<=m;j++){
		for(int i=n;i>=1;i--){
			Ans[j]=(2ll*Ans[j]+b[i][j])%Mod;
		}
	}
	for(int i=1;i<=n;i++)Ans[m+1]=(2ll*Ans[m+1]+1)%Mod;
	Ans[m+1]+=1;
	rk[m+1]=m+1;
	while(Q--){
		int l=0,r=m+1;
		scanf("%s",s+1);
		for(int i=1;i<=m;i++)if(s[rk[i]]=='1'){r=i;break;}
		for(int i=m;i>=1;i--)if(s[rk[i]]=='0'){l=i;break;}
		if(l>r)printf("%d\n",0);
		else printf("%d\n",(Ans[rk[r]]-Ans[rk[l]]+Mod)%Mod);
	}
	return 0;
}