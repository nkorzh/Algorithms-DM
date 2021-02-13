package Easy.Strings.AhoCorasick;

import java.util.*;
import java.util.function.UnaryOperator;

public class LongestCommonPrefix {


    private Node root;

    private void buildSufLinks() {
        Queue<Node> queue = new ArrayDeque<>();
        root.getEdges().forEach(node -> { if (node != null) queue.add(node); });

        while (!queue.isEmpty()) {
            Node head = queue.poll();
            head.getEdges().forEach(node -> { if (node != null) queue.add(node); });
            // add suff links to all letters
            Node parent = head.getParent();
            Node v = parent.getSufLink();
            char symbol = head.getSymbol();
            while (v != null) {
                if (v.jump(symbol) != null) {
                    head.setSufLink(v.jump(symbol));
                    break;
                }
                v = v.getSufLink();
            }
            if (v == null)
                head.setSufLink(root);
        }
    }

    public String longestCommonPrefix(String[] strs) {
        UnaryOperator<Node> getSingleNext = node -> {
            if (node.getEdges().size() != 1)
                return null;
            return node.getEdges().stream().findFirst().get();
        };
        root = new Node(null, null);
        root.setSufLink(null);

        for (String word : strs) {
            Node node = root;
            if (word.isEmpty())
                return "";
            for (int i = 0; i < word.length(); i++) {
                node = node.jumpOrCreate(word.charAt(i));
            }
            node.makeTerminal();
        }

        StringBuilder sb = new StringBuilder();
        Node node = getSingleNext.apply(root);
        while (node != null && !node.getParent().isTerminal()) {
            sb.append(node.getSymbol());
            node = getSingleNext.apply(node);
        }
        return sb.toString();
    }
}
