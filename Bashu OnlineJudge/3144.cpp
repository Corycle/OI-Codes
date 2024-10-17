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
int n,f1[10005],f2[10005],f3[10005],f4[10005],p1,p2,s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n;
	int i,j,k;
	for(i=1;i<=n;i++){
		cin>>f1[i]>>f2[i]>>f3[i]>>f4[i];
	}
	cin>>p1>>p2;
	for(i=1;i<=n;i++){
		if(p1<f1[i]||p2<f2[i])continue;
		if((p1-f1[i])<=f3[i]&&(p2-f2[i])<=f4[i])s=i;
	}
	if(s==0)s--;
	cout<<s;
	return 0;
}