import java.util.Iterator;

public class GenericStack<T> extends GenericList<T> {

    private Node<T> tail;

    //
    //  GenericStack() constructor: given a generic element
    //  we initialize the head and tail of our linked list
    //  with it.
    //
    public GenericStack(T newStackVal) {
        Node<T> stackHead = new Node<>(newStackVal);
        setHead(stackHead);
        setLength(getLength() + 1);
        this.tail = stackHead;
    }

    //
    //  removeTail() function: remove the tail in our linked list
    //  and return the value the tail had.
    //
    public T removeTail() {
        //  If our head is null then we have no list
        //  so return null
        if (getHead() == null) {
            return null;
        }
        else {
            //  If we have a list with a single element
            if (getHead() == tail) {
                Node<T> temp = getHead();
                //  Get the value from head
                T val = temp.data;
                //  Destroy our list
                setHead(null);
                tail = null;
                //  Update the length
                setLength(getLength() - 1);
                //  Return the val
                return val;

            } else {
                //  Else we have a list with more than one element
                Node<T> cur = getHead();
                //  Traverse to the second to last element
                while (cur.next != tail) {
                    cur = cur.next;
                }
                //  Get the value in the tail
                T val = tail.data;
                //  Set the second to last element as the new tail
                tail = cur;
                tail.next = null;
                //  Update the length
                setLength(getLength() - 1);
                //  Return the old tail's value
                return val;
            }
        }
    }

    //
    //  add() function: add a new value into our stack
    //
    @Override
    void add(T data) {
        //  Create a new node
        Node<T> newNode = new Node<>(data);
        //  Make the new node the head of our list since
        //  we need a stack
        newNode.next = getHead();
        setHead(newNode);
        //  Update the length
        setLength(getLength() + 1);
    }

    //
    //  push() function: call add to add a new node to our stack
    //
    public void push(T data) {
        add(data);
    }

    //
    //  pop() function: call super's delete function
    //  to remove the value at the top of our stack
    //
    public T pop() {
        return delete();
    }

    //
    //  iterator() function: return an iterator for
    //  our stack. Allows the use of a for each loop.
    //
    @Override
    public Iterator<T> iterator() {
        return new GLLIterator<T>(this);
    }
}
