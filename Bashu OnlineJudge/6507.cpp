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
const int M=531500;
const int Mod=4;
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,p[N],f[N][M],a[N][N];
int mod(int x){return x&3;}//mod 4
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		a[x][y]=a[y][x]=1;
	}
	p[0]=1;
	for(int i=1;i<=12;i++)p[i]=p[i-1]*3;
	f[1][0]=f[1][p[11]]=f[1][p[11]*2]=1;
	for(int i=2;i<=n;i++){
		for(int S=0;S<p[12];S++){
			if(f[i-1][S]){
				int T=S/3,flag1=1,flag2=1;
				f[i][T]=mod(f[i][T]+f[i-1][S]);
				for(int j=0;j<12;j++){
					if(i-12+j>=1&&a[i][i-12+j]){
						int x=(S/p[j])%3;
						if(x==1)flag2=0;
						if(x==2)flag1=0;
					}
				}
				if(flag1)f[i][T+p[11]]=mod(f[i][T+p[11]]+f[i-1][S]);
				if(flag2)f[i][T+p[11]*2]=mod(f[i][T+p[11]*2]+f[i-1][S]);
			}
		}
	}
	for(int S=0;S<p[12];S++)Ans=mod(Ans+f[n][S]);
	Ans=mod(Ans-1+Mod);//choose nothing
	printf("%d",(Ans==2));
	return 0;
}