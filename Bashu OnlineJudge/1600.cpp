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
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
char s1[2005],s2[2005];
int a[2005][2005],l1,l2;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>s1>>s2;
	scanf("%d",&k);
	l1=strlen(s1);l2=strlen(s2);
	for(i=1;i<=l1;i++)a[i][0]=i*k;
	for(i=1;i<=l2;i++)a[0][i]=i*k;
	for(i=1;i<=l1;i++){
		for(j=1;j<=l2;j++){
			a[i][j]=min(a[i-1][j-1]+abs(s1[i-1]-s2[j-1]),min(a[i-1][j]+k,a[i][j-1]+k));
		}
	}
	printf("%d",a[l1][l2]);
	return 0;
}