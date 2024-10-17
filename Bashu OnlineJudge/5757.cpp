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
const int N=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Node{int x,val;}a[N];
int n,m,Ans,fa[N],In[N],Out[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){fa[Find(x)]=Find(y);}
bool cmp(Node A,Node B){return A.val<B.val;}
int Calc(int x,int y){return (y-x+24)%24;}
void Solve(){
	int val1=0,val2=0;
	for(int i=1;i<=n;i++){
		if(i==1){
			val1=min(Calc(In[i],Out[i])+Out[i+n],Calc(In[i+n],Out[i+n])+Out[i]);
			val2=min(Calc(In[i],Out[i+n])+Out[i],Calc(In[i+n],Out[i])+Out[i+n]);
		}
		else{
			val1=Calc(In[i],Out[i])+Calc(In[i+n],Out[i+n]);
			val2=Calc(In[i],Out[i+n])+Calc(In[i+n],Out[i]);
		}
		
		if(val1<val2){
			Ans+=val1;
			a[i]=(Node){i,val2-val1};
			Union(i,i+2*n);Union(i+n,i+3*n);
		}
		else{
			Ans+=val2;
			a[i]=(Node){i,val1-val2};
			Union(i,i+3*n);Union(i+n,i+2*n);
		}
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int x=a[i].x;
		if(Find(x)==Find(x+n))continue;
		Ans+=a[i].val;
		Union(x,x+n);
	}
}
void Addedge(int x){
	int y=read(),st=read(),d=read();
	Out[x]=st;Ans+=d;
	if(In[y]==-1){
		In[y]=(st+d)%24;
		Union(x+2*n,y);
	}
	else{
		In[y+n]=(st+d)%24;
		Union(x+2*n,y+n);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	memset(In,-1,sizeof(In));
	for(int i=1;i<=(n<<2);i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		Addedge(i);
		Addedge(i+n);
	}
	Solve();
	printf("%d",Ans);
	return 0;
}