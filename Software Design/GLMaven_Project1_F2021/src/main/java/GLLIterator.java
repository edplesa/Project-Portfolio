import java.util.Iterator;

public class GLLIterator<E> implements Iterator<E> {

    //  Reference to the list we need to iterate over
    GenericList<E> list;

    //  Internal index for out iterator
    int index = 0;

    //
    //  GLLIterator() constructor: initialize our internal
    //  reference to the list we need to iterate over.
    //
    public GLLIterator(GenericList<E> ts) {
        list = ts;
    }

    //
    //  hasNext() function: return true if list has a next
    //  element we can iterate to else false.
    //  We start outside the list.
    //
    @Override
    public boolean hasNext() {
        return list.get(index) != null;
    }

    //
    //  next() function: return the value of the next
    //  element in our list
    //
    @Override
    public E next() {
        //  If our index contains a value
        if ( list.get(index) != null) {
            //  Extract the value from that index
            E val = list.get(index);
            //  Increment our internal index
            index++;
            //  Return the value
            return val;
        }

        //  Else return null
        return null;
    }

}
