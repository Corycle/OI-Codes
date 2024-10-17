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
#include<unordered_map>
#define ll long long
#define mp make_pair
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,q,Len;
struct Node{int l,r;}a[N];
namespace SAM{
	vector<int>G[N];
	int tot,lst,root;
	int fa[N],len[N],sum[N],dep[N],p[N][M],ch[N][M];
	inline void Insert(int num){
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
		lst=fx;sum[fx]=1;
	}
	void DFS(int x,int depth){
		dep[x]=depth;p[x][0]=fa[x];
		for(int i=1;i<=20;i++){
			if(p[x][i-1])p[x][i]=p[p[x][i-1]][i-1];
		}
		for(auto y:G[x]){
			DFS(y,depth+1);
			sum[x]+=sum[y];
		}
	}
	void Build(){
		tot=lst=root=1;
		for(register int i=1;i<=n;i++)Insert(s[i]-'a');
		for(register int i=1;i<=tot;i++)G[fa[i]].push_back(i);
		DFS(root,1);
	}
}
using namespace SAM;
namespace Task1{
	ll Ans[N];
	vector<int>S[N];
	vector<pii>F[N];
	unordered_map<int,int>vis[N];
	void Main(){
		for(register int i=1;i<=q;i++){
			scanf("%s",s+1);
			for(register int j=1;j<=Len;j++)S[i].push_back(s[j]-'a');
			int L=read()+1,R=read()+1;
			F[L-1].push_back(mp(i,-1));
			F[R].push_back(mp(i,1));
		}
		for(register int t=1;t<=m;t++){
			vis[a[t].l][a[t].r]++;
			for(auto P:F[t]){
				int id=P.fst,val=P.scd;
				for(register int i=1;i<=Len;i++){
					int p=root;
					for(register int j=i;j<=Len;j++){
						int x=S[id][j-1];
						if(!ch[p][x])break;
						p=ch[p][x];
						Ans[id]+=1ll*val*sum[p]*vis[i][j];
					}
				}
			}
		}
		for(register int i=1;i<=q;i++)printf("%lld\n",Ans[i]);
	}
}
namespace Task2{
	int pos[N],dis[N];
	inline int Climb(int x,int depth){
		for(register int k=20;k>=0;k--){
			if(len[p[x][k]]>=depth)x=p[x][k];
		}
		return x;
	}
	void Main(){
		while(q--){
			int p=root,d=0;
			scanf("%s",s+1);
			for(register int i=1;i<=Len;i++){
				int x=s[i]-'a';
				while(p&&!ch[p][x]){p=fa[p];d=len[p];}
				d=(p?d+1:0);p=(p?ch[p][x]:root);
				pos[i]=p;dis[i]=d;
			}
			ll Ans=0;
			int L=read()+1,R=read()+1;
			for(register int i=L;i<=R;i++){
				int l=a[i].l,r=a[i].r;
				if(dis[r]<r-l+1)continue;
				Ans+=sum[Climb(pos[r],r-l+1)];
			}
			printf("%lld\n",Ans);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();q=read();Len=read();
	scanf("%s",s+1);SAM::Build();
	for(register int i=1;i<=m;i++){
		a[i].l=read()+1;
		a[i].r=read()+1;
	}
	Task1::Main();
//	if(q<=sqrt(1e5))Task1::Main();
//	if(q>sqrt(1e5)) Task2::Main();
	return 0;
}