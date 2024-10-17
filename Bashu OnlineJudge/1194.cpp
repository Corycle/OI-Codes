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
#define re register
using namespace std;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot;
int c[N],a[N],b[N],f[N][N];
int Mod(int x){
	if(x>=mod)x-=mod;
	return x;
}
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(re int i=x;i<=tot+1;i+=lowbit(i)){
		c[i]=Mod(c[i]+y);
	}
}
int Ask(int x){
	int tmp=0;
	for(re int i=x;i>=1;i-=lowbit(i)){
		tmp=Mod(tmp+c[i]);
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int Case=0,T=read();
	while(T--){
		n=read();m=read();
		for(re int i=1;i<=n;i++){
			a[i]=b[i]=read();
		}
		sort(b+1,b+n+1);
		tot=unique(b+1,b+n+1)-b-1;
		for(re int i=1;i<=n;i++){
			a[i]=lower_bound(b+1,b+tot+1,a[i])-b+1;
		}
		a[0]=f[0][0]=1;
		for(re int i=1;i<=m;i++){
			memset(c,0,sizeof(c));
			Add(a[0],f[i-1][0]);
			for(re int j=1;j<=n;j++){
				f[i][j]=Ask(a[j]-1);
				Add(a[j],f[i-1][j]);
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=Mod(ans+f[m][i]);
		}
		printf("Case #%d: %d\n",++Case,ans);
	}
	return 0;
}