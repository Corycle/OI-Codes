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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int lx,ly,s;
int dx[8]={1,1,2,2,-1,-1,-2,-2};
int dy[8]={2,-2,1,-1,2,-2,1,-1};
int f[35][35];
int bfs(){
	int i,j,k;
	queue<int>q1,q2;
	int sx=15,sy=15,tx=sx+lx,ty=sy+ly;
	q1.push(sx);q2.push(sy);
	while(q1.size()){
		int x=q1.front(),y=q2.front();
		q1.pop();q2.pop();
		if(x==tx&&y==ty){
			return f[x][y];
		}
		for(i=0;i<8;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(fx<1||fy<1||fx>30||fy>30)continue;
			if(f[fx][fy]||fx==sx&&fy==sy)continue;
			f[fx][fy]=f[x][y]+1;
			q1.push(fx);q2.push(fy);
		}
	}
}
int x,y,a,b;
int main(){
//	freopen("distance.in","r",stdin);
//	freopen("distance.out","w",stdout);
	int i,j,k;
	x=read();y=read();a=read();b=read();
	lx=abs(a-x);
	ly=abs(b-y);
	while(lx>10||ly>10){
		if(lx>ly){lx=abs(lx-2);ly=abs(ly-1);}
		else{lx=abs(lx-1);ly=abs(ly-2);}
		s++;
	}
	printf("%d",s+bfs());
	return 0;
}