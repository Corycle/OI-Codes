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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N][N];
int n,A,B,Flow,Cost;
int S,T,Sum,Num,tot,cnt=1;
int h[N],vis[N],dis[N],pre[N];
int L[N],R[N],num1[N],num2[N];
struct edge{int to,next,flow,cost;}d[N*100];
void Add(int x,int y,int f,int c){
	d[++cnt]=(edge){y,h[x],f,c};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0,-c};h[y]=cnt;
}
bool SPFA(int s,int t){
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
	memset(dis,0x3f,sizeof(dis));
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]>dis[x]+d[i].cost){
				dis[y]=dis[x]+d[i].cost;pre[y]=i;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
	return dis[t]<inf;
}
void Adjust(int s,int t){
	int p=0,dlt=inf;
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		dlt=min(dlt,d[p].flow);
	}
	for(int i=t;i!=s;i=d[p^1].to){
		p=pre[i];
		d[p].flow-=dlt;
		d[p^1].flow+=dlt;
	}
	Flow+=dlt;
	Cost+=dlt*dis[t];
}
void Edmonds_Karp(int s,int t){
	Flow=Cost=0;
	while(SPFA(s,t))Adjust(s,t);
}
bool Check(int Max){
	cnt=1;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		Add(S,L[i],num1[i],0);
		Add(R[i],T,num2[i],0);
		Add(L[i],R[i],Max,0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='.')Add(L[i],R[j],1,1);
		}
	}
	Edmonds_Karp(S,T);
	if(Sum!=Flow)return false;
	return Max*B<=(Sum-Cost)*A;
}
void Prepare(){
	tot=Sum=Num=0;
	memset(num1,0,sizeof(num1));
	memset(num2,0,sizeof(num2));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=0;
	while(1){
		n=read();A=read();B=read();
		if(!n&&!A&&!B)break;
		Prepare();
		int Max=n;S=++tot;T=++tot;
		for(int i=1;i<=n;i++)L[i]=++tot;
		for(int i=1;i<=n;i++)R[i]=++tot;
		for(int i=1;i<=n;i++){
			scanf("%s",a[i]+1);
			for(int j=1;j<=n;j++){
				if(a[i][j]=='/')continue;
				num1[i]++;num2[j]++;Sum++;
				if(a[i][j]=='C')Num++;
			}
		}
		while(Max>=0){
			if(Check(Max))break;
			Max--;
		}
		printf("Case %d: ",++Case);
		if(Max==-1)printf("impossible\n");
		else printf("%d\n",Sum-Num-Cost);
	}
	return 0;
}