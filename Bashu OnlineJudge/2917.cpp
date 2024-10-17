#include<iostream>
using namespace std;
int a[1005][1005],s[1005][1005];
int main(){
	int m,n,r,c,ans;
	cin>>m>>n>>r>>c;
    int i,j;
    for(i=1;i<=m;i++){
    	for(j=1;j<=n;j++){
    		cin>>a[i][j];
    		s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	    } 
	}
    ans=-0x7ffffff/2;
    for(i=r;i<=m;i++){
    	for(j=c;j<=n;j++){
    		ans=max(ans,s[i][j]-s[i-r][j]-s[i][j-c]+s[i-r][j-c]);
		}	
	}
	cout<<ans;
	return 0;
}