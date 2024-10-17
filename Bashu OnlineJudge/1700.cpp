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
int n,ans;
struct Point{
	int x,y;
}p[1005];
int Cross(Point p1,Point p2,Point p0){
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		p[i].x=read();
		p[i].y=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int num=2;
			for(int k=j+1;k<=n;k++){
				if(Cross(p[j],p[k],p[i])==0)num++;
			}
			ans=max(ans,num);
		}
	}
	printf("%d",ans);
	return 0;
}