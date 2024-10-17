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
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,a[N],num[N],f[N][N][N];
int Sqr(int x){return x*x;}
int F(int l,int r,int k){
	if(l==r)return Sqr(num[r]+k);
	if(f[l][r][k])return f[l][r][k];
	f[l][r][k]=F(l,r-1,0)+Sqr(num[r]+k);
	for(int i=l;i<r;i++)if(a[i]==a[r])f[l][r][k]=max(f[l][r][k],F(l,i,num[r]+k)+F(i+1,r-1,0));
	return f[l][r][k];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	for(int Case=1;Case<=T;Case++){
		int lst=0;tot=0;n=read();memset(f,0,sizeof(f));memset(num,0,sizeof(num));
		for(int i=1;i<=n;i++){int x=read();if(x!=lst)a[++tot]=x;lst=x;num[tot]++;}
		printf("Case %d: %d\n",Case,F(1,tot,0));
	}
	return 0;
}
