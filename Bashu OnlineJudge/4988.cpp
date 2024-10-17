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
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int M=27;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char a[N],b[N];
ull f1[N],f2[N];
struct SAM{
	int tot,lst,root,ch[N][M],fa[N],len[N];
	int NewNode(int x){
		tot++;len[tot]=x;fa[tot]=0;
		memset(ch[tot],0,sizeof(ch[tot]));
		return tot;
	}
	void Init(){tot=0;tot=lst=root=NewNode(0);}
	void Insert(int num){
		int x=lst,fx=NewNode(len[x]+1);
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=NewNode(len[x]+1);
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
}sam1,sam2;
ull DFS2(int x){
	if(!x)return 0;
	if(f2[x])return f2[x];
	f2[x]=1;
	for(int i=1;i<=26;i++){
		int y=sam2.ch[x][i];
		if(y)f2[x]+=DFS2(y);
	}
	return f2[x];
}
ull DFS1(int x){
	if(f1[x])return f1[x];
	f1[x]=1;
	for(int i=1;i<=26;i++){
		int y=sam1.ch[x][i];
		if(y)f1[x]+=DFS1(y);
		else f1[x]+=DFS2(sam2.ch[1][i]);
	}
	return f1[x];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s%s",a+1,b+1);
		n=strlen(a+1);m=strlen(b+1);
		sam1.Init();sam2.Init();
		for(int i=1;i<=n;i++)sam1.Insert(a[i]-'a'+1);
		for(int i=1;i<=m;i++)sam2.Insert(b[i]-'a'+1);
		for(int i=1;i<=sam1.tot;i++)f1[i]=0;
		for(int i=1;i<=sam2.tot;i++)f2[i]=0;
		printf("%llu\n",DFS1(1));
	}
	return 0;
}