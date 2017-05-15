#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;
int flag = 1;
int insertItemAt(int pos, int item);
void shrink();
void deleteLast();
void clear();
void deleteAll();

int getLength()
{
    return length;
}
void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	int * tempList ;
	if(flag ==1)
	{
	    if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	}
	else if(flag ==0)
	{
	    flag =1;
	    initializeList();
	    insertItem( newitem);
	}
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	//shrink();
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);

}
int smain();
int main(void)
{

    initializeList();
    while(1)
    {

        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. (Add from homework). 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch == 4)
        {
            //printf("current length = %d\n",getLength());
            //printf("\n%d\n",getLength());

            /*printf("enter item to insert ");
            int a;
            scanf("%d",&a);
            printf("enter the position: ");
            int pos;
            scanf("%d",&pos);
            if(insertItemAt(pos,a) == NULL_VALUE)
            {
                printf("invalid\n");
            }
            else
            {
                printf("Successfully inserted\n");
            }*/
            //shrink();
            //deleteLast();
            //clear();
            //deleteAll();
            smain();
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
    }

}


int insertItemAt(int pos, int item)
{
   if(flag ==1)
   {
        if(pos>= length) return NULL_VALUE;
    int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};



    list[length] = list[pos];
    list[pos] = item;
    length++;
   }
   else if(flag ==0)
   {
       flag =1;
	    initializeList();
	    insertItemAt( pos, item);
   }
    return SUCCESS_VALUE;
}

void shrink()
{
    if(length == listMaxSize/2)
    {
        if(listMaxSize>LIST_INIT_SIZE)
        {
            int * tempList ;


		listMaxSize = listMaxSize/2 ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        free(list) ;
        list = tempList ;
        }
    }
}

void deleteLast()
{
    length--;
    shrink();
    return;
}

void clear()
{
    free(list);
    length =0;
    listMaxSize =0;
    flag = 0;
}

void deleteAll()
{
    length =0;

            listMaxSize = LIST_INIT_SIZE;
        list = (int*) realloc(list,LIST_INIT_SIZE*sizeof(int));


}
int smain()
{
    initializeList();

    char str[100],item;
    scanf("%s",str);

    int n = strlen(str),i,flag =1;
    for(i =0;i<n;i++)
    {
        if(str[i] == '('||str[i] == '{'||str[i] == '[' )
           {
               insertItem(str[i]);
           }
        else if(str[i] == ')'||str[i] == '}'|| str[i] == ']')
        {
            if(length ==0) {flag =0; break;}
            else
            {
                item = list[length-1];

                deleteLast();
                if(!((item=='('&& str[i]==')') ||(item=='['&& str[i]==']')||(item=='{'&& str[i]=='}')))
                {
                    flag =0; break;
                }
            }
        }
    }
    if(getLength()!=0) flag =0;
    if(flag ) printf("Balanced\n");
    else printf("Not balanced\n");
    clear();

    return 0;

}
