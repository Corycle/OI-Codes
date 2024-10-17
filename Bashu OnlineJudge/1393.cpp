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
struct hqq_edge{
	int to,next;
}d[80005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int n,m,dfn[15005],low[15005],cnt,h[15005],tot,prt[15005],ans;
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void hqq_dfs(int rt){
	int i,j,k;
	tot++;
	dfn[rt]=low[rt]=tot;
	for(i=h[rt];i;i=d[i].next){
		int y=d[i].to;
		if(prt[rt]!=y){//不是回边 
			if(dfn[y]==0){//y未被访问
				prt[y]=rt;
				hqq_dfs(y);
				low[rt]=min(low[rt],low[y]);
				if(low[y]>dfn[rt])ans++;//该边为割边  
			}
			else low[rt]=min(low[rt],dfn[y]);//y访问过 即为返祖边  
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(1){
		n=read();m=read();
		if(n==0&&m==0)break;
		cnt=tot=ans=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(prt,0,sizeof(prt));
		memset(h,0,sizeof(h));
		memset(d,0,sizeof(d));
		for(i=1;i<=m;i++){
			int x=read(),y=read();
			hqq_add(x,y);
			hqq_add(y,x);
		}
		hqq_dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}