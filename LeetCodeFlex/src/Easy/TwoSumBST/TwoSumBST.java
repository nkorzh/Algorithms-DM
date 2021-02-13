package Easy.TwoSumBST;

public class TwoSumBST {
    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        TreeNode() {}
        TreeNode(int val) { this.val = val; }
        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    static TreeNode root;
    public static boolean findTarget(TreeNode root, int k) {
        if (root == null) {
            return false;
        }
        return findKeyTarget(root, root, k);
    }

    private static boolean findKeyTarget(TreeNode startNode, TreeNode root, int k) {
        if (startNode == null) {
            return false;
        }
        return findKey(root, startNode, k - startNode.val) || // seek from here
                findKeyTarget(startNode.left, root, k) || // seek with key of left
                findKeyTarget(startNode.right, root, k); // and right
    }


    private static boolean findKey(TreeNode node, TreeNode currentRoot, int key) {
        if (node == null) {
            return false;
        }
        if (node.val == key && node != currentRoot) {
            return true;
        }
        if (key < node.val) {
            return findKey(node.left, currentRoot, key);
        }
        return findKey(node.right, currentRoot, key);
    }
}
