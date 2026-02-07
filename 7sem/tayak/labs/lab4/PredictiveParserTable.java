import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class PredictiveParserTable {
    public static Grammar readGrammar(String filename) throws IOException {
        Grammar grammar = new Grammar();
        BufferedReader reader = new BufferedReader(new FileReader(filename));
        String line;
        Set<String> allSymbols = new HashSet<>();
        while ((line = reader.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            String[] parts = line.split("→");
            if (parts.length < 2) continue;
            String nonTerminal = parts[0].trim();
            allSymbols.add(nonTerminal);
            String[] rightParts = parts[1].split("\\|");
            for (String rightPart : rightParts) {
                String[] symbols = rightPart.trim().split("\\s+");
                List<String> production = new ArrayList<>();
                for (String symbol : symbols) {
                    symbol = symbol.trim();
                    if (!symbol.isEmpty() && !symbol.equals("ε")) {
                        production.add(symbol);
                        allSymbols.add(symbol);
                    }
                }
                grammar.addProduction(nonTerminal, production);
            }
        }

        reader.close();
        for (String symbol : allSymbols) {
            if (grammar.nonTerminals.contains(symbol)) {
                continue;
            }
            if (symbol.matches("[A-Z_]+") || isSpecialTerminal(symbol)) {
                grammar.terminals.add(symbol);
            } else {
                grammar.nonTerminals.add(symbol);
            }
        }
        grammar.terminals.add("$");
        return grammar;
    }

    private static boolean isSpecialTerminal(String symbol) {
        return symbol.equals("(") || symbol.equals(")") || symbol.equals("{") ||
                symbol.equals("}") || symbol.equals(";") || symbol.equals("=") ||
                symbol.equals("<") || symbol.equals(">") || symbol.equals("==") ||
                symbol.equals("!=") || symbol.equals("+");
    }

    public static Map<String, Set<String>> computeFirst(Grammar grammar) {
        Map<String, Set<String>> first = new HashMap<>();

        // инициализация FIRST для терминалов
        for (String terminal : grammar.terminals) {
            Set<String> set = new HashSet<>();
            set.add(terminal);
            first.put(terminal, set);
        }

        // инициализация FIRST для нетерминалов
        for (String nonTerminal : grammar.nonTerminals) {
            first.put(nonTerminal, new HashSet<>());
        }

        boolean changed;
        do {
            changed = false;
            for (String nonTerminal : grammar.nonTerminals) {
                List<List<String>> prods = grammar.productions.get(nonTerminal);
                if (prods == null) continue;

                for (List<String> production : prods) {
                    Set<String> currentFirst = first.get(nonTerminal);
                    int oldSize = currentFirst.size();

                    if (production.isEmpty()) {
                        currentFirst.add("ε");
                    } else {
                        boolean allHaveEpsilon = true;
                        for (String symbol : production) {
                            Set<String> symbolFirst = first.get(symbol);
                            if (symbolFirst == null) {
                                allHaveEpsilon = false;
                                break;
                            }

                            // добавляем все символы из FIRST(symbol), кроме ε
                            for (String s : symbolFirst) {
                                if (!s.equals("ε")) {
                                    currentFirst.add(s);
                                }
                            }

                            // если ε не в FIRST(symbol), прекращаем
                            if (!symbolFirst.contains("ε")) {
                                allHaveEpsilon = false;
                                break;
                            }
                        }

                        // если все символы могут быть ε, добавляем ε
                        if (allHaveEpsilon) {
                            currentFirst.add("ε");
                        }
                    }

                    if (currentFirst.size() > oldSize) {
                        changed = true;
                    }
                }
            }
        } while (changed);

        return first;
    }

    public static Map<String, Set<String>> computeFollow(Grammar grammar, Map<String, Set<String>> first) {
        Map<String, Set<String>> follow = new HashMap<>();
        // инициализация FOLLOW для всех нетерминалов
        for (String nonTerminal : grammar.nonTerminals) {
            follow.put(nonTerminal, new HashSet<>());
        }
        // стартовый символ
        String startSymbol = "program";
        follow.get(startSymbol).add("$");

        boolean changed;
        do {
            changed = false;

            for (String nonTerminal : grammar.nonTerminals) {
                List<List<String>> prods = grammar.productions.get(nonTerminal);
                if (prods == null) continue;

                for (List<String> production : prods) {
                    for (int i = 0; i < production.size(); i++) {
                        String currentSymbol = production.get(i);
                        if (!grammar.nonTerminals.contains(currentSymbol)) continue;

                        Set<String> currentFollow = follow.get(currentSymbol);
                        int oldSize = currentFollow.size();

                        if (i < production.size() - 1) {
                            List<String> beta = production.subList(i + 1, production.size());
                            Set<String> firstBeta = computeFirstOfSequence(beta, first);

                            for (String symbol : firstBeta) {
                                if (!symbol.equals("ε")) {
                                    currentFollow.add(symbol);
                                }
                            }

                            if (firstBeta.contains("ε")) {
                                currentFollow.addAll(follow.get(nonTerminal));
                            }
                        } else {
                            currentFollow.addAll(follow.get(nonTerminal));
                        }

                        if (currentFollow.size() > oldSize) {
                            changed = true;
                        }
                    }
                }
            }
        } while (changed);

        return follow;
    }
    public static Set<String> computeFirstOfSequence(List<String> sequence, Map<String, Set<String>> first) {
        Set<String> result = new HashSet<>();
        if (sequence.isEmpty()) {
            result.add("ε");
            return result;
        }
        boolean allHaveEpsilon = true;
        for (String symbol : sequence) {
            Set<String> symbolFirst = first.get(symbol);
            if (symbolFirst == null) {
                allHaveEpsilon = false;
                break;
            }

            // добавляем все символы из FIRST(symbol), кроме epsilon
            for (String s : symbolFirst) {
                if (!s.equals("ε")) {
                    result.add(s);
                }
            }

            // если epsilon не в FIRST(symbol), прекращаем
            if (!symbolFirst.contains("ε")) {
                allHaveEpsilon = false;
                break;
            }
        }

        // если все символы могут быть epsilon, добавляем epsilon
        if (allHaveEpsilon) {
            result.add("ε");
        }

        return result;
    }
    public static Map<String, Set<String>> computeSyncTokens(Grammar grammar, Map<String, Set<String>> follow) {
        Map<String, Set<String>> syncTokens = new HashMap<>();
        for (String nonTerminal : grammar.nonTerminals) {
            syncTokens.put(nonTerminal, new HashSet<>(follow.get(nonTerminal)));
        }

        return syncTokens;
    }

    public static Map<String, Map<String, List<String>>> buildParsingTable(Grammar grammar) {
        Map<String, Set<String>> first = computeFirst(grammar);
        Map<String, Set<String>> follow = computeFollow(grammar, first);
        Map<String, Set<String>> syncTokens = computeSyncTokens(grammar, follow);

        Map<String, Map<String, List<String>>> parsingTable = new HashMap<>();

        // Инициализация таблицы
        for (String nonTerminal : grammar.nonTerminals) {
            parsingTable.put(nonTerminal, new HashMap<>());
            for (String terminal : grammar.terminals) {
                parsingTable.get(nonTerminal).put(terminal, null); // null означает error
            }
        }

        // Заполнение таблицы правилами
        for (String nonTerminal : grammar.nonTerminals) {
            List<List<String>> prods = grammar.productions.get(nonTerminal);
            if (prods == null) continue;

            for (List<String> production : prods) {
                Set<String> firstAlpha = computeFirstOfSequence(production, first);

                // Для каждого терминала a из FIRST(α) добавляем A → α в M[A, a]
                for (String terminal : firstAlpha) {
                    if (!terminal.equals("ε")) {
                        if (parsingTable.get(nonTerminal).get(terminal) != null) {
                            System.out.println("Конфликт в ячейке [" + nonTerminal + ", " + terminal + "]");
                        }
                        parsingTable.get(nonTerminal).put(terminal, production);
                    }
                }

                // Если ε ∈ FIRST(α), то для каждого терминала b из FOLLOW(A) добавляем A → α в M[A, b]
                if (firstAlpha.contains("ε")) {
                    for (String terminal : follow.get(nonTerminal)) {
                        if (parsingTable.get(nonTerminal).get(terminal) != null) {
                            System.out.println("Конфликт в ячейке [" + nonTerminal + ", " + terminal + "]");
                        }
                        parsingTable.get(nonTerminal).put(terminal, production);
                    }
                }
            }
        }

        // Добавляем синхронизирующие токены ТОЛЬКО для error-ячеек
        for (String nonTerminal : grammar.nonTerminals) {
            for (String terminal : syncTokens.get(nonTerminal)) {
                if (parsingTable.get(nonTerminal).get(terminal) == null) {
                    parsingTable.get(nonTerminal).put(terminal, Collections.singletonList("synch"));
                }
            }
        }

        return parsingTable;
    }

    public static void printParsingTable(Grammar grammar, Map<String, Map<String, List<String>>> parsingTable) {
        System.out.println("\nТаблица синтаксического анализа:");
        System.out.print("NonTerminal");
        List<String> sortedTerminals = new ArrayList<>(grammar.terminals);
        Collections.sort(sortedTerminals);

        for (String terminal : sortedTerminals) {
            System.out.printf("%15s", terminal);
        }
        System.out.println();
        List<String> sortedNonTerminals = new ArrayList<>(grammar.nonTerminals);
        Collections.sort(sortedNonTerminals);

        for (String nonTerminal : sortedNonTerminals) {
            System.out.printf("%-11s", nonTerminal);
            Map<String, List<String>> row = parsingTable.get(nonTerminal);

            for (String terminal : sortedTerminals) {
                List<String> production = row.get(terminal);
                if (production == null) {
                    System.out.printf("%15s", "error");
                } else if (production.size() == 1 && production.get(0).equals("synch")) {
                    System.out.printf("%15s", "synch");
                } else {
                    String prodStr;
                    if (production.isEmpty()) {
                        prodStr = nonTerminal + " → ε";
                    } else {
                        prodStr = nonTerminal + " → " + String.join(" ", production);
                    }
                    // Обрезаем строку если слишком длинная
                    if (prodStr.length() > 14) {
                        prodStr = prodStr.substring(0, 11) + "...";
                    }
                    System.out.printf("%15s", prodStr);
                }
            }
            System.out.println();
        }
    }

    public static void printFirstAndFollow(Grammar grammar,
                                           Map<String, Set<String>> first,
                                           Map<String, Set<String>> follow) {
        System.out.println("\nFIRST множества:");
        for (String nonTerminal : grammar.nonTerminals) {
            System.out.println("FIRST(" + nonTerminal + ") = " + first.get(nonTerminal));
        }

        System.out.println("\nFOLLOW множества:");
        for (String nonTerminal : grammar.nonTerminals) {
            System.out.println("FOLLOW(" + nonTerminal + ") = " + follow.get(nonTerminal));
        }
    }
}