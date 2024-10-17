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
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-5;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,sum1,sum2;
int p[N];
struct node{
	int cost;
	double x[N];
}b[N];
bool cmp(node x,node y){
	return x.cost<y.cost;
}
bool pd(double x){
	return abs(x)<eps;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i].x[j]=read();
		}
	}
	for(int i=1;i<=n;i++)b[i].cost=read();
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(pd(b[i].x[j]))continue;
			if(!p[j]){
				p[j]=i;
				sum1++;
				sum2+=b[i].cost;
				break;
			}
			else{
				double dlt=b[i].x[j]/b[p[j]].x[j];
				for(int k=j;k<=m;k++){
					b[i].x[k]-=dlt*b[p[j]].x[k];
				}
			}
		}
	}
	printf("%d %d",sum1,sum2);
	return 0;
}