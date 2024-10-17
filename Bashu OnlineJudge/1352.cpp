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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,tot=1;
struct Trie{
	int ch[27],fa,flag;
}t[N];
void Insert(char s[]){
	int p=1,len=strlen(s+1);
	for(int i=1;i<=len;i++){
		int x=s[i]-'a'+1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].flag++;
}
void Query(char s[]){
	int p=1,len=strlen(s+1),ans=0;
	for(int i=1;i<=len;i++){
		int x=s[i]-'a'+1;
		if(!t[p].ch[x])break;
		p=t[p].ch[x];
		ans+=t[p].flag;
	}
	printf("%d\n",ans);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		Insert(s);
	}
	while(m--){
		scanf("%s",s+1);
		Query(s);
	}
	return 0;
}