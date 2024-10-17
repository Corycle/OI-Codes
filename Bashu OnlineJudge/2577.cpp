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
int f[2005][2005],s[2005][2005],s2[2005][2005],a[2005],g[2005]={0},n,minn,maxx;
int main(){
	int i,j,k,t;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(i=1;i<=n*2;i++){
		g[i]=g[i-1]+a[i];
		f[i][i]=0;
		s[i][i]=i;
	}
	for(t=2;t<=n;t++){
		for(i=1;i<=2*n-t+1;i++){
			j=i+t-1;
        	f[i][j]=0x7ffffff;
//			f[i][j]=min(f[i+1][j],f[i][j-1])+g[j]-g[i-1];
//			f2[i][j]=max(f2[i+1][j],f2[i][j-1])+g[j]-g[i-1];
			for(k=s[i][j-1];k<=s[i+1][j];k++){
				if(f[i][j]>f[i][k-1]+f[k][j]){
					f[i][j]=f[i][k-1]+f[k][j];
					s[i][j]=k;
				}
			}
			f[i][j]+=g[j]-g[i-1];
    	}
	}
	minn=0x7ffffff,maxx=0;
	for(i=1;i<=n;i++){
		minn=min(minn,f[i][i+n-1]);
	}
	for(t=2;t<=n;t++){
		for(i=1;i<=2*n-t+1;i++){
			j=i+t-1;
			f[i][j]=max(f[i+1][j],f[i][j-1]);
			f[i][j]+=g[j]-g[i-1];
    	}
	}
	for(i=1;i<=n;i++){
		maxx=max(maxx,f[i][i+n-1]);
	}
	cout<<minn<<endl<<maxx;
	return 0;
}