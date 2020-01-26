#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <queue>
#include <semaphore.h>
#include <string.h>
#include "linkedlist.h"
using namespace std;
linkedlist::linkedlist()//constructor
{
    head = NULL;
}
linkedlist::~linkedlist()//deconstructor
{
    deletelist();
}
void linkedlist::add(int tid , int size,int index)//add new list end of linkedlist
{
    
    list *ptr = head;
    list *temp = new list;
    temp ->ID = tid;
    temp -> size = size;
    temp -> index = index;
    if(head == NULL)
    {
        head = temp;
        ptr = head;
        ptr ->next = NULL;
    }
    else
    {
        while(ptr -> next != NULL)
        {
            ptr = ptr -> next;
        }
        ptr ->next = temp;
        ptr = ptr->next;
        ptr ->next = NULL;
    }
}
bool linkedlist::enoughspace(int temp,int & index)//check if there is enough space to allocate and initialize index according to first empty space's index
{
    list * ptr = head;
    while(ptr != NULL)
    {
        if((ptr->ID) == -1)
        {
            if(ptr->size >= temp)
            {
                index = ptr ->index;
                ptr = ptr ->next;
                return true;
            }
        }
        ptr = ptr -> next;
    }
    index = -1;
    return false;
}
void linkedlist::printlist()//print the linkedlist
{
    list *ptr = head;
    while(ptr != NULL)
    {
        if(ptr -> next == NULL)
        {
            cout<<"[" << ptr->ID <<"]" <<"[" << ptr->size <<"]" <<"[" << ptr->index <<"]";
        }
        else
        {
            cout<<"[" << ptr->ID <<"]" <<"[" << ptr->size <<"]" <<"[" << ptr->index <<"]" << "- - -";
        }
        ptr = ptr->next;
    }
}
void linkedlist::truelist()//sort all linkedlist by their indexes
{
    list*ptr = head;
    list*temp = head;
    int tempid,tempsize,tempindex;
    while(temp != NULL)
    {
        while(ptr != NULL)
        {
            if(ptr ->next != NULL)
            {
                if((ptr->index) > ptr ->next ->index )
                {
                    tempid = ptr -> ID;
                    tempsize = ptr -> size;
                    tempindex = ptr -> index;
                    ptr -> ID = ptr -> next -> ID;
                    ptr -> size = ptr -> next -> size;
                    ptr -> index = ptr -> next -> index;
                    ptr -> next -> ID = tempid;
                    ptr -> next -> size = tempsize;
                    ptr -> next -> index = tempindex;
                }
            }
            ptr = ptr -> next;
        }
        temp = temp ->next;
        ptr = head;
    }
}
void linkedlist::checklist(int memory)//initialize size of last member of linkledlist if total of all member's size bigger than memory
{
    int lasttotal = 0;
    int newindex = 0;
    list *ptr = head;
    while(ptr->next != NULL)
    {
        lasttotal += ptr ->size;
        if(ptr -> next != NULL)
        {
            if(ptr ->next ->next == NULL)
            {
                newindex = ptr -> size + ptr->index;
            }
        }
        ptr = ptr ->next;
    }
    if(memory != lasttotal + (ptr->size))
    {
        ptr-> size = memory - lasttotal;
        ptr ->index = newindex;
    }
}

void linkedlist::change(int memory,int size)//find the member with id -1 than check size is enough for the new coming member if not find next member with id -1 then change the size of member with id -1 or remove it if their sizes equal
{
    list*ptr = head;
    list*dummy;
    list *ntr;
    int tempid,tempsize,tempindex;
    while(ptr ->ID != -1 || ptr->size < size)
    {
        dummy = ptr;
        ptr = ptr ->next;
    }
    list *temp = ptr->next;
    if(ptr->ID == -1 && ptr ->next !=NULL)
    {
        ntr = temp;
        if(ptr ->size > ntr ->size)
        {
            tempid = ptr -> ID;
            tempsize = ptr -> size;
            tempindex = ptr -> index;
            ptr -> ID = ntr -> ID;
            ptr -> size = ntr -> size;
            ptr -> index = ntr -> index;
            ntr -> ID = tempid;
            ntr -> size = tempsize - ptr -> size;
            ntr -> index = tempindex + ptr->size ;
        }
        else if(ptr ->size == ntr ->size)
        {
            if(ptr !=head)
            {
                dummy->next = temp;
                delete ptr;
            }
            else
            {
                head = ntr;
                delete ptr;
            }
        }
    }
}
void linkedlist::findandchange(int tid)//when freeing the memory change that member's id with -1
{
    list* ptr = head;
    list*temp;
    bool changed = false;
    while(ptr ->ID != tid)
    {
        if(ptr -> next != NULL)
        {
            if(ptr ->next->ID == tid)
            {
                if(ptr ->ID == -1)
                {
                    ptr->size = ptr->size + ptr ->next -> size;
                    changed = true;
                    temp = ptr -> next;
                    ptr->next = temp ->next;
                    delete temp;
                }
                else
                {
                    temp = ptr;
                }
            }
        }
        ptr = ptr->next;
    }
    if(ptr -> next != NULL)
    {
        if(ptr -> next ->ID == -1)
        {
            ptr -> next-> size = ptr->size + ptr ->next -> size;
            ptr ->next->index = ptr ->index;
            changed = true;
            if(ptr != head)
            {
                temp -> next = ptr -> next;
                temp = ptr;
                ptr = ptr -> next;
                delete temp;
            }
            else
            {
                head = ptr ->next;
                delete ptr;
            }
        }
    }
    if(!changed)
    {
        ptr ->ID = -1;
    }
}

void linkedlist::deletelist()//delete all list
{
    list *ptr = head;
    list* temp;
    while(ptr != NULL)
    {
        temp = ptr;
        ptr = ptr ->next;
        delete temp;
    }
    head = NULL;
}
void linkedlist::sameindex()//find that if there are same indexed members and remove one of them
{
    bool changed = false;
    list *ptr = head;
    list *temp;
    while (ptr !=NULL)
    {
        if(ptr -> ID == -1)
        {
            if(ptr->next != NULL)
            {
                if(ptr ->index == ptr->next->index)
                {
                    if(ptr == head)
                    {
                        temp = ptr->next;
                        head = temp;
                        delete ptr;
                        changed = true;
                        
                    }
                    else
                    {
                        temp -> next = ptr ->next;
                        delete ptr;
                        changed = true;
                    }
                }
            }
        }
        if(!changed)
        {
            temp = ptr;
        }
        ptr = ptr ->next;
    }
}
int linkedlist::find(int tid)//find index of member with given id
{
    list*ptr = head;
    while(ptr!=NULL)
    {
        if(ptr->ID == tid)
        {
            return ptr->index;
        }
        ptr = ptr ->next;
    }
    return -2;
}


#define NUM_THREADS 3
#define M 10
struct node
{
    int id;
    int size;
};

linkedlist list;//list
queue<node> myqueue; // shared que
pthread_mutex_t sharedLock = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_t server; // server thread handle
sem_t semlist[NUM_THREADS]; // thread semaphores
char  memory[M]; // memory size
int indexx;
bool allocated = false;
bool changed = false;
bool freed = false;

void release_function()
{
    for(int k = 0;k < M;k++)//change all memory with X
    {
        memory[k] = 'X';
    }
    printf("\nTerminating...\n");
    exit(0);
    //This function will be called
    //whenever the memory is no longer needed.
    //It will kill all the threads and deallocate all the data structures.
}
void free_mem(int tid,int size)
{
    for(int i = list.find(tid);i < list.find(tid)+size ;i++)//change freed memory with X
    {
        memory[i] = 'X';
    }
    list.findandchange(tid);
    list.sameindex();
    freed = true;
}
void use_mem()
{
    int waiting = rand() % 5 + 1;//random amount of sleep time
    usleep(waiting*1000);
}
void my_malloc(int thread_id, int size)
{
    //This function will add the struct to the queue
    pthread_mutex_lock(&sharedLock);
    node p;
    p.id= thread_id;
    p.size= size;
    myqueue.push(p);
    pthread_mutex_unlock(&sharedLock);
    sem_wait(&semlist[thread_id]);
}
void dump_memory()
{
    cout<< "List:"<<endl;
    list.printlist();
    cout <<endl;
    cout<< "Memory Dump:"<<endl;
    for(int k = 0;k < M;k++)
    {
        cout << memory[k];
    }
    cout <<endl;
    cout << "*********************************" << endl;
}
void * server_function(void *)
{
    while(true)
    {
        pthread_mutex_lock(&sharedLock);
        while(!myqueue.empty() && !changed)//if it is not empty and if one time we initialize indexx then wait the thread to finish its job and then next thread come and initialize its index
        {
            int index;
            int temp =myqueue.front().size;
            int tempid = myqueue.front().id;
            
            allocated = list.enoughspace(temp,index);
            indexx = index;
            changed = true;//false when thread done its job
            
            sem_post(&semlist[tempid]);
            myqueue.pop();
            
            pthread_mutex_unlock(&sharedLock);
            pthread_mutex_lock(&sharedLock);
        }
        pthread_mutex_unlock(&sharedLock);
    }
    return 0;//This function should grant or decline a thread depending on memory size.
}

void * thread_function(void * id)
{
    while(true)
    {
        int * tid = (int *) id;
        int ka = *tid;
        int tempm = M;
        int size = rand() % M + (M/3) ;
        my_malloc(ka,size);
        
        pthread_mutex_lock(&sharedLock);
        if(indexx > -1 && allocated)
        {
            int tempindex = indexx;
            int tempsize = size;
            list.add(ka, tempsize,tempindex);
            list.truelist();
            list.change(tempm,tempsize);
            list.checklist(tempm);
            for(int l = indexx; l < tempindex+tempsize ;l++)
            {
                memory[l] = ka + 48;//ascii number
            }
            changed = false;//job is done
            dump_memory();
            pthread_mutex_unlock(&sharedLock);
            use_mem();
            
            pthread_mutex_lock(&sharedLock);    //lock
            free_mem(ka,size);
            pthread_mutex_unlock(&sharedLock);    //unlock
        }
        else
        {
            changed = false;
            pthread_mutex_unlock(&sharedLock);
        }
    }
    //This function will create a random size, and call my_malloc
    //Block
    //Then fill the memory with 1's or give an error prompt
    return 0;
}

void init()
{
    pthread_mutex_lock(&sharedLock);    //lock
    for(int i = 0; i < NUM_THREADS; i++) //initialize semaphores
    {sem_init(&semlist[i],0,0);}
    for (int i = 0; i < M; i++)    //initialize memory
    { memory[i] = 'X';}
    pthread_create(&server,NULL,server_function,NULL); //start server
    pthread_mutex_unlock(&sharedLock); //unlock
}




int main (int argc, char *argv[])
{
    srand(time(NULL));
    list.add(-1,M,0);//first all member is full of X so insert -1 id with size Member size
    pthread_t creator[NUM_THREADS];
    int threadids[NUM_THREADS];
    //You need to create a thread ID array here
    for(int i = 0; i<NUM_THREADS; i++)
    {
        threadids[i] = i;
    }
    init();    // call init
    //You need to create threads with using thread ID array, using pthread_create()
    for(int i=0; i<NUM_THREADS; i++)
    {
        pthread_create(&(creator[i]), NULL, thread_function, &threadids[i]);
    }
    //You need to join the threads
    usleep(10000);//sleep 10 seconda
    release_function();//exit
    for(int i=0; i<NUM_THREADS; i++)
    {
        pthread_join(creator[i], NULL);
    }

    pthread_join(server, NULL);
    
}
