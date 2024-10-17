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
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
double Max,ans;
int fa[N],usd[N];
struct edge{int s,t,num;double data;}e[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Insert(int x,int y,double z,int num){
	int k=0;
	z/=2;
	for(int i=cnt;i>=1;i--){
		if(e[i].data<=z){
			k=i;break;
		}
	}
	for(int i=cnt;i>k;i--)e[i+1]=e[i];
	e[k+1]=(edge){x,y,num,z};cnt++;
}
void Kruscal(){
	memset(usd,0,sizeof(usd));
	int num=1;
	double sum=0,maxx=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=cnt;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		fa[x]=y;
		usd[e[i].num]=1;
		num++;sum+=e[i].data;
		maxx=max(maxx,e[i].data);
		if(num==n){
			Max=maxx;
			ans=sum;
			return;
		}
	}
}
void Print(int Cnt){
	if(ans==0)printf("0\n");
	else{
		printf("%.2lf ",ans);
		for(int i=1;i<=Cnt;i++){
			if(usd[i])printf("%d ",i);
		}
		printf("\n");
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	Max=inf;
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		if(z>Max*2){
			Print(i);
			continue;
		}
		Insert(x,y,z,i);
		Kruscal();
		Print(i);
	}
	return 0;
}