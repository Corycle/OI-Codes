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
const int M=350;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans[N];
int n,m,num;
int a[N],b[N],st[N],ed[N],pos[N],sum[N];
struct Ques{
	int l,r,id;
	friend bool operator<(Ques A,Ques B){
		return A.r<B.r;
	}
};
vector<Ques>G[N];
void Prepare(){
	while(ed[num]<n){num++;st[num]=ed[num-1]+1;ed[num]=min(n,ed[num-1]+M);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
}
void Solve(int p){
	ll ans=0;
	int R=ed[p];
	for(auto Q:G[p]){
		int l=Q.l,r=Q.r,id=Q.id;
		if(r<=ed[p]){
			for(int i=l;i<=r;i++)sum[a[i]]++;
			for(int i=l;i<=r;i++)Ans[id]=max(Ans[id],1ll*sum[a[i]]*b[a[i]]);
			for(int i=l;i<=r;i++)sum[a[i]]--;
		}
		else{
			while(R+1<=r){R++;sum[a[R]]++;ans=max(ans,1ll*sum[a[R]]*b[a[R]]);}
			Ans[id]=max(Ans[id],ans);
			for(int i=l;i<=ed[p];i++)sum[a[i]]++;
			for(int i=l;i<=ed[p];i++)Ans[id]=max(Ans[id],1ll*sum[a[i]]*b[a[i]]);
			for(int i=l;i<=ed[p];i++)sum[a[i]]--;
		}
	}
	for(int i=R;i>ed[p];i--)sum[a[i]]--;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	Prepare();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		G[pos[l]].push_back((Ques){l,r,i});
	}
	for(int i=1;i<=num;i++)sort(G[i].begin(),G[i].end());
	for(int i=1;i<=num;i++)Solve(i);
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}