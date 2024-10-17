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
struct _{
	int x,y,p;
};
//vector<_>_;
//stack<_>_;
queue<_>q;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int t,n,m,a[305][305],L,sx,sy,tx,ty,fl;
int s1[10]={0,1,2,1,2,-1,-2,-1,-2};
int s2[10]={0,2,1,-2,-1,2,1,-2,-1};
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		while(q.size())q.pop();
		fl=0;
		scanf("%d%d%d%d%d",&L,&sx,&sy,&tx,&ty);
		if(sx==tx&&sy==ty){
			printf("0\n");
			continue;
		}
		_ o;
		o.x=sx;o.y=sy;o.p=0;
		a[sx][sy]=1;
		q.push(o);
		while(q.size()){
			_ now=q.front();
			q.pop();
			for(int i=1;i<=8;i++){
				_ to;
				to.x=now.x+s1[i];
				to.y=now.y+s2[i];
				to.p=now.p+1;
				if(0<=to.x&&to.x<=L&&0<=to.y&&to.y<=L&&a[to.x][to.y]==0){
					a[to.x][to.y]=1;
					q.push(to);
					if(to.x==tx&&to.y==ty){
						printf("%d\n",to.p);
						fl=1;
						break;
					}
				}
				if(fl==1)break;
			}
		}
	}
	return 0;
}