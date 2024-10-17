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
const int N=600005;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],b[N],p1[N],p2[N],Root[N];
struct Tree{int ch[2],sum;};
struct Trie{
	int tot;
	Tree t[N*M];
	int Insert(int x,int num){
		int p=++tot,y=p;
		t[y]=t[x];t[y].sum++;
		for(int i=M;i>=0;i--){
			int c=(num>>i)&1;
			x=t[x].ch[c];
			y=t[y].ch[c]=++tot;
			t[y]=t[x];t[y].sum++;
		}
		return p;
	}
	int Query(int l,int r,int x,int y,int k){
		int ans=0;
		for(int i=l;i<=r;i++){p1[i]=x;p2[i]=y;}
		for(int i=M;i>=0;i--){
			int sum=0;
			for(int j=l;j<=r;j++){
				int c=((a[j]>>i)&1)^1;
				sum+=t[t[p2[j]].ch[c]].sum-t[t[p1[j]].ch[c]].sum;
			}
			int flag=(k<=sum);
			for(int j=l;j<=r;j++){
				int c=((a[j]>>i)&1)^flag;
				p1[j]=t[p1[j]].ch[c];
				p2[j]=t[p2[j]].ch[c];
			}
			if(k>sum)k-=sum;
			ans|=(flag<<i);
		}
		return ans;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=m;i++){
		Root[i]=tree.Insert(Root[i-1],b[i]);
	}
	int Q=read();
	while(Q--){
		int a=read(),b=read(),c=read(),d=read(),k=read();
		printf("%d\n",tree.Query(a,b,Root[c-1],Root[d],k));
	}
	return 0;
}