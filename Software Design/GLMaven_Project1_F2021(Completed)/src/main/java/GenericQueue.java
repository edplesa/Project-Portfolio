import java.util.Iterator;

public class GenericQueue<T> extends GenericList<T> {

    Node<T> tail;


    public GenericQueue(T newQueueVal) {
        Node<T> queueHead = new Node<>(newQueueVal);
        setHead(queueHead);
        setLength();
        this.tail = queueHead;
    }


    public T removeTail() {
        return null;
    }


    @Override
    void add(T data) {
        Node<T> newNode = new Node<>(data);
        this.tail.next = newNode;
        this.tail = newNode;
        setLength();
    }

    public void enqueue (T data) {
        add(data);
    }

    public T dequeue() {
        return delete();
    }

    @Override
    public Iterator<T> iterator() {
        return null;
    }
}
