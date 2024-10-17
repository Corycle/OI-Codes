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
int n,f[200005],s;
int dzh[200005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>dzh[i];
		f[i]=1;
	}
	int l,h,mid,p=0;
	for(i=1;i<=n;i++){
        if(dzh[i]>f[p]){  
            f[++p]=dzh[i];  
        }
        else{  
            l=1,h=p;
            while(l<=h){  
                mid=(l+h)/2;  
                if(dzh[i]>f[mid])l=mid+1;
                else h=mid-1;
            }
            f[l]=dzh[i];
        }  
    }
	cout<<n-p;
	return 0;
}