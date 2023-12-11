#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include <time.h>

#define ll long long int

struct node
{
    int data;
    struct node *next;
};


struct node* add_node(struct node **head,struct node **root)
{
    struct node *temp=*root;
    struct node *st=*root;
    int rem=0;
    struct node *ans=*head;
    struct node *prev=(struct node*)malloc(sizeof(struct node));
    struct node *prev1=(struct node*)malloc(sizeof(struct node));
    prev->next=NULL;
    prev->data=0;
    prev1->next=NULL;
    prev1->data=0;
    while(*head!=NULL && *root!=NULL)
    {
        prev=*head;
        int x=(*head)->data+(*root)->data+rem;
        (*head)->data=x%10;
        rem=x/10;
        *head=(*head)->next;
        prev1=*root;
        *root=(*root)->next;
    }
    // printf("%d",rem);
    if(*head==NULL && *root==NULL)
    {
         if(rem>0)
         {
            struct node *n=(struct node*)malloc(sizeof(struct node));
            n->next=NULL;
            n->data=rem;
            prev->next=n;

         }
    }
    else if(*head!=NULL)
    {
        struct node *start=*head;
        while(*head!=NULL)
        {
            int x=((*head)->data+rem);
            (*head)->data=x%10;
            rem=x/10;
            prev=*head;
            *head=(*head)->next;
        }
        if(rem>0)
        {
            struct node *n=(struct node*)malloc(sizeof(struct node));
            n->next=NULL;
            n->data=rem;
            prev->next=n;
        }

    }
    else
    {
        prev->next=*root;
        // printf("%d",rem);
        prev=prev->next;
        *head=prev;
        while(*head!=NULL)
        {
            int x=((*head)->data+rem);
            (*head)->data=x%10;
            rem=x/10;
            prev=(*head);
            *head=(*head)->next;
        }
        if(rem>0)
        {
            struct node *n=(struct node*)malloc(sizeof(struct node));
            n->next=NULL;
            n->data=rem;
            prev->next=n;
        }


    }
    *root=st;
    return ans;
}


void print_node(struct node *head)
{
    //printf("j");
    if(head==NULL) return ;
    int i=0;
    while(head!=NULL && i<100)
    {
        printf("%d",head->data);
        head=head->next;
        i++;
    }
    return ;
}


struct node *insert_at_begining(struct node *head,int val)
{
    struct node* n= (struct node*)malloc(sizeof(struct node));
    n->next=NULL;
    n->data=val;
    if(head==NULL)
    {
        head=n;
        return head;
    }
    else
    {
        n->next=head;
        head=n;
        return head;
    }
}

struct node* multiply(struct node *head1,struct node *head2)
{
    // if(head1==NULL) return ;
    //   print_node(head2);
    struct node *ans=(struct node*)malloc(sizeof(struct node));
    ans->next=NULL;
    ans->data=0;
    //print_node(ans);
    int i=0;
    int flag=0;
    while(head1!=NULL)
    {
        struct node *temp=NULL;
        struct node *start=NULL;

        for(int j=0;j<i;j++)
        {
            struct node *x=(struct node*)malloc(sizeof(struct node));
            // x->next=NULL;
            x->data=0;
            if(temp==NULL)
            {
                temp=x;
                start=temp;
            }
            else
            {
                temp->next=x;
                temp=temp->next;
            }
        }
        int rem=0;
        struct node *initial=head2;

        while(initial!=NULL)
        {
            struct node *x=(struct node*)malloc(sizeof(struct node));
            x->next=NULL;
            //printf("%d ",head2->data);
            x->data=(((head1->data)*(initial->data))+rem)%10;
            //printf("%d ",x->data);
            rem=(((head1->data)*(initial->data))+rem)/10;
            if(temp==NULL)
            {
                temp=x;
                start=temp;
            }
            else
            {
                temp->next=x;
                temp=temp->next;
            }
            // printf("%d ",start->data);
           initial=initial->next;
        }
        if(rem>0)
        {
             struct node *x=(struct node*)malloc(sizeof(struct node));
             x->data=rem;
             x->next=NULL;
             temp->next=x;
             temp=x;
        }
       // print_node(start);
        ///print_node(ans);
        //struct node *final=add_node(&start,&ans);
        if(ans==NULL)
        {
            printf("j");
           // print_node(ans);
           // ans=final;
        }
        else{
           // printf("%d",ans->data);
           //print_node(ans);
           //printf("\n");
        //    print_node(start);

           ans=add_node(&start,&ans);

        }

        // printf("\n");
        // print_node(start);
        //print_node(final);
        // ans->next=final;
        // ans=final;
        // free(temp);
        // free(start);
        i++;
        head1=head1->next;
    }
    // print_node(ans);
   // printf("\n");
    return ans;

}


struct node *reverse(struct node *head)
{
    if(head==NULL) return NULL;
    if(head->next==NULL) return head;
    struct node *curr=head;
    struct node *prev=NULL;
    while(curr->next!=NULL)
    {
        struct node *temp=curr;
        curr=curr->next;
        temp->next=prev;
        prev=temp;
    }
    curr->next=prev;
    return curr;

}
int count_zero(struct node *head)
{
    int ans=0;
    while(head!=NULL && head->data==0)
    {
        ans++;
        head=head->next;
    }
    return ans;
}

int count_match(struct node *head,struct node *matchhead)
{
    // while()
    int count=0;
    int flag=0;
    struct node *start=matchhead;
    while(head!=NULL)
    {
        struct node *temp=head;
        if(head->data==start->data)
        {
           // printf("%d",head->data);
            while(head!=NULL && start!=NULL && head->data==start->data)
            {
                head=head->next;
                start=start->next;
            }

            if(start==NULL)
            {
                count++;
                temp=temp->next;
                head=temp;
                start=matchhead;
            }
            else start=matchhead;
        }
        else
        {
            head=head->next;
        }
    }
    return count;

}
int count_size(struct node *head)
{
    int ans=0;
    while(head!=NULL)
    {
        ans++;
        head=head->next;
    }
    return ans;
}
//  char* convert(struct node *head,int s)
// {
//     int si=count_size(head);
//     char store[s] = "\0";
//     int i=0;
//     while(head!=NULL)
//     {
//         store[i]=head->data;
//         head=head->next;
//         i++;
//     }
//     return ans;
//     return store;
// }
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // int n;
    // scanf("%d",&n);
    // //printf("%d",n);
    // struct node *head1=NULL;
    //  struct node *head2=NULL;
    // for(int i=0;i<n;i++)
    // {
    //     int x;
    //     scanf("%d",&x);
    //     struct node *temp=insert_at_begining(head1,x);
    //     head1=temp;
    //    // printf("%d ",temp->data);

    // }
    // int m;
    // scanf("%d",&m);
    // for(int i=0;i<m;i++)
    // {
    //     int x;
    //     scanf("%d",&x);
    //     struct node *temp=insert_at_begining(head2,x);
    //     head2=temp;
    //    // printf("%d ",temp->data);

    // }
    // print_node(head1);
    // printf("\n");
    // print_node(head2);
    // print_node(head1);
    //  printf("\n");
//    struct node *result=add_node(&head1,&head2);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int k,m=2;
        scanf("%d",&k);
        char str[40];
        gets(str);
        //printf("%s ", str);
        //struct node *head1=NULL;
        struct node *ans=NULL;
        for(int i=1;i<=k;i++)
        {
            //printf("i");
            struct node *head1=NULL;
            int j=i;
            while(j!=0)
            {
                int x;
                x=j%10;
                struct node *temp=insert_at_begining(head1,x);
                head1=temp;
                j=j/10;
            // printf("%d ",temp->data);
            }
            // print_node(head1);
            struct node *rev=reverse(head1);
            if(i==1) ans=rev;
            // printf(" * ");
            // print_node(rev);
            // printf("->");
            struct node *result=rev;
            for(int start=1;start<i;start++)
            {

                result=multiply(result,rev);
                // print_node(result);
                // printf("\n");
            }
            ans=multiply(ans,result);
           // print_node(ans);
            // print_node(result);
            //printf("\n");
            // struct node *result=multiply(rev,rev);
            // print_node(result);
            // printf("\n");
            //print_node(head2);
        }
        int zero=count_zero(ans);
        // int size=count_size(ans);
        // ans=reverse(ans)
       // convert_string(ans);
        int j=m;
        struct node *match=NULL;
        int len=strlen(str);
        for (int i = 0; i<len; i++)
        {
            // if(i>0) printf("%d ",str[i]-'0');
            // int x;
            // x=j%10;
            struct node *temp=NULL;
            int x=str[i]-'0';
            if(i>0) temp=insert_at_begining(match,x);
            match=temp;
        }
        // while(j!=0)
        // {
        //     int x;
        //     x=j%10;
        //     struct node *temp=insert_at_begining(match,x);
        //     match=temp;
        //     j=j/10;
        // // printf("%d ",temp->data);
        // }
        // struct node *revmatch=reverse(match);

        // struct node *result=multiply(head1,head2);

        // print_node(match);
        // printf(" ");
        printf("%d ",zero);
        // print_node(ans);
        printf("%d ",count_match(ans,match));
        print_node(reverse(ans));
        printf("\n");
    }

}