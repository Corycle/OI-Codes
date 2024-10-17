#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int dis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=read(),k=read();
	queue<int>q;q.push(n);
	memset(dis,0x3f,sizeof(dis));
	dis[n]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x-1>=0&&dis[x-1]>dis[x]+1){
			dis[x-1]=dis[x]+1;q.push(x-1);
		}
		if(x+1<=2*k&&dis[x+1]>dis[x]+1){
			dis[x+1]=dis[x]+1;q.push(x+1);
		}
		if(x*2<=2*k&&dis[x*2]>dis[x]+1){
			dis[x*2]=dis[x]+1;q.push(x*2);
		}
	}
	printf("%d",dis[k]);
	return 0;
}