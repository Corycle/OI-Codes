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
int n,ans[50005];
int pd(int f){
	int i,j,k;
	for(i=2;i*i<=f;i++){
		if(f%i==0)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(scanf("%d",&n)!=EOF){
		memset(ans,0,sizeof(ans));
		for(i=2;i<=n;i++){
			if(pd(i)){
				while(n%i==0){
					n/=i;
					ans[++ans[0]]=i;
				}
			}
		}
		printf("%d",ans[1]);
		for(i=2;i<=ans[0];i++)printf("*%d",ans[i]);
		printf("\n");
	}
	
	return 0;
}