//
//  linkedlist.h
//  serhansilahyurekli_25205_hw4
//
//  Created by Serhan Silahyürekli on 23.11.2019.
//  Copyright © 2019 Serhan Silahyürekli. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

#include <string>
using namespace std;
struct list
{
    int ID;
    int size;
    int index;
    list *next;
    list()
    :next(NULL)
    {}
};

class linkedlist
{
public:
    linkedlist();//constructor
    ~linkedlist();//deconstructor
    void add(int tid, int size,int index);//add new list end of linkedlist
    void printlist();//print the linkedlist
    bool enoughspace(int temp,int & indexx);//check if there is enough space to allocate and initialize index
    void checklist(int memory);//initialize size of last member of linkledlist if total of all member's size bigger than memory
    void change(int memory,int size);//find the member with id -1 than check size is enough for the new coming member if not find next member with id -1 then change the size of member with id -1 or remove it if their sizes equal
    void findandchange(int tid);//when freeing the memory change that member's id with -1
    void deletelist();//delete all list
    void truelist();//sort all linkedlist by their indexes
    void sameindex();//find that if there are same indexed members and remove one of them
    int find(int tid);//find index of member with given id
private:
    list*head;
};


#endif /* linkedlist_h */
