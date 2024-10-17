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
const int N=800005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt,tot=1,lst=1,root=1;
int fa[N],vis[N],len[N],sum[N],ch[N][27];
void SAM(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			sum[fy]=sum[y];vis[fy]=vis[y];
			for(int i=1;i<=26;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
	while(fx&&vis[fx]!=cnt){
		vis[fx]=cnt;
		sum[fx]++;
		fx=fa[fx];
	}
}
int Count(){
	int p=root;
	int Len=strlen(s+1);
	for(int i=1;i<=Len;i++){
		int num=s[i]-'a'+1;
		if(!ch[p][num])return 0;
		else p=ch[p][num];
	}
	return sum[p];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		lst=root;cnt++;
		scanf("%s",s+1);
		int Len=strlen(s+1);
		for(int j=1;j<=Len;j++){
			SAM(s[j]-'a'+1);
		}
	}
	for(int i=1;i<=m;i++){
		scanf("%s",s+1);
		printf("%d\n",Count());
	}
	return 0;
}