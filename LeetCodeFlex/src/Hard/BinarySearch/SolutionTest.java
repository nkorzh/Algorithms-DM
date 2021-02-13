package Hard.BinarySearch;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class SolutionTest {
    private static Solution sol;

    @BeforeAll
    static void initClass() {
        sol = new Solution();
    }
    
    @Test
    void sample1() {
        int[] a = new int[] {3,4};
        int[] b = new int[] {};
        double expected = 3.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }

    @Test
    void sample2() {
        int[] a = new int[] {1,2};
        int[] b = new int[] {3,4};
        double expected = 2.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }

    @Test
    void sample3() {
        int[] a = new int[] {};
        int[] b = new int[] {2};
        double expected = 2;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }

    @Test
    void sample4() {
        int[] a = new int[] {1,3,4,6};
        int[] b = new int[] {};
        double expected = 3.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }
    @Test
    void sample5() {
        int[] a = new int[] {2,3,4,5,6,7,8};
        int[] b = new int[] {1};
        double expected = 4.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }
    @Test
    void sample6() {
        int[] a = new int[] {1,2,3,4,5};
        int[] b = new int[] {};
        double expected = 3;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }
    @Test
    void sample7() {
        int[] a = new int[] {1,2,3,4,7,8};
        int[] b = new int[] {5,6};
        double expected = 4.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }
    @Test
    void sample8() {
        int[] a = new int[] {1,2,3,4,5,8,9,10};
        int[] b = new int[] {6,7};
        double expected = 5.5;
        assertEquals(expected, sol.findMedianSortedArrays(a, b));
        assertEquals(expected, sol.findMedianSortedArrays(b, a));
    }
}
