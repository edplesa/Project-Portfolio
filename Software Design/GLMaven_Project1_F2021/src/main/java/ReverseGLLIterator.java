import java.util.Iterator;

public class ReverseGLLIterator<E> implements Iterator<E> {

    //  Reference to the list we need to iterate over
    GenericList<E> list;

    //  Internal index for out iterator
    int index;

    //
    //  ReverseGLLIterator() constructor: initialize our internal
    //  reference to the list we need to iterate over and
    //  start our internal index at the last position since
    //  this is a reverse iterator
    //
    public ReverseGLLIterator(GenericList<E> ts) {
        list = ts;
        index = ts.getLength() - 1;
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
            //  Decrement our internal index since we are working in reverse
            index--;
            //  Return the value
            return val;
        }

        //  Else return null
        return null;
    }
}
