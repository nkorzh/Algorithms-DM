package Easy.Substring;

import java.util.function.Function;
import java.util.function.LongUnaryOperator;

public class Substring {

    private int prime;
    private int maxLen;

    public Substring(int maxStringSize) {
        this.maxLen = maxStringSize;
        this.prime = 31; // bigger than amount of letters, enough for lower case
    }
    public Substring() {
        this(100000);
    }
    private String swapStrings(String a, String b) { return a; }

    private int substrKnutMorissPratt(String s, String t) {
        Function<StringBuilder, int[]> getPrefArray = str -> {
            int[] pref = new int[str.length()];
            for (int i = 1; i < str.length(); ++i) {
                int j = pref[i - 1];
                while (j > 0 && str.charAt(i) != str.charAt(j))
                    j = pref[j - 1];
                if (str.charAt(i) == str.charAt(j))
                    j++;
                pref[i] = j;
            }
            return pref;
        };
        StringBuilder stringBuilder = new StringBuilder(t);
        stringBuilder.append('$').append(s);
        int[] pref = getPrefArray.apply(stringBuilder);
        for (int i = 0; i < pref.length; i++) {
            if (pref[i] == t.length())
                return i - t.length() * 2;
        }
        //     _ _ _ _ _ $ - - - - _ _ _ _ i - - - -
        return -1;
    }

    private int substrRabinCarp(String s, String t) {
        if (t.isEmpty()) return 0;
        else if (t.length() > s.length()) return -1;
        long absValue = ~0x8000000000000000L;
        LongUnaryOperator abs = val -> val & absValue;
        Function<Character, Long> charCode = letter -> (long) (letter - 'a' + 1);

        long[] hash = new long[s.length() + 1];
        long[] prime_power = new long[s.length() + 1];
        // count primes
        prime_power[0] = 1;
        for (int i = 1; i < s.length() + 1; ++i)
           prime_power[i] = abs.applyAsLong(prime_power[i - 1] * prime);
        // count hash
        for (int i = 0; i < s.length(); i++) {
            hash[i] = abs.applyAsLong(charCode.apply(s.charAt(i)) * prime_power[i] + (i > 0 ? hash[i - 1] : 0));
        }
        long tokenHash = 0;
        for (int i = 0; i < t.length(); i++) {
            tokenHash += abs.applyAsLong(charCode.apply(t.charAt(i)) * prime_power[i]);
            tokenHash = abs.applyAsLong(tokenHash);
        }

        for (int i = 0; i + t.length() - 1 < s.length(); i++) {
            long originalHash = abs.applyAsLong(hash[i + t.length() - 1] - (i - 1 >= 0 ? hash[i - 1] : 0));
            long largenedTokenHash = abs.applyAsLong(tokenHash * prime_power[i]);
            if (largenedTokenHash == originalHash) {
                // full-check
                for (int j = 0; j < t.length(); j++) {
                    if (t.charAt(j) != s.charAt(i + j))
                        break;
                }
                return i;
            }
        }

        return -1;
    }
    public int strStr(String haystack, String needle) {
        return substrKnutMorissPratt(haystack, needle);
    }
}
