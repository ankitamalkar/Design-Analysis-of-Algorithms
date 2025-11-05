import java.util.*;
import java.io.*;

class Graph {
    int V;
    ArrayList<ArrayList<Integer>> adj;

    Graph(int n) {
        V = n;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++)
            adj.add(new ArrayList<>());
    }

    void addEdge(int u, int v) {
        if (u >= 0 && v >= 0 && u < V && v < V && u != v) {
            adj.get(u).add(v);
            adj.get(v).add(u);
        }
    }

    void prepare() {
        for (ArrayList<Integer> nbrs : adj) {
            Collections.sort(nbrs);
            nbrs.removeIf(new HashSet<>(nbrs)::add);
        }
    }
}

public class Main {
    static int[] dsaturColoring(Graph G) {
        int n = G.V;
        int[] color = new int[n];
        int[] degree = new int[n];
        int[] satDeg = new int[n];
        @SuppressWarnings("unchecked")
        HashSet<Integer>[] usedColors = new HashSet[n];
        for (int i = 0; i < n; i++) {
            usedColors[i] = new HashSet<>();
            degree[i] = G.adj.get(i).size();
        }

        for (int step = 0; step < n; step++) {
            int sel = -1;
            for (int i = 0; i < n; i++) {
                if (color[i] == 0) {
                    if (sel == -1 || satDeg[i] > satDeg[sel] ||
                        (satDeg[i] == satDeg[sel] && degree[i] > degree[sel]))
                        sel = i;
                }
            }
            if (sel == -1) break;

            boolean[] used = new boolean[n + 1];
            for (int v : G.adj.get(sel))
                if (color[v] != 0)
                    used[color[v]] = true;

            int c = 1;
            while (c <= n && used[c]) c++;
            color[sel] = c;

            for (int v : G.adj.get(sel))
                if (color[v] == 0) {
                    usedColors[v].add(c);
                    satDeg[v] = usedColors[v].size();
                }
        }
        return color;
    }

    static void showColoring(int[] color) {
        System.out.println("\nCourse → Slot Allocation:");
        System.out.println("---------------------------");
        int total = Arrays.stream(color).max().orElse(0);
        for (int i = 0; i < color.length; i++)
            System.out.println("Course " + i + " → Slot " + color[i]);
        System.out.println("---------------------------");
        System.out.println("Minimum Slots Needed: " + total);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("=== University Timetable Scheduler (Fast DSATUR) ===\n");
        System.out.print("Enter number of courses and conflicts: ");
        int V = sc.nextInt(), E = sc.nextInt();
        if (V <= 0 || V > 200) {
            System.err.println("Invalid course count (1–200 allowed).");
            return;
        }
        Graph G = new Graph(V);
        System.out.println("Enter " + E + " conflict pairs (u v):");
        for (int i = 0; i < E; i++) {
            int u = sc.nextInt(), v = sc.nextInt();
            G.addEdge(u, v);
        }
        G.prepare();
        long start = System.nanoTime();
        int[] color = dsaturColoring(G);
        long end = System.nanoTime();
        showColoring(color);
        double timeMs = (end - start) / 1e6;
        System.out.printf("\nExecution Time: %.3f ms\n", timeMs);
        System.out.println("Program completed successfully.");
        sc.close();
    }
}
