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
const int Mod=1e9;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,tot,Ans;
int a[N][N],id[N][N];
int dx[2]={1,0},dy[2]={0,1};
void Kirchhoff(){
	Ans=1;
	for(int i=1;i<tot;i++){
		int t=i,Max=a[i][i];
		for(int j=i+1;j<tot;j++){
			if(a[j][i]>Max){Max=a[j][i];t=j;}
		}
		if(t!=i){swap(a[i],a[t]);Ans=(Mod-Ans)%Mod;}
		for(int j=i+1;j<tot;j++){
			int A=a[i][i],B=a[j][i];
			while(B){
				int dlt=A/B;A%=B;swap(A,B);
				for(int k=i;k<tot;k++){
					a[i][k]=(a[i][k]-1ll*dlt*a[j][k]%Mod+Mod)%Mod;
				}
				swap(a[i],a[j]);
				Ans=(Mod-Ans)%Mod;
			}
		}
		Ans=1ll*Ans*a[i][i]%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='*')continue;
			id[i][j]=++tot;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!id[i][j])continue;
			for(int k=0;k<2;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x<1||x>n||y<1||y>m||!id[x][y])continue;
				int fx=id[i][j],fy=id[x][y];
				a[fx][fx]++;a[fy][fy]++;
				a[fx][fy]--;a[fy][fx]--;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++){
			a[i][j]=(a[i][j]%Mod+Mod)%Mod;
		}
	}
	Kirchhoff();
	printf("%d",Ans);
	return 0;
}