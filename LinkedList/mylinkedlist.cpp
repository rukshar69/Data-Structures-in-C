#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    //write your codes here
    struct listNode * newNode ,*temp, *prev;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = 0;
	if(list ==0 )
	{
	    list = newNode;
	    return SUCCESS_VALUE;
	}
	temp = list ; //start at the beginning
	while (temp != 0)
	{
        //if (temp->next == 0) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}

	prev->next = newNode;
	return SUCCESS_VALUE ;
}

int insertAfter(int oldItem, int newItem)
{
    //write your codes here
    struct listNode * newNode ,*temp;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem ;
	temp = list;
	while(temp != 0)
	{
	    if(temp->item == oldItem) break;
	    temp = temp->next;
	}

	if(temp ==0) return NULL_VALUE;
	if(temp->next ==0)
	{
	    temp->next = newNode;
	    newNode->next = 0;
	}
	else
	{
	    newNode->next = temp->next;
	    temp->next = newNode;
	}
	return SUCCESS_VALUE;
}

int deleteLast()
{
    //write your codes here
    struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
    if(temp == 0) return NULL_VALUE;
    if(temp->next == 0)
    {
        free(list);
        initializeList();
        return SUCCESS_VALUE;
    }

	while (temp != 0)
	{
        if (temp->next == 0) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	prev->next = temp->next ;
		free(temp);

	return SUCCESS_VALUE ;

}

int deleteFirst()
{
    //write your codes here
    if(list ==0) return NULL_VALUE;
    struct listNode *temp;
    temp = list;
    list = temp->next;
    free(temp);

    return SUCCESS_VALUE;
}
void prefixSum(int item)
{
    if(searchItem(item) == 0)
    {
        printf("item not present\n");
    }
    else
    {
        struct listNode *temp; temp = list;
        int sum =0;
        while(temp != 0)
        {
            sum += temp->item;
            printf("%d ",sum);

            if(temp->item == item) break;
            temp = temp->next;
        }
         //sum += temp->item;
         //printf("%d ",sum);
         printf("\n");
    }
}

int main()
{
    initializeList();
    int choice,item,item2;
    while(1)
    {
        printf("1. insert @ first, 2.delete an item, 3.search, 4. print all 5.insert after 6. exit\n");
        printf("7. insertLast 8. deleteLast 9.deleteFirst 10.prefixSum\n\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            printf("Insert item : \n");
            scanf("%d", &item);
            insertItem(item);
            //insertLast(item);
            break;

        case 2:
            printf("Delete item:\n ");
            scanf("%d",&item);
            deleteItem(item);
            //deleteFirst();
            //deleteLast();
            break;

        case 3:
            printf("search item: \n");
            scanf("%d",&item);
            searchItem(item);break;

        case 4:
            printf("\n");
            printList();break;
        case 5:
            printf("old item: ");
            scanf("%d",&item2);
            printf("new item: ");
            scanf("%d",&item);
            insertAfter(item2, item);
            break;

        case 6: exit(0);
        case 7:  printf("Insert item : \n");
            scanf("%d", &item);
            //insertItem(item);
            insertLast(item);
                break;
        case 8:
            //deleteFirst();
            deleteLast();
                break;
        case 9:
            deleteFirst();
            //deleteLast();
                break;

        case 10:
            int item;
            printf("enter item\n");
            scanf("%d",&item);
            prefixSum(item);
            break;


    }
    }

    return 0;
}
