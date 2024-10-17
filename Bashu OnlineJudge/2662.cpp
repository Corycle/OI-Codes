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
int a[500005];
int lxx[500005];
long long ans;
void lxxsort(int l,int r){
	if(l==r)return ;
	int mid=(l+r)/2;
	lxxsort(l,mid);
	lxxsort(mid+1,r);
	int i=l,j=mid+1,p=l;
	while(i<=mid&&j<=r){
		if(a[i]>a[j]){
			lxx[p++]=a[j++];
			ans+=mid-i+1;//因为数组为有序的，ai比aj大，且ai后面的大于aj，所以ai后面的都比aj大，有mid-i+1个逆序对（比aj大） 
		}
		else lxx[p++]=a[i++];
	}
	while(i<=mid)lxx[p++]=a[i++];
	while(j<=r)lxx[p++]=a[j++];
	for(i=l;i<=r;i++)a[i]=lxx[i];
}
int main(){
	int n,i;
	while(1){
		scanf("%d",&n);
		if(!n)break;
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		memset(lxx,0,sizeof(lxx));
		ans=0;
		lxxsort(1,n);
		printf("%lld\n",ans);
	}
    return 0;
}