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

public class GSTest {

    private static int iter;
    private GenericStack<Integer> testStack;

    @BeforeAll
    static void setup() {
        iter = 0;
    }

    @BeforeEach
    void init() {
        testStack = new GenericStack<>(10);
        testStack.push(11);
        testStack.push(12);
    }

    @Test
    void testGSConstructorValue() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertEquals(myStack.get(0), 10, "Wrong value in constructor.");
        assertEquals(myStack.getLength(), 1, "Wrong value in constructor.");
    }

    @Test
    void testGSConstructorLength() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertEquals(myStack.getLength(), 1, "Wrong length for constructor.");
    }

    @Test
    void testGSGetBoundCheck() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertNull(myStack.get(1), "Getting for greater bound should be null.");
        assertNull(myStack.get(-1), "Getting for less than 0 bound should be null.");
    }

    @Test
    void testGSDeleteForOneElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertEquals(myStack.delete(), 10, "Wrong value after calling delete");
        assertEquals(myStack.getLength(), 0, "Wrong length after calling delete.");
    }

    @Test
    void testGSDeleteForNoElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.delete();
        assertNull(myStack.delete(), "Wrong value for after calling delete on empty list.");
        assertEquals(myStack.getLength(), 0, "Wrong length after calling delete.");
    }

    @Test
    void testGSDeleteForMoreElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.push(11);
        assertEquals(myStack.delete(), 11, "Wrong value for after calling delete.");
        assertEquals(myStack.getLength(), 1, "Wrong length after calling delete.");
    }

    @Test
    void testGSSetBoundCheck() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertNull(myStack.set(100, 1), "Bound check for set greater than length wrong value");
        assertNull(myStack.set(-1, 1), "Bound check for set less than 0 returned wrong value");
        myStack.delete();
        assertNull(myStack.set(0, 1), "Bound check for empty list returned wrong value");
    }

    @Test
    void testGSSetForOneElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertEquals(myStack.set(0,100), 10, "Wrong value returned after setting an index");
        assertEquals(myStack.get(0), 100, "Wrong value for set function.");
    }

    @Test
    void testGSSetForNoElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.delete();
        assertNull(myStack.set(0, 1),  "Wrong value for set function.");
    }

    @ParameterizedTest
    @ValueSource(ints = {12,11,10})
    void testGSPushValues(int arg) {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.push(11);
        myStack.push(12);
        assertEquals(myStack.get(iter),arg, "Values in stack incorrect after push");
        iter++;
    }

    @Test
    void testGSPushLength() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.push(11);
        myStack.push(12);
        assertEquals(myStack.getLength(), 3, "Wrong length for stack push.");
    }



    @Test
    void testGSPopValueForOne() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        assertEquals(myStack.pop(), 10, "Wrong value for stack pop.");
    }

    @Test
    void testGSPopLengthForOne() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.pop();
        assertEquals(myStack.getLength(), 0, "Wrong length for stack pop.");
    }

    @Test
    void testGSPopValueForMore() {
        assertEquals(testStack.pop(), 12, "Wrong value for stack pop.");
    }

    @Test
    void testGSPopLengthForMore() {
        testStack.pop();
        assertEquals(testStack.getLength(), 2, "Wrong length for stack pop.");
    }

    @Test
    void testGSRemoveTailNullHeadAndTail() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        myStack.pop();
        // we have an empty stack and removing tail should just return null and not affect length
        myStack.removeTail();
        assertEquals(myStack.getLength(), 0, "Wrong value for removed tail.");
    }

    @Test
    void testGSRemoveTailOneElem() {
        GenericStack<Integer> myStack = new GenericStack<>(10);
        // making sure stack has one value
        assertEquals(myStack.getLength(), 1, "Wrong length for stack.");
        // removing the one elem
        assertEquals(myStack.removeTail(), 10, "Wrong value for stack remove tail.");
        // making sure the correct element was removed
        assertEquals(myStack.getLength(), 0, "Wrong length after removing tail.");
    }

    @Test
    void testGSRemoveTailMoreThanOneElem() {
        assertEquals(testStack.removeTail(), 10, "Wrong value for stack remove tail.");
        assertEquals(testStack.getLength(), 2, "Wrong length after removing tail.");
    }

    @Test
    void testGSDumpList() {
        ArrayList<Integer> myList = testStack.dumpList();
        ArrayList<Integer> correctVals = new ArrayList<>();
        correctVals.add(12);
        correctVals.add(11);
        correctVals.add(10);
        assertEquals(correctVals, myList, "Wrong Array list values");
    }

    @Test
    void testGSIterator() {
        GenericStack<Integer> stack = new GenericStack<>(5);
        stack.push(4);
        stack.push(3);
        stack.push(2);
        stack.push(1);
        Iterator<Integer> itr = stack.iterator();

        int count = 0;
        while (itr.hasNext()) {
            Integer elem = itr.next();
            count++;

            if (count == 1)
                assertEquals(elem, 1, "Wrong value for iterator.");
            else if (count == 2)
                assertEquals(elem, 2, "Wrong value for iterator.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for iterator.");
            else if (count == 4)
                assertEquals(elem, 4, "Wrong value for iterator.");
            else if (count == 5)
                assertEquals(elem, 5, "Wrong value for iterator.");

        }
    }

    @Test
    void testGSForEach() {
        GenericStack<Integer> stack = new GenericStack<>(5);
        stack.push(4);
        stack.push(3);
        stack.push(2);
        stack.push(1);
        int count = 1;
        for (Integer elem : stack) {
            if (count == 1)
                assertEquals(elem, 1, "Wrong value for forEach.");
            else if (count == 2)
                assertEquals(elem, 2, "Wrong value for forEach.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for forEach.");
            else if (count == 4)
                assertEquals(elem, 4, "Wrong value for forEach.");
            else if (count == 5)
                assertEquals(elem, 5, "Wrong value for forEach.");
            count++;
        }
    }

    @Test
    void testGSReverseIterator() {
        GenericStack<Integer> stack = new GenericStack<>(5);
        stack.push(4);
        stack.push(3);
        stack.push(2);
        stack.push(1);
        Iterator<Integer> itr = stack.descendingIterator();

        int count = 0;
        while (itr.hasNext()) {
            Integer elem = itr.next();
            count++;

            if (count == 1)
                assertEquals(elem, 5, "Wrong value for descending iterator.");
            else if (count == 2)
                assertEquals(elem, 4, "Wrong value for descending iterator.");
            else if (count == 3)
                assertEquals(elem, 3, "Wrong value for descending iterator.");
            else if (count == 4)
                assertEquals(elem, 2, "Wrong value for descending iterator.");
            else if (count == 5)
                assertEquals(elem, 1, "Wrong value for descending iterator.");

        }
    }

    @Test
    void testGSListIterator() {
        GenericStack<Integer> stack = new GenericStack<>(1);
        stack.push(2);
        stack.push(3);
        stack.push(4);
        stack.push(5);

        ListIterator<Integer> lItr = stack.listIterator(2); // should be at position 2: val 3

        // next should return value: 2 since it is next after 3 and update the internal index to 3
        assertEquals(lItr.next(), 2, "Wrong next value for List Iterator");

        // next index should be 4 based on the previous operation "next()" changed the index to 3
        assertEquals(lItr.nextIndex(), 4, "Wrong next index for List Iterator");

        // iterate forward completely
        while (lItr.hasNext()) {
            lItr.next();
        }
        // last value should be at index 5 meaning next index should return -1 meaning out of bounds
        assertEquals(lItr.nextIndex(), -1, "Wrong next index for List Iterator");

        // iterate backwards 3 times to bring us to position 1: val 4
        lItr.previous();
        lItr.previous();
        lItr.previous();

        // one more previous operation should bring us to position 0: val 5
        assertEquals(lItr.previous(), 5, "Wrong previous value");

        // and one more previous operation should bring us out of bounds for the index
        assertEquals(lItr.previousIndex(), -1, "Wrong previous value");

    }

}
