/**
 * ITSC 1212 ArrayUtil_Test class for Project 4
 */
import java.util.*;
public class ArrayUtil_Test {
    public static void main(String[] args) {
//        Set<Integer> set = new HashSet<>();
//        set.addAll(Arrays.asList(1,2,9,1,2,3,1,4,1,5,7));
//
//        System.out.println(set);
        divide(4,0);
    }

    // DO NOT MODIFY validate METHOD
    public static int divide(int a, int b) {
        int c = -1;
        try {
            c = a/b;
        }
        catch (Exception e) {
            System.err.print("Exception ");
        }
        finally {
            System.err.println("Finally ");
        }
        return c;
    }
}