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
const double eps=1e-5;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int val[N],h[N],vis[N],c[N];
double dis[N],da[N*5];
struct edge{
	int to,next;
	double data;
}d[N*5];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;da[cnt]=z;
}
bool SPFA(){
	queue<int>q;
	for(int i=1;i<=n;i++){
		vis[i]=c[i]=0;
		dis[i]=inf;
	}
	dis[1]=0;
	q.push(1);
	while(q.size()){
		int x=q.front();q.pop();
		vis[x]=0;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				c[y]++;
				if(c[y]>=20)return true;
				dis[y]=dis[x]+d[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	return false;
}
bool Check(double k){
	for(int i=1;i<=cnt;i++){
		d[i].data=k*da[i]-val[d[i].to];
	}
	return SPFA();
}
double Solve(){
	double l=0,r=1e4,ans=0;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(Check(mid)){
			ans=mid;
			l=mid;
		}
		else r=mid;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		val[i]=read();
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z);
	}
	printf("%.2lf",Solve());
	return 0;
}
/*
令在一个环里，点权为 v[i]，对应的边权为 e[i]，
即要求：∑v[i]/∑e[i]最大的环
设题目答案为 Ans，即对于所有的环都有∑v[i]/∑e[i]<=Ans
变形得： Ans*∑e[i]>=∑v[i]
再得： ∑(Ans*e[i]-v[i])>=0
则有：
当 k<Ans 时，就存在至少一个环∑(k*e[i]-v[i])<0，即有负权回路；
当 k>=Ans 时，就对于所有的环∑(k*e[i]-v[i])>=0，即没有负权回路
*/
