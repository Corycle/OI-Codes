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
const int M=(1<<18)+5;
const int N=40;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Sta,Ans,Num;
int a[N],b[N],f[N][M],g[N][M],num[M];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("repair.in","r",stdin);
//	freopen("repair.out","w",stdout);
	n=read();m=read();Sta=(1<<n)-1;
	for(int i=1;i<=n;i++){a[i]=read();b[++tot]=a[i];b[++tot]=a[i]+1;}
	sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
		g[a[i]][1<<(i-1)]=1;
	}
	for(int i=1;i<=Sta;i++)num[i]=num[i>>1]+(i&1);
	for(int S=1;S<=Sta;S++){
		for(int i=1;i<=n;i++){
			if((S>>(i-1))&1)continue;
			int T=S|(1<<(i-1));
			for(int x=1;x<=tot;x++){
				int y=(a[i]!=x?max(a[i],x):x+1);
				g[y][T]=mod(g[y][T]+g[x][S]);
				f[y][T]=mod(f[y][T]+mod(f[x][S]+1ll*g[x][S]*b[y]%Mod*m%Mod));
			}
		}
	}
	int Sum=0,tmp=0,pos=0;
	for(int i=2;i<=n;i++){Sum=mod(Sum+tmp);tmp=mod(tmp+tmp+1);}
	for(int i=tot;i>=1;i--)if(g[i][Sta]||f[i][Sta]){Ans=f[i][Sta];Num=g[i][Sta];pos=i;break;}
	Ans=mod(Ans+1ll*Num*Sum%Mod);
	printf("%d %d\n",b[pos],Ans);
	return 0;
}