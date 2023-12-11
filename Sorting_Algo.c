#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
clock_t start_time;
clock_t end_time;
double total_time_consumed=0;
void merge(int arr[],int start,int mid,int end)
{
    // cont[0]=19;
    int lt_size=mid-start+1;
    int rt_size=end-mid;
    // // printf("%d",left_size);
    // // printf("%d",right_size);
    // // printf("j");
    int left[lt_size];
    int right[rt_size];
    for(int i=0;i<lt_size;i++)
    {
        left[i]=arr[i+start];
        // printf("%d",left[i+start]);
    }
    for(int i=0;i<rt_size;i++)
    {
        right[i]=arr[i+mid+1];
        // printf("%d",right[j]);
        // printf("k");
    }
    int st1=0,st2=0;
    int index=start;
    while(st1<lt_size && st2<rt_size)
    {
        if(left[st1]>=right[st2])
        {
            arr[index]=right[st2];
            st2++;
        }
        else
        {
            arr[index]=left[st1];
            st1++;
        }
        index++;
    }

    if(st1<lt_size)
    {
        while(st1<lt_size)
        {
            arr[index]=left[st1];
            // cont[index]=right[st1];
            index++;
            st1++;
        }
    }
    if(st2<rt_size)
    {

        while(st2<rt_size)
        {
            arr[index]=right[st2];
            // cont[index]=right[st2];
            index++;
            st2++;
        }
    }
    // printf("%d",index);
    return;

}
void merge_sort(int a[],int left,int right)
{
    // cont[0]=1;
    // printf("j");
    if(left>=right) return ;

    int mid=(right+left)/2;
    // printf("%d",a[mid]);
    // printf("\n");
    merge_sort(a,left,mid);
    merge_sort(a,mid+1,right);
    merge(a,left,mid,right);
    //  merge(a,left,right,mid,cont);
    //  cont[0]=12;
    // printf("j");
     return;
}
void insertion_sort(int a[],int n)
{
    int temp=a[0];
    for(int i=0;i<n;i++)
    {
        int comp=a[i];
        int j=i-1;
        for(j=i-1;j>=0;j--)
        {
            if(comp<a[j])
            {
                a[j+1]=a[j];
            }
            else break;
        }
        a[j+1]=comp;
    }
}
void bubble_sort(int a[],int n)
{
    start_time = clock(); // start time
    for(int i=0;i<n;i++)
    {

        for(int j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                // swap(&a[j],&a[j+1]);
            }
        }
    }
    // printf("%f",total_time_consumed);

}
void selection_sort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        int element=a[i];
        int index=i;
        for(int j=i;j<n;j++)
        {
            if(element>a[j])
            {
                element=a[j];
                index=j;
            }
        }
        int temp=a[i];
        a[index]=temp;
        a[i]=element;
    }
}
int divide(int a[],int n,int left,int right)
{

    // Your code here
    int pivot=a[right];
    int next=left;
    for(int j=left;j<=right-1;j++)
    {
        if(a[j]<pivot)
        {
            // swap(a[next],a[j]);
            int temp=a[j];
            a[j]=a[next];
            a[next]=temp;
            next++;
        }
    }
    // swap(a[next],a[right]);
    int temp1=a[right];
    a[right]=a[next];
    a[next]=temp1;

    return next;
}
void quick_sort(int a[],int n,int left,int right)
{
    if(left>=right) return;
    int next=divide(a,n,left,right);
    quick_sort(a,n,left,next-1);
    quick_sort(a,n,next+1,right);
    return;
}
void array_reverse(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void add_constant(int arr[], int length, int num)
{
    int i =0;
    for(i=0;i<length;i++)
    {
        arr[i]=arr[i]+num;
    }
}

void mul_constant(int arr[], int length, int num)
{
    int i =0;
    for(i=0;i<length;i++)
    {
        arr[i]=arr[i]*num;
    }
}
int take_input()
{
    // printf("Choose the sorting algorithm which you want like \n");
    // printf(" 0 for Bubble sort \n");
    // printf(" 1 for Selection sort \n");
    // printf(" 2 for Insertion sort \n");
    // printf(" 3 for Merge sort \n");
    // printf(" 4 for Quick sort \n");
    int s;
    scanf("%d",&s);
    return s;
}
void generate(int arr[],int n,int rawdata[],int k)
{
    if(k==0)
    {
        int temp=n,num=3;
        for (temp=10000; temp<=50000; temp=temp+20000)
        {

            for(int i=0;i<n;i++)
            {
                arr[i] = rand()%10000; // Generate a number between 0 and 9999
                rawdata[i]=arr[i];
                // printf("k");
            }
        }
    }
    else if(k==1)
    {
        for(int i=0;i<n;i++)
        {
            arr[i]=i+1;
            rawdata[i]=arr[i];
        }
    }
    else
    {
        for(int i=n-1;i>=0;i--)
        {
            arr[i]=n-1-i;
            rawdata[i]=arr[i];
        }
    }
    // mul_constant(arr,n,num);
    // array_reverse(arr, 0, n-1);
    // for(int i=0;i<n;i++)
    // {
    //     printf("%d",arr[i]);
    //     printf(" ");
    // }
    // printf("\n");
}
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    //printf("%d",t);
    while(t--)
    {
        // // time_t rawtime;
        // // struct tm * timeinfo;

        // // time ( &rawtime );
        // // timeinfo = localtime(&rawtime);
        // // printf("Current local time and date: %s", asctime (timeinfo) );

        int n;
        // printf("Enter the number of Element in array \n");
        scanf("%d",&n);
        // // scanf("%d",&k);
        // // scanf("%d",&p);
        // // clock_t start, end; // For time calculation
        // // double total_time_consumed,t1,t2,t3;
        int arr[n];
        int rawdata[n];
        // // start = clock(); // start time
        // // array_reverse(arr, 0, n-1);
        // // end = clock(); // end time
        // // total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
        // // t1= total_time_consumed;
        // // start = clock(); // start time
        // // add_constant(arr,n,num);
        // // end = clock(); // end time
        // // total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
        // // t2= total_time_consumed;
        // // start = clock(); // start time
        // // mul_constant(arr,n,num*2);
        // // end = clock(); // end time
        // // total_time_consumed = ((double) (end - start)) / CLOCKS_PER_SEC;
        // // t3= total_time_consumed;
        // // printf("\n Time Consumed when n=%d => %f \t %f \t %f",n, t1, t2, t3);
        // int s=take_input();
        int s;
        scanf("%d",&s);
        int k;
        scanf("%d",&k);
        int p;
        scanf("%d",&p);
        int mini=n;
        if(n>50) mini=50;
        // int mini=min(2,50);
        if(k==0)
        {
            generate(arr,n,rawdata,k);
            if(s==0)
            {
                printf("you have choosen bubble sort");
                 start_time = clock();
                bubble_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if (s==1)
            {
                printf("you have choosen selection sort");
                start_time = clock();
                selection_sort(arr,n);
                 end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==2)
            {
                printf("you have choosen insertion sort");
                start_time = clock();
                insertion_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==3)
            {
                 printf("you have choosen merge sort");
                 start_time = clock();
                merge_sort(arr,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==4)
            {
                 printf("you have choosen quick sort");
                 start_time = clock();
                quick_sort(arr,n,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }


            if(p==0)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
            }
            else if(p==1)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                 printf("\n");
            }
            else if(p==2)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                printf("\n");
                printf("This is input data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",rawdata[i]);
                    printf(" ");
                }
                printf("\n");
            }
        }
        else if(k==1)
        {
            generate(arr,n,rawdata,k);
            if(s==0)
            {
                printf("you have choosen bubble sort");
                 start_time = clock();
                bubble_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if (s==1)
            {
                printf("you have choosen selection sort");
                start_time = clock();
                selection_sort(arr,n);
                 end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==2)
            {
                printf("you have choosen insertion sort");
                start_time = clock();
                insertion_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==3)
            {
                 printf("you have choosen merge sort");
                 start_time = clock();
                merge_sort(arr,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==4)
            {
                 printf("you have choosen quick sort");
                 start_time = clock();
                quick_sort(arr,n,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }


            if(p==0)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                 printf("\n");
            }
            else if(p==1)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                printf("\n");
            }
            else if(p==2)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                printf("\n");
                printf("This is input data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",rawdata[i]);
                    printf(" ");
                }
                printf("\n");
            }
        }
        else if(k==2)
        {
           generate(arr,n,rawdata,k);
            if(s==0)
            {
                printf("you have choosen bubble sort");
                 start_time = clock();
                bubble_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if (s==1)
            {
                printf("you have choosen selection sort");
                start_time = clock();
                selection_sort(arr,n);
                 end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==2)
            {
                printf("you have choosen insertion sort");
                start_time = clock();
                insertion_sort(arr,n);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==3)
            {
                 printf("you have choosen merge sort");
                 start_time = clock();
                merge_sort(arr,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }
            else if(s==4)
            {
                 printf("you have choosen quick sort");
                 start_time = clock();
                quick_sort(arr,n,0,n-1);
                end_time = clock(); // end time printf("%d",end)
                total_time_consumed = ((double) (end_time - start_time))/ CLOCKS_PER_SEC ;
                // printf("%f",total_time_consumed);
            }


            if(p==0)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                 printf("\n");
            }
            else if(p==1)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                 printf("\n");
            }
            else if(p==2)
            {
                printf(", total time consumed to sort -> ");
                printf(" %0.09f",total_time_consumed);
                printf("sec");
                printf("\n");
                printf("This is sorted data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",arr[i]);
                    printf(" ");
                }
                printf("\n");
                printf("This is input data \n");
                for(int i=0;i<mini;i++)
                {
                    printf("%d",rawdata[i]);
                    printf(" ");
                }
                printf("\n");
            }
        }
        printf("\n");
    //     generate(arr,n,rawdata,0);
    //     merge_sort(arr,0,n-1);
    //     printf("input Data  ");
    //     for(int i=0;i<n;i++) printf("%d ",rawdata[i]);
    //     printf("\n");
    //    for(int i=0;i<n;i++) printf("%d ",arr[i]);
    }
    return 0;
}
