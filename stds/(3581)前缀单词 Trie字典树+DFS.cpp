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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,tot;
int h[55],fa[55];
ll c[55],ans=1;
string s[55];
struct edge{int to,next;}d[2505];
struct trie{int next[26],flag;}t[2505];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Insert(int p){
	int len=s[p].length()-1,now=0;
	for(int i=0;i<=len;i++){
		int x=s[p][i]-'a';
		if(!t[now].next[x])t[now].next[x]=++tot;
		now=t[now].next[x];
		if(t[now].flag)fa[p]=t[now].flag;
	}
	t[now].flag=p;
}
void dfs(int x){
	ll p=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		dfs(y);
		p*=c[y];
	}
	c[x]=p+1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++){
		Insert(i);
		Add(fa[i],i);
	}
	for(int i=1;i<=n;i++){
		if(!fa[i]){
			dfs(i);
			ans*=c[i];
		}
	}
	printf("%lld",ans);
	return 0;
}
/*

Description
　　一组单词是安全的，当且仅当不存在一个单词是另一个单词的前缀，这样能保证数据不容易被误解。现在你手上有一个单词集合S，你需要计算有多少个子集是安全的。
　　注意空集永远是安全的。
Input
　　第一行一个数n，表示集合大小；
　　以下n行，每行一个由'a'..'z'构成的字符串。
Output
　　输出安全子集的个数。
Sample Input
3
hello
hell
hi

Sample Output
6

Hint
　　对于30%的数据，满足 1 ≤ n ≤ 10；
　　对于100%的数据，满足 1 ≤ n ≤ 50 ；字符串长度 ≤ 50,没有两个字符串是完全相同的。

*/ 
