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
long long maxx,a[1000005],n,m,p,f[1000005],b[1000005],f1[1000005],ans;  
bool dzh;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k=1;
	cin>>n>>p;
	for(i=1;i<=n;i++){
		cin>>a[i];
	} 
    f[1]=maxx=f1[1]=a[1];  
    for(i=2;i<=n;i++){  
        f[i]=max(f[i-1]+a[i],a[i]);  
        f1[i]=max(maxx,f[i]);  
        maxx=f1[i];  
    }  
    b[1]=f1[1];  
    b[2]=f1[1]+b[1];  
    if(b[2]>=b[1])dzh=true;  
    maxx=b[2];  
    for(int i=3;i<=n;i++){  
        if(f1[i-1]>0){  
            b[i]=b[i-1]+f1[i-1];  
            if(b[i]>b[1])dzh=true;  
            if(b[i]>1000000000)b[i]%=p;  
        }  
        else b[i]=b[2];    
    }  
    if(!dzh)ans=b[1];  
    else ans=b[n];  
    ans%=p;   
    cout<<ans;
	return 0;
}
