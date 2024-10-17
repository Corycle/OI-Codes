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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,ans,q[N],root=1;
struct Trie{
	int ch[26],bj,fail;
	void init(){
		memset(ch,0,sizeof(ch));
		bj=fail=0;
	}
}t[N];
char a[105],s[N];
void Insert(){
	int now=root,len=strlen(a+1);
	for(int i=1;i<=len;i++){
		int x=a[i]-'a';
		if(!t[now].ch[x]){
			t[now].ch[x]=++tot;
			t[tot].init();
		}
		now=t[now].ch[x];
	}
	t[now].bj++;
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
void AC(){
	int len=strlen(s+1),p=root;
	ans=0;
	for(int i=1;i<=len;i++){
		int j=s[i]-'a';
		while(p&&!t[p].ch[j])p=t[p].fail;
		if(p)p=t[p].ch[j];
		else p=root;
		for(j=p;j;j=t[j].fail){
			ans+=t[j].bj;
			t[j].bj=0;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();tot=1;
		t[tot].init();
		for(int i=1;i<=n;i++){
			scanf("%s",a+1);
			Insert();
		}
		scanf("%s",s+1);
		Build();
		AC();
		printf("%d\n",ans);
	}
	return 0;
}