#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum dataType
{
    INT=1,
    FLOAT,
    STR,
    DOUBLE,
    LIST,
};

struct queue
{
    struct node *front;
    struct node *rear;
};

struct node
{
    union
    {
        int a;
        float b;
        char c[100];
        double d;
        struct queue* list;
    };
    struct node* next;
    enum dataType type;
};

int length(struct node* head)
{
    struct node* current = head;   
    int count = 0;  

    if(head == NULL)
    {
        printf("your list is empty\n");
    } 

    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}


void append(struct queue *q)
{
    struct node* temp;
    temp= malloc(sizeof(struct node));
    printf("Enter data type (1-int, 2- float, 3- string, 4- double, 5-list): ");
    scanf("%d",&temp->type);
    fflush(stdin);
    switch(temp->type)
    {
        case INT: printf("Enter a whole number: ");
                    scanf("%d",&temp->a);
                    break;
        case FLOAT: printf("Enter a real number: ");
                    scanf("%f",&temp->b);
                    break;
        case STR: printf("Enter a string: ");
                    scanf("%s",temp->c);
                    break;
        case DOUBLE: printf("Enter a double number: ");
                    scanf("%lf",&temp->d);
                    break;
        case LIST: ;struct queue *list1;
                    list1=malloc(sizeof(struct queue));
                    list1->front=NULL;
                    list1->rear=NULL;
                    temp->list=list1;
                    printf("Follow the prompts for the first element of your list.\n");
                    append(list1);
                    break;
        default:printf("Invalid choice\n\n");
    }
    temp->next=NULL;

    if (!(q->rear==NULL))
    {
        q->rear->next=temp;
        q->rear=temp;
    }

    else
    {
        q->front= q->rear= temp;
    }
}

void displayE(struct node* temp)
{
    switch(temp->type)
            {
        case INT: printf("%d",temp->a);
                    break;
        case FLOAT: printf("%f",temp->b);
                    break;
        case STR: printf("%s",temp->c);
                    break;
        case DOUBLE: printf("%lf",temp->d);
                    break;
        case LIST: ;struct node* current=temp->list->front;
                    printf("[");
                    while(current!=NULL)
                    {
                        displayE(current);
                        if (temp->list->rear!=current)
                        {
                            printf(", ");
                        }
                        current=current->next;
                    }
                    printf("]");
                    break;
            }
}

void displayList(struct queue *q)
{
    if (q->front==NULL)
        printf("The list is empty\n\n");
    else
    {
        struct node* temp=q->front;
        printf("[");
        while(temp!=NULL)
        {
            switch(temp->type)
            {
        case INT: printf("%d",temp->a);
                    break;
        case FLOAT: printf("%f",temp->b);
                    break;
        case STR: printf("%s",temp->c);
                    break;
        case DOUBLE: printf("%lf",temp->d);
                    break;
        case LIST: ;struct node* current=temp->list->front;
                    printf("[");
                    while(current!=NULL)
                    {
                        displayE(current);
                        if (temp->list->rear!=current)
                        {
                            printf(", ");
                        }
                        current=current->next;
                    }
                    printf("]");
                    break;
            }
            if (temp!=q->rear)
            {
                printf(", ");
            }
            temp=temp->next;
        }
        printf("]\n\n");
    }
}


void deleteList(struct queue *q)
{

    if (q->front!=NULL)
    {
        if (q->front->next==NULL)
        {
            free(q->front);
            q->front=NULL;
            q->rear=NULL;
        }
        else
        {
            while (q->front!=NULL)
            {
                struct node* temp=q->front;
                q->front=q->front->next;
                free(temp);
            }
            q->front=NULL;
            q->rear=NULL;
        }
    }
}

void insert(struct queue *q)
{
    if (q->front == NULL)
    {
        printf("The list is empty.\n\n");
    } 
    else
    {
        int index;
        printf("Enter the index: ");
        scanf("%d",&index);
        //index validation
        if (index<0 || index>length(q->front))
        {
            printf("Index is out of range.\n");
        }
        
        if (index==length(q->front))
        {
            append(q);
        }

        else
        {
            struct node* temp;
            int found=0, counter=0;
            temp= malloc(sizeof(struct node));
            printf("Enter data type (1-int, 2- float, 3- string, 4- double, 5- list): ");
            scanf("%d",&temp->type);
            fflush(stdin);
            switch(temp->type)
            {
                case INT: printf("Enter a whole number: ");
                        scanf("%d",&temp->a);
                        break;
                case FLOAT: printf("Enter a real number: ");
                    scanf("%f",&temp->b);
                    break;
                case STR: printf("Enter a string: ");
                    scanf("%s",temp->c);
                    break;
                case DOUBLE: printf("Enter a double number: ");
                        scanf("%lf",temp->d);
                        break;
                case LIST: ;struct queue *list1;
                    list1=malloc(sizeof(struct queue));
                    list1->front=NULL;
                    list1->rear=NULL;
                    temp->list=list1;
                    printf("Follow the prompts for the first element of your list.\n");
                    append(list1);
                    break;
                default:printf("Invalid choice\n\n");
            }
            temp->next=NULL;
            struct node* check=q->front;
            for (int i=0; i<index; i++)
            {
                check=check->next;
            }
            if (check->type==LIST)
            {
                int index2;
                printf("Enter index number within the list: ");
                scanf("%d",&index2);
                if (index2<0 || index2>length(check->list->front))
                {
                    printf("Index is out of range.\n");
                }
                else
                {
                    if (index2==length(check->list->front))
                    {
                        printf("Enter new data information again...\n\n");
                        append(check->list);
                    }
                    else if (index2==0)
                    {
                        temp->next=check->list->front;
                        check->list->front=temp;
                    }
                    else
                    {
                        struct node* current;
                        current = check->list->front;
                        while ((current != NULL) || (!found))
                        {
                            if(counter == index2-1)
                            {
                                temp->next=current->next;
                                current->next=temp;
                                found++;
                            } 
                            else 
                            {
                                current = current->next;
                            }
                            counter++;
                        }
                    }
                }
            }
            else
            {
                if (index==0)
                {
                    temp->next=q->front;
                    q->front=temp;
                }
                else
                {
                    struct node* current;
                    current = q->front;
                    while ((current != NULL) || (!found))
                    {
                        if (counter == index-1)
                        {
                            temp->next=current->next;
                            current->next=temp;
                            found++;
                        } 
                        else 
                        {
                            current = current->next;
                        }
                        counter++;
                    }
                }
            }
        }
    }
}

void reverse(struct queue *q)
{
    if (q->front!=NULL)
    {
        struct node* current=q->front;
        struct node* previous=NULL;
        struct node* next=NULL;
        while (current !=NULL)
        {
            next=current->next;
            current->next=previous;
            previous=current;
            current=next;
        }
        q->rear=q->front;
        q->front=previous;
    }
}

void sort(struct queue *q)
{
    printf("Sorted\n\n");
    int swapped;
    struct node* prev;
    struct node* curr=NULL;
    struct node* next;
    struct node* lptr=NULL;

    char result1[100];
    char result2[100]; 

    if (q->front!=NULL)
    {
        do 
        {
            swapped=0;
            curr=q->front;
            prev=NULL;
            next=q->front->next;

            while(next!=lptr)
            {
                switch(curr->type)
                {
                    case INT: sprintf(result1, "%d", curr->a);
                                break;
                    case FLOAT: sprintf(result1, "%f",curr->b);
                                break;
                    case STR: strcpy(result1,curr->c);
                                break;
                    case DOUBLE: sprintf(result1, "%lf", curr->d);
                                break;
                }
                switch(next->type)
                {
                    case INT: sprintf(result2, "%d", next->a);
                                break;
                    case FLOAT: sprintf(result2, "%f",next->b);
                                break;
                    case STR: strcpy(result2,next->c);
                                break;
                    case DOUBLE: sprintf(result2, "%lf", next->d);
                                break;
                }

                if (strcmp(result1, result2)>0)
                {
                    if (curr==q->front)
                    {
                        curr->next=next->next;
                        next->next=curr;
                        q->front=next;
                    }
                    else
                    {
                        curr->next=next->next;
                        next->next=curr;
                        prev->next=next;
                    }
                    swapped=1;
                prev=next;
                next=curr->next;
                }
                else
                {
                    prev=curr;
                    curr=next;
                    next=next->next;
                }
            }

            lptr=curr;

        }while (swapped);
        struct node* temp;
        temp=q->front;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        q->rear=temp;
    }
}

void displayElement(struct node *head){
    int found, index = 0, counter = 0;

    printf("please enter the index of the element you would like to print: ");
    scanf("%d", &index);
    if (index<0 || index>length(head)-1)
    {
        printf("Index is out of range.\n");
    }
    else
    {
        if (head==NULL){
        printf("The list is empty.\n\n");
    } else {
        struct node* temp;
        temp = head;
        while ((temp != NULL) || (!found)){
            if(counter == index){
                if (temp->type!=LIST)
                {
                    printf("the element at index %d is: ", index);
                }
                switch(temp->type){
                case INT: printf("%d\n",temp->a);
                            break;
                case FLOAT: printf("%f\n",temp->b);
                            break;
                case STR: printf("%s\n",temp->c);
                            break;
                case DOUBLE: printf("%lf\n", temp->d);
                            break;
                case LIST: displayElement(temp->list->front);
                            printf("\n");
                            break;
            }
                found++;
            } else {
                temp=temp->next;
            }
            counter++;
        }
    }
    }
}


void modify(struct queue *q)
{
    if (q->front == NULL)
    {
        printf("The list is empty.\n\n");
    } 
    else
    {
        int found, index = 0, value = 0, counter = 0;
    struct node* temp;
    temp= malloc(sizeof(struct node));

    printf("please enter the index of the element you would like to modify: ");
    scanf("%d", &index);
    //index validation
    if (index<0 || index>length(q->front)-1)
    {
        printf("Index is out of range.\n");
    }

    else
    {
        printf("Enter data type (1) int, (2) float, (3) string, (4) double), (5) list: ");
    scanf("%d",&temp->type);

    switch(temp->type){
        case INT: printf("Enter a new whole number: ");
                    scanf("%d",&temp->a);
                    break;
        case FLOAT: printf("Enter a new real number: ");
                    scanf("%f",&temp->b);
                    break;
        case STR: printf("Enter a new string: ");
                    scanf("%s",temp->c);
                    break;
        case DOUBLE: printf("Enter a new double number: ");
                        scanf("%lf",&temp->d);
                        break;  
        case LIST: ;struct queue *list1;
                    list1=malloc(sizeof(struct queue));
                    list1->front=NULL;
                    list1->rear=NULL;
                    temp->list=list1;
                    printf("Follow the prompts for the first element of your list.\n");
                    append(list1);
                    break;
        default:
            printf("Invalid choice");
    }
        struct node* check=q->front;
        for (int i=0; i<index-1; i++)
        {
            check=check->next;
        }
        if (check->next==q->rear)
        {
            check->next=temp;
            q->rear=temp;
        }
        else if (index==0)
        {
            if (q->front==q->rear)
            {
                q->rear=temp;
            }
            temp->next=q->front->next;
            q->front=temp;
            found++;
        }
        else
        {
            struct node* current;
            current = q->front;
            while ((current != NULL) || (!found)){
            if(counter == index-1){
                temp->next=current->next->next;
                current->next = temp;
                found++;
            } else {
                current = current->next;
            }
            counter++;
            }
        }
    }
    }   
}

void min(struct queue *q, struct node *head){
    char *min = (char*)(malloc(2*sizeof(char)));
    strcpy(min, "z");
    char* s[10000];
    struct node* current;
    current = malloc(sizeof(struct node));
    current = head;

    if(current == NULL){
        printf("The list is empty.\n\n");
    } else {
        for (int i = 0; i < length(current); i++){
            switch(current->type){
                case INT: s[i] = (char*)(malloc(1000));
                          sprintf(s[i], "%d", current->a);
                          current = current->next;
                          break;
                case FLOAT: s[i] = (char*)(malloc(1000));
                            sprintf(s[i], "%f", current->b);
                            current = current->next;
                            break;
                case STR: s[i] = (char*)(malloc(1000));
                          strcpy(s[i], current->c);
                          current = current->next;
                          break;
                case DOUBLE: s[i] = (char*)(malloc(1000));
                             sprintf(s[i], "%lf", current->d);
                             current = current->next;
                             break; 
                default:
                    printf("Invalid choice");
            }
            if((strcmp(s[i], min) < 0)){
                min = s[i];
            }
        }
        printf("the min value is: %s\n", min);
    }
}

void concat(struct queue *q)
{
    int n;
    printf("Enter the number of elements you would like to concat to your list: ");
    scanf("%d",&n);
    for (int i=0; i<n; i++)
    {
        printf("For element %d:\n",i+1);
        append(q);
        printf("\n");
    }
}


void max(struct queue *q, struct node *head){
    char *max = (char*)(malloc(2*sizeof(char)));
    strcpy(max, "0");
    char* s[10000];
    struct node* current;
    current = malloc(sizeof(struct node));
    current = head;

    if(current == NULL){
        printf("The list is empty.\n\n");
    } else {
        for (int i = 0; i < length(current); i++){
            switch(current->type){
                case INT: s[i] = (char*)(malloc(1000));
                          sprintf(s[i], "%d", current->a);
                          current = current->next;
                          break;
                case FLOAT: s[i] = (char*)(malloc(1000));
                            sprintf(s[i], "%f", current->b);
                            current = current->next;
                            break;
                case STR: s[i] = (char*)(malloc(1000));
                          strcpy(s[i], current->c);
                          current = current->next;
                          break;
                case DOUBLE: s[i] = (char*)(malloc(1000));
                             sprintf(s[i], "%lf", current->d);
                             current = current->next;
                             break; 
                default:
                    printf("Invalid choice");
            }
            if((strcmp(s[i], max) > 0)){
                max = s[i];
            }
        }
        printf("the max value is: %s\n", max);
    }
}


int main()
{
    struct queue *q;
    q=malloc(sizeof(struct queue));
    q->front=NULL;
    q->rear=NULL;
    int exit=0, choice=0;

    while(exit != 1){

        printf("These are your options:\n(1) display your list\n"
            "(2) display element at index\n(3) modify an element at index"
            "\n(4) append an element\n(5) get the length of your list\n"
            "(6) insert an element at index\n(7) delete the list\n(8) min\n"
            "(9) max\n(10) concat\n(11) reverse\n(12) sort\n(13) exit\n"
            "Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice){
            case 1:
                displayList(q);
                break;
            case 2:
                displayElement(q->front);
                break;
            case 3:
                modify(q);
                break;
            case 4:
                append(q);
                break;
            case 5:
                printf("Length: %d\n",length(q->front));
                break;
            case 6:
                insert(q);
                break;
            case 7:
                deleteList(q);
                break;
            case 8:
                min(q, q->front);
                break;
            case 9:
                max(q, q->front);
                break;
            case 10:
                concat(q);
                break;
            case 11:
                reverse(q);
                break;
            case 12:
                sort(q);
                break;
            case 13:
                printf("see ya!\n");
                exit++;
                break;
            default:
                printf("Invalid input.\n");
        }

    }
    while (q->front != NULL)
    {
        deleteList(q); 
    }
    return 0;
}
