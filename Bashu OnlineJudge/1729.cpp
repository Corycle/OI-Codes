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
const int N=12005;
const int M=150;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,Ans;
int a[N],f[M][N],Root[N],st[M],ed[M],pos[N];
struct Tree{int ch[2],sum;};
struct Trie{
	int tot;
	Tree t[N*32];
	void Insert(int &p,int y,int v){
		p=++tot;
		int x=p;t[x]=t[y];
		for(int i=30;i>=0;i--){
			int c=(v>>i)&1;
			t[x].ch[c]=++tot;
			t[t[x].ch[c]]=t[t[y].ch[c]];
			x=t[x].ch[c];y=t[y].ch[c];
			t[x].sum++;
		}
	}
	int Query(int x,int y,int v){
		int ans=0;
		for(int i=30;i>=0;i--){
			int c=(v>>i)&1;
			int num=t[t[y].ch[c^1]].sum-t[t[x].ch[c^1]].sum;
			if(num){x=t[x].ch[c^1];y=t[y].ch[c^1];ans+=(1<<i);}
			else{x=t[x].ch[c];y=t[y].ch[c];}
		}
		return ans;
	}
}tree;
int Query(int l,int r){
	int x=pos[l],ans=f[x+1][r];
	for(int i=l;i<=min(ed[x],r);i++){
		if(l)ans=max(ans,tree.Query(Root[l-1],Root[r],a[i]));
		else ans=max(ans,tree.Query(Root[l],Root[r],a[i]));
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]^read();
	for(int i=1;i<=n;i++)tree.Insert(Root[i],Root[i-1],a[i]);
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(n,ed[num-1]+M);}
	for(int i=1;i<=num;i++){
		for(int j=st[i];j<=ed[i];j++)pos[j]=i;
		for(int j=st[i];j<=n;j++)f[i][j]=max(f[i][j-1],tree.Query(Root[st[i]-1],Root[j],a[j]));
	}
	while(m--){
		int l=(read()%n+Ans%n)%n+1;
		int r=(read()%n+Ans%n)%n+1;
		if(l>r)swap(l,r);
		printf("%d\n",Ans=Query(l-1,r));
	}
	return 0;
}