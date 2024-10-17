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
const ll inf=1e18;
const int N=2e5+5;
const int M=4;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,a[M][M];
struct SAM{
	int tot,lst,root;
	int fa[N],len[N],dis[N],ch[N][M];
	void Init(){tot=lst=root=1;}
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
	void BFS(int sx,int fst){
		for(int i=1;i<=tot;i++)dis[i]=0;
		queue<int>q;q.push(sx);dis[sx]=1;
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<M;i++){
				int y=ch[x][i];
				if(!y)a[fst][i]=min(a[fst][i],(ll)dis[x]);
				else if(!dis[y]){dis[y]=dis[x]+1;q.push(y);}
			}
		}
	}
}sam;
struct Matrix{
	ll a[M][M];
	void Init(){for(int i=0;i<M;i++)for(int j=0;j<M;j++)a[i][j]=inf;}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<M;i++){
			for(int j=0;j<M;j++){
				for(int k=0;k<M;k++){
					C.a[i][j]=min(C.a[i][j],A.a[i][k]+B.a[k][j]);
				}
			}
		}
		return C;
	}
}Ans,tot;
ll Check(ll t){
	t--;
	memcpy(tot.a,a,sizeof(tot.a));
	memcpy(Ans.a,a,sizeof(Ans.a));
	while(t){
		if(t&1)Ans=Ans*tot;
		tot=tot*tot;
		t>>=1;
	}
	ll ans=inf;
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){
			ans=min(ans,Ans.a[i][j]);
		}
	}
	return ans;
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	n=read();scanf("%s",s+1);m=strlen(s+1);sam.Init();
	for(int i=1;i<=m;i++)sam.Insert(s[i]-'A');
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++)a[i][j]=inf;
		sam.BFS(sam.ch[1][i],i);
	}
	ll l=1,r=1e18,ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(Check(mid)>=n){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}