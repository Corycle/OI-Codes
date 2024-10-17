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
long long a[3000005],n;
int main(){
	cin>>n;
	int i,j,k;
	for(i=1;i<=n;i++){
		a[i]++;
		j=i/2;
		for(k=1;k<=j;k++)a[i]+=a[k];
	}
	cout<<a[n];
	return 0;
}