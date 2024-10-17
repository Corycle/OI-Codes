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
const int maxn=100005;
int n,m,sum,a[maxn];
int bin(int lim){
    int s=0,cnt=1;
    for(int i=1;i<=n;i++){
        if(a[i]>lim)return n;
        if(s+a[i]<=lim)s+=a[i];
        else{
            s=a[i];
            ++cnt;
        }
    }
    return cnt;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    int l=0,r=sum,tmp,mid;
    while(l<r){
        mid=l+r>>1;
        tmp=bin(mid);
        if(tmp>m)l=mid+1;
        else r=mid;
    }
    printf("%d\n",l);
	return 0;
}