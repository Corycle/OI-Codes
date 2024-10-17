#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int a[100005];
int lxx[100005];
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
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	lxxsort(1,n);
	printf("%lld",ans);
    return 0;
}