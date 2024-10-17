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
#define ld long double
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const ld INF=1e60;
const ll inf=1e18;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],sum[N];
int n,A,B,C,L,R;
ll Sqr(ll x){return x*x;}
ll W(ll l,ll r){return A*Sqr(sum[r]-sum[l-1])+B*(sum[r]-sum[l-1])+C;}
namespace Task1{
	const int M=505;
	ll f[M][M];
	void Main(){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++)f[i][j]=-inf;
		}
		f[0][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=max(i-R+1,1);k<=i-L+1;k++){
					f[i][j]=max(f[i][j],f[k-1][j-1]+W(k,i));
				}
			}
		}
		ll Ans=-inf;
		for(int i=1;i<=n;i++)Ans=max(Ans,f[n][i]);
		printf("%lld",Ans);
	}
}
namespace Task2{
	ll f[N],q[N];
	ll F(ll x){return f[x]+A*Sqr(sum[x])-B*sum[x];}
	void Main(){
		int l=1,r=1;
		for(int i=1;i<=n;i++){
			while(l<r&&(F(q[l+1])-F(q[l]))>2*A*sum[i]*(sum[q[l+1]]-sum[q[l]]))l++;
			f[i]=f[q[l]]+W(q[l]+1,i);
			while(l<r&&(F(q[r])-F(q[r-1]))*(sum[i]-sum[q[r]])*A<(F(i)-F(q[r]))*(sum[q[r]]-sum[q[r-1]])*A)r--;
			q[++r]=i;
		}
		printf("%lld",f[n]);
	}
}
namespace Task3{
	ll f[N],st[N];
	struct Node{ll x,y,id;}P[N];
	ll F(ll x){return f[x]+A*Sqr(sum[x])-B*sum[x];}
	void Update(int x,int y){f[x]=max(f[x],f[y]+W(y+1,x));}
	ld Slope(int x,int y){return (ld)(P[x].y-P[y].y)/(P[x].x-P[y].x);}
	struct Segment_Tree{
		vector<int>t[N*4];
		void Insert(int x,int y,int id,int p,int l,int r){
			if(y<l||x>r)return;
			if(x<=l&&r<=y){t[p].push_back(id);return;}
			int mid=(l+r)>>1;
			Insert(x,y,id,lson);Insert(x,y,id,rson);
		}
		void Solve(int p,int l,int r){
			if(l!=r){
				int mid=(l+r)>>1;
				Solve(lson);Solve(rson);
			}
			if(t[p].size()){
				int tot=0,top=0;
				for(int i=l;i<=r;i++)P[++tot]=(Node){2*A*sum[i],F(i),i};
				sort(P+1,P+tot+1,[](Node A,Node B){return A.x!=B.x?A.x<B.x:A.y>B.y;});
				for(int i=1;i<=tot;i++){
					if(i==1||P[i].x!=P[i-1].x){
						while(top>1&&Slope(st[top-1],st[top])<=Slope(st[top],i))top--;
						st[++top]=i;
					}
				}
				for(auto x:t[p]){
					int l=2,r=top,pos=1;
					while(l<=r){
						int mid=(l+r)>>1;
						if(Slope(st[mid-1],st[mid])>sum[x]){
							pos=mid;l=mid+1;
						}
						else r=mid-1;
					}
					Update(x,P[st[1]].id);
					Update(x,P[st[pos]].id);
				}
			}
		}
	}tree;
	void Main(){
		for(int i=1;i<=n;i++)f[i]=-inf;
		for(int i=L;i<=n;i++)tree.Insert(max(i-R,0),i-L,i,1,0,n);
		tree.Solve(1,0,n);
		printf("%lld",f[n]);
	}
}
int main(){
//	freopen("paint.in","r",stdin);
//	freopen("paint.out","w",stdout);
	n=read();A=read();B=read();C=read();L=read();R=read();
	for(int i=1;i<=n;i++){a[i]=read();sum[i]=sum[i-1]+a[i];}
	if(n<=501){Task1::Main();return 0;}
	ll Min=inf;
	for(int i=1;i<=n;i++)Min=min(Min,a[i]);
	if(Min>=0&&L==1&&R==n){Task2::Main();return 0;}
	Task3::Main();
	return 0;
}