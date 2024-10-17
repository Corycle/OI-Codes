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
using namespace std;
int a[2000];  
char s[2000];  
int n,len,step;  
bool check(int a[])  
{  
     for (int i=1;i<=len/2;++i)  
         if (a[i]!=a[len-i+1]) return false;  
     return true;  
}  
int main()  
{  
    scanf("%d",&n);  
    scanf("%s",s);  
    len=strlen(s);  
    for (int i=1;i<=len;++i)  
        if (s[i-1]<'A')  
           a[i]=s[i-1]-'0';  
        else  
            a[i]=s[i-1]-'A'+10;  
    do  
    {  
            int b[2000];  
            memset(b,0,sizeof(b));  
            for (int i=1;i<=len;++i)  
                b[i]=a[i]+a[len-i+1];  
            len*=2;  
            for (int j=1;j<=len;++j)  
            {  
                b[j+1]+=b[j]/n;  
                b[j]%=n;  
            }  
            while (b[len]==0) --len;  
            for (int i=1;i<=len;++i) a[i]=b[i];  
            ++step;  
    }  
    while (!check(a)&&step<=30);  
    if (step>30) printf("Impossible\n");  
    else printf("%d\n",step);  
    return 0;  
}