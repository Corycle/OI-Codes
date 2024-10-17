/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
#define pii pair<int,int>
#define mp make_pair
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
vector<pii>G[N];
struct Node{int L,R,x,ed;}P[N];
int n,m,st,ed,blk,tag,Max,cnt1,cnt2;
int a[N],b[N],c[N],d[N],lst[N],sum[N],vis[N];
bool Cover(int x,int y,int l,int r){return (x<=l&&r<=y);}
void Calc(){Max=0;for(int i=st;i<=ed;i++)Max=max(Max,b[i]);}
void Update(int l,int r,int val){
	if(r<st||l>ed)return;
	if(l<=st&&ed<=r)tag+=val;
	else{
		int L=max(l,st),R=min(r,ed);
		for(int i=L;i<=R;i++)b[i]-=val;
		Calc();
	}
}
void Solve(){
	Calc();cnt1=cnt2=tag=0;
	for(int i=1,j=0;i<=m;i++){
		sum[i]=sum[i-1];
		Update(P[i].L,P[i].R,-1);
		while(j<=m&&Max-tag>0){j++;Update(P[j].L,P[j].R,1);}
		if(P[i].R<st||P[i].L>ed)continue;
		if(Cover(P[i].L,P[i].R,st,ed)){
			sum[i]++;c[++cnt1]=i;
			P[i].ed=max(P[i].ed,j);
		}
		else{d[++cnt2]=i;lst[cnt2]=cnt1;}
	}
	
	for(int i=st;i<=ed;i++){
		int dlt=a[i];
		for(int j=1,k=0;j<=cnt2;j++){
			dlt+=sum[d[j]]-sum[d[j-1]]+Cover(P[d[j]].L,P[d[j]].R,i,i);
			if(!Cover(P[d[j]].L,P[d[j]].R,i,i))continue;
			while(k<cnt2&&dlt>0){
				k++;
				dlt-=sum[d[k]]-sum[d[k-1]]+Cover(P[d[k]].L,P[d[k]].R,i,i);
			}
			int x=d[j],y=d[k];
			if(dlt==0){
				if(Cover(P[y].L,P[y].R,i,i))P[x].ed=max(P[x].ed,y);
				else P[x].ed=max(P[x].ed,c[lst[k]+dlt]);
			}
			else if(dlt>0){
				if(dlt>sum[m]-sum[y])P[x].ed=m+1;
				else P[x].ed=max(P[x].ed,c[lst[k]+dlt]);
			}
			else if(dlt<0){
				if(Cover(P[y].L,P[y].R,i,i))P[x].ed=max(P[x].ed,c[lst[k]+dlt+1]);
				else P[x].ed=max(P[x].ed,c[lst[k]+dlt]);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=1;i<=m;i++){
		P[i].L=read();
		P[i].R=read();
		P[i].x=read();
	}
	blk=sqrt(n);
	while(ed!=n){st=ed+1;ed=min(ed+blk,n);Solve();}
	for(int i=1;i<=m;i++){
		G[i].push_back(mp(P[i].x,1));
		G[P[i].ed].push_back(mp(P[i].x,-1));
	}
	int Ans=0;
	for(int i=1;i<=m;i++){
		for(auto t:G[i]){
			vis[t.fst]+=t.scd;
			if(t.scd==1&&vis[t.fst]==1)Ans++;
			if(t.scd==-1&&vis[t.fst]==0)Ans--;
		}
		printf("%d\n",Ans);
	}
	return 0;
}