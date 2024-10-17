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
const int M=1000005;
const int N=2022;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,q,P,tot;
int p[M],f[N][N],num[N],sum[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void Divide(){
	int maxn=sqrt(P);
	for(int i=1;i<=maxn;i++){
		if(P%i==0){
			int x=i,y=P/i;
			num[++tot]=x;
			if(x!=y)num[++tot]=y;
		}
	}
	sort(num+1,num+tot+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();q=read();
	P=read();Divide();p[0]=1;
	for(int i=1;i<=n;i++)p[i]=mod(p[i-1]<<1);
	for(int i=0;i<=n;i++)p[i]=mod(p[i]-1+Mod);
	for(int i=1;i<=n;i++){
		int x=read();
		int pos=lower_bound(num+1,num+tot+1,gcd(x,P))-num;
		sum[pos]++;
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++)f[i][j]=f[i-1][j];
		for(int j=1;j<=tot;j++){
			int pos=lower_bound(num+1,num+tot+1,gcd(num[i],num[j]))-num;
			f[i][pos]=mod(f[i][pos]+1ll*f[i-1][j]*p[sum[i]]%Mod);
		}
		f[i][i]=mod(f[i][i]+p[sum[i]]);
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=i;j++){
			if(num[i]%num[j]==0){
				Ans[i]=mod(Ans[i]+f[tot][j]);
			}
		}
	}
	while(q--){
		int x=read();
		int pos=lower_bound(num+1,num+tot+1,gcd(x,P))-num;
		printf("%d\n",Ans[pos]);
	}
	return 0;
}