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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
struct Graph{
	vector<int>G[N];
	int id,tot,num,flag,fa[N],deg[N],sum[N];
	int Find(int x){
		return x==fa[x]?x:fa[x]=Find(fa[x]);
	}
	void Init(int x){
		num=0;id=x;
		for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	}
	void Link(int x,int y){
		if(id!=0&&(x==id||y==id||flag))return;
		deg[x]++;deg[y]++;
		G[x].push_back(y);
		G[y].push_back(x);
		if(!id){
			x=Find(x);y=Find(y);
			if(x==y){num++;tot+=sum[x];}
			else{fa[x]=y;sum[y]+=sum[x];}
		}
		else if(deg[x]>2||deg[y]>2)flag=1;
		else{
			x=Find(x);y=Find(y);
			if(x==y)flag=1;
			else{fa[x]=y;sum[y]+=sum[x];}
		}
	}
}F[5];
void Build(int t){
	F[++cnt].Init(t);
	for(int x=1;x<=n;x++){
		for(auto y:F[0].G[x]){
			if(x<y)F[cnt].Link(x,y);
		}
	}
}
void Update(int x){
	Build(x);
	for(int i=0;i<3;i++){
		Build(F[0].G[x][i]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	F[0].Init(0);
	char s[10];
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		if(s[0]=='L'){
			int x=read(),y=read();
			for(int i=0;i<=cnt;i++)F[i].Link(x,y);
			if(cnt==0){
				if(F[0].deg[x]==3)Update(x);
				else if(F[0].deg[y]==3)Update(y);
			}
		}
		if(s[0]=='Q'){
			if(cnt==0){
				if(F[0].num==1)printf("%d\n",F[0].tot);
				else if(!F[0].num)printf("%d\n",n);
				else printf("0\n");
			}
			else{
				int Ans=0;
				for(int i=1;i<=cnt;i++)Ans+=(!F[i].flag);
				printf("%d\n",Ans);
			}
		}
	}
	return 0;
}