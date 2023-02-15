#include "lab11List.h"

//  Code for the methods is the MyLNode class
//    These are the Node Level operations
//    Contains: 
//      2 constructors
//      Getters and Setters for the 2 data members
MyLNode::MyLNode (int v1)
{
  elem = v1;
  next = NULL;
}
  
MyLNode::MyLNode (int v1, MyLNode* n)
{
  elem = v1;
  next = n;
}

void MyLNode::setElem (int e)
{
  elem = e;
}

int MyLNode::getElem ()
{
  return elem;
}

void MyLNode::setNext (MyLNode* n)
{
  next = n;
}

MyLNode* MyLNode::getNext()
{
  return next;
}



//  Methods for the MyList class
//    These are the List Level operations
MyList::MyList()
{
  head = NULL;
}

MyList::MyList ( const MyList &p)   //LINE 99
{
 head = p.head;    // This code does Shallow Copy
 makeCopy (p);       // This code does a Deep Copy
}

// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void MyList::makeCopy ( const MyList &p)
{
 head = NULL;
 copyNode (p.head);
} 
 
void MyList::copyNode (MyLNode* pNode)
{
  if (pNode != NULL)
  {
    copyNode ( pNode->getNext() );

    // insert nodes at the front of the list while returning
    //   from the recursive calls  (adds values to the front
    //   in reverse order - this copies the list on O(n) time
    head = new MyLNode ( pNode->getElem(), head );
  }
}

// method to print out all of the values in the list
void MyList::show()
{
  MyLNode* tmp = head;
  
  while ( tmp != NULL )
  {
    printf ("%d, ", tmp->getElem() );
    tmp = tmp->getNext();
  }
  printf ("\n");
}

void MyList::insert (int v1)
{
  MyLNode* tmp = new MyLNode (v1);
  
  // this code just inserts the node at the beginning of the list
  tmp->setNext (head);
  head = tmp;

 }

void MyList::insertAtEnd (int v1){
	MyLNode* tmp = new MyLNode(v1);
	
	MyLNode* curr = head;
	MyLNode* prev = NULL;

	 /* find the end of the list */
	 while (curr != NULL)
	   {
		prev = curr;
		curr = curr->getNext();
	   }	
	tmp->setNext(curr);
	
	if (prev == NULL) {
		head = tmp;
	}
	else {
		prev->setNext(tmp);
	}

}


void MyList::insertInOrder(int v1){

	MyLNode* tmp = new MyLNode (v1);
	
	MyLNode* curr = head;
 	MyLNode* prev = NULL;
 	
 	while ((curr != NULL) && (curr->getElem() < v1))
   {
    prev = curr;
    curr = curr->getNext();
   }
   tmp->setNext(curr);
   
   if (prev == NULL) {
  	head = tmp;
   }
   else {
   	prev->setNext(tmp);
   }
	
}

void MyList::remove (int v1)
{
  MyLNode* curr = head;
  MyLNode* prev = NULL;
  
  while ( ( curr != NULL ) && ( curr->getElem() != v1 ) )
  {
    prev = curr;
    curr = curr->getNext();
  }

  if ( curr == NULL ) // v1 does not exist in list
    return;

  if ( prev == NULL ) // v1 is in first/head node in list
  {
    head = curr->getNext();
    delete curr;
  }
  else
  {
    prev->setNext( curr->getNext() );
    delete curr;
  }
}

  

void MyList::removeAll ()
{
  while (head != NULL) {
  	MyLNode* temp = head;
  	head = head->getNext();
  	delete temp;
  }
  
}

MyList::~MyList()
{
  printf ("In Destructor: ");
  // Note that removeAll() does same operation as required by destructor
  removeAll();
  
 
}

// the overloaded assignment operator
//
MyList& MyList::operator= (const MyList& p)
{
 if ( this == &p )   // both operands are the same
   return *this;     //   do nothing, just return

 removeAll();        // Deallocate the existing list

 makeCopy (p);       // Do a deep copy

 return *this;       // allow for "cascading assignments":  a = b = c;
}

int MyList::getListLength(){
	int count = 0;
	
	MyLNode* cur = head;
	
	while (cur != NULL) {
		count++;
		cur = cur->getNext();
	}
	return count;

}


int MyList::getNthElem(int n){
	int count = 0;
	
	MyLNode* cur = head;
	
	while (cur != NULL && count != n) {
		count++;
		cur = cur->getNext();
	}
	return cur->getElem();
}

