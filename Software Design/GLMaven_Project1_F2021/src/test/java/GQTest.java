import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class GQTest {

    private static int iter;
    private GenericQueue<Integer> testQueue;

    @BeforeAll
    static void setup() {
        iter = 0;
    }

    @BeforeEach
    void init() {
        testQueue = new GenericQueue<>(10);
        testQueue.enqueue(11);
        testQueue.enqueue(12);
    }

    @Test
    void testGQConstructorValue() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertEquals(myQueue.get(0), 10, "Wrong value in constructor.");
        assertEquals(myQueue.getLength(), 1, "Wrong value in constructor.");
    }

    @Test
    void testGQConstructorLength() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertEquals(myQueue.getLength(), 1, "Wrong length for constructor.");
    }

    @Test
    void testGQGetBoundCheck() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertNull(myQueue.get(1), "Getting for greater bound should be null.");
        assertNull(myQueue.get(-1), "Getting for less than 0 bound should be null.");
        myQueue.delete();
        assertNull(myQueue.set(0, 1), "Bound check for empty list returned wrong value");
    }

    @Test
    void testGQDeleteForOneElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertEquals(myQueue.delete(), 10, "Wrong value after calling delete");
        assertEquals(myQueue.getLength(), 0, "Wrong length after calling delete.");
    }

    @Test
    void testGQDeleteForNoElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.delete();
        assertNull(myQueue.delete(), "Wrong value for after calling delete on empty list.");
        assertEquals(myQueue.getLength(), 0, "Wrong length after calling delete.");
    }

    @Test
    void testGQDeleteForMoreElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.enqueue(11);
        assertEquals(myQueue.delete(), 10, "Wrong value for after calling delete.");
        assertEquals(myQueue.getLength(), 1, "Wrong length after calling delete.");
    }

    @Test
    void testGQSetBoundCheck() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertNull(myQueue.set(100, 1), "Bound check for set greater than length wrong value");
        assertNull(myQueue.set(-1, 1), "Bound check for set less than 0 returned wrong value");
    }

    @Test
    void testGQSetForOneElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertEquals(myQueue.set(0,100), 10, "Wrong value returned after setting an index");
        assertEquals(myQueue.get(0), 100, "Wrong value for set function.");
    }

    @Test
    void testGQSetForNoElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.delete();
        assertNull(myQueue.set(0, 1),  "Wrong value for set function.");
    }

    @ParameterizedTest
    @ValueSource(ints = {10,11,12})
    void testGQEnqueueValues(int arg) {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.enqueue(11);
        myQueue.enqueue(12);
        assertEquals(myQueue.get(iter),arg, "Values in queue incorrect after enqueue");
        iter++;
    }

    @Test
    void testGQEnqueueLength() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.enqueue(11);
        myQueue.enqueue(12);
        assertEquals(myQueue.getLength(), 3, "Wrong length after enqueue.");
    }

    @Test
    void testGQDequeueValueForOne() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        assertEquals(myQueue.dequeue(), 10, "Wrong value after dequeue.");
    }

    @Test
    void testGQDequeueLengthForOne() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.dequeue();
        assertEquals(myQueue.getLength(), 0, "Wrong length after dequeue.");
    }

    @Test
    void testGQDequeueValueForMore() {
        assertEquals(testQueue.dequeue(), 10, "Wrong value after dequeue.");
    }

    @Test
    void testGQDequeueLengthForMore() {
        testQueue.dequeue();
        assertEquals(testQueue.getLength(), 2, "Wrong length after dequeue.");
    }

    @Test
    void testGQRemoveTailNullHeadAndTail() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        myQueue.dequeue();
        // we have an empty queue and removing tail should just return null and not affect length
        myQueue.removeTail();
        assertEquals(myQueue.getLength(), 0, "Wrong value for removed tail.");
    }

    @Test
    void testGQRemoveTailOneElem() {
        GenericQueue<Integer> myQueue = new GenericQueue<>(10);
        // making sure queue has one value
        assertEquals(myQueue.getLength(), 1, "Wrong length for queue.");
        // removing the one elem
        assertEquals(myQueue.removeTail(), 10, "Wrong value after removing tail.");
        // making sure the correct element was removed
        assertEquals(myQueue.getLength(), 0, "Wrong length after removing tail.");
    }

    @Test
    void testGQRemoveTailMoreThanOneElem() {
        assertEquals(testQueue.removeTail(), 12, "Wrong value after removing tail in GenericQueue.");
        assertEquals(testQueue.getLength(), 2, "Wrong length after removing tail  in GenericQueue.");
    }

    @Test
    void testGQDumpList() {
        ArrayList<Integer> myList = testQueue.dumpList();
        ArrayList<Integer> correctVals = new ArrayList<>();
        correctVals.add(10);
        correctVals.add(11);
        correctVals.add(12);
        assertEquals(correctVals, myList, "Wrong Array list values");
    }

    @Test
    void testGQIterator() {
        GenericQueue<Integer> queue = new GenericQueue<>(5);
        queue.enqueue(4);
        queue.enqueue(3);
        queue.enqueue(2);
        queue.enqueue(1);
        Iterator<Integer> itr = queue.iterator();

        int count = 0;
        while (itr.hasNext()) {
            Integer elem = itr.next();
            count++;

            if (count == 1)
                assertEquals(elem, 5, "Wrong value for iterator.");
            else if (count == 2)
                assertEquals(elem, 4, "Wrong value for iterator.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for iterator.");
            else if (count == 4)
                assertEquals(elem, 2, "Wrong value for iterator.");
            else if (count == 5)
                assertEquals(elem, 1, "Wrong value for iterator.");

        }
    }

    @Test
    void testGQForEach() {
        GenericQueue<Integer> queue = new GenericQueue<>(5);
        queue.enqueue(4);
        queue.enqueue(3);
        queue.enqueue(2);
        queue.enqueue(1);
        int count = 1;
        for (Integer elem : queue) {
            if (count == 1)
                assertEquals(elem, 5, "Wrong value for forEach.");
            else if (count == 2)
                assertEquals(elem, 4, "Wrong value for forEach.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for forEach.");
            else if (count == 4)
                assertEquals(elem, 2, "Wrong value for forEach.");
            else if (count == 5)
                assertEquals(elem, 1, "Wrong value for forEach.");
            count++;
        }
    }

    @Test
    void testGQReverseIterator() {
        GenericQueue<Integer> queue = new GenericQueue<>(5);
        queue.enqueue(4);
        queue.enqueue(3);
        queue.enqueue(2);
        queue.enqueue(1);
        Iterator<Integer> itr = queue.descendingIterator();

        int count = 0;
        while (itr.hasNext()) {
            Integer elem = itr.next();
            count++;

            if (count == 1)
                assertEquals(elem, 1, "Wrong value for descending iterator.");
            else if (count == 2)
                assertEquals(elem, 2, "Wrong value for descending iterator.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for descending iterator.");
            else if (count == 4)
                assertEquals(elem, 4, "Wrong value for descending iterator.");
            else if (count == 5)
                assertEquals(elem, 5, "Wrong value for descending iterator.");

        }
    }


    @Test
    void testGQListIterator() {
        GenericQueue<Integer> queue = new GenericQueue<>(1);
        queue.enqueue(2);
        queue.enqueue(3);
        queue.enqueue(4);
        queue.enqueue(5);

        ListIterator<Integer> lItr = queue.listIterator(2); // should be at position 2: val 3

        // next should return value: 4 since it is next after 3 and update the internal index to 3
        assertEquals(lItr.next(), 4, "Wrong next value for List Iterator");

        // next index should be 4 based on the previous operation "next()" changed the index to 3
        assertEquals(lItr.nextIndex(), 4, "Wrong next index for List Iterator");

        // iterate forward completely
        while (lItr.hasNext()) {
            lItr.next();
        }
        // last value should be at index 5 meaning next index should return -1 meaning out of bounds
        assertEquals(lItr.nextIndex(), -1, "Wrong next index for List Iterator");

        // iterate backwards 3 times to bring us to position 1: val 2
        lItr.previous();
        lItr.previous();
        lItr.previous();

        // one more previous operation should bring us to position 0: val 1
        assertEquals(lItr.previous(), 1, "Wrong previous value");

        // and one more previous operation should bring us out of bounds for the index
        assertEquals(lItr.previousIndex(), -1, "Wrong previous value");

    }

}
