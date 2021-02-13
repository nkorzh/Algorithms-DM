package Easy.Strings.CheckAnagram;

import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;

public class EasyAnagram {
    public boolean isAnagram(String s, String t) {
        Map<Character, Integer> appearance = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            appearance.merge(s.charAt(i), 1, Integer::sum);
        }
        for (int i = 0; i < t.length(); i++) {
            appearance.merge(t.charAt(i), -1, Integer::sum);
        }
        for (Map.Entry<Character, Integer> p : appearance.entrySet())
            if (p.getValue() != 0)
                return false;
            s = s.toLowerCase().replaceAll("^[\\p{Alpha}]", "");
        return true;
    }

    public boolean isAnagram1(String s, String t) { // doesnt do it on test "aa", "bb", all codes are equal zero
        if (s.length() != t.length()) return false;
        Function<String, Integer> countCode = str -> {
            int code = 0;
            for (int i = 0; i < str.length(); i++)
                code ^= str.charAt(i);
            return code;
        };
        return countCode.apply(s).equals(countCode.apply(t));
    }
}

