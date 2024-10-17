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
int n,a[1005][1005],f[1005][1005],ans;
int main(){
    int i,j,k;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
    	for(j=1;j<=n;j++){
    		scanf("%1d",&a[i][j]);
    		f[i][j]=a[i][j];
//    		cout<<a[i][j]<<" ";
		}
//		cout<<endl;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j])f[i][j]=max(f[i][j],min(f[i][j-1],min(f[i-1][j],f[i-1][j-1]))+1);
			ans=max(ans,f[i][j]);
//			cout<<f[i][j]<<" ";
		}
//		cout<<endl;
	}
	ans*=ans;
	printf("%d",ans);
    return 0;
}