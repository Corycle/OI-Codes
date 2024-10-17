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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>G[N];
int n,m,num,a[N],rd[N],ans[N];
void Solve(){
	queue<int>q;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();ans[x]=max(ans[x],a[x]);
		for(auto E:G[x]){
			int y=E.fst;
			if(!(--rd[y]))q.push(y);
			ans[y]=max(ans[y],ans[x]+E.scd);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();num=read();
	for(int i=1;i<=n;i++)a[i]=read();
	while(num--){int x=read(),y=read();G[x].push_back(mp(y,read()));rd[y]++;}
	Solve();
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
