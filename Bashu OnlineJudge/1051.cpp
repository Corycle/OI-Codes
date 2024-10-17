#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
struct student
{	char name[25];
	int term;
	int class_;
	char ganbu;
	char xibu;
	int lunwen;
	long long money;};
int main(){
	int n,i,j,k;cin>>n;
	long long s=0;
	student a[n+1];
	for(i=1;i<=n;i++)
	{	a[i].money=0;
		cin>>a[i].name>>a[i].term>>a[i].class_>>a[i].ganbu>>a[i].xibu>>a[i].lunwen;
		if(a[i].term>80&&a[i].lunwen>=1)a[i].money+=8000;
		if(a[i].term>85&&a[i].class_>80)a[i].money+=4000;
		if(a[i].term>90)a[i].money+=2000;
		if(a[i].term>85&&a[i].xibu=='Y')a[i].money+=1000;
		if(a[i].class_>80&&a[i].ganbu=='Y')a[i].money+=850;
		s+=a[i].money;}
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(a[i].money<a[j].money)
			{	swap(a[i].name,a[j].name);
				swap(a[i].money,a[j].money);}
	puts(a[1].name);
	cout<<a[1].money<<endl<<s;
	return 0;
}