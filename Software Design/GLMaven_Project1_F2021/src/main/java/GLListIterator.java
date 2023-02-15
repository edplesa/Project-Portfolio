import java.util.ListIterator;

public class GLListIterator<T> implements ListIterator<T> {

    //  Reference to the list we need to iterate over
    GenericList<T> list;

    //  Internal index for out iterator
    int listIndex;

    //
    //  GLListIterator() constructor: initialize our internal
    //  reference to the list we need to iterate over. Also
    //  initialize at the index we are supposed to start at.
    //
    public GLListIterator(GenericList<T> ts, int index) {
        list = ts;
        listIndex = index;
    }

    //
    //  hasNext() function: return true if list has a next
    //  element we can iterate to else false.
    //  We start at the internal index.
    //
    @Override
    public boolean hasNext() {
        return list.get(listIndex+1) != null;
    }


    //
    //  next() function: return the value of the next
    //  element in our list
    //
    @Override
    public T next() {
        //  If our next index contains a value
        if ( list.get(listIndex+1) != null) {
            //  Extract the value from that index
            T val = list.get(listIndex+1);
            //  Increment our internal index
            listIndex++;
            //  Return the value
            return val;
        }

        //  Else return null
        return null;
    }

    //
    //  hasPrevious() function: return true if list has a previous
    //  element we can iterate to else false.
    //  We start at the internal index.
    //
    @Override
    public boolean hasPrevious() {
        return list.get(listIndex-1) != null;
    }

    //
    //  previous() function: return the value of the previous
    //  element in our list
    //
    @Override
    public T previous() {
        //  If our previous index contains a value
        if ( list.get(listIndex-1) != null) {
            //  Extract the value from that index
            T val = list.get(listIndex-1);
            //  Decrement our internal index
            listIndex--;
            //  Return that value
            return val;
        }
        //  Else return null
        return null;
    }

    //
    //  nextIndex() function: return the next index of our
    //  iterator. If we are outside the list return -1
    //
    @Override
    public int nextIndex() {
        if (list.get(listIndex+1) != null) {
            return listIndex+1;
        }
        return -1;
    }

    //
    //  previousIndex() function: return the next previous of our
    //  iterator. If we are outside the list return -1
    //
    @Override
    public int previousIndex() {
        if (list.get(listIndex-1) != null) {
            return listIndex-1;
        }
        return -1;
    }

    //
    //  Don't have to implement
    //
    @Override
    public void remove() {
    }

    //
    //  Don't have to implement
    //
    @Override
    public void set(Object o) {
    }

    //
    //  Don't have to implement
    //
    @Override
    public void add(Object o) {
    }
}
