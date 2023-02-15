import java.util.Iterator;

public class GenericQueue<T> extends GenericList<T> {

    private Node<T> tail;

    //
    //  GenericQueue() constructor: given a generic element
    //  we initialize the head and tail of our linked list
    //  with it.
    //
    public GenericQueue(T newQueueVal) {
        Node<T> queueHead = new Node<>(newQueueVal);
        setHead(queueHead);
        setLength(getLength() + 1);
        this.tail = queueHead;
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
    //  add() function: add a new value into our queue
    //
    @Override
    void add(T data) {
        //  Create a new node with the specified value
        Node<T> newNode = new Node<>(data);
        //  Set the tail of our list as the new value
        //  since we are working with a queue (LIFO)
        this.tail.next = newNode;
        this.tail = newNode;
        //  Update the length
        setLength(getLength() + 1);
    }

    //
    //  enqueue() function: call add to add a new node to our queue
    //
    public void enqueue (T data) {
        add(data);
    }

    //
    //  pop() function: call super's delete function
    //  to remove the value at the front of our queue
    //
    public T dequeue() {
        return delete();
    }

    //
    //  iterator() function: return an iterator for
    //  our queue. Allows the use of a for each loop.
    //
    @Override
    public Iterator<T> iterator() {
        return new GLLIterator<T>(this);
    }
}
