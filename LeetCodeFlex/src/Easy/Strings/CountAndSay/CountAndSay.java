package Easy.Strings.CountAndSay;

import java.util.function.IntConsumer;

public class CountAndSay {
    private String[] seq;
    public String countAndSay(int n) {
        IntConsumer countNext = i -> {
            String last = seq[i - 1];
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < last.length(); j++) {
                int k = 0;
                while (k + j + 1 < last.length() &&
                        last.charAt(k + j + 1) == last.charAt(k + j))
                    k++;
                sb.append(k + 1).append(last.charAt(j));
                j += k;
            }
            seq[i] = sb.toString();
        };
        seq = new String[n + 1];
        seq[1] = "1";
        
        for (int i = 2; i <= n; i++) {
            countNext.accept(i);
        }
        return seq[n];
    }
}
