#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
struct tom{
	int x,y;
}a[1005];
using namespace std;
int n,i,j,k,l,f[33000];
bool cmp(tom o,tom p){
	return o.y<=p.y;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++){
			scanf("%d%d",&a[i].x,&a[i].y);
			l=max(l,a[i].y);
		}
		sort(a+1,a+n+1,cmp);
		for(i=1;i<=n;i++){
			for(j=1;j<=l;j++){
				f[j]=max(f[j],f[j-1]);
				if(j==a[i].y)f[j]=max(f[j],f[a[i].x]+1);
			}
		}
		cout<<f[l]<<endl;
	}
	return 0;
}