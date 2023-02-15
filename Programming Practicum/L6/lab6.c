#include <stdio.h>
#include <stdlib.h>

#define TRUE   1
#define FALSE  0

#define COUNT 10

struct nodeStruct
{
 int elem;
 struct nodeStruct*  next;
};
 
typedef struct nodeStruct node;
typedef node* nodePtr; 

/* written with a pass-by-value parameter */
/* calling code:                          */
/*     node* head = NULL;               */
/*      ...                               */
/*     listLength (head);                 */
int listLength (node* hd)
{
 int length = 0;
 while (hd != NULL)
   {
    length++;
    hd = hd->next;
   }
 return length;
}

/* written with a C-style pass-by-"reference" parameter */
/* calling code:                                        */
/*     node* head = NULL;                             */
/*      ...                                             */
/*     listLength (&head);                              */
int listLengthPBR (node** hd)
{
 int length = 0;
 while (*hd != NULL)
   {
    length++;
    *hd = (*hd)->next;
   }
 return length;
}

/* the first parameter, hd, is pass-by-value */
node* insertAtFront2 (node* hd, int val)
{
 node* ptr = (node*) malloc (sizeof(node));
 ptr->elem = val;
 ptr->next = hd;	/* note that head is NOT de-referenced here */
 hd = ptr;
 return hd;
}

/* the first parameter hd is C-style pass-by-reference */
void insertAtFront (node** hd, int val)
{
 node* ptr = (node*) malloc (sizeof(node));
 ptr->elem = val;
 ptr->next = *hd;       /* note that hd must be "de-referenced" when used */
 *hd = ptr;             /*   the unary * operator is the "de-reference" operator */
}


void removeFromFront (node** hd)
{
 node* ptr = *hd;

 if (ptr != NULL)
   {
    *hd = ptr->next;
    free (ptr);
   }
}

node* removeFromFront2 (node* hd)
{  // code to be written as part of Lab 5, Q. 6
 







 return hd;
}

int getFirstValue (node* hd)
{
 if (hd != NULL)
   return hd->elem;
 else
   return -999;   /* returns -999 if list is empty */
}

int isEmpty (node* hd)
{
 if (hd == NULL)
   return TRUE;
 else
   return FALSE;
}


void show (node* hd)
{
 while (hd != NULL)
   {
    printf ("%d, ", hd->elem);
    hd = hd->next;
   }
 printf ("\n");
}

/* code to insert at the end of the linked list */
void insertAtEnd (node** hd, int val)
{
 node* curr = *hd;
 node* prev = NULL;

 /* find the end of the list */
 while (curr != NULL)
   {
    prev = curr;
    curr = curr->next;
   }

 /* create the new node to be inserted into the list */
 node* ptr = (node*) malloc (sizeof(node));
 ptr->elem = val;
 ptr->next = curr;   /* curr is always NULL at this line of code */

 /* if the list is empty the new node goes at the front (update head) */
 if (prev == NULL)
   {
    *hd = ptr;
   }
 else
   {
    prev->next = ptr;
   }
}


/* code to remove the node at the end of the linked list */
void removeFromEnd (node** hd)
{
 node* curr = *hd;
 node* prev = NULL;

 /* if curr is NULL, then list is empty.  Therefore, just return */
 if (curr == NULL)
   return;

 /* find the end of the list, 
  *   curr will point to node to be removed (last node in list) 
  *   prev will point to curr            
  */
 while (curr->next != NULL)
   {
    prev = curr;
    curr = curr->next;
   }


 /* deallocate the node pointed to by curr */
 free ( curr);

 /* if prev is NULL, original list only had 1 value, so now list is empty */
 if (prev == NULL)
   {
    *hd = NULL;
   }
 else /* second to last node in list becomes the last node */
   {
    prev->next = NULL;
   }
}


/* code to insert at the end of the linked list */
node* insertAtEnd2 (node* hd, int val)
{
  /* place needed code here */



  /* return the newly updated head of the list */
  return hd;
}



/* code to insert values in increasing order               */
/*   smaller values placed closer to the front of the list */
/*   larger values placed closer to the end of the list    */
void insertInOrder (node** hd, int val)
{
 node* curr = *hd;
 node* prev = NULL;

 /* set curr to refer to the node in the list that is >= val */
 /*   prev will be set to the node just before curr */
 while ((curr != NULL) && (curr->elem < val))
   {
    prev = curr;
    curr = curr->next;
   }

 /* create the node to add into the list */
 node* ptr = (node*) malloc (sizeof(node));
 ptr->elem = val;
 ptr->next = curr;

 /* if prev is null, insert at the front of the list */
 if (prev == NULL)
   {
    *hd = ptr;
   }
 else
   {  /* otherwise insert right after prev */
    prev->next = ptr;
   }
}

/* code to insert values in increasing order               */
/*   smaller values placed closer to the front of the list */
/*   larger values placed closer to the end of the list    */
node* insertInOrder2 (node* hd, int val)

{

 node* curr = hd;

 node* prev = NULL;



 while ((curr != NULL) && (curr->elem < val)) {

   prev = curr;

   curr = curr->next;

 }



 node* ptr = (node*) malloc (sizeof(node));

 ptr->elem = val;

 ptr->next = curr;



 if(prev == NULL) {

   hd = ptr;

 } else {

   prev->next = ptr;

 }





 /* return the newly updated head of the list */

 return hd;

}

/* code to remove a given value from a list                */
void removeFromList (node** hd, int val)
{
	node* curr = *hd;
 	node* prev = NULL;

 	while ((curr != NULL) && (curr->elem != val))
  	 {
   		 prev = curr;
    	curr = curr->next;
   	 }

 
 
 if (!curr)
   {
   	*hd = NULL;
    return;
   }
   else if(prev == NULL && curr != NULL)
   {
  		free(curr);
    	*hd = NULL;
   }   
 else
   {  
    	prev->next = curr->next;
    	free(curr);
   }

}

int main (int argc, char**argv)
{
  node* head1 = NULL;
  node* head2 = NULL;
  node* head3 = NULL;
  int i;
  int temp;

  /* adding values to the front of the list */
  for (i = 0 ; i < COUNT; ++i)
    {
     temp = rand() % 100;
     printf ("In main(): Adding Value of: %6d\n", temp);

     /* head1 being sent as C-style pass-by-reference */
     insertInOrder (&head1, temp);		  /* must send the address of head here */

     /* head2 being sent as C pass-by-value */
     head2 = insertInOrder2 (head2, temp);  /* must send the value of head2 here */

     /* head3 being send as C-style pass-by-refernce */
     insertAtEnd ( &head3, temp);

     printf ("List 1 has %d nodes\n", listLength(head1));
     show (head1);
     printf ("List 2 has %d nodes\n", listLength(head2));
     show (head2);
     printf ("List 3 has %d nodes\n", listLength(head3));
     show (head3);
     printf ("\n");
    }

  printf ("\n\nRemoving items from the list\n");
  for (i = 0 ; i < COUNT/2 ; i++)
    {
     int val = getFirstValue (head3);
     printf ("The first item in list 3 is: %d\n", val);
     removeFromList (&head1, val);
     removeFromEnd (&head2);
     removeFromFront (&head3);

     /* to help show what is going on */
     printf ("List 1 has %d nodes\n", listLength(head1));
     show (head1);
     printf ("List 2 has %d nodes\n", listLength(head2));
     show (head2);
     printf ("List 3 has %d nodes\n", listLength(head3));
     show (head3);
     printf ("\n");
    }

  printf ("\n");


}
