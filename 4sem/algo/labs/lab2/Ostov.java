import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

class Edge implements Comparable<Edge> {
    int start;
    int end;
    int weight;

    public Edge(int start, int end, int weight) {
        if (start > end) {
            this.start = end;
            this.end = start;
        } else {
            this.start = start;
            this.end = end;
        }

        this.weight = weight;
    }

    @Override
    public int compareTo(Edge edge) {
        return Integer.compare(weight, edge.weight);
    }
}

class Graph {
    Edge[] edges;
    int nodes;


    public Graph(Edge[] edges, int nodes) {
        this.edges = new Edge[edges.length];
        System.arraycopy(edges, 0, this.edges, 0, edges.length);
        this.nodes = nodes;
    }

    public void printArray(ArrayList<ArrayList<Integer>> takenV) {
        for (int i = 0; i < nodes; i++) {
            System.out.print(takenV.get(i));
        }
        System.out.println();
    }

    // вспомогательный метод поиска индекса множества, где находится вершина
    public int findV(ArrayList<ArrayList<Integer>> arraylist, int v) {
        for (int i = 0; i < arraylist.size(); i++) {
            if (arraylist.get(i).contains(v)) {
                return i;
            }
        }
        return -1;
    }

    // нахождение минимального остова методом Крускала
    public int kruscal() {
        int totalWeight = 0;
        Arrays.sort(edges);
        ArrayList<ArrayList<Integer>> takenV = new ArrayList<>(nodes);

        // инициализация ячеек массива takenV
        for (int i = 0; i < nodes; i++) {
            ArrayList<Integer> group = new ArrayList<>();
            group.add(i + 1);
            takenV.add(i, group);
        }

        printArray(takenV);

        int c = 0;
        boolean exitFlag = true;
        while (exitFlag) {
            // ищем множества, где находятся вершины текущего ребра
            int tempstart = findV(takenV, edges[c].start);
            int tempend = findV(takenV, edges[c].end);

            boolean flag = true;
            // проверяем, что добавление текущего ребра не приведёт к циклу
            // если в множестве где находится первая вершина ребра есть конечная вершина ребра, то образуется цикл
            for (int i = 0; i < takenV.get(tempend).size(); i++) {
                if ((takenV.get(tempstart).contains(takenV.get(tempend).get(i)))) {
                    System.out.print("Не добавляю ребро: (" + edges[c].start + ", " + edges[c].end + ") с весом: " + edges[c].weight + ". \n");
                    flag = false;
                    break;
                }
            }

            // если ребро не приводит к циклу
            if (flag) {
                System.out.print("Добавляю ребро: (" + edges[c].start + ", " + edges[c].end + ") с весом: " + edges[c].weight + ". ");
                totalWeight += edges[c].weight;

                // сливаем два множества в одно
                for (int i = 0; i < takenV.get(tempend).size(); i++) {
                    takenV.get(tempstart).add(takenV.get(tempend).get(i));
                    Collections.sort(takenV.get(tempstart));

                }
                // очищаем лишнее множество
                takenV.get(tempend).clear();
                printArray(takenV);
            }
            // проверяем условие выхода алгоритма - если все вершины в одном множестве
            for (int i = 0; i < takenV.size(); i++) {
                if (takenV.get(i).size() == nodes) {
                    exitFlag = false;
                    break;
                }
            }
            c += 1;

        }

        return totalWeight;
    }

    // вспомогательный метод, возвращающий все смежные ребра графу takenV
    public ArrayList<Edge> getNewEdges(ArrayList<Integer> takenV, ArrayList<Integer> notTakenV) {
        ArrayList<Edge> neighbours = new ArrayList<>();
        for (int i = 0; i < edges.length; i++) {
            if ((takenV.contains(edges[i].start) && notTakenV.contains(edges[i].end)) || (takenV.contains(edges[i].end) && notTakenV.contains(edges[i].start))) {
                neighbours.add(edges[i]);
            }
        }
        return neighbours;
    }

    // нахождение минимального остова методом Прима
    public int prima(int v) {
        int totalweight = 0;
        Arrays.sort(edges);

        // массивы, содержащие обработанные и необработанные вершины
        ArrayList<Integer> takenV = new ArrayList<>();
        ArrayList<Integer> notTakenV = new ArrayList<>();

        // инициализация массива с необработанными вершинами
        for (int i = 0; i < nodes; i++) {
            notTakenV.add(i + 1);
        }

        // начинаем просмотр с v-той вершины
        takenV.add(v);
        notTakenV.remove((Integer) v);

        boolean exitFlag = true;
        while (exitFlag) {
            // получаем смежные ребра и ищем ребро с минимальным весом
            ArrayList<Edge> neighbours = getNewEdges(takenV, notTakenV);
            Edge minEdge = neighbours.get(0);
            for (int j = 0; j < neighbours.size(); j++) {
                if (neighbours.get(j).weight < minEdge.weight) {
                    minEdge.weight = neighbours.get(j).weight;
                }
            }
            totalweight += minEdge.weight;

            // перемещаем вершину из необработанного массива в обработанный
            System.out.print("Добавляю ребро: (" + minEdge.start + ", " + minEdge.end + ") с весом: " + minEdge.weight + ". ");
            if (takenV.contains(minEdge.start)) {
                takenV.add(minEdge.end);
                notTakenV.remove((Integer) minEdge.end);
            } else {
                takenV.add(minEdge.start);
                notTakenV.remove((Integer) minEdge.start);
            }

            Collections.sort(takenV);
            System.out.println("Выбранные: " + takenV + " Невыбранные: " + notTakenV);

            // проверяем условие выхода алгоритма - если все вершины в одном множестве
            if (takenV.size() == nodes) {
                exitFlag = false;
            }

        }
        return totalweight;
    }
}

public class Ostov {
    public static void main(String[] args) {
        Edge edge1 = new Edge(1, 2, 2);
        Edge edge2 = new Edge(2, 3, 1);
        Edge edge3 = new Edge(1, 4, 4);
        Edge edge4 = new Edge(1, 7, 6);
        Edge edge5 = new Edge(2, 4, 1);
        Edge edge6 = new Edge(2, 8, 8);
        Edge edge7 = new Edge(2, 5, 2);
        Edge edge8 = new Edge(3, 5, 7);
        Edge edge9 = new Edge(4, 7, 1);
        Edge edge10 = new Edge(4, 6, 5);
        Edge edge11 = new Edge(6, 7, 1);
        Edge edge12 = new Edge(7, 8, 2);
        Edge edge13 = new Edge(5, 7, 2);
        Edge edge14 = new Edge(5, 8, 2);
        Graph graph = new Graph(new Edge[]{edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11, edge12, edge13, edge14}, 8);

        System.out.println("Вес минимального остова методом Крускала = " + graph.kruscal() + "\n");
        System.out.println("Вес минимального остова методом Прима = " + graph.prima(5));
    }
}