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
int n,m,a[105],b[105],c[10005],f[10005],p;
int main(){
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
	}
	for(i=1;i<=n;i++){
		cin>>b[i];
		for(j=p+1;j<=b[i]+p;j++)c[j]=a[i];
		p+=b[i];
	}
	sort(c+1,c+p+1);
	for(i=1;i<=m;i++)f[i]=0xffffff;
	f[0]=0;
	for(i=1;i<=p;i++){
		for(j=m;j>=c[i];j--){
			f[j]=min(f[j],f[j-c[i]]+1);
		}
	}
	for(i=1;i<=m;i++){
		if(f[i]!=0xffffff)cout<<f[i]<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}