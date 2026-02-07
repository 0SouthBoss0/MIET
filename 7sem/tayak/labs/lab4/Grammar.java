import java.util.*;

public class Grammar {
    Map<String, List<List<String>>> productions = new HashMap<>();
    Set<String> nonTerminals = new HashSet<>();
    Set<String> terminals = new HashSet<>();

    public void addProduction(String nonTerminal, List<String> production) {
        productions.computeIfAbsent(nonTerminal, k -> new ArrayList<>()).add(production);
        nonTerminals.add(nonTerminal);
    }
}