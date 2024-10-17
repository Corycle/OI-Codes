#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
using namespace std;

struct missile{
	int s1,s2,x,y;
}a[100005];
bool cmp(missile a,missile b){
	return a.s1<b.s1;
}
int main(){
	int x1,x2,y1,y2,n;
	cin>>x1>>y1>>x2>>y2>>n;
	for(int i=1;i<=n;i++)
	{	scanf("%d%d",&a[i].x,&a[i].y);
		a[i].s1=(a[i].x-x1)*(a[i].x-x1)+(a[i].y-y1)*(a[i].y-y1);
		a[i].s2=(a[i].x-x2)*(a[i].x-x2)+(a[i].y-y2)*(a[i].y-y2);
	}
	sort(a+1,a+n+1,cmp);
	int rb=0,mn=1000000000;
	
	for(int i=n;i;i--)
	{	rb=max(a[i+1].s2,rb);
		mn=min(mn,a[i].s1+rb);
	}
	cout<<mn;
	return 0;
}