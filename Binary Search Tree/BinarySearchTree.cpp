#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1
//#define NULL 0
struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;
int minimum;

void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node ==0) return 0;
    int L, R;
    L = getSize(node->left);
    R = getSize(node->right);
    return L+R+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    //write your codes here
    int item = node->item;
    struct treeNode *t = searchItem(root, item);
    if(t == 0) return -1;

    if(root -> item == node->item)
    return 0;

    struct treeNode *temp = root;
    int h = 0;
    while(temp->item != node->item)
    {
        if(temp->item < node->item)
        {
            temp = temp->right;h++;
        }
        else
        {
            temp = temp->left; h++;
        }

    }
    return h;
}


int calcDepth(int item)//return depth of an item in the tree
{
    //write your codes here
    struct treeNode *t = searchItem(root, item);
    if(t == 0) return -1;
    return calcNodeDepth(t);
}


struct treeNode * minValueNode(struct treeNode* node)
{
    struct treeNode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != 0)
        current = current->left;

    return current;
}


struct treeNode* deleteNode(struct treeNode* node, int key)
{

    if (node == 0) return node;


    if (key < node->item)
        node->left = deleteNode(node->left, key);


    else if (key > node->item)
        node->right = deleteNode(node->right, key);


    else
    {

        if(root->item == key && root->left == 0 && root->right ==0)
        {

            free(root);
            root= 0;
            return root;
        }
        if (node->left == 0)
        {
            struct treeNode *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == 0)
        {
            struct treeNode *temp = node->left;
            free(node);
            return temp;
        }


        struct treeNode* temp = minValueNode(node->right);


        node->item = temp->item;


        node->right = deleteNode(node->right, temp->item);
    }
    return node;
}
int deleteItem(struct treeNode *node,int item)
{
    if(deleteNode(node, item) == 0) return FALSE_VALUE;
    return TRUE_VALUE;
}
int getMinItem() //returns the minimum item in the tree
{
    //write your codes here
    struct treeNode *t;
    t = root;
    while(t->left != 0)
    {
        t = t->left;
    }
    int n = t->item;
    return n;
}

int getMaxItem() //returns the maximum item in the tree
{
    //write your codes here
    struct treeNode *t;
    t = root;
    while(t->right != 0)
    {
        t = t->right;
    }
    int n = t->item;

    return n;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
     if (node == 0) return 0;





    if (node->item <= rightBound && node->item >=leftBound)
         return 1 + rangeSearch(node->left,leftBound,rightBound) +
                    rangeSearch(node->right,leftBound,rightBound);


    else if (node->item < leftBound)
         return rangeSearch(node->right,leftBound,rightBound);
    else
        return rangeSearch(node->left,leftBound,rightBound);



}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit. 8.getSize 9.minimum\n");
        printf("10. maximum 11.calcNodeDepth(node) 12.calcDepth(item)\n");
        printf("13.range search\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            printf("the item to delete: \n");
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==8)
        {
            printf("Size : %d\n",getSize(root));
            //break;
        }
        else if(ch ==7) return 0;
        else if(ch == 9)
        {
            printf("minimum : %d\n", getMinItem());

        }
        else if(ch == 10)
        {
            printf("maximum : %d\n", getMaxItem());

        }
        else if(ch == 11)
        {
            struct treeNode *newNode ;
            newNode = (struct treeNode*) malloc(sizeof(struct treeNode));
            printf("item: \n");
            int item;
            scanf("%d",&item);
            newNode->item = item;

            printf("depth of node : %d\n",calcNodeDepth(newNode));
        }
        else if(ch == 12)
        {
            printf("item: \n");
            int item;
            scanf("%d",&item);
            //newNode->item = item;

            printf("depth of node : %d\n",calcDepth(item));
        }
        else if(ch == 13)
        {
            int leftBound ,rightBound;
            printf("left and right bounds: \n");
            scanf("%d %d",&leftBound,&rightBound);


            printf("range : %d\n\n",rangeSearch(root, leftBound,rightBound));
        }
        else if(ch == 14)
        {

        }
    }

}
