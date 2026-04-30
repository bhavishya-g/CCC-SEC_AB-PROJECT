#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 10
#define INF INT_MAX

// City names
char cities[MAX_CITIES][30];
int graph[MAX_CITIES][MAX_CITIES];  // Adjacency matrix
int numCities = 0;

// ─────────────────────────────────────────
//  Utility: find city index by name
// ─────────────────────────────────────────
int findCity(const char *name) {
    for (int i = 0; i < numCities; i++) {
        if (strcmp(cities[i], name) == 0)
            return i;
    }
    return -1;
}

// ─────────────────────────────────────────
//  Add a city
// ─────────────────────────────────────────
void addCity(const char *name) {
    if (numCities >= MAX_CITIES) {
        printf("  [!] Maximum city limit reached!\n");
        return;
    }
    if (findCity(name) != -1) {
        printf("  [!] City '%s' already exists.\n", name);
        return;
    }
    strcpy(cities[numCities], name);
    for (int i = 0; i <= numCities; i++) {
        graph[numCities][i] = 0;
        graph[i][numCities] = 0;
    }
    numCities++;
    printf("  [+] City '%s' added successfully.\n", name);
}

// ─────────────────────────────────────────
//  Add a road (edge) between two cities
// ─────────────────────────────────────────
void addRoad(const char *city1, const char *city2, int distance) {
    int u = findCity(city1);
    int v = findCity(city2);
    if (u == -1 || v == -1) {
        printf("  [!] One or both cities not found!\n");
        return;
    }
    if (distance <= 0) {
        printf("  [!] Distance must be positive.\n");
        return;
    }
    graph[u][v] = distance;
    graph[v][u] = distance;  // Undirected road
    printf("  [+] Road added: %s <--> %s (Distance: %d km)\n", city1, city2, distance);
}

// ─────────────────────────────────────────
//  Display the graph (adjacency matrix)
// ─────────────────────────────────────────
void displayGraph() {
    if (numCities == 0) {
        printf("  [!] No cities added yet.\n");
        return;
    }
    printf("\n  +----- City Connection Map -----+\n");
    printf("  %-15s", " ");
    for (int i = 0; i < numCities; i++)
        printf("  %-10s", cities[i]);
    printf("\n  ");
    for (int i = 0; i < numCities * 12 + 15; i++) printf("-");
    printf("\n");

    for (int i = 0; i < numCities; i++) {
        printf("  %-15s", cities[i]);
        for (int j = 0; j < numCities; j++) {
            if (graph[i][j] == 0 && i != j)
                printf("  %-10s", "-");
            else if (i == j)
                printf("  %-10s", "0");
            else
                printf("  %-10d", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ─────────────────────────────────────────
//  DIJKSTRA'S ALGORITHM (Dynamic Programming)
// ─────────────────────────────────────────
void dijkstra(int src, int dest) {
    int dist[MAX_CITIES];
    int visited[MAX_CITIES];
    int prev[MAX_CITIES];

    // Initialize
    for (int i = 0; i < numCities; i++) {
        dist[i]    = INF;
        visited[i] = 0;
        prev[i]    = -1;
    }
    dist[src] = 0;

    // Main loop
    for (int count = 0; count < numCities - 1; count++) {
        // Find unvisited city with minimum distance
        int u = -1;
        for (int i = 0; i < numCities; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        if (u == -1 || dist[u] == INF) break;
        visited[u] = 1;

        // Relax neighbors
        for (int v = 0; v < numCities; v++) {
            if (!visited[v] && graph[u][v] != 0) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    // ── Print Result ──
    printf("\n  ╔══════════════════════════════════════╗\n");
    printf("  ║        SHORTEST PATH RESULT          ║\n");
    printf("  ╚══════════════════════════════════════╝\n");

    if (dist[dest] == INF) {
        printf("  [!] No path found from '%s' to '%s'.\n",
               cities[src], cities[dest]);
        return;
    }

    // Reconstruct path
    int path[MAX_CITIES], pathLen = 0;
    for (int v = dest; v != -1; v = prev[v])
        path[pathLen++] = v;

    printf("\n  Source      : %s\n", cities[src]);
    printf("  Destination : %s\n", cities[dest]);
    printf("  Total Distance : %d km\n", dist[dest]);
    printf("\n  Path: ");
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);
        if (i != 0) printf(" --> ");
    }
    printf("\n\n");

    // Step-by-step breakdown
    printf("  Step-by-step breakdown:\n");
    int cumDist = 0;
    for (int i = pathLen - 1; i > 0; i--) {
        int from = path[i], to = path[i - 1];
        int d = graph[from][to];
        cumDist += d;
        printf("    %s --> %s  : %d km  (Total so far: %d km)\n",
               cities[from], cities[to], d, cumDist);
    }
    printf("\n");
}

// ─────────────────────────────────────────
//  Display all cities
// ─────────────────────────────────────────
void listCities() {
    if (numCities == 0) {
        printf("  [!] No cities added yet.\n");
        return;
    }
    printf("\n  Cities in the map (%d):\n", numCities);
    for (int i = 0; i < numCities; i++)
        printf("    [%d] %s\n", i + 1, cities[i]);
    printf("\n");
}

// ─────────────────────────────────────────
//  Load sample data for demo
// ─────────────────────────────────────────
void loadSampleData() {
    addCity("Delhi");
    addCity("Agra");
    addCity("Jaipur");
    addCity("Mumbai");
    addCity("Pune");
    addCity("Hyderabad");

    addRoad("Delhi",     "Agra",      200);
    addRoad("Delhi",     "Jaipur",    280);
    addRoad("Agra",      "Jaipur",    240);
    addRoad("Agra",      "Mumbai",    1200);
    addRoad("Jaipur",    "Mumbai",    1150);
    addRoad("Mumbai",    "Pune",      150);
    addRoad("Mumbai",    "Hyderabad", 700);
    addRoad("Pune",      "Hyderabad", 560);

    printf("\n  [✓] Sample city map loaded!\n");
}

// ─────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────
int main() {
    int choice;
    char cityName[30], city1[30], city2[30];
    int distance;

    printf("\n");
    printf("  ╔══════════════════════════════════════════════╗\n");
    printf("  ║       SHORTEST PATH FINDER  v1.0            ║\n");
    printf("  ║   Using Dijkstra's Algorithm (DP)           ║\n");
    printf("  ║   CCC GitHub Project                        ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n\n");

    while (1) {
        printf("  ┌─────────────── MENU ───────────────┐\n");
        printf("  │  1. Load Sample City Map (Demo)    │\n");
        printf("  │  2. Add City                       │\n");
        printf("  │  3. Add Road Between Cities        │\n");
        printf("  │  4. Find Shortest Path             │\n");
        printf("  │  5. List All Cities                │\n");
        printf("  │  6. Display City Map (Matrix)      │\n");
        printf("  │  7. Exit                           │\n");
        printf("  └────────────────────────────────────┘\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                loadSampleData();
                break;

            case 2:
                printf("  Enter city name: ");
                scanf("%s", cityName);
                addCity(cityName);
                break;

            case 3:
                printf("  Enter city 1: ");
                scanf("%s", city1);
                printf("  Enter city 2: ");
                scanf("%s", city2);
                printf("  Enter distance (km): ");
                scanf("%d", &distance);
                addRoad(city1, city2, distance);
                break;

            case 4:
                if (numCities < 2) {
                    printf("  [!] Add at least 2 cities first.\n\n");
                    break;
                }
                listCities();
                printf("  Enter SOURCE city name: ");
                scanf("%s", city1);
                printf("  Enter DESTINATION city name: ");
                scanf("%s", city2);
                {
                    int src = findCity(city1);
                    int dst = findCity(city2);
                    if (src == -1 || dst == -1)
                        printf("  [!] City not found. Check spelling.\n\n");
                    else if (src == dst)
                        printf("  [!] Source and destination are the same!\n\n");
                    else
                        dijkstra(src, dst);
                }
                break;

            case 5:
                listCities();
                break;

            case 6:
                displayGraph();
                break;

            case 7:
                printf("  Thank you! Goodbye. 👋\n\n");
                return 0;

            default:
                printf("  [!] Invalid choice. Try again.\n\n");
        }
    }
    return 0;
}
