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
int n,m,h[10005],cnt,f[10005];
struct edge{
	int to,next,data;
}d[200005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
queue<int>q;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
//	while(1)system("taskkill /im StudentMain.exe -t -f");
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		j=read();k=read();
		int p=read();
		hqq_add(j,k,p);
	}
	memset(f,-0x3f,sizeof(f));
	f[1]=0;
	q.push(1);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(f[y]<d[i].data+f[x]){
				f[y]=d[i].data+f[x];
				q.push(y);
			}
		}
	}
	if(f[n]==f[0])printf("-1");
	else printf("%d",f[n]);
	return 0;
}