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
int n,m,cnt,h[105],p[105][505],f[105][505],num[105],dis[105];
bool s[105][505][505];
struct edge{
	int to,next;
}d[205];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
struct data{
	int sum,l,ans[105],x;
}c,main_ans;
queue<data>q;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		j=read();
		if(j)hqq_add(j,i);
		else{
			printf("%d\n",i);
			c.x=i;
		}
		for(j=1;j<=m;j++){
			p[i][j]=read();
		}
	}
	if(!c.x){
		printf("not found");
		return 0;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			f[i][j]=f[i-1][j];
			for(k=1;k<=j;k++){
				if(f[i][j]<f[i-1][j-k]+p[i][k]){
					f[i][j]=f[i-1][j-k]+p[i][k];
					s[i][j][k]=1;
				}
			}
		}
	}
	printf("%d\n",f[n][m]);
	j=n;k=m;
	while(j!=0&&k!=0){
		for(i=k;i>=1;i--){
			if(s[j][k][i]){
				k-=i;
				num[j]=i;//num->装备数量 
				break;
			}
		}
		j--;
	}
	for(i=1;i<=n;i++){
		num[i]=p[i][num[i]];//num->每只鸟的战斗力 
	}
	c.sum=num[c.x];
	c.ans[++c.l]=c.x;
	q.push(c);
	while(q.size()){
		data now=q.front();
		q.pop();
		for(i=h[now.x];i;i=d[i].next){
			j=d[i].to;
			if(dis[j]<dis[now.x]+num[j]){
				data des;
				des.x=j;
				des.sum=dis[j]=dis[now.x]+num[j];
				memcpy(des.ans,now.ans,sizeof(now.ans));
				des.l=now.l+1;
				des.ans[des.l]=des.x;
				q.push(des);
				if(des.sum>main_ans.sum){
					main_ans=des;
				}
			}
		}
	}
	printf("%d",main_ans.ans[1]);
	for(i=2;i<=main_ans.l;i++){
		printf("->%d",main_ans.ans[i]);
	}
	return 0;
}