#include "lab11List.h"


void functPBR ( MyList &p)
{
 printf ("In functPBR: ");
 p.show();
}

void functPBV ( MyList p)
{
 printf ("In functPBV: ");
 p.show();
}



int main (int argc, char** argv)
{
  MyList list1;
  MyList list2;

  // insert some values
  printf ("\nTesting the insert() and show() methods\n");
  list1.insert (5);
  list1.insert (18);
  list1.insert (10);
  list1.show();
  list1.insert (3);
  list1.show();

  printf ("\nTesting the insertAtEnd() and remove() methods\n");
   
  list2.insertAtEnd (51);
  list2.insertAtEnd (68);
  list2.insertAtEnd (24);
  list2.show();
  list2.remove(22);
  list2.show();
  list2.remove(68);
  list2.show();
  list2.insertAtEnd(12);
    
  // remove some values
  list1.remove (10);
  list1.show();
  list1.remove (7);
  list1.show();
  list1.remove (3);
  list1.show();
  list1.remove (18);
  list1.show();
       
  /* add code to test the getListLength and getNthElem methodes */
  printf ("\nTesting the getListLength() and getNthElem() methods\n");
  MyList list3;
  // insert some values and verify they are correct
  list3.insertInOrder (6);
  list3.insertInOrder (4);
  list3.insertInOrder (10);
  list3.insertInOrder (2);
  list3.insertInOrder (8);
  list3.show();

  int sum = 0;
  for ( int pos = 0 ; pos < list3.getListLength() ; pos++)
   {
       sum = sum + list3.getNthElem( pos );
    }
  printf("The total of the values in the list is: %d\n", sum);


   
  // For the following code, make sure to complete the destructor
  // Code to test the Copy Constructor
  printf ("\nTesting the Copy Constructor\n");
  // creating a nested block of code for a local variable
  if ( true )
  { 
    MyList list4 ( list3 );
    list3.show();
    list4.show();
    list4.insertInOrder(7);
    printf ("If the next 2 lines are the same, Shallow Copy occurred\n");
    list3.show();
    list4.show();

    // as nested block of code ends, destructor will be invoked on list4
  } // LINE 304
    // all of the nodes from list4 were removed
  printf ("\nTesting destructor's impact on list3 for LINE 304 \n");
  list3.show();

  // Test of destructor and Copy Constructor
  printf ("\nTesting the destructor and Copy Constructor LINE 322 and LINE 326\n");
  MyList list5;
  list5.insert (30);
  list5.insert (50);
  list5.insert (10);
  list5.insert (20);
  list5.insert (40);
  list5.show();
  MyList list6;
  list6.makeCopy ( list5 );
  list6.show();
  // call a function sending list5 as pass-by-reference
  functPBR ( list5 );       // LINE 322
  list5.show();

  // call a function sending list6 as pass-by-value
  functPBV ( list6 );       // LINE 326
  list6.show();
  
  // Use the overloaded assignment operator 
  MyList list7, list8, list9;
  list7.insert (3);
  list7.insert (6);
  list7.insert (9);
  list7.insert (12);
  list8.insert (2);
  list8.insert (4);
  list8.insert (6);
  list9.insert (12);
  list9.insert (14);
  list9.insert (16);
  list7.show();
  list8.show();
  list9.show();
  list7 = list8;
  list9 = list9;		// LINE 345
  list7.show();
  list8.show();
  list9.show();
  list7 = list8 = list9;	// LINE 349
  list7.show();
  list8.show();
  list9.show();


  // At End of Main
  printf ("\nAt End of Main: Destructor is invoked\n"); 
 
  return 0;
}
