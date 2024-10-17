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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],p[N],f[N][2][2][2];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();p[0]=1;
	for(int i=1;i<=n;i++)p[i]=mod(p[i-1]<<1);
	for(int i=1;i<=n;i++)a[i]=read();
	f[0][0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int c=0;c<=1;c++){
			for(int x=0;x<=1;x++){
				for(int y=0;y<=1;y++){
					if(!f[i-1][c][x][y])continue;
					if(a[i]==-1||a[i]==0){
						if(y==0){
							f[i][c^1][1][y]=mod(f[i][c^1][1][y]+1ll*f[i-1][c][x][y]*p[i-1]%Mod);
						}
						if(y==1){
							f[i][c^1][1][y]=mod(f[i][c^1][1][y]+1ll*f[i-1][c][x][y]*p[i-2]%Mod);
							f[i][c][x][y]=mod(f[i][c][x][y]+1ll*f[i-1][c][x][y]*p[i-2]%Mod);
						}
					}
					if(a[i]==-1||a[i]==1){
						if(x==0){
							f[i][c^1][x][1]=mod(f[i][c^1][x][1]+1ll*f[i-1][c][x][y]*p[i-1]%Mod);
						}
						if(x==1){
							f[i][c^1][x][1]=mod(f[i][c^1][x][1]+1ll*f[i-1][c][x][y]*p[i-2]%Mod);
							f[i][c][x][y]=mod(f[i][c][x][y]+1ll*f[i-1][c][x][y]*p[i-2]%Mod);
						}
					}
				}
			}
		}
	}
	printf("%d",mod(mod(f[n][1][0][0]+f[n][1][0][1])+mod(f[n][1][1][0]+f[n][1][1][1])));
	return 0;
}