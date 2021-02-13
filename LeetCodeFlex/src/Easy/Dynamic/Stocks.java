package Easy.Dynamic;

import java.util.Arrays;

public class Stocks {
    public int maxProfit(int[] prices) {
        int profit = 0;
        int enterPrice = Integer.MAX_VALUE;
        for (int price : prices) {
            if (price < enterPrice) {
                enterPrice = price;
            } else {
                profit = Math.max(profit, price - enterPrice);
            }
        }
        return profit;
    }
}
