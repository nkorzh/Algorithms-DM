package Easy.TwoSumSorted;

import java.util.HashMap;
import java.util.Map;

public class TwoSum {

    private int[] twoSumSimpler(int[] numbers, int target) {
        int i = 0;
        int j = numbers.length - 1;

        while (i < j) {
            if (numbers[i] + numbers[j] > target)
                j--;
            else if (numbers[i] + numbers[j] < target)
                i++;
            else
                break;
        }

        return new int[] {i + 1, j + 1};
    }
    
    private static Integer searchNumber(int x, int[] numbers, int right, Map<Integer, Integer> map, int target) {
        Integer index = map.get(x);
        if (index != null && 0 <= index && index < right) {
            return index;
        }

        int left = 0;
        int mid = (left + right) / 2;

        while (right - left > 1) {
            map.putIfAbsent(numbers[mid], mid);
            if (x < numbers[mid]) {
                right = mid;
            } else if (numbers[mid] < x) {
                left = mid + 1;
            } else
                return mid;
            mid = (left + right) / 2;
        }

        if (numbers[left] == x)
            return left;

        return null;
    }

    public static int[] twoSum(int[] numbers, int target) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int i = numbers.length - 1; i >= 0; i--) {
            Integer cIndex = searchNumber(target - numbers[i], numbers, i, map, target);
            if (cIndex != null) {
                return new int[] {cIndex + 1, i + 1};
            }
        }
        return new int[] {-1, -1};
    }
}
