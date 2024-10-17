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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
int lx[N],ly[N],visx[N],visy[N],p[N],w[N][N];
bool DFS(int x){
	visx[x]=1;
	for(int y=1;y<=n;y++){
		if(!visy[y]&&lx[x]+ly[y]==w[x][y]){
			visy[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
void Adjust(){
	int d=inf;
	for(int i=1;i<=n;i++){
		if(!visx[i])continue;
		for(int j=1;j<=n;j++){
			if(!visy[j])d=min(d,lx[i]+ly[j]-w[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		if(visx[i])lx[i]-=d;
		if(visy[i])ly[i]+=d;
	}
}
void KM(){
	for(int i=1;i<=n;i++){
		lx[i]=-inf;
		ly[i]=0;
		for(int j=1;j<=n;j++){
			lx[i]=max(lx[i],w[i][j]);
		}
	}
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++){
		while(1){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(DFS(i))break;
			Adjust();
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			w[i][j]=-read();
		}
	}
	KM();
	int ans1=0;
	for(int i=1;i<=n;i++){
		if(p[i])ans1-=w[p[i]][i];
	}
	printf("%d\n",ans1);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			w[i][j]=-w[i][j];
		}
	}
	KM();
	int ans2=0;
	for(int i=1;i<=n;i++){
		if(p[i])ans2+=w[p[i]][i];
	}
	printf("%d\n",ans2);
	return 0;
}