package Easy.LinkedList;

import java.util.Stack;

public class ListReverse {
    private ListNode reverse(ListNode node) {
        ListNode head = node;
        if (node == null)
            return null;
        if (head.next == null)
            return head;

        ListNode reversedHead = reverse(head.next);
        if (head.next != null) {
            head.next.next = head;
            head.next = null;
        }

        return reversedHead;
    }

    private ListNode reverseLoop(ListNode head) {
        ListNode node = head;
        ListNode prev = null;
        ListNode next;
        while (node != null) {
            next = node.next;
            node.next = prev;
            prev = node;
            node = next;
        }
        return prev;
    }

    public ListNode reverseList(ListNode head) {
        return reverseLoop(head);
    }

    private boolean isPalCycle(ListNode head) {
        int amount = 0;
        ListNode node = head;
        while (node != null) {
            node = node.next;
            amount++;
        }
        Stack<Integer> stack = new Stack<>();
        node = head;
        for (int i = 0; i < amount / 2; i++) {
            stack.push(node.val);
            node = node.next;
        }
        if (amount % 2 != 0)
            node = node.next;
        while (node != null) {
            if (node.val != stack.pop())
                return false;
            node = node.next;
        }
        return true;
    }

    // list invalidates
    public boolean isPalindrome(ListNode head) {
        if (head == null)
            return true;
        int amount = 0;
        ListNode node = head;
        while (node != null) {
            node = node.next;
            amount++;
        }
        node = head;
        for (int i = 0; i < amount / 2; i++) {
            node = node.next;
        }
        ListNode leftMid = node;
        if (amount % 2 != 0)
            node = node.next;
        ListNode right = reverse(node);
        leftMid.next = null;
        ListNode nodeLeft = head;
        ListNode nodeRight = right;
        while (nodeLeft != null && nodeRight != null) {
            if (nodeLeft.val != nodeRight.val)
                return false;
            nodeLeft = nodeLeft.next;
            nodeRight = nodeRight.next;
        }
        return true;
    }
}
