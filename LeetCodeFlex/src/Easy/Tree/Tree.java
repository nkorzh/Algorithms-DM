package Easy.Tree;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.function.Predicate;

public class Tree {

    public boolean isSymLoop(TreeNode root) {
        List<TreeNode> level = new LinkedList<>();
        level.add(root);
        Predicate<List<TreeNode>> listSymmetric = list -> {
            int size = list.size();
            ListIterator<TreeNode> left = list.listIterator();
            ListIterator<TreeNode> right = list.listIterator(size);
            TreeNode leftNode, rightNode;
            while (left.hasNext() && right.hasPrevious() &&
                    left.nextIndex() <= right.previousIndex()) {
                leftNode = left.next();
                rightNode = right.previous();
                if (leftNode == null ^ rightNode == null ||
                        leftNode != null && leftNode.val != rightNode.val)
                    return false;
            }
            return true;
        };
        while (!level.isEmpty()) {
            if (!listSymmetric.test(level))
                return false;
            ListIterator<TreeNode> nodeIt = level.listIterator();
            TreeNode node;
            while (nodeIt.hasNext()) {
                node = nodeIt.next();
                nodeIt.remove();
                if (node != null) {
                    nodeIt.add(node.left);
                    nodeIt.add(node.right);
                }
            }
        }
        return true;
    }
    public boolean isSymRec(TreeNode leftNode, TreeNode rightNode) {
        if ((leftNode == null) && (rightNode == null))
            return true;
        return leftNode != null && rightNode != null && leftNode.val == rightNode.val &&
                isSymRec(leftNode.left, rightNode.right) && isSymRec(leftNode.right, rightNode.left);
    }
    public boolean isSymmetric(TreeNode root) {
        return isSymRec(root, root);
    }


    int[] values;
    private TreeNode createTree(int left, int right) {
        if (right - left == 1)
            return new TreeNode(values[left]);
        else if (right <= left)
            return null;
        int mid = (right + left) / 2;
        return new TreeNode(values[mid], createTree(left, mid), createTree(mid + 1, right));
    }
    public TreeNode sortedArrayToBST(int[] nums) {
        if (nums == null || nums.length == 0)
            return null;
        values = nums;
        return createTree(0, nums.length);
    }
}
