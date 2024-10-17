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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
vector<int>G[N];
int f[N],g[N],num[N],tmp[N];
struct Heap{
	priority_queue<int>q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	void Clear(){
		while(q1.size())q1.pop();
		while(q2.size())q2.pop();
	}
	int Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.top();
	}
}F;
struct Node{
	int tot,ans[N];
	vector<int>P[N];
	void Insert(int l,int r,int val){if(l>n)return;P[l].push_back(val);if(r<n)P[r+1].push_back(-val);}
	void Solve(){
		F.Clear();
		for(int i=1;i<=n;i++){
			for(auto tmp:P[i])tmp>0?F.Insert(tmp):F.Delete(-tmp);
			ans[i]=F.Top();
		}
	}
}F0,F1;
pii P[N*2];
void Calc(int x,int fa){//even
	int tot=0;num[x]=0;F.Clear();
	for(auto y:G[x]){
		num[x]++;num[y]=-1;
		P[++tot]=mp(f[y]+1,-x);
		if(y!=fa){
			P[++tot]=mp(f[y]+1,+y);
			for(auto z:G[y])if(z!=x){
				num[y]++;
				P[++tot]=mp(f[z]+1,-y);
			}
			F.Insert(num[y]);
		}
	}
	sort(P+1,P+tot+1);
	for(int i=1;i<=tot;i++){
		int y=abs(P[i].scd);
		F0.Insert(2,P[i].fst*2,num[x]+F.Top());
		if(P[i].scd>0){F.Delete(num[y]);F.Insert(++num[y]);}
		else{
			if(y==x)num[x]--;
			else{F.Delete(num[y]);F.Insert(--num[y]);}
		}
	}
}
void DFS1(int x,int fa){for(auto y:G[x])if(y!=fa){DFS1(y,x);f[x]=max(f[x],f[y]+1);}}
void DFS2(int x,int fa){
	if(fa)swap(f[fa],g[x]);
	int tot=0;Calc(x,fa);
	for(auto y:G[x])tmp[++tot]=f[y]+1;
	sort(tmp+1,tmp+tot+1);tmp[tot+1]=0;
	for(int i=1;i<=tot;i++){//odd
		F0.Insert(2,tmp[i]*2,tot-i+1);
		F1.Insert(1,tmp[i]*2-1,tot-i+1);
		if(tmp[i]<tmp[i+1])F1.Insert(1,tmp[i]*2+1,tot-i+1);
	}
	for(auto y:G[x])if(y!=fa)g[y]=(f[y]+1==tmp[tot]?tmp[tot-1]:tmp[tot]);
	for(auto y:G[x])if(y!=fa)DFS2(y,x);
	if(fa)swap(f[fa],g[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS1(1,0);DFS2(1,0);F0.Solve();F1.Solve();F1.ans[1]++;
	for(int i=1;i<=n;i++)printf("%d ",(i&1)?F1.ans[i]:F0.ans[i]);
	return 0;
}
