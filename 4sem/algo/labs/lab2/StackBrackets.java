import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;


public class StackBrackets {
    static Scanner in = new Scanner(System.in);
    static Map<String, String> bracketPairs = new HashMap<>();

    public static boolean checkBrackets(String s) {
        Stack<String> brackets = new Stack<>();

        for (int i = 0; i < s.length(); i++) {
            switch (String.valueOf(s.charAt(i))) {
                case "[", "{", "(":
                    brackets.push(String.valueOf(s.charAt(i)));
                    break;
                case "]", "}", ")":
                    if (brackets.isEmpty()) {
                        return false;
                    }
                    String pair = bracketPairs.get(brackets.peek());
                    if (pair.equals(String.valueOf(s.charAt(i)))) {
                        brackets.pop();
                    } else {
                        return false;
                    }
                    break;
            }
        }

        return brackets.isEmpty();
    }

    public static void main(String[] args) {
        bracketPairs.put("{", "}");
        bracketPairs.put("[", "]");
        bracketPairs.put("(", ")");

        System.out.println("Введите строку:");
        String s = in.nextLine();
        System.out.println(checkBrackets(s));
    }
}