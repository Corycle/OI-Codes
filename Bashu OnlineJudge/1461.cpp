#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=70;
int n,a[N],cnt,maxn,maxnn;
bool cmp(int x,int y){return x>y;}
bool use[N];
inline void dfs(int ans,int sum,int goal,int now){
    if(sum*goal==maxn){
		printf("%d\n",goal);
		exit(0);
	}   //因为公因数是从小到大所以这里有答案直接退出
    if(maxn-ans<a[cnt])return;    //如果最小长度大于本组剩余长度return
    if(ans==goal){
		dfs(0,sum+1,goal,1);
		return;
	}    //满足长度 下一组 如果不行直接return
    for(register int i=now;i<=cnt;i++)
        if(!use[i] && ans+a[i]<=goal){
            use[i]=1;
            dfs(ans+a[i],sum,goal,i+1);
            use[i]=0;
            if(ans+a[i]==goal || ans==0)break;   //如果能组成一组却不可行或者有一组行不通直接退出
            while(a[i]==a[i+1])i++;
        }
}
int main(){
    scanf("%d",&n);
    for(register int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
		a[++cnt]=x;
		maxn+=a[cnt];
		maxnn=max(a[cnt],maxnn);
    }
    sort(a+1,a+cnt+1,cmp);
    for(register int i=maxnn;i<=maxn/2;i++)  //最小的答案大于等于最大的一根，所以从最大的一根开始
        if(maxn%i==0)dfs(0,0,i,1);    //如果是总和的公因数 那么dfs 
    printf("%d\n",maxn);
    return 0;
}