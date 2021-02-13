package Easy.Strings.AhoCorasick;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class Node {
    private Node sufLink;
    private Node parent;
    private final Map<Character, Node> edges;
    private final Character symbol;
    private boolean isTerminal;

    public Node(Character symbol, Node parent) {
        this.symbol = symbol;
        this.parent = parent;
        this.edges = new HashMap<>();
        this.isTerminal = false;
    }

    public java.util.Collection<Node> getEdges() {
        return edges.values();
    }
    public Node jump(char symbol) {
        return edges.get(symbol);
    }
    public Node jumpOrCreate(char symbol) {
        if (!edges.containsKey(symbol))
            edges.put(symbol, new Node(symbol, this));
        return edges.get(symbol);
    }
    public Node setSufLink(Node link) {
        sufLink = link;
        return this;
    }
    public void makeTerminal() {
        isTerminal = true;
    }
    public boolean isTerminal() {
        return isTerminal;
    }
    public Node getSufLink() {
        return sufLink;
    }
    public Node getParent() {
        return parent;
    }
    public char getSymbol() {
        return symbol;
    }
}

