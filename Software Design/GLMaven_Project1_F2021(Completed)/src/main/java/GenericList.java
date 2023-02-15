import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

public abstract class GenericList<T> implements Iterable<T> {


    static class Node<T> {
        T data;
        Node<T> next;

        public Node(T val) {
            this.data = val;
        }
    }

    private Node<T> head;
    private int length;


    public void print() {
        Node<T> cur = this.head;
        
        if (cur == null) {
        	System.out.println("Empty List");
        } 

        if (cur != null) {
            while (cur != null) {
                System.out.println(cur.data);
                cur = cur.next;
            }
        }
               
    }

    abstract void add(T data);

    public T delete() {

        Node<T> cur = this.head;

        if (cur != null) {
            this.head = cur.next;
            this.length--;
            return cur.data;
        }
        
        return null;
    }


    public ArrayList<T> dumpList() {
        ArrayList<T> newList = new ArrayList<T>();

        for (int i = 0; i < length; i++) {
            newList.add(this.get(i));
        }
        this.head = null;
        this.length = 0;
        return newList;
    }


    public T get(int index) {
        if (index < 0 || index >= length) {
            return null;
        }

        Node<T> cur = this.head;

        int count = 0;

        while (cur != null && index != count) {
            cur = cur.next;
            count++;
        }
        return cur.data;
    }

    public T set(int index, T element) {
        if (index < 0 || index >= length) {
            return null;
        }

        Node<T> cur = this.head;

        int count = 0;

        while (cur != null && index != count) {
            cur = cur.next;
            count++;
        }

        T oldVal = cur.data;

        cur.data = element;

        return oldVal;
    }


    public int getLength() {
        return length;
    }

    // unsure here
    public void setLength() {
        length++;
    }

    public Node<T> getHead() {
        return this.head;
    }

    // unsure here
    public void setHead(Node<T> newHead) {
        this.head = newHead;
    }




    public ListIterator<T> listIterator(int index) {
        return null;
    }

    public Iterator<T> iterator() {
    	return null;
        //return new GLLIterator<T>(this);
    }

    public Iterator<T> descendingIterator() {
    	return null;
        //return new ReverseGLLIterator<T>();
    }



}
