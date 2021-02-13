package Easy.LinkedList;

public class ListNode {
   int val;
   ListNode next;
   ListNode() {}
   public ListNode(int val) { this.val = val; }
   public ListNode(int val, ListNode next) { this.val = val; this.next = next; }
//   @Override
//   public String toString() {
//      StringBuilder sb = new StringBuilder("[");
//      ListNode cur = this;
//      while (cur != null) {
//         sb.append(cur.val);
//         if (cur.next != null)
//            sb.append(", ");
//         cur = cur.next;
//      }
//      return sb.append("]").toString();
//   }
 }
