import java.util.*;
public class ArrayUtil {
    private int[] intArray;
    public ArrayUtil() {

    }
    public ArrayUtil(int[] arr) {
        intArray = arr;
    }
    public int[] getIntArray() {
        return intArray;
    }

    public void setIntArray(int[] arr) {
        intArray = arr;
    }

    /*
    int minValue():
        if len(intArray) == 0
            return 0

        min = MIN(Int)

        for elem in intArray
            if elem < min
                min = elem

        return min
     */

    public int minValue() {
        if (intArray.length == 0) {
            return 0;
        }
        int min = Integer.MAX_VALUE;
        for (int elem: intArray) {
            if (elem < min) {
                min = elem;
            }
        }

        return min;
    }


    /*
    int maxValue():
        if len(intArray) == 0
            return 0

        max = MAX(Int)

        for elem in intArray
            if elem > min
                min = elem

        return min
     */
    public int maxValue() {
        if (intArray.length == 0) {
            return 0;
        }
        int max = Integer.MIN_VALUE;
        for (int elem: intArray) {
            if (elem > max) {
                max = elem;
            }
        }
        return max;
    }



    /*
    int countUniqueIntgers():
        if len(intArray) == 0
            return 0

        count = 1

        for (i = 1; i < len(intArray); i++)
            j = 0
            for (j = 0; j < u; j++)
                if intArray[i] == intArray[j]
                    break
            if ( i == j )
                count++

        return count
     */

    public int countUniqueIntegers() {
        if (intArray.length == 0) {
            return 0;
        }
        int count = 1;
        for (int i = 1; i < intArray.length; i++){
            int j = 0;
            for (j = 0; j < i; j++){
                if (intArray[i] == intArray[j]){
                    break;
                }
            }
            if (i == j){
                count++;
            }
        }
        return count;
    }

}
