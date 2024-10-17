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
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n=1,ans;
struct Point{
	int x,y;
}p[105];
int vis[105],b[105];
int Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
int Ask(Point A,Point B,Point C,Point D){
	return (Cross(C,D,A)*Cross(C,D,B)<0)&&(Cross(A,B,C)*Cross(A,B,D)<0);
}
int Check(int k,int x){
	for(int i=1;i<=k-1;i++){
		if(Ask(p[b[i]],p[b[i+1]],p[b[k]],p[x]))return 0;
	}
	return 1;
}
void dfs(int num){
	if(num==n+1){
		if(Check(num-1,1))ans++;
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&Check(num-1,i)){
			vis[i]=1;
			b[num]=i;
			dfs(num+1);
			vis[i]=b[num]=0;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d%d",&p[n].x,&p[n].y)!=EOF)n++;
	n--;
	vis[1]=b[1]=1;
	dfs(2);
	printf("%d",ans/2);
	return 0;
}