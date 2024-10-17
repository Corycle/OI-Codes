#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot;
struct tree{
	int next[27],flag;
}t[400005];
void build(char a[],int p){
	int i,j,k;
	int now=0,len=strlen(a)-1;
	for(i=0;i<=len;i++){
		int x=a[i]-'a'+1;
		if(!t[now].next[x])t[now].next[x]=++tot;
		now=t[now].next[x];
	}
	t[now].flag=max(0,t[now].flag+p);
}
int ask(char a[]){
	int i,j,k;
	int now=0,len=strlen(a)-1;
	for(i=0;i<=len;i++){
		int x=a[i]-'a'+1;
		if(!t[now].next[x])return 0;
		now=t[now].next[x];
	}
	return t[now].flag;
}
int main(){
//	freopen("t1.in","r",stdin);
//	freopen("t1.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		char p=getchar(),a[105];
		while(p<'A'||'Z'<p)p=getchar();
		scanf("%s",&a);
		if(p=='A')build(a,1);
		if(p=='B')build(a,-1);
		if(p=='C'){
			if(ask(a))printf("yes\n");
			else printf("no\n");
		}
	}
	return 0;
}