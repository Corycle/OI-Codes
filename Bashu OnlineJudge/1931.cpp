#include<iostream>
#include<iomanip>
//#include<cmath>
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
int x1,x2,y1,y2,k,father[1000002],n,m,ans;
int f(int x,int y){
    return n*(x-1)+y;   
}
int find(int x){
    if(father[x]!=x)father[x]=find(father[x]);
    return father[x];
}
main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
    scanf("%d%d",&m,&n);
    for(i=1;i<=m*n;i++)
    father[i]=i;
    while(cin>>x1>>y1>>x2>>y2){
        int p=find(f(x1,y1)),q=find(f(x2,y2));
        if(p!=q){
			father[p]=q;
			k++;
		}
    }
    for(i=1;i<=n;i++){
    	for(j=1;j<m;j++){
    	    if(k==n*m-1)break;
    	    int x,y;
    	    x=find(f(j,i));
			y=find(f(j+1,i));
			if(x!=y){
				father[x]=y;
				k++;
				ans++;
			}
    	}
	}
    for(j=1;j<=m;j++){
    	for(i=1;i<n;i++){
        	if(k==n*m-1)break;
        	int x,y;
        	x=find(f(j,i));
			y=find(f(j,i+1));
        	if(x!=y){
				father[x]=y;
				k++;
				ans+=2;
			}
    	}
	}
    printf("%d",ans);
    return 0;
}