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
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m;
vector<int>e1[N],e2[N];
int sum[N],vis[N],cnt[N];
int a[N],id[N],rk[N],deg[N];
bool cmp(int x,int y){
	return deg[x]!=deg[y]?deg[x]>deg[y]:x>y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		e1[x].push_back(y);
		e1[y].push_back(x);
		deg[x]++;deg[y]++;
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++)rk[id[i]]=i;
	for(int x=1;x<=n;x++){
		for(auto y:e1[x]){
			if(rk[x]<rk[y])e2[x].push_back(y);
		}
	}
	for(int x=1;x<=n;x++){
		for(auto y:e2[x]){
			for(auto z:e1[y]){
				if(rk[x]<rk[z])cnt[z]++;
			}
		}
		for(auto y:e2[x]){
			for(auto z:e1[y]){
				if(rk[x]<rk[z]){
					if(vis[z]!=x){
						sum[x]+=(cnt[z]-1)*cnt[z]/2;
						sum[z]+=(cnt[z]-1)*cnt[z]/2;
						vis[z]=x;
					}
					sum[y]+=cnt[z]-1;
				}
			}
		}
		for(auto y:e2[x]){
			for(auto z:e1[y]){
				if(rk[x]<rk[z])cnt[z]--;
			}
		}
	}
	int Ans=0;
	for(int i=1;i<=n;i++){
		Ans=(Ans+1ll*sum[i]*a[i]%Mod)%Mod;
	}
	printf("%d",Ans);
	return 0;
}