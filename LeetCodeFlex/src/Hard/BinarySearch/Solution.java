package Hard.BinarySearch;

import java.util.function.IntPredicate;

public class Solution {

    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int[] A;
        int[] B;
        if (nums1.length < nums2.length) {
            A = nums2;
            B = nums1;
        } else {
            A = nums1;
            B = nums2;
        }
        if (B.length == 0) {
            if (A.length % 2 == 0) {
                return (A[A.length / 2 - 1] + A[A.length / 2]) / 2.0;
            } else
                return A[A.length / 2];
        }
        IntPredicate inA = i -> 0 <= i && i < A.length;
        IntPredicate inB = i -> 0 <= i && i < B.length;
        int total = A.length + B.length;
        int half = total / 2;
        int l = 0;
        int r = A.length - 1;

        while (true) {
            int i = (l + r) / 2;
            int j = half - i - 2;
            int Amid = inA.test(i) ? A[i] : (i < 0 ? Integer.MIN_VALUE : Integer.MAX_VALUE);
            int Bmid = inB.test(j) ? B[j] : (j < 0 ? Integer.MIN_VALUE : Integer.MAX_VALUE);
            int Anext = inA.test(i + 1) ? A[i + 1] : Integer.MAX_VALUE;
            int Bnext = inB.test(j + 1) ? B[j + 1] : (j + 1 < 0 ? Integer.MIN_VALUE : Integer.MAX_VALUE);

            if (Amid <= Bnext && Bmid <= Anext) {
                if (total % 2 == 0) { // is even
                    return (Math.min(Anext, Bnext) + Math.max(Amid, Bmid)) / 2.0;
                } else {
                    return Math.min(Anext, Bnext);
                }
            } else if (Amid > Bnext) {
                r = r > 0 ? i - 1 : r - 1;
            } else {
                l = l != i ? i : l + 1;
            }
        }
    }
}