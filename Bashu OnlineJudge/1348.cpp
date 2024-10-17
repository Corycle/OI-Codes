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
#include<set>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int h[N],g[N];
struct node{int x,y;};
set<node>s;
set<node>::iterator it,lt,rt;
bool operator<(node a,node b){return a.y<b.y;}
bool cmp(int a,int b,int i){
	return (abs(h[a]-h[i])<abs(h[b]-h[i]))||(abs(h[a]-h[i])==abs(h[b]-h[i])&&h[a]<h[b]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++){
		node p=(node){i,h[i]};
		s.insert(p);
		it=s.find(p);
		lt=rt=it;m=0;
		if(lt!=s.begin()){lt--;g[++m]=lt->x;}
		if(++rt!=s.end())g[++m]=rt->x;
		if(i>=2){
			int ans=0;
			if(m<2||cmp(g[1],g[2],i))ans=g[1];
			else ans=g[2];
			printf("%d %d\n",abs(h[i]-h[ans]),ans);
		}
	}
	return 0;
}