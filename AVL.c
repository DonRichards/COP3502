/**
    Donald Richards
    ASSIGNMENT AVL
    10/23/2013
*/

#include<conio.h>
#include<stdio.h>

typedef struct node
{  int data;
   struct node *left,*right;
   int ht;
}node;

int process(node *);
int height(node *);
int BF(node *);
node *insert(node *,int);

void main()
{
    node *root=NULL;
    int T,x,n,i,k;

    scanf("%d",&T);                                 // NUMBER OF CASES

    for(k=0;k<T;k++){
        root=NULL;                                  // RESET root TO NULL
        char temp;

        scanf("%d%c",&n,&temp);                     // INPUT NUMBER OF INT
        for(i=0;i<n;i++){                           //
            scanf("%d%c",&x,&temp);                 // temp USED TO EXCEPT SPACE OR \n CHAR
            root=insert(root,x);                    //
            if(temp=='\n')
                break;
            } // END OF INT FOR LOOP

        printf("Tree #%d: ", k+1);                  //
        if(process(root)==1)                        //
            printf("REMOVE\n");                     // OUTPUT
            else                                    //
                printf("KEEP\n");                   //

    } // END OF CASES

}

node * insert(node *Tree,int x)
{
    if(Tree==NULL){
        Tree=(node*)malloc(sizeof(node));
        Tree->data=x;
        Tree->left=NULL;
        Tree->right=NULL;
        }
    else
        if(x > Tree->data){
            Tree->right=insert(Tree->right,x);
            }
        else
            if(x<Tree->data){
                Tree->left=insert(Tree->left,x);
                }
        Tree->ht=height(Tree);
        return(Tree);
} // END OF INSERT TO TREE


int height(node *Tree) {
    int leftHeight,rightHeight;
    if(Tree==NULL)
        return(0);
    if(Tree->left==NULL)
        leftHeight=0;
    else
        leftHeight=1+Tree->left->ht;
    if(Tree->right==NULL)
        rightHeight=0;
    else
        rightHeight=1+Tree->right->ht;
    if(leftHeight>rightHeight)
        return(leftHeight);
    return(rightHeight);
} // END OF HEIGHT

int BF(node *Tree){
    int leftHeight,rightHeight;
    if(Tree==NULL)
        return(0);
    if(Tree->left==NULL)
        leftHeight=0;
    else
        leftHeight=1+Tree->left->ht;
    if(Tree->right==NULL)
        rightHeight=0;
    else
        rightHeight=1+Tree->right->ht;
    return(leftHeight-rightHeight);
} // END OF CHECK Ballance

int process(node *Tree){
    if(Tree!=NULL){
//        printf("%d\n",BF(Tree));
        if( !(BF(Tree)>-2)&&(BF(Tree)<2))
            return 1;
        process(Tree->left);
        process(Tree->right);
    }
}
