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
double dfs(double x,double y,int d){
    if(x<y)swap(x,y); 
    if(d==1)return x/y;
    double ans=0xfffffff,ans1,ans2;
    double xx=x/d*1.0,yy=y/d*1.0;
    for(int i=1;i<=d/2;i++){
        ans1=max(dfs(xx*i,y,i),dfs(x-xx*i,y,d-i));
        ans2=max(dfs(x,yy*i,i),dfs(x,y-yy*i,d-i));
        ans=min(ans,min(ans1,ans2));
    }
    return ans;
}
int main(){
    int x,y;
    int n;
    scanf("%d%d%d",&x,&y,&n);
    printf("%.6lf",dfs(x,y,n));
    return 0;
}