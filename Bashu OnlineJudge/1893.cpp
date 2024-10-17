#include<iostream>
#include<algorithm>
using namespace std;
struct sj
{
	long long a;
	long long b;
}z[20020];
bool cp(sj x,sj y)
 {
 	if(x.a>y.a) return 0;
 	if(x.a<y.a) return 1;
	return x.b>y.b;
 }
int main()
{
	long long n,sum=0,j,k,maxx=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>z[i].a>>z[i].b;
	sort(z+1,z+n+1,cp);
	j=z[1].a;k=z[1].b;
	maxx=k-j;sum=0;
	for(int i=2;i<=n;i++)
		{
			if(z[i].a>k){sum+=maxx;j=z[i].a;k=z[i].b;maxx=k-j;}
				else {k=max(z[i].b,k);maxx=k-j;}
		}
	sum+=maxx;
	cout<<sum;
	return 0;
}