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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,cnt,tot=1,root=1;
int q[N],pos[N],h[N];
struct Trie{
	int ch[26],fail,sum;
}t[N];
struct edge{
	int to,next;
}d[N];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Insert(int num){
	int len=strlen(s+1),p=root;
	for(int i=1;i<=len;i++){
		int x=s[i]-'a';
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
		t[p].sum++;
	}
	pos[num]=p;
}
void Build(){
	int l=1,r=1;
	q[1]=root;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<26;i++){
			int y=t[x].ch[i];
			if(!y)continue;
			q[++r]=y;
			int p=t[x].fail;
			while(p&&!t[p].ch[i])p=t[p].fail;
			if(p)t[y].fail=t[p].ch[i];
			else t[y].fail=root;
		}
	}
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y);
		t[x].sum+=t[y].sum;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		Insert(i);
	}
	Build();
	for(int i=2;i<=tot;i++){
		edge_add(t[i].fail,i);
	}
	DFS(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",t[pos[i]].sum);
	}
	return 0;
}