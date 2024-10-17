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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}

char s[N];
int n,m,tot,cnt,tmp[2];
int a[N],h[N],b[N][2],id[N][2],vis[N],opp[N];
struct edge{int to,next;}d[N*N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
}
bool dfs(int x){
	if(vis[opp[x]])return false;vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		if(!dfs(y))return false;
	}
	return true;
}
bool Check(int pos){
	for(int i=1;i<=tot;i++)vis[i]=0;
	for(int i=1;i<=pos;i++)if(!dfs(id[i][a[s[i]-'a'+1]]))return false;
	for(int i=pos+1;i<=n;i++){
		if(vis[id[i][0]])s[i]=b[1][0]+'a'-1;
		if(vis[id[i][1]])s[i]=b[1][1]+'a'-1;
		if(!vis[id[i][0]]&&!vis[id[i][1]]){
			int x=min(b[1][0],b[1][1]);
			int y=max(b[1][0],b[1][1]);
			if(dfs(id[i][a[x]]))s[i]=x+'a'-1;
			else if(dfs(id[i][a[y]]))s[i]=y+'a'-1;
			else return false;
		}
	}
	return true;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);m=strlen(s+1);n=read();
	for(int i=1;i<=n;i++){
		id[i][0]=++tot;id[i][1]=++tot;
		opp[id[i][0]]=id[i][1];
		opp[id[i][1]]=id[i][0];
	}
	tmp[0]=tmp[1]=b[m+1][0]=b[m+1][1]=m+1;
	for(int i=m;i>=1;i--){
		tmp[a[i]=(s[i]=='V'?0:1)]=i;
		b[i][0]=tmp[0];b[i][1]=tmp[1];
	}
	int T=read();
	while(T--){
		char op1[5],op2[5];
		int x=read();scanf("%s",op1);int c1=(op1[0]=='V'?0:1);
		int y=read();scanf("%s",op2);int c2=(op2[0]=='V'?0:1);
		Add(id[x][c1],id[y][c2]);Add(id[y][c2^1],id[x][c1^1]);
	}
	scanf("%s",s+1);
	if(Check(n)){printf("%s",s+1);return 0;}
	if(b[1][0]==m+1||b[1][1]==m+1){puts("-1");return 0;}
	for(int i=n;i>=1;i--){
		int c=s[i]-'a'+1;
		int x=min(b[c+1][0],b[c+1][1]);
		int y=max(b[c+1][0],b[c+1][1]);
		if(x!=m+1){s[i]=x+'a'-1;if(Check(i)){printf("%s",s+1);return 0;}}
		if(y!=m+1){s[i]=y+'a'-1;if(Check(i)){printf("%s",s+1);return 0;}}
	}
	puts("-1");
	return 0;
}
