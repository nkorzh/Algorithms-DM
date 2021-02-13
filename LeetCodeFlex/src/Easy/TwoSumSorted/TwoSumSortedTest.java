package Easy.TwoSumSorted;

import org.junit.jupiter.api.Test;

import static Easy.TwoSumSorted.TwoSum.twoSum;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;

public class TwoSumSortedTest {
    @Test
    void sample1() {
        int[] nums = new int[] {2,7,11,15};
        int target = 9;
        assertArrayEquals(new int[] {1, 2}, twoSum(nums, target));
    }

    @Test
    void sample2() {
        int[] nums = new int[] {2, 3, 4};
        int target = 6;
        assertArrayEquals(new int[] {1, 3}, twoSum(nums, target));
    }

    @Test
    void sample3() {
        int[] nums = new int[] {-1, 0};
        int target = -1;
        assertArrayEquals(new int[] {1, 2}, twoSum(nums, target));
    }

    @Test
    void sample4() {
        int[] nums = new int[] {3,24,50,79,88,150,345};
        int target = 200;
        assertArrayEquals(new int[] {3, 6}, twoSum(nums, target));
    }


    @Test
    void sample5() {
        int[] nums = new int[] {0, 0, 3, 4};
        int target = 0;
        assertArrayEquals(new int[] {1, 2}, twoSum(nums, target));
    }
}
