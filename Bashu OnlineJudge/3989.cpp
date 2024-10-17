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
#define pii pair<ll,ll>
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>v[N];
ll n,m,id,cnt,Max,Ans,Num;
ll h[N],sum[N],num[N],vis[N],tot[N],flag[N];
struct edge{ll to,next,data,type;}d[N*2];
struct node{ll dis,db;}ans[N][2];
void Add(ll x,ll y,ll z,ll type){
	d[++cnt]=(edge){y,h[x],z,type};
	h[x]=cnt;
}
void dfs(ll x,ll fa){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==fa)continue;dfs(y,x);
		v[x].push_back(make_pair(y,d[i].data));
	}
}
void Rebuild(ll x){
	ll len=v[x].size();
	if(len<=2){
		for(ll i=0;i<len;i++){
			ll y=v[x][i].first;
			ll z=v[x][i].second;
			Add(x,y,z,flag[y]);
			Add(y,x,z,flag[y]);
		}
	}
	else{
		ll L=++n,R=++n,tot=0;
		Add(x,L,0,0);Add(L,x,0,0);
		Add(x,R,0,0);Add(R,x,0,0);
		for(ll i=0;i<len;i++){
			ll y=v[x][i].first;
			ll z=v[x][i].second;
			if((++tot)&1)v[R].push_back(make_pair(y,z));
			else v[L].push_back(make_pair(y,z));
		}
	}
}
void Find(ll x,ll fa,ll Sum){
	sum[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[i>>1]||y==fa)continue;
		Find(y,x,Sum);sum[x]+=sum[y];
		if(Max>max(sum[y],Sum-sum[y])){
			Max=max(sum[y],Sum-sum[y]);id=i;
		}
	}
}
void Update(){
	for(ll i=1;i<=num[1];i++){
		if(ans[i][1].dis<=Num){
			tot[ans[i][1].dis]=min(tot[ans[i][1].dis],ans[i][1].db);
		}
	}
	for(ll i=1;i<=num[0];i++){
		if(ans[i][0].dis<=Num&&tot[Num-ans[i][0].dis]!=inf){
			Ans=min(Ans,ans[i][0].db+d[id].type+tot[Num-ans[i][0].dis]);
		}
	}
	for(ll i=1;i<=num[1];i++){
		if(ans[i][1].dis<=Num)tot[ans[i][1].dis]=inf;
	}
}
void Clac(ll x,ll fa,ll dis,ll db,ll pos){
	if(flag[x])ans[++num[pos]][pos]=(node){dis,db};
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(vis[i>>1]||y==fa)continue;
		Clac(y,x,dis+d[i].data,db+d[i].type,pos);
	}
}
void DFS(ll x,ll fa,ll Sum){
	Max=inf;Find(x,fa,Sum);
	if(Max==inf||Sum==1)return;
	ll S=d[id].to,T=d[id^1].to;
	vis[id>>1]=1;Num=m-d[id].data;
	if(Num>0){
		num[0]=num[1]=0;
		Clac(S,0,0,0,0);
		Clac(T,0,0,0,1);
		Update();
	}
	else if(Num==0){
		Ans=1;
		return;
	}
	ll p=sum[d[id].to];
	DFS(S,0,p);DFS(T,0,Sum-p);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll size=160<<20;//160MB
//	__asm__ ("movl %0,%%esp\n"::"r"((char*)malloc(size)+size));//调试用这个
	__asm__ ("movq %0,%%rsp\n"::"r"((char*)malloc(size)+size));//提交用这个
	Ans=inf;cnt=1;
	n=read();m=read();
	for(ll i=2;i<=n;i++){
		ll x=read()+1,y=read()+1,z=read();
		Add(x,y,z,1);Add(y,x,z,1);
	}
	dfs(1,0);
	memset(h,0,sizeof(h));cnt=1;
	memset(tot,0x3f,sizeof(tot));
	for(ll i=1;i<=n;i++)flag[i]=1;
	for(ll i=1;i<=n;i++)Rebuild(i);
	DFS(1,0,n);if(Ans==inf)Ans=-1;
	printf("%lld",Ans);
	exit(0);
	return 0;
}