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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,D,X,Y;
ll s[N],d[N],p[N];
vector<int>b[N],g[N];
void Exgcd(int a,int b,int &d,int &x,int &y){
	if(!b){d=a;x=1;y=0;}
	else{
		Exgcd(b,a%b,d,x,y);
		int t=x;x=y;y=t-a/b*y;
	}
}
bool cmp(int x,int y){return s[x]!=s[y]?s[x]<s[y]:x>y;}
ll Solve(int m,int n,int x,vector<int>G,vector<int>B){//B Make G Happy
	if((int)G.size()==m)return -1;
	int tot=0;
	for(auto i:G){s[++tot]=1ll*i*x%m;d[tot]=i;}
	for(auto i:B){s[++tot]=1ll*i*x%m;d[tot]=i;}
	for(int i=1;i<=tot;i++)p[i]=i;
	sort(p+1,p+tot+1,cmp);
	s[p[0]=0]=s[p[tot]]-m;
	s[p[tot+1]=tot+1]=s[p[1]]+m;
	ll dis=1e18,ans=0;
	for(int i=1;i<=tot;i++)dis=min(dis+1ll*n*(s[p[i]]-s[p[i-1]]),d[p[i]]);
	for(int i=1;i<=tot;i++){
		dis=min(dis+1ll*n*(s[p[i]]-s[p[i-1]]),d[p[i]]);
		if(s[p[i]]==s[p[i+1]])continue;
		if(s[p[i]]+1==s[p[i+1]]&&p[i]<=(int)G.size())continue;
		ans=max(ans,dis+1ll*n*(s[p[i+1]]-s[p[i]]-1));
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Exgcd(m,n,D,X,Y);if(D>2e5){puts("-1");return 0;}
	int B=read();for(int i=1;i<=B;i++){int x=read();b[x%D].push_back(x/D);}
	int G=read();for(int i=1;i<=G;i++){int x=read();g[x%D].push_back(x/D);}
	X=(X+n)%n;Y=(Y+m)%m;
	for(int i=0;i<D;i++){
		if(b[i].empty()&&g[i].empty()){puts("-1");return 0;}
		Ans=max(Ans,Solve(m/D,n/D,Y,g[i],b[i])*D+i);
		Ans=max(Ans,Solve(n/D,m/D,X,b[i],g[i])*D+i);
	}
	printf("%lld",Ans);
	return 0;
}
