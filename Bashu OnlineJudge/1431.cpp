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
map<int,int>dis,vis,d;
int a[4][4],b[4][4],st,ed=123456780;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int change1(int p[][4]){
	int i,j,k=0;
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			k=k*10+p[i][j];
		}
	}
	return k;
}
void change2(int x,int p[][4]){
	int i,j,k;
	for(i=3;i>=1;i--){
		for(j=3;j>=1;j--){
			p[i][j]=x%10;
			x/=10;
		}
	}
}
struct node{
	int num,xx,yy;
};
queue<node>q;
void spfa(){
	int i,j,k;
	d[st]=1;
	dis[st]=0;
	while(q.size()){
		int now=q.front().num,x[4][4];
		i=q.front().xx;j=q.front().yy;
		q.pop();vis[now]=0;
		change2(now,x);
		for(k=1;k<=4;k++){
			if(1>i+dx[k]||i+dx[k]>3||1>j+dy[k]||j+dy[k]>3)continue;
			int y[4][4];
			node des;
			memcpy(y,x,sizeof(y));
			swap(y[i][j],y[i+dx[k]][j+dy[k]]);
			des.num=change1(y);
			des.xx=i+dx[k];
			des.yy=j+dy[k];
			if(d[des.num]==0){
				d[des.num]=1;
				dis[des.num]=0x3f3f3f3f;
			}
			if(dis[now]+1<dis[des.num]){
				dis[des.num]=dis[now]+1;
//				cout<<now<<" "<<des.num<<" "<<des.xx<<" "<<des.yy<<" "<<dis[des.num]<<endl;
//				system("pause");
				if(des.num==ed)return;
				if(vis[des.num]==0){
					vis[des.num]=1;
					q.push(des);
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	node first;
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			a[i][j]=read();
			if(a[i][j]==0){
				first.xx=i;
				first.yy=j;
			}
		}
	}
	st=change1(a);
	change2(ed,b);
//	cout<<first.xx<<endl<<first.yy<<endl;
	first.num=st;
	q.push(first);
	spfa();
	if(d[ed]==0)printf("Impossible");
	else printf("%d",dis[ed]);
	return 0;
}