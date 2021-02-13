package Easy.TwoSum;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TwoSumTest {

    @Test
    void sampleOne() {
        int[] nums = new int[] {2,7,11,15};
        int target = 9;
        assertArrayEquals(new int[] {0, 1}, TwoSum.twoSum(nums, target));
    }

    @Test
    void sampleTwo() {
        int[] nums = new int[] {3, 2, 4};
        int target = 6;
        assertArrayEquals(new int[] {1, 2}, TwoSum.twoSum(nums, target));
    }

    @Test
    void sampleThree() {
        int[] nums = new int[] {3,3};
        int target = 6;
        assertArrayEquals(new int[] {0, 1}, TwoSum.twoSum(nums, target));
    }

    @org.junit.jupiter.api.BeforeEach
    void setUp() {
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
    }
}