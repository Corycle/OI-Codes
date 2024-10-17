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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int m,n,k,a[1005],b[1005],c[1005],dp[105][105],vis[100];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,z;
	cin>>m>>n;
    cin>>k;
    for(i=1;i<=k;i++){
        cin>>a[i]>>b[i]>>c[i];
    }
    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            dp[i][j]=0xffffff;
        }
    }
    int t1,t2;
    dp[0][0]=0;
    for(i=1;i<=k;i++){
        for(j=m;j>=0;j--){
            for(z=n;z>=0;z--){
                t1=j+a[i];
				t2=z+b[i];
                if(t1>=m)t1=m;
                if(t2>=n)t2=n;
                dp[t1][t2]=min(dp[t1][t2],dp[j][z]+c[i]);
            }
        }
    }
    printf("%d",dp[m][n]);
	return 0;
}