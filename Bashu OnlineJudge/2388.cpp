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
using namespace std;
const int inf=0x3f3f3f3f;
const int mod=31011;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
vector<int>E[N];
int g[N][N],c[N][N];
int b[N],fa[N],vis[N];
struct edge{int s,t,data;}e[N*N];
bool cmp(edge x,edge y){return x.data<y.data;}
int Find1(int x){return x==fa[x]?x:fa[x]=Find1(fa[x]);}
int Find2(int x){return x==b[x]?x:b[x]=Find2(b[x]);}
void Init(){
	memset(g,0,sizeof(g));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)E[i].clear();
}
int Det(int a[][N],int p){
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			a[i][j]%=mod;
		}
	}
	int ans=1;p--;
	for(int i=1;i<=p;i++){
		for(int j=i+1;j<=p;j++){
			while(a[j][i]){
				int t=a[i][i]/a[j][i];
				for(int k=i;k<=p;k++)a[i][k]=(a[i][k]-a[j][k]*t)%mod;
				for(int k=i;k<=p;k++)swap(a[i][k],a[j][k]);
				ans=-ans;
			}
		}
		if(a[i][i]==0)return 0;
		ans=ans*a[i][i]%mod;
	}
	return (ans+mod)%mod;
}
void Solve(){
	int lst=-1,ans=1;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int k=1;k<=m+1;k++){
		if(e[k].data!=lst||k==m+1){
			for(int i=1;i<=n;i++){
				if(vis[i]){
					vis[i]=0;
					E[Find2(i)].push_back(i);
				}
			}
			for(int i=1;i<=n;i++){
				if(E[i].size()>1){//点数 >1 
					memset(c,0,sizeof(c));
					int len=E[i].size();
					for(int x=0;x<len;x++){
						for(int y=x+1;y<len;y++){
							int fx=E[i][x],fy=E[i][y];
							c[x+1][y+1]-=g[fx][fy];
							c[y+1][x+1]-=g[fx][fy];
							c[x+1][x+1]+=g[fx][fy];
							c[y+1][y+1]+=g[fx][fy];
						}
					}
					int dlt=Det(c,len);
					ans=(ans*dlt)%mod;
					for(int x=0;x<len;x++){
						fa[E[i][x]]=i;
					}
				}
			}
			for(int i=1;i<=n;i++){
				b[i]=fa[i]=Find1(i);
				E[i].clear();
			}
			if(k==m+1)break;
			lst=e[k].data;
		}
		int x=Find1(e[k].s);
		int y=Find1(e[k].t);
		if(x==y)continue;
		vis[x]=vis[y]=1;
		g[x][y]++;g[y][x]++;
		b[Find2(x)]=Find2(y);//权值相同的边按原连通性并起来 
	}
	for(int i=2;i<=n;i++){
		if(b[i]!=b[i-1]){
			printf("0\n");
			return;
		}
	}
	if(!m)printf("0\n");
	else printf("%d\n",ans%mod);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
	}
	sort(e+1,e+m+1,cmp);
	Solve();
	return 0;
}