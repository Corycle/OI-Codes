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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int tot=1,lst=1,root=1;
int ch[N][30],fa[N],len[N],c[N];
void SAM(int num){
	int x=lst,fx=++tot;
	len[fx]=len[x]+1;
	while(x&&!ch[x][num]){
		ch[x][num]=fx;
		x=fa[x];
	}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;
			len[fy]=len[x]+1;
			for(int i=1;i<=26;i++){
				ch[fy][i]=ch[y][i];
			}
			fa[fy]=fa[y];
			fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){
				ch[x][num]=fy;
				x=fa[x];
			}
		}
	}
	lst=fx;
}
void DFS(int x){
	c[x]=1;
	for(int i=1;i<=26;i++){
		int y=ch[x][i];
		if(!y)continue;
		if(!c[y])DFS(y);
		c[x]+=c[y];
	}
}
void Ask(int x,int k){
	while(k){
		for(int i=1;i<=26;i++){
			int y=ch[x][i];
			if(!y)continue;
			if(k>c[y])k-=c[y];
			else{
				printf("%c",'a'+i-1);
				x=y;k--;
				break;
			}
		}
	}
	printf("\n");
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		SAM(s[i]-'a'+1);
	}
	DFS(root);
	c[root]--;
	int T=read();
	while(T--){
		int k=read()%c[root];
		if(k==0)k=c[root];
		Ask(root,k);
	}
	return 0;
}