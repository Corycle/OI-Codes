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
int n,m,s[505][505],d[505],f[505],fs,ft,vis[505];
void print(int x){
	int i,j,k;
	k=f[x];
	if(f[x]!=0)print(f[x]);
	printf("%d ",x);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	n=read();m=read();
	memset(s,0x3f,sizeof(s));
	for(i=1;i<=m;i++){
		j=read();k=read();l=read();
		s[j][k]=min(l,s[j][k]);
	}
	for(i=1;i<=n;i++)s[i][i]=0;
	fs=read();ft=read();
	for(i=1;i<=n;i++){
		d[i]=s[fs][i];
		if(d[i]!=0x3f3f3f3f)f[i]=fs;
	}
	f[fs]=0;vis[fs]=1;
	for(i=1;i<=n;i++){
		k=0;
		int minn=0x3f3f3f3f;
		for(j=1;j<=n;j++){
			if(vis[j]==0&&d[j]!=0x3f3f3f3f&&minn>d[j]){
				k=j;minn=d[j];
			}
		}
		if(k==0)break;
		vis[k]=1;
		for(j=1;j<=n;j++){
			if(d[j]>d[k]+s[k][j]){
				d[j]=d[k]+s[k][j];
				f[j]=k;
			}
		}
	}
	printf("%d\n",d[ft]);
	print(ft);
	return 0;
}