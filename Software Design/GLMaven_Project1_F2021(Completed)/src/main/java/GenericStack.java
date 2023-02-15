import java.util.Iterator;

public class GenericStack<T> extends GenericList<T> {

    Node<T> tail;



    public GenericStack(T newStackVal) {
        Node<T> stackHead = new Node<>(newStackVal);
        setHead(stackHead);
        setLength();
        this.tail = stackHead;
    }

    public T removeTail() {
        return null;
    }



    @Override
    void add(T data) {
        Node<T> newNode = new Node<>(data);
        newNode.next = getHead();
        setHead(newNode);
        setLength();
    }

    public void push(T data) {
        add(data);
    }

    public T pop() {
        return delete();
    }


    @Override
    public Iterator<T> iterator() {
        return null;
    }
}
