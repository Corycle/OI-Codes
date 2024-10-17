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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Len,top,tot=1,st[N],vis[N];
struct Tree{int ch[27],flag;}t[N];
void Insert(char s[],int num){
	int p=1,len=strlen(s+1);
	for(int i=1;i<=len;i++){
		int x=s[i]-'a'+1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].flag=num;
}
void Add(int p){
	if(!vis[p]&&t[p].flag){
		vis[p]=1;
		st[++top]=p;
	}
}
void DFS(int p,int depth,int flag){
	if(depth==Len+1){
		Add(p);
		if(flag){
			for(int i=1;i<=26;i++){
				if(!t[p].ch[i])continue;
				DFS(t[p].ch[i],depth,0);
			}
		}
		return;
	}
	int x=s[depth]-'a'+1;
	if(t[p].ch[x])DFS(t[p].ch[x],depth+1,flag);
	if(flag){
		DFS(p,depth+1,0);
		for(int i=1;i<=26;i++){
			if(!t[p].ch[i])continue;
			DFS(t[p].ch[i],depth,0);
			DFS(t[p].ch[i],depth+1,0);
		}
	}
}
void Query(char s[]){
	int p=1;Len=strlen(s+1);
	for(int i=1;i<=Len;i++){
		int x=s[i]-'a'+1;
		if(!t[p].ch[x])break;
		p=t[p].ch[x];
		if(i==Len&&t[p].flag){
			printf("-1\n");
			return;
		}
	}
	DFS(1,1,1);
	printf("%d\n",top);
	while(top)vis[st[top--]]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){scanf("%s",s+1);Insert(s,i);}
	for(int i=1;i<=m;i++){scanf("%s",s+1);Query(s);}
	return 0;
}