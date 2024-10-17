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
int n,m,s[1005][1005],d1[1005],d2[1005],fs,ft,vis[1005],ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	n=read();m=read();fs=read();
	memset(s,0x3f,sizeof(s));
	for(i=1;i<=m;i++){
		j=read();k=read();l=read();
		s[j][k]=min(l,s[j][k]);
	}
	for(i=1;i<=n;i++)s[i][i]=0;
	for(i=1;i<=n;i++){
		d1[i]=s[i][fs];
		d2[i]=s[fs][i];
	}
	vis[fs]=1;
	for(i=1;i<=n;i++){
		k=0;
		int minn=0x3f3f3f3f;
		for(j=1;j<=n;j++){
			if(vis[j]==0&&d1[j]!=0x3f3f3f3f&&minn>d1[j]){
				k=j;minn=d1[j];
			}
		}
		vis[k]=1;
		if(k==0)break;
		for(j=1;j<=n;j++){
			if(d1[j]>d1[k]+s[j][k]){
				d1[j]=d1[k]+s[j][k];
			}
		}
	}
	memset(vis,0,sizeof(vis));
	vis[fs]=1;
	for(i=1;i<=n;i++){
		k=0;
		int minn=0x3f3f3f3f;
		for(j=1;j<=n;j++){
			if(vis[j]==0&&d2[j]!=0x3f3f3f3f&&minn>d2[j]){
				k=j;minn=d2[j];
			}
		}
		vis[k]=1;
		if(k==0)break;
		for(j=1;j<=n;j++){
			if(d2[j]>d2[k]+s[k][j]){
				d2[j]=d2[k]+s[k][j];
			}
		}
	}
	for(i=1;i<=n;i++){
		ans=max(ans,d1[i]+d2[i]);
	}
	printf("%d",ans);
	return 0;
}