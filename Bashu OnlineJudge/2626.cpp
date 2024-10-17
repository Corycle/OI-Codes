#include<iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
using namespace std;
int num,m1,m2,n,k,a1[10005],a2[10005],f[10005],vis[10005],dis[10005],cnt,h[10005];
struct edge{
	int to,next;
}d[20005];
void add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void gettree(int x,int deep){
	vis[x]=1;dis[x]=deep;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		gettree(y,deep+1);
	}
}
int main(){
	cin>>k;
	while(k--){
		int ans1=0,ans2=0;
		memset(a1,0,sizeof(a1));
		memset(a2,0,sizeof(a2));
		memset(f,0,sizeof(f));
		memset(h,0,sizeof(h));
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
		cnt=0;
		cin>>n>>m1>>m2;
		vis[0]=1;
		for(int i=1;i<n;i++){
			cin>>a1[i]>>a2[i];
			add(a1[i],a2[i]);
			add(a2[i],a1[i]);
		}
		gettree(0,0);
		int x;
		for(int i=1;i<=m1;i++){
			cin>>x;ans1+=dis[x];
		}
		for(int i=1;i<=m2;i++){
			cin>>x;ans2+=dis[x];
		}
		if(ans1<=ans2)cout<<"Bob"<<endl;
		else cout<<"Alice"<<endl;
	}
}