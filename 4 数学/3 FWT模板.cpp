inline void FWT(int *a,int n,int f){
    for (int k=1;k<n;k<<=1)
        for (int i=0;i<n;i+=(k<<1))
            for (int j=0;j<k;j++)
                if (f==1){
                    int x=a[i+j],y=a[i+j+k];
                    //and:a[i+j]+=a[i+j+k];
                    //or :a[i+j+k]+=a[i+j];
                    //xor:a[i+j]=x+y;a[i+j+k]=x-y;
                } else{
                    int x=a[i+j],y=a[i+j+k];
                    //and:a[i+j]-=a[i+j+k];
                    //or :a[i+j+k]-=a[i+j];
                    //xor:a[i+j]=(x+y)/2;a[i+j+k]=(x-y)/2;
                }
}
