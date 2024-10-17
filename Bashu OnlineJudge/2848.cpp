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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,pos[N],q[N*3];
int root=1,cnt=1;
struct Trie{
	int ch[27],fail,count,bj;
}t[N*3];
string addv1,addv2,addv,s[N];
void Insert(string a,int num){
	int p=root,len=a.length();
	for(int i=0;i<len;i++){
		int x=a[i]-'a';
		if(a[i]=='-')x=26;
		if(!t[p].ch[x])t[p].ch[x]=++cnt;
		p=t[p].ch[x];
	}
	t[p].bj=1;
	pos[num]=p;
}
void Build(){
	int l=1,r=1;
	q[1]=root;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<27;i++){
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
void Ask(string a){
	int p=root,len=a.length();
	for(int i=0;i<len;i++){
		int x=a[i]-'a';
		if(a[i]=='-')x=26;
		while(p&&!t[p].ch[x])p=t[p].fail;
		if(p)p=t[p].ch[x];
		else p=root;
		for(int j=p;j;j=t[j].fail){
			t[j].count+=t[j].bj;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]=s[i]+'-'+s[i];
	}
	m=read();
	for(int i=1;i<=m;i++){
		cin>>addv1>>addv2;
		addv=addv2+'-'+addv1;
		Insert(addv,i);
	}
	Build();
	for(int i=1;i<=n;i++)Ask(s[i]);
	for(int i=1;i<=m;i++)printf("%d\n",t[pos[i]].count);
	return 0;
}