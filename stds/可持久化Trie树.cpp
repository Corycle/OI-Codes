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
#include<ctime>
#include<vector>
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e7+5;
const int P=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
s[1] = a[0]  xor a[1] 
s[p] = s[p-1] xor a[p]
a[p] xor a[p+1] xor ... xor a[N] xor x = s[p-1] xor s[N] xor x
*/
int n,m,tot;
int a[N],s[N],root[N];
struct Trie{
	int ch[2],s;
}t[N];
int Insert(int x,int data){
	int rt=++tot;
	int y=rt;
	for(int i=P;i>=0;i--){
		t[y].ch[0]=t[x].ch[0];
		t[y].ch[1]=t[x].ch[1];
		t[y].s=t[x].s+1;
		int c=(data>>i)&1;
		x=t[x].ch[c];
		y=t[y].ch[c]=++tot;
	}
	t[y].s=t[x].s+1;
	return rt;
}
int Ask(int x,int y,int data){
	int ans=0;
	for(int i=P;i>=0;i--){
		int c=(data>>i)&1;
		if(t[t[y].ch[!c]].s-t[t[x].ch[!c]].s>0){
			x=t[x].ch[!c];y=t[y].ch[!c];
			ans+=(1<<i);
		}
		else{
			x=t[x].ch[c];y=t[y].ch[c];
		}
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read()+1;m=read();
	root[1]=Insert(0,0);
	for(int i=2;i<=n;i++){
		a[i]=read();
		s[i]=s[i-1]^a[i];
		root[i]=Insert(root[i-1],s[i]);
	}
	while(m--){
		char op[2];
		scanf("%s",op);
		if(op[0]=='A'){
			a[++n]=read();
			s[n]=s[n-1]^a[n];
			root[n]=Insert(root[n-1],s[n]);
		}
		if(op[0]=='Q'){
			int l=read(),r=read(),x=read();
			printf("%d\n",Ask(root[l-1],root[r],s[n]^x));
		}
	}
	return 0;
}
/*
有 M个操作，有以下两种操作类型：
　　1.A x：添加操作，表示在序列末尾添加一个数 x，序列的长度 N+1。
　　2.Q l r x：询问操作，你需要找到一个位置 p，满足 l<=p<=r，使得：
　　a[p] xor a[p+1] xor ... xor a[N] xor x 最大，输出最大是多少。
*/
