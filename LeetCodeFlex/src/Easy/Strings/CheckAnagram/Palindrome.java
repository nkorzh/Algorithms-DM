package Easy.Strings.CheckAnagram;

public class Palindrome {
    public boolean isPalindrome(String s) { // skip whitespaces with 'if'
        s = s.toLowerCase().replaceAll("[\\W_]", "");
        for (int i = 0; i < s.length() / 2; i++) {
            if (s.charAt(i) != s.charAt(s.length() - i - 1))
                return false;
        }
        return true;
    }
}
