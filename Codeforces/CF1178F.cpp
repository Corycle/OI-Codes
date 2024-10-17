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
const int Mod=998244353;
const int M=1e6+5;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,a[M],Min[N],Max[N],f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){Max[i]=0;Min[i]=m+1;}
	for(int i=1;i<=m;i++){a[i]=read();if(a[i]==a[i-1]){m--;i--;}}
	if(m>n*2){puts("0");return 0;}
	for(int i=1;i<=m;i++){Max[a[i]]=max(Max[a[i]],i);Min[a[i]]=min(Min[a[i]],i);}
	for(int i=1;i<=n;i++)if(Min[i]==Max[i])f[Min[i]][Max[i]]=1;
	for(int i=0;i<=m;i++)f[i+1][i]=1;
	for(int t=2;t<=m;t++){
		for(int l=1;l+t-1<=m;l++){
			int r=l+t-1,tmp=l;
			for(int i=l;i<=r;i++)if(a[i]<a[tmp])tmp=i;
			int L=Min[a[tmp]],R=Max[a[tmp]];
			if(L<l||r<R)continue;
			int s1=0,s2=0;
			for(int i=l;i<=L;i++)s1=mod(s1+1ll*f[l][i-1]*f[i][L-1]%Mod);
			for(int i=R;i<=r;i++)s2=mod(s2+1ll*f[R+1][i]*f[i+1][r]%Mod);
			f[l][r]=1ll*s1*s2%Mod;
			for(int i=l,j=0;i<=r;i++){
				if(a[i]==a[tmp]){
					if(j)f[l][r]=1ll*f[l][r]*f[j+1][i-1]%Mod;
					j=i;
				}
			}
		}
	}
	printf("%d\n",f[1][m]);
	return 0;
}
