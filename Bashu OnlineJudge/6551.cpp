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
#define ull unsigned ll
#define pii pair<int,int>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const ull Mul=131;
const int N=4e5+5;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ull P[N];
char s[N];
string S[N];
pii Right[N];
vector<int>G[N];
vector<pii>F[N];
vector<ull>Hash[N];
int n,m,Sum,MaxS,Ans,tot=1,lst=1,root=1;
int f[N],t[N],rd[N],ch[N][M],fa[N],len[N],pre[N];
void Insert(int num,int id1,int id2){
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
	lst=fx;Right[lst]=mp(id1,id2);
}
void Clear(){
	for(int i=1;i<=n;i++)Hash[i].clear();
	for(int i=1;i<=tot;i++){
		G[i].clear();
		fa[i]=len[i]=0;
		Right[i]=mp(0,0);
		memset(ch[i],0,sizeof(ch[i]));
	}
	tot=lst=root=1;
}
void DFS(int x){for(auto y:G[x]){DFS(y);Right[x]=Right[y];}}
int Find(int x,int y){for(int i=0;i<26;i++)if(ch[x][i]==y)return i;return -1;}
int GetHash(int x,int l,int r){return Hash[x][r]-Hash[x][l-1]*P[r-l+1];}
bool Check(int k){
	for(int i=1;i<=tot;i++){F[i].clear();f[i]=rd[i]=pre[i]=0;}
	for(int i=1;i<=tot;i++){
		if(len[fa[i]]<k&&k<=len[i]){
			if(k==len[fa[i]]+1){
				int x=fa[i];rd[i]++;F[x].push_back(mp(i,0));
				for(int i=0;i<26;i++)if(ch[x][i]){rd[x]++;F[ch[x][i]].push_back(mp(x,1));}
			}
			else{
				int x=i;
				for(int i=0;i<26;i++)if(ch[x][i]){rd[x]++;F[ch[x][i]].push_back(mp(x,1));}
			}
		}
	}
	queue<int>q;
	for(int i=1;i<=tot;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		for(auto t:F[x]){
			int y=t.fst,w=t.scd;
			if(f[y]<f[x]+w){f[y]=f[x]+w;pre[y]=x;}
			else if(f[y]==f[x]+w&&Find(y,x)<Find(y,pre[y]))pre[y]=x;
			if(!(--rd[y]))q.push(y);
		}
	}
	int Max=-inf;t[0]=0;
	for(int i=1;i<=tot;i++)if(rd[i])return 1;
	for(int i=1;i<=tot;i++){
		if(len[fa[i]]<k&&k<=len[i]){
			if(Max<f[i]){Max=f[i];t[t[0]=1]=i;}
			else if(Max==f[i])t[++t[0]]=i;
		}
	}
	return (Max+k>Sum);
}
bool cmp(int x,int y){
	int p1=Right[x].fst,q1=Right[x].scd-Ans+1;
	int p2=Right[y].fst,q2=Right[y].scd-Ans+1;
	int l=1,r=Ans,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(GetHash(p1,q1,q1+mid-1)==GetHash(p2,q2,q2+mid-1)){ans=mid;l=mid+1;}
		else r=mid-1;
	}
	return S[p1][q1+ans]<S[p2][q2+ans];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();P[0]=1;
	for(int i=1;i<N;i++)P[i]=P[i-1]*Mul;
	while(Case--){
		n=read();Sum=MaxS=0;
		for(int i=1;i<=n;i++){
			lst=1;
			scanf("%s",s+1);
			S[i]=" "+(string)(s+1);
			int Len=strlen(s+1);
			Hash[i].push_back(0);
			for(int j=1;j<=Len;j++){
				Insert(s[j]-'a',i,j);
				Hash[i].push_back((Hash[i][j-1]*Mul+s[j]));
			}
			Sum+=Len;MaxS=max(MaxS,Len);
		}
		for(int i=2;i<=tot;i++)G[fa[i]].push_back(i);
		DFS(root);
		int l=1,r=MaxS;Ans=MaxS+1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid))l=mid+1;
			else {Ans=mid;r=mid-1;}
		}
		printf("%d\n",Ans);
		if(Ans>MaxS)for(int i=1;i<=MaxS;i++)printf("a");
		else{
			Check(Ans);
			sort(t+1,t+t[0]+1,cmp);
			int x=Right[t[1]].fst,ed=Right[t[1]].scd;
			for(int i=ed-Ans+1;i<=Ans;i++)printf("%c",S[x][i]);
			int p=t[1];
			while(pre[p]){
				int c=Find(p,pre[p]);
				if(c>=0)printf("%c",c+'a');
				p=pre[p];
			}
		}
		puts("");
		Clear();
	}
	return 0;
}