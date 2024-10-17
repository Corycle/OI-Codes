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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans;
int c[N],nxt[N],h[N*10],st[N*10],s[N*10],ft[N*10];
void Change(int a,int b){
	for(int i=h[a];i;i=nxt[i]){
		if(c[i+1]==b)ans--;
		if(c[i-1]==b)ans--;
	}
	for(int i=h[a];i;i=nxt[i])c[i]=b;
	nxt[st[a]]=h[b];
	h[b]=h[a];s[b]+=s[a];
	h[a]=st[a]=s[a]=0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		c[i]=read();
		ft[c[i]]=c[i];
		if(c[i]!=c[i-1])ans++;
		if(!h[c[i]])st[c[i]]=i;
		s[c[i]]++;
		nxt[i]=h[c[i]];
		h[c[i]]=i;
	}
	for(int i=1;i<=m;i++){
		int x=read();
		if(x==1){
			int a=read(),b=read();
			if(a==b)continue;
			if(s[ft[a]]>s[ft[b]])swap(ft[a],ft[b]);
			a=ft[a];b=ft[b];
			if(s[a]==0)continue;
			Change(a,b);
		}
		if(x==2)printf("%d\n",ans);
	}
	return 0;
}