import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

public abstract class GenericList<T> implements Iterable<T> {

    //  Node inner class for a singly linked list. Static
    //  so that we can use it without an object.
    static class Node<T> {
        T data;
        Node<T> next;

        //  single constructor to initialize our data with.
        public Node(T val) {
            this.data = val;
        }
    }

    private Node<T> head;
    private int length;


    //
    //  print() function: Prints the whole linked list elements
    //  from beginning to end. Used mainly for testing.
    //
    public void print() {
        Node<T> cur = this.head;

        //  If our head is null then the whole list is empty.
        if (cur == null) {
        	System.out.println("Empty List");
        } 

        //  If out head is not null then we have nodes to print out.
        if (cur != null) {
            while (cur != null) {
                System.out.println(cur.data);
                cur = cur.next;
            }
        }
               
    }

    //
    //  abstract add(): implemented in the child classes.
    //
    abstract void add(T data);

    //
    //  delete() function: removes the head node of any
    //  linked list object and returns the value in it.
    //
    public T delete() {

        Node<T> cur = this.head;

        //  if our head is not null then we remove it and update the
        //  next node to be the head.
        if (cur != null) {
            this.head = cur.next;
            this.length--;
            return cur.data;
        }

        //  otherwise return null since we have an empty list
        //  with no elements
        return null;
    }

    //
    //  dumpList() function: creates an array list object and
    //  populates it with all the values stored in our list.
    //  This will clear our linked list and return the ArrayList.
    //
    public ArrayList<T> dumpList() {
        ArrayList<T> newList = new ArrayList<T>();

        //  for each value in out list: add it to the ArrayList
        for (int i = 0; i < length; i++) {
            newList.add(this.get(i));
        }

        //  Destroy the list and restore to initial values
        this.head = null;
        this.length = 0;
        return newList;
    }

    //
    //  get function(): return the value stored at
    //  a specific index in our list.
    //
    public T get(int index) {

        //  Bound check to make sure we are in the list
        if (index < 0 || index >= length) {
            return null;
        }
        Node<T> cur = this.head;
        int count = 0;
        //  traverse our list and stop at the given index
        while (cur != null && index != count) {
            cur = cur.next;
            count++;
        }
        //  return the element at that index
        return cur.data;
    }


    //
    //  set() function: sets a new value to a given index
    //  then returns the original value in that position
    //
    public T set(int index, T element) {

        //  Bound check to make sure we are in the list
        if (index < 0 || index >= length) {
            return null;
        }

        Node<T> cur = this.head;

        int count = 0;

        //  traverse the list until we get to the specified index
        while (cur != null && index != count) {
            cur = cur.next;
            count++;
        }

        //  extract the original value
        T oldVal = cur.data;

        //  set the index with the new value
        cur.data = element;

        //  return original value
        return oldVal;
    }

    //
    //  getLength() function: return the length of our list
    //
    public int getLength() {
        return length;
    }

    //
    //  setLength() function: set the length of our list.
    //  Used mainly in child classes.
    //
    public void setLength(int newLength) {
        length = newLength;
    }

    //
    //  getHead() function: get the head of our list.
    //  Used mainly in child classes.
    //
    public Node<T> getHead() {
        return this.head;
    }

    //
    //  setHead() function: set the head of our list.
    //  Used mainly in child classes.
    //
    public void setHead(Node<T> newHead) {
        this.head = newHead;
    }

    //
    //  listIterator() function: return a list iterator object
    //  for our object
    //
    public ListIterator<T> listIterator(int index) {
        return new GLListIterator<T>(this, index);
    }

    //
    //  listIterator() function: return a descending iterator object
    //  for our object
    //
    public Iterator<T> descendingIterator() {
        return new ReverseGLLIterator<T>(this);
    }
}
