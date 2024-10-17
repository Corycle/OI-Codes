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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string op;
int n,m,b[N];
struct edge{int s,t,w;}e[N];
bool cmp(edge A,edge B){return A.w<B.w;}
void Ask(int x,int y){
	int ans=inf;
	for(int i=1;i<=m;i++){
		if(b[e[i].s]==x&&b[e[i].t]==y){ans=e[i].w;break;}
		if(b[e[i].s]==y&&b[e[i].t]==x){ans=e[i].w;break;}
	}
	if(ans==inf)printf("No Found!\n");
	else printf("%d\n",ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)b[i]=1;
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].w=read();
	}
	sort(e+1,e+m+1,cmp);
	int T=read();
	while(T--){
		cin>>op;
		if(op=="MoveA")b[read()]=1;
		if(op=="MoveB")b[read()]=2;
		if(op=="MoveC")b[read()]=3;
		if(op=="AskAA")Ask(1,1);
		if(op=="AskAB")Ask(1,2);
		if(op=="AskAC")Ask(1,3);
		if(op=="AskBB")Ask(2,2);
		if(op=="AskBC")Ask(2,3);
		if(op=="AskCC")Ask(3,3);
	}
	return 0;
}