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
//struct _{};
using namespace std;
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,s[1000005],t[1000005],k,i,j,l,f;
char c;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n>>k;
	for(i=0;i<=n;i++){
		s[i]=i-1;
		t[i]=i+1;
	}
	for(i=1;i<=k;i++){
		cin>>c>>j>>l;
		if(c=='A'){
			t[s[j]]=t[j];
			s[t[j]]=s[j];
			t[j]=l;
			s[j]=s[l];
			t[s[l]]=j;
			s[l]=j;
		}
		if(c=='B'){
			s[t[j]]=s[j];
			t[s[j]]=t[j];
			s[j]=l;
			t[j]=t[l];
			s[t[l]]=j;
			t[l]=j;
		}
	}
	while(1){
		f=t[f];
		if(f>n)break;
		printf("%d\n",f);
	}
	return 0;
}