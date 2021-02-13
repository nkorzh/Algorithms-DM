package Easy.TwoSum;

import java.util.HashMap;
import java.util.Map;

public class TwoSum {

    public static int[] twoSum(int[] nums, int target) {

        Map<Integer, Integer> compl = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            Integer indexCompl = compl.get(nums[i]);
            if (indexCompl != null) {
                return new int[] {indexCompl, i};
            }
            compl.put(complement, i);
        }
        return new int[] {-1, -1};
    }

}
