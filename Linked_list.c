#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct node
{
    int value;
    struct node *next;
};

void insert_at_end(struct node *head,int data)
{
    struct node* n= (struct node*)malloc(sizeof(struct node));
    n->next=NULL;
    n->value=data;
    if(head==NULL)
    {
        head=n;
        return ;
    }
    while(head->next!=NULL)
    {
        head=head->next;
    }
    head->next=n;
    head=head->next;
    return ;
}
struct node *insert_at_begining(struct node *head,int data)
{
    struct node* n= (struct node*)malloc(sizeof(struct node));
    n->next=NULL;
    n->value=data;
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


struct node *delete_at_first(struct node *head)
{
    if(head==NULL)
    {
        printf(" N ");
        return NULL;
    }
    struct node *temp=head;
    if(head->next==NULL)
    {
        return NULL;
    }
    else
    {
        head=head->next;
        temp->next=NULL;
        return head;
    }
}
void delete_at_end(struct node *head)
{
    if(head==NULL)
    {
        printf(" N ");
        return;
    }
    struct node *temp=head;
    if(head->next==NULL)
    {
        head=NULL;
        return ;
    }
    while(head->next->next!=NULL)
    {
       head=head->next;
    }
    head->next=NULL;
    return ;
}
size_t memoryDistance(void* addr1, void* addr2) {
    return (size_t)((char*)addr2 - (char*)addr1);
}

void find_node(struct node *head,int val)
{
    struct node *temp=head;
    if(head==NULL)
    {
        printf(" N ");
        return ;
    }
    int i=0;
    while(head!=NULL)
    {
        if(head->value==val)
        {
            i++;
            printf("%d ",i);
            printf("(");
            printf("%d",memoryDistance(temp,head));
            printf(") ");
            return ;
        }
        i++;
        head=head->next;
    }
    printf(" N ");
    return ;
}

void size_of_linked(struct node *head)
{
    int i=0;
    if(head==NULL)
    {
        printf("%d ",0);
        //printf("");
        return ;
    }
    while(head!=NULL)
    {
        head=head->next;
        i++;

    }
    printf("%d ",i);
    return ;
}
void delete_specific_node(struct node* (*head),int val)
{
    struct node *dup=(*head);
    if((*head)==NULL)
    {
        printf(" N ");
    }
    //printf("%d ",val);
    if((*head)->next==NULL ||(*head)->value==val)
    {

        if((*head)->next==NULL)
        {
            if((*head)->value==val)
            {
                struct node *temp=(*head)->next;
                (*head)->next=NULL;

                (*head)=temp;
                return ;
            }
            else
            {
                printf(" N ");
                return;
            }
        }
        else if((*head)->next!=NULL && (*head)->value==val)
        {
            struct node *temp=*head;
           (*head)=(*head)->next;
            temp->next=NULL;
            // printf("%d",temp->value);
            // printf("hfh");
            // (*head)=temp;
            return ;
        }
        else
        {
            *head=dup;
            printf(" N ");
        }
    }
    else
    {
        // printf("hihr");
        struct node *temp=*head;
        struct node *prev=NULL;
        while(temp->next!=NULL)
        {
            if(temp->value==val)
            {
               // printf("%d ",val);

               prev->next=temp->next;
               return ;
            }
            prev=temp;
            temp=temp->next;
        //    (*head)=(*head)->next;

        }
        if(temp->next==NULL)
        {
            if((temp->value)==val)
            {
                // printf("%d",(*head)->value);
               temp=prev;
               temp->next=NULL;
            //    (*head)=temp;
                return ;
            }
            else
            {
                *head=dup;
                printf(" N ");
            }
            return ;
        }
        // delete_at_end(*head);
    }
}



void print_node(struct node *head)
{
    if(head==NULL)
    {
        printf(" E ");
    }
    else
    {
        printf("[");
        while(head->next!=NULL )
        {

            printf("%d",head->value);
            printf("-");
            head=head->next;
        }
        printf("%d",head->value);
        printf("]");
    }
    printf(" ");
}
int main()
{
   // freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    // to give input in file just uncomment it make a two file input and output txt file
    int t;
    scanf("%d",&t);
    int x=t;
    while(t--)
    {
        printf("#");
        printf("%d ",x-t);
        int n;
        scanf("%d",&n);
        struct node *head=NULL;
        // print_node(head);
        for(int i=0;i<n;i++)
        {
            int choice;
            scanf("%d",&choice);
            if(choice==1)
            {
                int data;
                scanf("%d",&data);
                // printf("%d ",data);
                struct node *temp=insert_at_begining(head,data);
                head=temp;

            }
            else if(choice==2)
            {
                int data;
                scanf("%d",&data);
               // printf("%d ",data);
                if(head==NULL)
                {
                     struct node* n= (struct node*)malloc(sizeof(struct node)); n->next=NULL;
                     n->value=data;
                     head=n;
                }
                else
                {
                    struct node *temp=head;
                    insert_at_end(temp,data);
                }
                // head=temp;

            }
            else if(choice==3)
            {
                //printf("%d ",head->value);
                 //print_node(head);
                struct node *temp=delete_at_first(head);
                //printf("%d ",temp->value);
                //print_node(head);
                head=temp;
            }
            else if(choice==4)
            {
                struct node *temp=head;
                delete_at_end(temp);
            }
            else if(choice==5)
            {
                int data;
                scanf("%d",&data);
            //    printf("%d ",data);
                struct node *temp=head;
                delete_specific_node(&head,data);
                //print_node(head);
                // head=temp;

                //  print_node(head);
                //  printf("\n");
            }
            else if(choice==6)
            {
                int data;
                scanf("%d",&data);
                find_node(head,data);
            }
           else if(choice==7)
           {
                size_of_linked(head);
           }
           else if(choice==8)
           {
                print_node(head);
           }
           else if(choice!=0)
           {
                // printf("%d ",choice);
                printf(" W ");
           }
           else if(choice==0) break;



        }
        printf("\n");
    }
}