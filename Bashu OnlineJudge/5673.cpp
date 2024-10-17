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
const int N=300005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
struct Node{int tag,num,fail,ch[M],son[M];};
struct Tree{
	Node t[N];
	int tot,top,root[N],sum[N];
	void Build(int rt){
		queue<int>q;
		t[rt].fail=rt;
		for(int i=0;i<26;i++){
			if(t[rt].ch[i]){
				t[rt].son[i]=t[rt].ch[i];
				t[t[rt].ch[i]].fail=rt;
				q.push(t[rt].ch[i]);
			}
			else t[rt].son[i]=rt;
		}
		while(q.size()){
			int x=q.front();q.pop();
			t[x].num=t[t[x].fail].num+t[x].tag;
			for(int i=0;i<26;i++){
				int y=t[x].ch[i];
				if(y){
					q.push(y);
					t[x].son[i]=t[x].ch[i];
					t[y].fail=t[t[x].fail].son[i];
				}
				else t[x].son[i]=t[t[x].fail].son[i];
			}
		}
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		t[x].tag+=t[y].tag;
		for(int i=0;i<26;i++){
			t[x].ch[i]=Merge(t[x].ch[i],t[y].ch[i]);
		}
		return x;
	}
	void Insert(){
		root[++top]=++tot;sum[top]=1;
		int p=root[top],len=strlen(s+1);
		for(int i=1;i<=len;i++){
			int x=s[i]-'a';
			if(!t[p].ch[x])t[p].ch[x]=++tot;
			p=t[p].ch[x];
		}
		t[p].tag=1;
		while(top>=2&&sum[top]==sum[top-1]){
			top--;
			sum[top]+=sum[top+1];
			root[top]=Merge(root[top],root[top+1]);
		}
		Build(root[top]);
	}
	int Query(){
		int ans=0,len=strlen(s+1);
		for(int k=1;k<=top;k++){
			int p=root[k];
			for(int i=1;i<=len;i++){
				int x=s[i]-'a';
				p=t[p].son[x];
				ans+=t[p].num;
			}
		}
		return ans;
	}
}tree1,tree2;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int m=read();
	while(m--){
		int op=read();
		scanf("%s",s+1);
		if(op==1){tree1.Insert();}
		if(op==2){tree2.Insert();}
		if(op==3)printf("%d\n",tree1.Query()-tree2.Query());
	}
	return 0;
}