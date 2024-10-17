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
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Node{int x,k;};
vector<Node>F[N];
int n,m,p1,p2L,p2R,p3,f[2][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Update(int t,int x,int y,int v){
	if(x<p3||y>=p1||y<p2R||x>=p2L)return;
	f[t][x][y]=mod(f[t][x][y]+v);
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();m=read();int flag=1;
		for(int i=1;i<=m;i++){
			int l=read(),r=read(),num=read();
			F[r].push_back((Node){l,num});
			if(num>(r-l+1))flag=0;
		}
		if(!flag){puts("0");continue;}
		memset(f,0,sizeof(f));
		int t=0;f[t][0][0]=3;
		for(int i=2;i<=n;i++){
			t^=1;memset(f[t],0,sizeof(f[t]));
			p1=i;p2L=i;p2R=0;p3=0;
			for(int j=0,num=F[i].size();j<num;j++){
				int k=F[i][j].k;
				if(k==1)p1=min(p1,F[i][j].x);
				else if(k==2){p2L=min(p2L,F[i][j].x);p2R=max(p2R,F[i][j].x);}
				else if(k==3)p3=max(p3,F[i][j].x);
			}
			for(int x=0;x<i;x++){
				for(int y=x;y<i;y++){
					Update(t,x,y,f[t^1][x][y]);
					Update(t,x,i-1,f[t^1][x][y]);
					Update(t,y,i-1,f[t^1][x][y]);
				}
			}
		}
		int Ans=0;
		for(int x=0;x<=n;x++){
			for(int y=x;y<=n;y++)Ans=mod(Ans+f[t][x][y]);
			F[x].clear();
		}
		printf("%d\n",Ans);
	}
	return 0;
}