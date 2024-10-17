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
struct data {
    int x,y;
    int city;
}a[405];
int s,t,A,B,T[105];
double dis[405];
double juli(int xx1,int yy1,int xx2,int yy2){
	return sqrt((xx1-yy1)*(xx1-yy1)+(xx2-yy2)*(xx2-yy2));
}
void p4(int xx1,int yy1,int xx2,int yy2,int x3,int y3,int i){
    int ab=(xx1-xx2)*(xx1-xx2)+(yy1-yy2)*(yy1-yy2),ac=(xx1-x3)*(xx1-x3)+(yy1-y3)*(yy1-y3),bc=(xx2-x3)*(xx2-x3)+(yy2-y3)*(yy2-y3);
    int x4,y4;
    if(ab+ac==bc)x4=xx2+x3-xx1,y4=yy2+y3-yy1;
    if(ab+bc==ac)x4=xx1+x3-xx2,y4=yy1+y3-yy2;
    if(ac+bc==ab)x4=xx1+xx2-x3,y4=yy1+yy2-y3;
    a[i+3].x=x4;
    a[i+3].y=y4;
}
queue<int>q;
bool mark[405];
void spfa(){
	int i,j,k;
	memset(mark,0,sizeof(mark));
    while(q.size())q.pop();
    for(i=1;i<=4*s;i++)dis[i]=0x3f3f3f3f;
    for(i=A*4-3;i<=A*4;i++){
    	dis[i]=0;
		q.push(i);
		mark[i]=true;
	}
    while(q.size()){
        int x=q.front();
		q.pop();
		mark[x]=0;
        for(i=1;i<=4*s;i++){
            if(i==x)continue;
            double cost=juli(a[x].x,a[i].x,a[x].y,a[i].y);
            if(a[i].city==a[x].city)cost*=T[a[i].city];
            else cost*=t;
            if(dis[x]+cost<dis[i]){
                dis[i]=dis[x]+cost;
                if(!mark[i]){
                	mark[i]=true;
					q.push(i);
				}
            }
        }
    }
}

int main() {
    int n,i,j,k;
    scanf("%d",&n);
    while(n--){
		memset(a,0,sizeof(a));
    	scanf("%d%d%d%d",&s,&t,&A,&B);
    	for(i=1;i<=4*s;i+=4){
    	    scanf("%d%d%d%d%d%d%d",&a[i].x,&a[i].y,&a[i+1].x,&a[i+1].y,&a[i+2].x,&a[i+2].y,&T[i/4+1]);
    	    a[i].city=a[i+1].city=a[i+2].city=a[i+3].city=i/4+1;
    	    p4(a[i].x,a[i].y,a[i+1].x,a[i+1].y,a[i+2].x,a[i+2].y,i);
    	}
        spfa();
        double ans=dis[B*4];
        for(i=B*4-3;i<B*4;i++)if(dis[i]<ans)ans=dis[i];
        printf("%.2lf\n",ans);
    }
}