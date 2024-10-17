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
const int N=200005;
const int M=27;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s1[N],s2[N];
int n,m,cnt,tot,lst,root;
int h[N],f[N],fa[N],ch[N][M],len[N],sum[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void SAM(int num){
	int x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;len[fy]=len[x]+1;
			memcpy(ch[fy],ch[y],sizeof(ch[y]));
			fa[fy]=fa[y];fa[fx]=fa[y]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		f[x]=max(f[x],f[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	tot=lst=root=1;
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1);m=read();
	for(int i=1;i<=n;i++)SAM(s1[i]-'a'+1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s2[i]=='0');
	for(int i=1;i<=tot;i++)Add(fa[i],i);
	int p=root,pos=1;
	for(int i=1;i<=n;i++){
		while(sum[i]-sum[pos-1]>m)pos++;
		p=ch[p][s1[i]-'a'+1];
		f[p]=i-pos+1;
	}
//	for(int i=1;i<=tot;i++)cout<<len[i]<<" ";cout<<endl;
//	for(int i=1;i<=tot;i++)cout<<f[i]<<" ";cout<<endl;
	DFS(root);
//	for(int i=1;i<=tot;i++)cout<<f[i]<<" ";cout<<endl;
	ll Ans=0;
	for(int i=1;i<=tot;i++){
		Ans+=max(min(f[i],len[i])-len[fa[i]],0);
	}
	printf("%lld",Ans);
	return 0;
}