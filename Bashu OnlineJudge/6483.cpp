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
const double inf=9e18;
const double eps=1e-4;
const int N=1505;
const int M=10;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double f[N][N];
int n,m,g[N][N][2];
char s[N],S[N],Ans[N];
struct Tree{int num,fail,ch[M];double val;};
struct AC_Tree{
	int tot=1;
	Tree t[N];
	void Insert(double val){
		int len=strlen(s+1),p=1;
		for(int i=1;i<=len;i++){
			int c=s[i]-'0';
			if(!t[p].ch[c])t[p].ch[c]=++tot;
			p=t[p].ch[c];
		}
		t[p].num++;t[p].val+=val;
	}
	void Build(){
		queue<int>q;
		t[1].fail=1;
		for(int i=0;i<=9;i++){
			if(t[1].ch[i]){
				t[t[1].ch[i]].fail=1;
				q.push(t[1].ch[i]);
			}
			else t[1].ch[i]=1;
		}
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<=9;i++){
				if(t[x].ch[i]){
					int y=t[x].ch[i];
					t[y].fail=t[t[x].fail].ch[i];
					t[y].num+=t[t[y].fail].num;
					t[y].val+=t[t[y].fail].val;
					q.push(y);
				}
				else t[x].ch[i]=t[t[x].fail].ch[i];
			}
		}
	}
	double Solve(double v){
		for(int i=1;i<=tot;i++)t[i].val-=t[i].num*v;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=tot;j++)f[i][j]=-inf;
		}
		f[0][1]=0;
		for(int i=0;i<n;i++){
			for(int x=1;x<=tot;x++){
				if(f[i][x]==-inf)continue;
				if(S[i+1]=='.'){
					for(int j=0;j<=9;j++){
						int y=t[x].ch[j];
						if(f[i+1][y]<f[i][x]+t[y].val){
							f[i+1][y]=f[i][x]+t[y].val;
							g[i+1][y][0]=x;
							g[i+1][y][1]=j;
						}
					}
				}
				else{
					int j=S[i+1]-'0';
					int y=t[x].ch[j];
					if(f[i+1][y]<f[i][x]+t[y].val){
						f[i+1][y]=f[i][x]+t[y].val;
						g[i+1][y][0]=x;
						g[i+1][y][1]=j;
					}
				}
			}
		}
		int pos=0;
		for(int i=1;i<=tot;i++)t[i].val+=t[i].num*v;
		for(int i=1;i<=tot;i++)if(f[n][i]>f[n][pos])pos=i;
		for(int i=n,p=pos;i>=1;i--){Ans[i]=g[i][p][1]+'0';p=g[i][p][0];}
		return f[n][pos];
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	scanf("%s",S+1);
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);
		tree.Insert(log(read()));
	}
	tree.Build();
	double l=0,r=25;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(tree.Solve(mid)>0)l=mid;
		else r=mid;
	}
	tree.Solve(l);
	printf("%s",Ans+1);
	return 0;
}