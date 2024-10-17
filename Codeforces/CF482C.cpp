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
const int Maxn=(1<<20)+5;
const int N=55;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll g[Maxn];
double f[Maxn];
int n,m,Sta,num[Maxn];
char s[N][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	if(n==1){printf("%.12lf",0.0);return 0;}
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);m=strlen(s[1]+1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int sta=0;
			for(int k=1;k<=m;k++)if(s[i][k]==s[j][k])sta|=(1<<(k-1));
			g[sta]|=(1ll<<i)|(1ll<<j);
		}
	}
	Sta=(1<<m)-1;
	for(int S=Sta;S>=0;S--)for(int i=1;i<=m;i++)g[S]|=g[S|(1<<(i-1))];
	for(int S=0;S<=Sta;S++)num[S]=__builtin_popcountll(g[S]);
	for(int S=Sta;S>=0;S--){
		if(!num[S]){f[S]=0;continue;}
		int tot=m-__builtin_popcount(S);
		for(int i=1;i<=m;i++){
			if((S>>(i-1))&1)continue;
			double P=(double)num[S|(1<<(i-1))]/num[S];
			f[S]+=(f[S|(1<<(i-1))]*P+1)/tot;
		}
	}
	printf("%.12lf",f[0]);
	return 0;
}
