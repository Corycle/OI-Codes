#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define re register int
using namespace std;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,ans,cnt;
struct trie{
	int next[40],flag;
}t[200005];
char s[1005];
inline void Insert(){
	int len=strlen(s),now=0;
	s[len]='/';
	for(re i=1;i<=len;i++){//s[0] -> '/'
		int x=s[i]-'a';
		if(s[i]=='/')x=26;
		if('0'<=s[i]&&s[i]<='9')x=s[i]-'0'+27;
		if(!t[now].next[x])t[now].next[x]=++cnt;
		now=t[now].next[x];
		if(s[i]=='/'&&!t[now].flag){
			t[now].flag=1;
			ans++;
		}
	}
}
int main(){
	n=read();
	for(re i=1;i<=n;i++){
		scanf("%s",s);
		Insert();
		printf("%d\n",ans);
	}
	return 0;
}