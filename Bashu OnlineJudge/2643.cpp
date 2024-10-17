#include<iostream>
using namespace std;
int n,m,a[5005],b[5005],i,j,t,k,s=0; 
main()
{
    
    cin>>n>>m;
    k=int(1.5*m);
    for(i=0;i<n;i++)
    cin>>b[i]>>a[i];
    for(i=0;i<n-1;i++)
        for(j=0;j<n-1-i;j++)
            if((a[j]<a[j+1])||(a[j]==a[j+1]&&b[j]>b[j+1]))
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                t=b[j];
                b[j]=b[j+1];
                b[j+1]=t;
            }
    for(i=0;i<n;i++)
       if(a[i]>=a[k-1]) s++; 
    cout<<a[k-1]<<" "<<s<<endl; 
    for(i=0;i<s;i++)
    cout<<b[i]<<" "<<a[i]<<endl;
    return 0;
}