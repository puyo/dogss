// Templatised 2-way linked list
// v1.0


// NODE = generic list node (like a 'container' class)
// ITEM = list specific data in a node


#ifndef _LISTHAND_H_
#define _LISTHAND_H_


#ifndef NULL
#define NULL  0
#endif

// ??? any good?
#define WHILE_LIST_F(l, x)  l.ptr_rewind();       \
                            while (!l.ptr_done()) \
                              {                   \
                               (x)                \
                               l.ptr_forward();   \
                              }                   \


template <class ITEM>
class NODE
{
public:
 ITEM * item;
 NODE * next;
 NODE * prev;
};



template <class ITEM>
class LIST
{
public:
 NODE<ITEM> * start;
 NODE<ITEM> * end;
 NODE<ITEM> * pointer;

 LIST();
 ~LIST();

 // list handling //////////////////////////////////////////////////////

 // list traversal
 NODE<ITEM> *find_node(ITEM * item);

 void ptr_rewind()      { pointer = start;          } // forwards
 void ptr_forward()     { if (pointer != NULL) pointer = pointer->next;  }
 void ptr_fastforward() { pointer = end;            } // backwards
 void ptr_backward()    { if (pointer != NULL) pointer = pointer->prev;  }
 bool ptr_done()        { return (pointer == NULL); }

 // node making
 NODE<ITEM> * make_node(ITEM * item);

 // link an already made node
 void link_node_to_front(NODE<ITEM> * node);
 void link_node_to_back(NODE<ITEM> * node);

 // make a node with an already made item and link it
 void link_item_to_front(ITEM * item);
 void link_item_to_back(ITEM * item);

 // free/unlink/remove by node (remove = free + unlink)
 void free_node(NODE<ITEM> * node);
 void unlink_node(NODE<ITEM> * node);
 void remove_node(NODE<ITEM> * node);

 // free/unlink/remove by item (remove = free + unlink)
 void free_item(ITEM * item);
 void unlink_item(ITEM * item);
 void remove_item(ITEM * item);

 // returning items
 ITEM * current_item();
 NODE<ITEM> * current_node();
};


template <class ITEM>
LIST<ITEM>::LIST()
{
 start   = NULL;
 end     = NULL;
 pointer = NULL;
}



template <class ITEM>
LIST<ITEM>::~LIST()
{
 ptr_rewind();
 while (!ptr_done())
   {
    remove_node(pointer);
    ptr_forward();
   }
}



template <class ITEM>
NODE<ITEM> *LIST<ITEM>::find_node(ITEM * item)
{
 pointer_reset();
 while (!pointer_at_end())
   {
    if (&pointer->item == item)
      return pointer;
   }
 return NULL;
}



template <class ITEM>
NODE<ITEM> *LIST<ITEM>::make_node(ITEM * item)
{
 NODE<ITEM> *newnode = new (NODE<ITEM>);
 newnode->item = item;
 return newnode;
}



template <class ITEM>
void LIST<ITEM>::link_node_to_front(NODE<ITEM> * node)
{
                        //  n    .s-> ...
 node->prev = NULL;     // .n    .s-> ...
 node->next = start;    // .n->  .s-> ...
 if (start != NULL)
   start->prev = node;  // .n-> <-s-> ...
 start = node;          // .s-> <-x-> ...

 if (end == NULL)
   end = node;
}



template <class ITEM>
void LIST<ITEM>::link_node_to_back(NODE<ITEM> * node)
{
                      // ... <-e.    n
 node->prev = end;    // ... <-e.  <-n
 node->next = NULL;   // ... <-e.  <-n.
 if (end != NULL)
   end->next = node;  // ... <-e-> <-n.
 end = node;          // ... <-x-> <-e.

 if (start == NULL)
   start = node;
}



template <class ITEM>
void LIST<ITEM>::link_item_to_front(ITEM * item)
{
 NODE<ITEM> * node = make_node(item);
 link_node_to_front(node);
}



template <class ITEM>
void LIST<ITEM>::link_item_to_back(ITEM * item)
{
 NODE<ITEM> * node = make_node(item);
 link_node_to_back(node);
}



template <class ITEM>
void LIST<ITEM>::free_node(NODE<ITEM> * node)
{
 if (node != NULL)
   delete node;
}



template <class ITEM>
void LIST<ITEM>::unlink_node(NODE<ITEM> * node)
{
 if (node != NULL)                    // p = prev, o = node, n = next
   {
    if (node->prev != NULL)           // !(  .N.  <-o-> <-n-> )
      node->prev->next = node->next;  // A: p-> n, o <-n

    if (node->next != NULL)           // !( <-p-> <-o->  .N.  )
      node->next->prev = node->prev;  // B: p <-n, p-> o

                                      // A & B: <-p-> <-n->
    if (node == start)
      start = node->next;
    if (node == end)
      end = node->prev;
   }
}



template <class ITEM>
void LIST<ITEM>::remove_node(NODE<ITEM> * node)
{
 NODE<ITEM> * temp;

 if (node != NULL)
   free_item(node->item);

 if (pointer == node)
   {
    if (pointer->next != NULL)
      pointer = pointer->next;
    else
      pointer = pointer->prev;
   }

 // unlink the node and free its alloc'd memory
 temp = node;
 unlink_node(node);
 free_node(temp);
}



template <class ITEM>
void LIST<ITEM>::free_item(ITEM * item)
{
 if (item != NULL)
   delete item;
 item = NULL;
}



template <class ITEM>
void LIST<ITEM>::unlink_item(ITEM * item)
{
 NODE * node = find_node(item);
 unlink_node(node);
}



template <class ITEM>
void LIST<ITEM>::remove_item(ITEM * item)
{
 NODE * node = find_node(item);
 remove_node(node);
}



template <class ITEM>
ITEM * LIST<ITEM>::current_item()
{
 if (pointer != NULL)
   return pointer->item;
}



template <class ITEM>
NODE<ITEM> * LIST<ITEM>::current_node()
{
 return pointer;
}


#endif
