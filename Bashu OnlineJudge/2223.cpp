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
int dis[66000],a[5][5],b[5][5],vis[66000];
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int hash1(int p[][5]){
	int i,j,k=0;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			k=k*2+p[i][j];
		}
	}
	return k;
}
void hash2(int k,int p[][5]){
	int i,j;
	for(i=4;i>=1;i--){
		for(j=4;j>=1;j--){
			p[i][j]=k%2;
			k/=2;
		}
	}
}
queue<int>q;
void spfa(){
	int i,j,k;
	q.push(hash1(a));
	while(q.size()){
		int x[5][5],now=q.front();
		vis[now]=0;
		hash2(now,x);
		q.pop();
		for(i=1;i<=4;i++){
			for(j=1;j<=4;j++){
				for(k=1;k<=4;k++){
					int y[5][5];
					memcpy(y,x,sizeof(y));
					if(i+dx[k]<1||i+dx[k]>4||j+dy[k]<1||j+dy[k]>4)continue;
					swap(y[i][j],y[i+dx[k]][j+dy[k]]);
					int des=hash1(y);
					if(dis[now]+1<dis[des]){
						dis[des]=dis[now]+1;
						if(vis[des]==0){
							vis[des]=1;
							q.push(des);
						}
					}
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			char c;
			cin>>c;
			a[i][j]=c-'0';
		}
	}
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			char c;
			cin>>c;
			b[i][j]=c-'0';
		}
	}
	memset(dis,0x3f,sizeof(dis));
	dis[hash1(a)]=0;
	spfa();
	printf("%d",dis[hash1(b)]);
	return 0;
}