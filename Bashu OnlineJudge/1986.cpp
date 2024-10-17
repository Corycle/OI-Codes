#include<iostream>
#include<algorithm>
#include<string>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<cstring>
#define LL long long int 
using namespace std;
struct node{
    int num;
    int mincost;
    node(int _num=0,int _mincost=0):num(_num),mincost(_mincost){}
};
bool operator <(node a,node b){
    return a.mincost>b.mincost;
}
int n,T,a[50005],dp[50005];
int check(int x){
	int i,j,k;
    dp[0]=0;
    priority_queue<node>que;
    que.push(node(0,0));
    for(i=1;i<=n;i++){
        while(!que.empty()){
            node u=que.top();
            if(i-u.num-1<=x){
                dp[i]=a[i]+u.mincost;
                que.push(node(i,dp[i]));
                break;
            }
            else{
                que.pop();
            }
        }
        if(n-i<=x){//到了末尾我们最多可以空x道题不写，所以如果此时dp[i]小于等于所给的时间T时，说明发怒度x满足条件，check返回1
            if(dp[i]<=T){
				return 1;
            }
        }
    }
    return 0;
}
int main(){
	int i,j,k;
    scanf("%d%d",&n,&T);
    for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
    int l=-1,r=n;
    while(r-l>1){
        int mid=(r+l)/2;
        if(check(mid))
        r=mid;
        else 
        l=mid;
    }
    printf("%d",r);
    return 0;
}