#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,rt,cnt,tot,Min;
int h[N],flag[N],p[N][M];
int dep[N],sum[N],prt[N],vis[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
struct Heap{
	priority_queue<int>Add,Del;
	void Push(int x){Add.push(x);}
	void Erase(int x){Del.push(x);}
	int Size(){return Add.size()-Del.size();}
	void Pop(){
		while(Del.size()&&Add.top()==Del.top()){
			Add.pop();Del.pop();
		}
		Add.pop();
	}
	int Top(){
		while(Del.size()&&Add.top()==Del.top()){
			Add.pop();Del.pop();
		}
		if(!Add.size())return 0;
		return Add.top();
	}
	int Sec(){
		if(Size()<2)return 0;
		int fir=Top();Pop();
		int sec=Top();Push(fir);
		return sec;
	}
};
Heap A,B[N],C[N];
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[p[x][k]]>=dep[y])x=p[x][k];
	}
	if(x==y)return x;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){x=p[x][k];y=p[y][k];}
	}
	return p[x][0];
}
int Dist(int x,int y){
	return dep[x]+dep[y]-dep[lca(x,y)]*2;
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==p[x][0])continue;
		p[y][0]=x;DFS(y,depth+1);
	}
}
void Find(int x,int fa,int num){
	int dlt=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y]||y==fa)continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		dlt=max(dlt,sum[y]);
	}
	dlt=max(dlt,num-sum[x]);
	if(Min>dlt){Min=dlt;rt=x;}
}
void Build(int x,int fa,int num){
	Min=inf;Find(x,0,num);
	x=rt;prt[x]=fa;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Build(y,x,sum[y]);
	}
}
void Turn_Off(int x,int y){
	if(x==y){
		B[x].Push(0);
		if(B[x].Size()==2)A.Push(B[x].Top());
	}
	if(!prt[x])return;
	int fa=prt[x];
	int dis=Dist(fa,y);
	int tmp=C[x].Top();
	C[x].Push(dis);
	if(dis>tmp){
		int Size=B[fa].Size();
		int Max=B[fa].Top()+B[fa].Sec();
		if(tmp)B[fa].Erase(tmp);B[fa].Push(dis);
		int now=B[fa].Top()+B[fa].Sec();
		if(now>Max){
			if(Size>=2)A.Erase(Max);
			if(B[fa].Size()>=2)A.Push(now);
		}
	}
	Turn_Off(fa,y);
}
void Turn_On(int x,int y){
	if(x==y){
		if(B[x].Size()==2)A.Erase(B[x].Top());
		B[x].Erase(0);
	}
	if(!prt[x])return;
	int fa=prt[x];
	int dis=Dist(fa,y);
	int tmp=C[x].Top();
	C[x].Erase(dis);
	if(dis==tmp){
		int Max=B[fa].Top()+B[fa].Sec();
		int Size=B[fa].Size();B[fa].Erase(dis);
		if(C[x].Top())B[fa].Push(C[x].Top());
		int now=B[fa].Top()+B[fa].Sec();
		if(now<Max){
			if(Size>=2)A.Erase(Max);
			if(B[fa].Size()>=2)A.Push(now);
		}
	}
	Turn_On(fa,y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS(1,1);ST();Build(1,0,n);
	for(int i=1;i<=n;i++)C[i].Push(0);
	for(int i=1;i<=n;i++){
		Turn_Off(i,i);//关 
		tot++;
	}
	m=read();
	while(m--){
		char s[10];
		scanf("%s",s);
		if(s[0]=='C'){
			int x=read();
			if(flag[x]){Turn_Off(x,x);tot++;}//开 -> 关 
			else{Turn_On(x,x);tot--;}//关 -> 开 
			flag[x]^=1;
		}
		if(s[0]=='G'){
			if(tot<=1)printf("%d\n",tot-1);
			else printf("%d\n",A.Top());
		}
	}
	return 0;
}