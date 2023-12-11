#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include <time.h>
#include <stdbool.h>

#define ll long long int
int st[35];
int qu[35];
int end=-1;
int stq=0;
int endq=-1;

void st_push(int data)
{
    end++;
    st[end]=data;

}
void st_pop()
{
   end=end-1;
   return;
}
bool st_empty()
{
    if(end==-1) return true;
    return false;
}
int st_top()
{
    return st[end];
}



void q_push(int data)
{
    endq++;
    qu[endq]=data;

}
void q_pop()
{
    stq+=1;
    return;
}
bool q_empty()
{
    if(stq>endq) return true;
    return false;
}
int q_front()
{
    return qu[stq];
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a=*b;
    *b=temp;
}

// Function to generate permutations of an array arr
int ind=0;
void permutations(int arr[], int size, int index,int perm[10000][31])
{
    if(index==size-1)
    {
        for(int i=0;i<size;i++)
        {
           // printf("%d ", arr[i]);
            perm[ind][i]=arr[i];
        }
        ind+=1;
        //printf("\n");
        return;
    }

    for (int i=index;i<size;i++)
    {
        swap(&arr[index],&arr[i]);

        permutations(arr,size,index + 1,perm);

        swap(&arr[index],&arr[i]); // Backtrack
    }
}
int isStackPermutation(int N,int A[],int B[])
{
    for(int i=0;i<N;i++) q_push(B[i]);
    //for(int i=0;i<N;i++) printf("%d ",qu[i]);
    for(int i=0;i<N;i++)
    {
        st_push(A[i]);
        //printf("%d ",stq);
        //printf("%d ",q_front());
        while(st_empty()==false && q_empty()==false && st_top()==q_front())
        {
           // printf("%d ",st_top());
            //printf("%d ",q_front());
            st_pop();
          //  printf("%d ",end);
            q_pop();
        }

    }
    //printf("%d",st_top());
    // printf("%d",q_front());
    int check=st_empty();
    end=-1;
    stq=0;
    endq=-1;
    if(check) return 1;
    else return 0;
}
int fact(int n)
{
    int prev=1;
    if(n==0 || n==1) return prev;
    for(int i=2;i<=n;i++)
    {
        prev=(prev*(i));
    }
    return prev;
}
int number_stack_per(int n)
{
    int dp[n+2];
    dp[0]=1;
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++)
    {
        int temp=0;
        for(int j=0;j<i;j++)
        {
            temp+=(dp[j]*dp[i-j-1]);
        }
        dp[i]=temp;
    }
    return dp[n];

}
int main()
{
   // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,k;
        scanf("%d",&n);
        scanf("%d",&k);
        // printf("%d",n);
        // st_push(10);
        // printf("%d ",st_empty());
        // printf("%d ",st_top());
        // st_pop();
        // st_push(11);
        // printf("%d ",st_empty());
        // st_push(19);
        printf("%d ",number_stack_per(n));
        // printf("%d ",st_top());
        // // q_push(12);
        // q_push(133);
        // q_pop();
        // // q_pop();
        // q_push(12);
        // q_pop();
        // q_push(111);
        int a[n];
        for(int i=0;i<n;i++)
        {
            a[i]=i+1;
            // printf("%d ",a[i]);
        }
        // printf("%d",isStackPermutation(3,a,b));

        int count=0;
        int perm[10000][31];
        permutations(a, n, 0,perm);
        int flag=0;
        ind=0;
        // printf("%d ",fact(n));
        for(int i=0;i<fact(n);i++)
        {
            int b[n];
            for(int j=0;j<n;j++)
            {
                // printf("%d ",perm[i][j]);
                b[j]=perm[i][j];
            }
            // for(int j=0;j<n;j++)
            // {
            //     printf("%d ",perm[i][j]);
            //     // printf("%d ",b[j]);
            // }
            // printf("\n");
            if(isStackPermutation(n,a,b)) count++;

            if(count==k)
            {
                for(int x=0;x<n;x++)
                {
                    printf("%d ",b[x]);

                }
                flag=1;
                break;
            }
            if(flag==1) break;
            // printf("\n");
        }
        if(flag==0) printf("-1");
        printf("\n");

    }
        // printf("%d ",q_front());



}