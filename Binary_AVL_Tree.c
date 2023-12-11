#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

struct node *st[1000];
struct node *qu[1000];
int end=-1;
int stq=0;
int endq=-1;

void st_push(struct node *data)
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
struct node *st_top()
{
    return st[end];
}

struct node
{
    int data;
    struct node *right;
    struct node *left;
    int height;
};


void q_push(struct node * data)
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
int q_size()
{
    return endq-stq+1;
}
struct node *q_front()
{
    return qu[stq];
}



struct node *initial(int val)
{
   struct node *root=(struct node*)malloc(sizeof(struct node));
    root->left=NULL;
    root->right=NULL;
    root->data=val;
    root->height=1;
    return root;
}
void print(int x)
{
   // printf("j");
    printf("%d ",x);
    return ;
}
struct node *AddNode_BST(struct node *root,int x)
{
    if(root==NULL) return initial(x);
    if(root->data >= x) root->left=AddNode_BST(root->left,x);
    else root->right=AddNode_BST(root->right,x);
    return root;
}
struct node *get_sucess(struct node *root)
{
    root=root->right;
    while(root->left!=NULL) root=root->left;
    return root;
}
struct node *delete_node_BST(struct node *root,int x)
{
    if(root==NULL) return NULL;
    if(root->data > x) root->left=delete_node_BST(root->left,x);
    else if(root->data < x) root->right=delete_node_BST(root->right,x);
    else
    {
        if(root->left==NULL)
        {
            struct node *temp=root->right;
           // print(root->data);
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct node *temp=root->left;
            free(root);
            return temp;
        }
        else
        {
            struct node *curr=root;
            struct node *temp=get_sucess(curr);
            curr->data=temp->data;
            root->right=delete_node_BST(root->right,temp->data);
            return root;
        }
    }
}
void inorder_trav(struct node *root)
{
    // printf("jru");
    if(root==NULL) return ;
    inorder_trav(root->left);

    printf("%d ",root->data);
    inorder_trav(root->right);
    return ;
}
bool search_tree(struct node *root,int x)
{
    if(root==NULL) return false;
    if(root->data > x) return search_tree(root->left,x);
    else if(root->data==x) return true;
    else return search_tree(root->right,x);
}
int number_nodes(struct node *root)
{
    if(root==NULL) return 0;
    int left=0;
    int right=0;
    if(root->left!=NULL) left=1+number_nodes(root->left);
    if(root->right!=NULL) right=1+number_nodes(root->right);
    return left+right;
}
void leaves(struct node *root,int *c)
{
    if(root==NULL) return ;
    if(root->left==NULL && root->right==NULL)
    {
        (*c)++;
        return ;
    }
    leaves(root->left,c);
    leaves(root->right,c);
    return ;

}
void preorder_WR(struct node *root)
{
    struct node *curr=root;
    st_push(curr);
    while(st_empty()==false)
    {
        struct node *temp=st_top();
        print(temp->data);
        st_pop();
        if(temp->right!=NULL) st_push(temp->right);
        if(temp->left!=NULL) st_push(temp->left);
    }
    end=-1;
    return ;

}

void preorder(struct node *root)
{
    if(root==NULL) return ;
    print(root->data);
    preorder(root->left);
    preorder(root->right);
    return ;
}
void inorder(struct node *root)
{
    if(root==NULL) return ;
    inorder(root->left);
    print(root->data);
    inorder(root->right);
    return ;
}
void postorder(struct node *root)
{
    if(root==NULL) return ;
    postorder(root->left);
    postorder(root->right);
    print(root->data);
    return ;
}
void level_order_Traversal(struct node* root)
{
    q_push(root);
    while(q_empty()==false)
    {
        struct node *temp=q_front();
        q_pop();
        print(temp->data);
        if(temp->left!=NULL) q_push(temp->left);
        if(temp->right!=NULL) q_push(temp->right);
    }
    stq=0;
    endq=-1;
    return ;
}
int height_tree(struct node *root)
{
    if(root==NULL) return -1;
    int l=height_tree(root->left);
    int r=height_tree(root->right);
    if(l>r) return 1+l;
    else return 1+r;
}
struct node *Ancestor(struct node *root,int x,int y)
{
    if(root==NULL) return NULL;
    if(root->data==x || root->data==y) return root;
    struct node *lft=Ancestor(root->left,x,y);
    struct node *rgt=Ancestor(root->right,x,y);

    if(lft!=NULL && rgt!=NULL) return root;
    if(lft!=NULL) return lft;
    else return rgt;
}
int width_tree(struct node* root)
{
    int maxi=0;
    q_push(root);
    while(q_empty()==false)
    {
        int sz=q_size();
        if(sz>maxi) maxi=sz;
        while(sz!=0)
        {
            struct node *temp=q_front();
            q_pop();
            sz--;
            if(temp->left!=NULL) q_push(temp->left);
            if(temp->right!=NULL) q_push(temp->right);

        }
    }
    stq=0;
    endq=-1;
    return maxi;
}

void sumleaves(struct node *root,int *c,int hash[1000])
{
    if(root==NULL) return ;
    if(root->left==NULL && root->right==NULL)
    {
        print(root->data);
        hash[root->data]=1;
        (*c)+=root->data;
        return ;
    }
    sumleaves(root->left,c,hash);
    sumleaves(root->right,c,hash);
    return ;

}

int diameter_tree(struct node *root,int *ans)
{
    if(root==NULL) return 0;
    int l=diameter_tree(root->left,ans);
    int r=diameter_tree(root->right,ans);
    int h=l+r+1;
    if((*ans)<h) (*ans)=h;
    if(l>r) return 1+l;
    else return 1+r;
}

void path(struct node* node1,int x)
{
    if(node1==NULL) return ;
    if(node1->data==x)
    {
        print(node1->data);
        return;
    }
    if(node1->data > x)
    {
        print(node1->data);
        printf("L ");
        path(node1->left, x);
    }
    else
    {
        print(node1->data);
        printf("R ");
        path(node1->right,x);
    }
    return ;
}

int nd_h(struct node* root)
{
    if (root==NULL) return 0;
    return root->height;
}

void up_h(struct node* root)
{
    if (root==NULL) return;
    int lft=nd_h(root->left);
    int rgt=nd_h(root->right);
    if(lft>rgt) root->height=lft+1;
    else root->height=rgt+ 1;
}

struct node* rgt_rot(struct node* y)
{
    struct node* temp1=y->left;
    struct node* temp2=temp1->right;
    temp1->right=y;
    y->left=temp2;
    up_h(y);
    up_h(temp1);
    return temp1;
}

struct node* lft_rot(struct node* y)
{
    struct node* temp1=y->right;
    struct node* temp2=temp1->left;
    temp1->left=y;
    y->right=temp2;
    up_h(y);
    up_h(temp1);
    return temp1;
}

int bal_fact(struct node* root)
{
    if (root==NULL) return 0;
    return (nd_h(root->left)-nd_h(root->right));
}

struct node* AddNode_avl(struct node* root, int data)
{
    if (root==NULL) return initial(data);
    if (data<root->data) root->left=AddNode_avl(root->left, data);
    else if(data>root->data) root->right=AddNode_avl(root->right, data);
    else return root;

    up_h(root);
    int balance=bal_fact(root);
    if (balance > 1)
    {
        if (data<root->left->data) return rgt_rot(root);
        else
        {
            root->left=lft_rot(root->left);
            return rgt_rot(root);
        }
    }

    if (balance < -1)
    {
        if (data>root->right->data) return lft_rot(root);
        else
        {
            root->right=rgt_rot(root->right);
            return lft_rot(root);
        }
    }
    return root;
}

struct node* minValueNode(struct node* root)
{
    struct node* current=root;
    while (current->left != NULL) current=current->left;
    return current;
}
void left1(struct node *root,int *sum)
{
    if(root==NULL || (root->left==NULL && root->right==NULL)) return ;

    print(root->data);
    (*sum)+=root->data;
    if(root->left!=NULL) left1(root->left,sum);
    else left1(root->right,sum);
    return ;

}
void leaf(struct node *root,int *sum)
{
        if(root==NULL) return ;
    if(root->left==NULL && root->right==NULL)
    {
         print(root->data);
        (*sum)+=root->data;
        return ;
    }
    leaf(root->left,sum);
    leaf(root->right,sum);
    return ;

}
void right1(struct node *root,int *sum)
{
    if(root==NULL || (root->left==NULL && root->right==NULL)) return ;

    if(root->right!=NULL)
    {
        right1(root->right,sum);
        print(root->data);
        (*sum)+=root->data;
    }
    else
    {
        right1(root->left,sum);
         print(root->data);
        (*sum)+=root->data;
    }
    return ;

}

struct node* delete_node_avl(struct node* root, int data)
{
    //print(data);
    if (root==NULL)
        return root;
    if (data<root->data) root->left=delete_node_avl(root->left, data);
    else if (data>root->data) root->right=delete_node_avl(root->right, data);
    else
    {

        if (root->left==NULL)
        {
            struct node* temp=root->right;
            free(root);
            return temp;
        }
        else if (root->right==NULL)
        {
            struct node* temp=root->left;
            free(root);
            return temp;
        }
        // struct node* temp=get_sucess(root);
        // root->data=temp->data;
        // root->right=delete_node_avl(root->right, temp->data);
        struct node* temp = minValueNode(root->right);
        root->data=temp->data;
        root->right=delete_node_avl(root->right, temp->data);
    }
    up_h(root);

    int balance=bal_fact(root);

    if (balance>1)
    {
        if (bal_fact(root->left)>=0) return rgt_rot(root);
        else
        {
            root->left=lft_rot(root->left);
            return rgt_rot(root);
        }
    }

    if (balance<-1)
    {
        if (bal_fact(root->right)<=0)
            return lft_rot(root);
        else
        {
            root->right=rgt_rot(root->right);
            return lft_rot(root);
        }
    }
    return root;
}
int perimeter_tree(struct node *root)
{
    int hash[1000]={0};
    // int leaf_sum=0;
    // sumleaves(root,&leaf_sum,hash);
    // //print(leaf_sum);
    // int sum_end=0;
    // q_push(root);
    // while(q_empty()==false)
    // {
    //     int sz=q_size();
    //     int i=1;
    //     while(i<=sz)
    //     {
    //         struct node *temp=q_front();
    //         if((i==1 || i==sz) && hash[temp->data]==0)
    //         {
    //             sum_end+=temp->data;
    //             hash[temp->data]=1;
    //             print(temp->data);
    //         }
    //         q_pop();
    //         i++;
    //         if(temp->left!=NULL) q_push(temp->left);
    //         if(temp->right!=NULL) q_push(temp->right);

    //     }
    // }

    // stq=0;
    // endq=-1;
    int sum=root->data;
    left1(root->left,&sum);
    struct node *temp2=root;
    leaf(temp2->left,&sum);
    leaf(temp2->right,&sum);
    right1(root->right,&sum);
    return sum;
}
int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


//**********************************************************************************
    // A T H U Please add in last of their input to -1000 to stop the reading input other wise it will go in infinite loop

// ***************************************************************************




    int t;
    scanf("%d",&t);
    //printf("%d",t);
    int flag1=0;
    int flag2=0;
    struct node *root=NULL;
    int hash[1000]={0};
    while(t--)
    {
        //char *inst=(char*) malloc(size*sizeof(char));
    //     int k;
    //     scanf("%d",&k);
    //    // print(n);
        char ch;
        scanf(" %c",&ch);
        // printf("%c",ch);
        //printf("%d",n);
        if(ch=='T')
        {
            // printf("%c",c);
            // if(flag2==1)
            // {
            //     flag2=0;
            //     root=NULL;
            // // }
            // size_t getline(char **lineptr, size_t *n, FILE *stream);

            // cout<<size_t<<" ";

            root=NULL;
            for(int i=0;i<1000;i++) hash[i]=0;
            flag1=1;
            flag2=0;
            // int n;
            // scanf("%d ",&n);
           // printf("\n");
            while(1>0)
            {
                int x;
                scanf("%d",&x);
                // if(x==-1000) break;
                if(x>=0 && hash[x]==0)
                {
                    root=AddNode_BST(root,x);
                    hash[x]=1;
                }
                else if(x<0 && hash[-1*x]==1)
                {
                    root=delete_node_BST(root,-x);
                    hash[x]=0;
                }
                if(getchar()=='\n') break;
            }
            // level_order_Traversal(root);
          // inorder(root);
        }
        else if(ch=='H')
        {
            // if(flag1==1)
            // {
            //     flag1=0;
            //     root=NULL;
            // }
            root=NULL;
            for(int i=0;i<1000;i++) hash[i]=0;
            flag2=1;
            flag1=0;
            while(1>0)
            {
                int x;
                scanf("%d",&x);
                // if(x==-1000) break;
                if(x>0 && hash[x]==0)
                {
                    root=AddNode_avl(root,x);
                    hash[x]=1;
                }
                else if(x<0 && hash[-1*x]==1)
                {
                    //print(-x);
                    root=delete_node_avl(root,-x);
                    hash[x]=0;
                }
                 if(getchar()=='\n') break;
            }
           //inorder(root);
        }
        else if(ch=='A')
        {
            while(1>0)
            {
                int x;
                scanf("%d",&x);
                if(x==-1000) break;
                if(flag1==1) root=AddNode_BST(root,x);
                else if (flag2==1) root=AddNode_avl(root,x);
                hash[x]=1;
                if(getchar()=='\n') break;

            }

        }
        else if(ch=='U')
        {
            while(1>0)
            {
                int x;
                scanf("%d",&x);
                // if(x==-1000) break;
                //print(x);
                if(hash[x]==1)
                {
                    if(flag1==1) root=delete_node_BST(root,x);
                    else if(flag2==1) root=delete_node_avl(root,x);
                    hash[x]=0;
                }
                if(getchar()=='\n') break;
            }
            //printf("\n");
        }
        else if(ch=='F')
        {
            int n;
            scanf("%d",&n);
            if(n<0) printf("NO");
            else
            {
                if(search_tree(root,n)==true) printf("Yes");
                else printf("No");
            }
        }
        else if(ch=='Q')
        {
            int c=0;
            leaves(root,&c);
            print(c);
        }
        else if(ch=='N')
        {
            print(number_nodes(root));
        }
        else if(ch=='P')
        {
            preorder_WR(root);
        }
        else if(ch=='I')
        {

            inorder(root);
        }
        else if(ch=='S')
        {
            postorder(root);
        }
        else if(ch=='L')
        {
            level_order_Traversal(root);
        }
        else if(ch=='W')
        {
            print(width_tree(root));
        }
        else if(ch=='C')
        {
            int x,y;
            scanf("%d",&x);
            scanf("%d",&y);
            if(search_tree(root,x)==false) printf("-1");
            else if(search_tree(root,y)==false) printf("-1");
            else print(Ancestor(root,x,y)->data);
        }
        else if(ch=='R')
        {
            int i,j;
            scanf("%d",&i, &j);
            scanf("%d",&j);
            if(search_tree(root,i)==false) printf("Source does not exist");
            else if(search_tree(root,j)==false) printf("Destination does not exist");
            else if(Ancestor(root,i,j)->data==i)
            {
                path(Ancestor(root,i,j),j);
            }
            else if(Ancestor(root,i,j)->data==j)
            {
                path(Ancestor(root,i,j),i);
            }
            else
            {
                printf("Unreachable");
            }
        }
        else if(ch=='X')
        {
             int ans=0;
            diameter_tree(root,&ans);
            print(ans);
        }
        else if(ch=='Y')
        {

            print(perimeter_tree(root));
        }
        else if(ch=='D')
        {
            print(height_tree(root));
        }
        else
        {
            //print(t);
            printf("Invalid Input");
        }

        if(ch!='T' && ch!='U' && ch!='H' && ch!='A') printf("\n");
    }
    return 0;
}