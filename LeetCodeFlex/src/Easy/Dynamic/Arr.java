package Easy.Dynamic;

public class Arr {
    public int maxSubArray(int[] nums) {
        int max = Integer.MIN_VALUE;
        int curSum = 0;
        for (int num : nums) {
            curSum += num;
            max = Math.max(max, curSum);
            if (curSum < 0)
                curSum = 0;
        }
        return max;
    }
}
