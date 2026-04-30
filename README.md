# 🗺️ Shortest Path Finder
### CCC GitHub Project | Dynamic Programming (Dijkstra's Algorithm)

---

## 📌 About
This project implements **Dijkstra's Algorithm** — a classic **Dynamic Programming** approach — to find the shortest path between cities on a map.

---

## 🧠 Algorithm Used
**Dijkstra's Algorithm** works by:
1. Starting from the source city with distance = 0
2. Visiting the nearest unvisited city
3. Updating distances to all neighboring cities
4. Repeating until the destination is reached

This is a **Dynamic Programming** technique because it breaks the problem into subproblems (shortest distance to each city) and builds the final answer from them.

---

## 🚀 How to Run

### Compile:
```bash
gcc main.c -o shortest_path
```

### Run:
```bash
./shortest_path
```

---

## 📋 Features
- ✅ Add custom cities
- ✅ Add roads with distances between cities
- ✅ Find shortest path using Dijkstra's Algorithm
- ✅ Display step-by-step path breakdown
- ✅ View city connection map (adjacency matrix)
- ✅ Built-in sample city map (Demo mode)

---

## 🗂️ Sample Output
```
Source      : Delhi
Destination : Hyderabad
Total Distance : 1050 km

Path: Delhi --> Agra --> Mumbai --> Hyderabad

Step-by-step breakdown:
  Delhi --> Agra      : 200 km  (Total so far: 200 km)
  Agra  --> Mumbai    : 1200 km (Total so far: 1400 km)
  ...
```

---

## 📁 File Structure
```
shortest-path-finder/
│
├── main.c        ← Full C program (Dijkstra's Algorithm)
└── README.md     ← Project description
```

---

## 👨‍💻 Team Members
- Member 1
- Member 2
- (Add your names here)

---

## 🏫 Submitted to: CCC
