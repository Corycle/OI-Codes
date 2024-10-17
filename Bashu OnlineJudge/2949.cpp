#include<iostream>
#include<string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>
#include <cstdio>
using namespace std;
int a[1000000];
int main()
{
    int n,c;
    while(scanf("%d%d",&n,&c)!=EOF)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        sort(a,a+n);
        int sum=0;
        int qq=1;
        for(int i=0;i<=n;i++)
        {
            if(a[i]==a[i+1])  //加速- -
            {
                qq++;
                //cout<<qq<<endl;
                continue;
            }
            int l=i+1,h=n-1,mid;
            while(l<=h)  //二分大加速
            {
                mid=(l+h)/2;
                if(a[mid]-a[i]>c) h=mid-1;
                else if(a[mid]-a[i]<c) l=mid+1;
                else break;
            }
 
            if(a[mid]-a[i]==c)
            {
                sum+=qq;
                while(a[mid]==a[mid-1]) mid--;
                while(a[mid]==a[mid+1])
                {
                    sum+=qq;
                    mid++;
                }
            }
 
            if(a[i]!=a[i+1]) qq=1;
        }
        printf("%d\n",sum);
    }
}
