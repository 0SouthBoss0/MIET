import java.util.*;

public class Automation {
    public ArrayList<Transition> transitions;

    public Automation() {
        this.transitions = new ArrayList<>();
    }

    public void addTransition(Transition transition) {
        this.transitions.add(transition);
    }

    public void printTransitions() {
        for (Transition t : transitions) {
            System.out.println(t);
        }
    }

    public boolean isDeterministic() {
        Map<String, Set<Character>> stateSymbols = new HashMap<>();

        for (Transition transition : transitions) {
            String state = transition.from.name;
            char symbol = transition.letter;

            // если для state уже есть переход - автомат недетерминированный
            if (stateSymbols.containsKey(state) && stateSymbols.get(state).contains(symbol)) {
                return false;
            }

            // добавляем symbol в множество символов для данного состояния
            if (!stateSymbols.containsKey(state)) {
                stateSymbols.put(state, new HashSet<>());
            }
            stateSymbols.get(state).add(symbol);
        }

        return true;
    }


    public Automation determinize() {
        if (isDeterministic()) {
            System.out.println("Автомат уже детерминированный");
            return this;
        }

        Automation deterministicAutomaton = new Automation();
        Set<Character> alphabet = getAlphabet();


        // начальное состояние - состояние q0 (или первое состояние)
        Set<Node> startState = new HashSet<>();
        startState.add(findInitialState(this));

        // очередь для обработки состояний нового автомата
        Queue<Set<Node>> queue = new LinkedList<>();
        queue.add(startState);

        // соответствие между множеством состояний и именем нового состояния
        Map<Set<Node>, String> stateNames = new HashMap<>();
        stateNames.put(startState, generateCompactStateName(startState, 0));

        // множество для отслеживания уже добавленных переходов (чтобы избежать дубликатов)
        Set<String> addedTransitions = new HashSet<>();

        int stateCounter = 0;

        while (!queue.isEmpty()) {
            Set<Node> currentStateSet = queue.poll();
            String currentStateName = stateNames.get(currentStateSet);

            // Проверяем, является ли текущее состояние конечным
            boolean isFinal = false;
            for (Node node : currentStateSet) {
                if (node.isFinal) {
                    isFinal = true;
                    break;
                }
            }

            // Создаем узел для нового состояния
            Node currentStateNode = new Node(isFinal ? "f" + currentStateName : currentStateName);
            currentStateNode.isFinal = isFinal;

            // Для каждого символа алфавита строим переход
            for (char symbol : alphabet) {
                Set<Node> nextStateSet = new HashSet<>();

                // Для каждого состояния в текущем множестве находим переходы по символу
                for (Node node : currentStateSet) {
                    for (Transition t : transitions) {
                        if (t.from.name.equals(node.name) && t.letter == symbol) {
                            nextStateSet.add(t.to);
                        }
                    }
                }

                if (!nextStateSet.isEmpty()) {
                    String existingName = findExistingStateName(stateNames, nextStateSet);
                    if (existingName == null) {
                        stateCounter++;
                        stateNames.put(nextStateSet, generateCompactStateName(nextStateSet, stateCounter));
                        queue.add(nextStateSet);
                    }

                        String nextStateName = stateNames.get(nextStateSet);
                        boolean nextIsFinal = false;
                        for (Node node : nextStateSet) {
                            if (node.isFinal) {
                                nextIsFinal = true;
                                break;
                            }
                        }

                    Node nextStateNode = new Node(nextIsFinal ? "f" + nextStateName : nextStateName);
                    nextStateNode.isFinal = nextIsFinal;

                    // Создаем уникальный идентификатор перехода для проверки дубликатов
                    String transitionKey = currentStateName + "," + symbol + "=" + nextStateName;

                    // Добавляем переход только если он еще не был добавлен
                    if (!addedTransitions.contains(transitionKey)) {
                        deterministicAutomaton.addTransition(new Transition(currentStateNode, nextStateNode, symbol));
                        addedTransitions.add(transitionKey);
                    }
                }
            }
        }

        return deterministicAutomaton;
    }
    private String findExistingStateName(Map<Set<Node>, String> stateNames, Set<Node> stateSet) {
        for (Map.Entry<Set<Node>, String> entry : stateNames.entrySet()) {
            if (entry.getKey().equals(stateSet)) {
                return entry.getValue();
            }
        }
        return null;
    }
    public boolean canParseString(String inputString) {
        if (inputString == null || inputString.isEmpty()) {
            return acceptsEmptyString();
        }

        Automation automatonToUse = this;
        if (!isDeterministic()) {
            automatonToUse = determinize();
        }

        Node currentState = findInitialState(automatonToUse);
        if (currentState == null) {
            return false;
        }

        for (int i = 0; i < inputString.length(); i++) {
            char symbol = inputString.charAt(i);
            Node nextState = findNextState(automatonToUse, currentState, symbol);

            if (nextState == null) {
                return false;
            }

            currentState = nextState;
        }
        return currentState.isFinal;
    }

    private boolean acceptsEmptyString() {
        Node initialState = findInitialState(this);
        return initialState != null && initialState.isFinal;
    }

    private Node findInitialState(Automation automaton) {
        Set<Node> allStates = automaton.getAllStates();

        for (Node state : allStates) {
            if (state.name.equals("q0")) {
                return state;
            }
        }

        if (!automaton.transitions.isEmpty()) {
            return automaton.transitions.getFirst().from;
        }

        return null;
    }

    private Node findNextState(Automation automaton, Node currentState, char symbol) {
        for (Transition transition : automaton.transitions) {
            if (transition.from.equals(currentState) && transition.letter == symbol) {
                return transition.to;
            }
        }
        return null;
    }

    private String generateCompactStateName(Set<Node> states, int counter) {
        if (states.isEmpty()) {
            return "empty";
        }
        //  return "S" + counter;

        // Создаем список имен состояний и сортируем для детерминированности
        List<String> stateNames = new ArrayList<>();
        for (Node node : states) {
            stateNames.add(node.name);
        }
        Collections.sort(stateNames); // Сортировка для гарантии одинакового порядка

        // Объединяем имена через нижнее подчеркивание
        return String.join("_", stateNames);
    }

    private Set<Character> getAlphabet() {
        Set<Character> alphabet = new HashSet<>();
        for (Transition t : transitions) {
            alphabet.add(t.letter);
        }
        return alphabet;
    }


    private Set<Node> getAllStates() {
        Set<Node> states = new HashSet<>();
        for (Transition t : transitions) {
            states.add(t.from);
            states.add(t.to);
        }
        return states;
    }
}