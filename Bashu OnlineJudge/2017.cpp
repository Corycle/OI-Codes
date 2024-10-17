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
int h[10005],dfn[10005],low[10005],p[10005],b[10005],t[10005],st[10005],cd[10005],number[10005];
int cnt,n,m,tot,num,tp,ans;
struct edge{
	int to,next,s;
}d[50005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].s=x;
	h[x]=cnt;
}
void hqq_tarjan(int rt){
	int i,j,k;
	dfn[rt]=low[rt]=++tot;
	p[rt]=1;st[++tp]=rt;
	for(i=h[rt];i;i=d[i].next){
		j=d[i].to;
		if(!dfn[j]){
			hqq_tarjan(j);
			low[rt]=min(low[rt],low[j]);
		}
		else if(p[j]){
			low[rt]=min(low[rt],dfn[j]);
		}
	}
	if(dfn[rt]==low[rt]){
		num++;
		do{
			k=st[tp];
			tp--;
			p[k]=0;
			b[k]=num;
			number[num]++;
//			cout<<k<<" "<<b[k]<<endl;
		}while(k!=rt);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		j=read();k=read();
		hqq_add(j,k);
	}
	for(i=1;i<=n;i++){
		if(!dfn[i]){
			hqq_tarjan(i);
		}
	}
	for(i=1;i<=m;i++){
		j=d[i].s;
		k=d[i].to;
		if(b[j]!=b[k]){
			cd[b[j]]++;
		}
	}
	for(i=1;i<=num;i++){
		if(cd[i]==0){
			if(ans==0)ans=i;
			else{
				printf("0");
				return 0;
			}
		}
	}
	printf("%d",number[ans]);
	return 0;
}