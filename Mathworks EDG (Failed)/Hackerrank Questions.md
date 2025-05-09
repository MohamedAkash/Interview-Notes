What to know for the interview:

They might ask the hackerrank question that was previously done and ask to run through the solution and thought process

Hackerrank questions:

Mathematical questions (probability, numerical computation, …)

## 6. Minimum Length Subarray

For an array of n positive integers arr[n] and an integer k, a subarray is considered good if it consists of at least k distinct integers. Find the minimum length subarray that is good. If there is no such subarray, return -1.

Example

Arr = [2,2,1,1,3]

K = 3

The subarrays with at least k = 3 distinct integers are [2,2,1,1,3] and [2,1,1,3]. Return 4, the minimum length of a good subarray

Function Description:

findMinimumLength has the following parameters:
	int arr [n]: the array to partion
	int k: the number of distinct elements a good subarray must contain

returns
	int: the minimum length possible for a good subarray, or -1 if there is none

constraints:
1 <= n <= 10^5 
1 <= arr[i] <= 10^6
1 <= k <= n

``` C
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findMinimumLengthSubarray(int arr_count, int* arr, int k) {
    int left = 0;
    int min_length = arr_count + 1;
    int distinct_count = 0;

    // Allocate a frequency array for counting occurrences, assuming arr[i] <= 1,000,000
    int freq[1000001] = {0};


    for (int right = 0; right < arr_count; ++right) {
        // Add the current element at the right end to the window
        if (freq[arr[right]] == 0) {
            ++distinct_count;
        }
        ++freq[arr[right]];

        // Shrink the window from the left while we have at least `k` distinct elements
        while (distinct_count >= k) {
            // Update the minimum length if the current window is smaller
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }

            // Remove the element at the left end from the window
            --freq[arr[left]];
            if (freq[arr[left]] == 0) {
                --distinct_count;
            }
            ++left;
        }
    }

    // If no valid subarray was found, return -1
    return (min_length == arr_count + 1) ? -1 : min_length;
}
```

```python
from collections import defaultdict

def findMinimumLength(arr, k):    
    left = 0
    min_length = float('inf')
    distinct_count = 0
    freq = defaultdict(int)  # dictionary to track frequencies

    for right in range(len(arr)):
        freq[arr[right]] += 1
        if freq[arr[right]] == 1:  # new distinct element
            distinct_count += 1

        # Shrink from the left while we have at least k distinct integers
        while distinct_count >= k:
            current_length = right - left + 1
            min_length = min(min_length, current_length)

            # Remove element at the left end
            freq[arr[left]] -= 1
            if freq[arr[left]] == 0:
                distinct_count -= 1
                del freq[arr[left]]  # optional: keep dictionary clean
            left += 1

    return min_length if min_length != float('inf') else -1

# Example usage:
arr = [2, 2, 1, 1, 3]
k = 3
print(findMinimumLength(arr, k))  # Output: 4

```


### **Understanding the Question**

The problem is about finding the **minimum length subarray** that contains **at least `k` distinct integers** in a given array. If no such subarray exists, the function should return `-1`.

---

### **How the Code Solves the Problem**

The code uses a **sliding window technique** combined with a **frequency array** to efficiently track the number of distinct integers in the current window. Here’s the step-by-step explanation:

#### **Step 1: Initialization**

1. **Variables**:
    - `left`: The start index of the current sliding window.
    - `min_length`: Tracks the smallest subarray length found. Initialized to `arr_count + 1`, which is an impossible value for valid subarrays, to help with edge case handling.
    - `distinct_count`: Counts the number of distinct integers in the current window.
2. **Frequency Array**:
    - `freq[]`: An array to track the frequency of each integer in the current window. The problem assumes that the integers are bounded (`arr[i] <= 1,000,000`), so an array of size `1,000,001` is used.

#### **Step 2: Expanding the Window**

- Iterate over the array using the `right` pointer. This represents the **end of the current window**.
- For each `arr[right]`:
    1. If `arr[right]` is not already in the window (`freq[arr[right]] == 0`), increment `distinct_count` because a new distinct integer is added.
    2. Increment `freq[arr[right]]` to reflect the addition of `arr[right]` to the window.

#### **Step 3: Shrinking the Window**

- Once the current window has at least `k` distinct integers (`distinct_count >= k`), the code tries to **shrink the window** from the left (`left` pointer) to find the smallest possible subarray that still satisfies the condition:
    1. Calculate the current window length: `right - left + 1`.
    2. Update `min_length` if the current window is smaller than the previously recorded minimum.
    3. Remove `arr[left]` from the window:
        - Decrement its frequency in `freq[]`.
        - If its frequency becomes `0`, decrement `distinct_count` because the integer is no longer in the window.
    4. Move `left` one step to the right.

#### **Step 4: Result**

- After iterating through the array, check if a valid subarray was found:
    - If `min_length` was updated, return it.
    - Otherwise, return `-1` (no valid subarray was found).

---

### **Why This Approach Is Efficient**

1. **Time Complexity**:
    
    - The sliding window ensures that each element is processed at most twice—once when expanding the window and once when shrinking it.
    - Thus, the overall time complexity is **O(n)**, where `n` is `arr_count`.
2. **Space Complexity**:
    
    - The `freq[]` array uses **O(max(arr[i]))** space, which is bounded by `1,000,000` in this problem.

---

### **How to Explain Key Parts to an Interviewer**

1. **Why Sliding Window?**
    
    - Sliding window is a natural choice for problems requiring contiguous subarrays, as it avoids recalculating results for overlapping parts of the array.
2. **Why Use a Frequency Array?**
    
    - The frequency array allows us to efficiently track the number of distinct integers in the current window in constant time, making the algorithm much faster than other approaches like rechecking the entire window for distinctness.
3. **Edge Cases Considered**:
    
    - Empty array: The function will correctly return `-1` because no valid subarray can exist.
    - `k > arr_count`: If the array doesn't have enough elements to satisfy the condition, the function will return `-1`.
    - All elements are distinct: The function will correctly identify the smallest subarray containing `k` distinct integers.

---

### **How to Answer Follow-Up Questions**

1. **What if `arr[i]` is not bounded (e.g., large integers)?**
    
    - Instead of using a frequency array, we could use a hash map (`unordered_map` in C++ or `dict` in Python) to store frequencies. This would handle larger or negative integers at the cost of additional memory overhead for hash table storage.
2. **Why Initialize `min_length` to `arr_count + 1`?**
    
    - This ensures that if no valid subarray is found, the final check `(min_length == arr_count + 1)` correctly returns `-1`.
3. **Can this handle very large arrays?**
    
    - Yes, since the algorithm is linear (`O(n)`), it can handle large inputs efficiently as long as there’s enough memory for the frequency array.

---

### **Example Walkthrough**

#### Input:

`arr = [2, 2, 1, 1, 3], k = 3`

#### Execution:

1. **Initialization**:
    
    - `left = 0`, `min_length = 6`, `distinct_count = 0`.
    - `freq = [0, 0, 0, ...]`.
2. **Iteration**:
    
    - `right = 0`: Add `2`. `distinct_count = 1`. `freq[2] = 1`.
    - `right = 1`: Add `2`. `distinct_count = 1`. `freq[2] = 2`.
    - `right = 2`: Add `1`. `distinct_count = 2`. `freq[1] = 1`.
    - `right = 3`: Add `1`. `distinct_count = 2`. `freq[1] = 2`.
    - `right = 4`: Add `3`. `distinct_count = 3`. `freq[3] = 1`.
        - Shrink window:
            - `left = 0 -> 1 -> 2`: Subarray `[2, 1, 1, 3]` has length `4`.
3. **Result**:
    
    - Smallest subarray length with 3 distinct integers is `4`.

---

The problem requires finding the smallest subarray with at least `k` distinct integers. The code solves this efficiently using the **sliding window technique**. It expands the window with a `right` pointer and keeps track of distinct integers using a frequency array. When the number of distinct integers in the window reaches `k`, it tries to shrink the window from the left while maintaining the condition, updating the minimum length whenever a smaller valid window is found. The frequency array ensures efficient tracking of distinct integers in constant time for each element. This approach runs in **O(n)** time since each element is processed at most twice, making it optimal for large arrays. Edge cases like no valid subarray (`k > arr_count`) are handled by returning `-1` if no valid subarray is found. If asked to improve the solution for unbounded integers, replacing the frequency array with a hash map would work at the cost of additional memory.

## 7. Minimum Travel Cost

The country of Hackerland is represented as a graph of g_nodes cities numbered from 1 to g_nodes. The cities are connected through g_edges bidirectional roads where the i^th road connects city g_from[i] and city g_to[i] and the amount of fuel required to travel a road is g_weight[i] units. The cars in Hackeralnd have an infinite fuel capacity. The cost of one unit of fuel in the i^th city is arr[i]. Any amount of fuel can be obtained in any city.

Given two cities A and B (1 <= A, B <= road_nodes), find the minimum cost to travel from city A to city B. if it is not possible, return -1.

Examples

g_nodes = 5
g_from = [4,5,4,1,3,4,4]
g_to = [1,3,5,5,1,2,3]
g_weight = [1,1,8,1,3,9,5]
arr = [9,11,3,2,10]
A = 3
B = 2
Nodes are Labeled (City Number):(fuel cost)
![[Pasted image 20241122142754.png]]

One optimal path is 3->5->1->4->2. Buy 3 units of fuel at 3 with a cost of 3 * 3 = 9 and 9 units at city 4 for 9 * 2 = 18. The total cost is 9 + 18 = 27

Function Description
Complete the function getMinCost in the editor below.

getMinCost has the following parameters:
	int g_nodes: the number of cities
	int g_from\[g_eges\]: one endpoint of each road
	int g_to\[g_edges\]: the other endpoint of each road
	int g_weight\[g_edges]: the weight of each road 
	int arr\[g_nodes]: the cost of unit fuel in each city
	int A: the city to start from
	int B: the destination city

Returns
	long int: the minimum cost to go from City A to City B, or -1 if it is impossible


Constraints
2 <= g_nodes <= 200
1 <= g_edges <= g_nodes * (g_nodes - 1)/2
1 <= g_from\[i] <= g_nodes
1 <= g_to\[i] <= g_nodes
1 <= g_weight\[i] <= 10^6
1 <= arr[i] <= 10^6
1 <= A, B <= g_nodes

``` cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

long getMinCost(int g_nodes, const vector<int>& g_from, const vector<int>& g_to, const vector<int>& g_weight, const vector<int>& arr, int A, int B) {
    // Build the graph as an adjacency list
    vector<vector<pair<int, int>>> graph(g_nodes + 1);
    for (int i = 0; i < g_from.size(); ++i) {
        graph[g_from[i]].emplace_back(g_to[i], g_weight[i]);
        graph[g_to[i]].emplace_back(g_from[i], g_weight[i]);
    }

    // Initialize minCost array with large values
    vector<long long> minCost(g_nodes + 1, LLONG_MAX);
    minCost[A] = 0;

    // Priority queue to store (cost, city), using min-heap
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, A});

    while (!pq.empty()) {
        auto [current_cost, city] = pq.top();
        pq.pop();

        // If we reached city B, return the cost
        if (city == B) {
            return current_cost;
        }

        // Skip if this cost is not the minimum for the city (outdated entry)
        if (current_cost > minCost[city]) continue;

        // Traverse neighbors
        for (const auto& [neighbor, weight] : graph[city]) {
            // Calculate cost to travel to the neighbor using the fuel rate of the current city
            long long travel_cost = current_cost + weight * arr[city - 1];
            
            // Only proceed if this path is cheaper
            if (travel_cost < minCost[neighbor]) {
                minCost[neighbor] = travel_cost;
                pq.push({travel_cost, neighbor});
            }
        }
    }

    // If city B is not reachable
    return -1;
}

int main() {
    int g_nodes = 4;
    vector<int> g_from = {1, 2, 2};
    vector<int> g_to = {2, 3, 4};
    vector<int> g_weight = {3, 1, 7};
    vector<int> arr = {3, 6, 2, 2};
    int A = 1;
    int B = 4;

    long result = getMinCost(g_nodes, g_from, g_to, g_weight, arr, A, B);
    cout << "Minimum travel cost from city " << A << " to city " << B << " is: " << result << endl;

    return 0;
}

```

### **How This Differs from Basic Dijkstra**

This implementation extends Dijkstra's algorithm by incorporating **fuel costs**:

- Instead of minimizing just the distance (or edge weights), this version minimizes the **total travel cost**, which depends on:
    1. The road weight (fuel required).
    2. The fuel cost at the current city.

This is why the cost calculation is:

```cpp
long long travel_cost = current_cost + weight * arr[city - 1];
```

---

### **Why It’s Dijkstra**

The algorithm adheres to the core principles of Dijkstra:

- Uses a priority queue to process the least-cost paths first.
- Relaxes edges to update the minimum cost to neighbors.
- Guarantees correctness by skipping outdated paths and stopping when the destination is reached.

By adapting the cost calculation to include fuel prices, this algorithm effectively applies Dijkstra's logic to a more complex problem.

---
### Quick Summary

The problem is to calculate the minimum travel cost between two cities in a weighted graph, considering both road distances and varying fuel costs at each city. I used Dijkstra's algorithm to find the shortest path efficiently. The graph is represented as an adjacency list, and a priority queue ensures the least costly path is explored first.

At each step, the cost to travel to a neighbor is calculated as the current cost plus the road weight multiplied by the current city’s fuel price. If this cost is lower than the recorded minimum for that neighbor, it’s updated, and the neighbor is added to the queue.

The algorithm terminates when the destination is reached, returning the accumulated cost. If the destination is unreachable, it returns -1. The approach runs in O((V+E)log⁡V), making it efficient for large graphs. A possible improvement would be tracking the cheapest fuel dynamically along the path for better optimization.

Here’s an elaborated yet concise explanation of the **code**, focusing on how it works:

---

### **Code Explanation**

1. **Graph Representation**:
    
    - The graph is represented as an adjacency list:
        
        ```cpp
        for (int i = 0; i < g_from.size(); ++i) {
            graph[g_from[i]].emplace_back(g_to[i], g_weight[i]);
            graph[g_to[i]].emplace_back(g_from[i], g_weight[i]);
        }
        ```
        
    - Each city (node) is connected to its neighbors (other cities) with weights representing the fuel required for the road segment.
    - This representation ensures efficient traversal and updates when exploring paths.
2. **Priority Queue**:
    
    - The priority queue is initialized with the starting city A:
        
        ```cpp
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        pq.push({0, A});
        ```
        
    - Each entry in the queue is a pair of:
        - current cost\text{current cost}: Total cost incurred to reach the city so far.
        - current city\text{current city}: The city being explored.
    - The queue ensures the city with the **lowest cost** is processed first, following the greedy approach of Dijkstra's algorithm.
3. **Cost Tracking**:
    
    - A `minCost` array is used to store the minimum cost to reach each city:
        
        ```cpp
        vector<long long> minCost(g_nodes + 1, LLONG_MAX);
        minCost[A] = 0;
        ```
        
    - This ensures that only cheaper paths update the cost for a given city.
4. **Main Loop**:
    
    - The algorithm processes cities from the priority queue:
        
        ```cpp
        while (!pq.empty()) {
            auto [current_cost, city] = pq.top();
            pq.pop();
        }
        ```
        
    - If the destination city BB is dequeued, the algorithm terminates and returns the current cost.
5. **Travel Cost Calculation**:
    
    - For each neighboring city, the cost to reach it is calculated as:
        
        ```cpp
        long long travel_cost = current_cost + weight * arr[city - 1];
        ```
        
    - The fuel cost for the road segment is determined by the current city’s fuel price (arr[city - 1]\text{arr[city - 1]}) multiplied by the road weight.
6. **Updating Costs**:
    
    - If the new travel cost to the neighbor is less than its recorded cost, update it and push the neighbor into the queue:
        
        ```cpp
        if (travel_cost < minCost[neighbor]) {
            minCost[neighbor] = travel_cost;
            pq.push({travel_cost, neighbor});
        }
        ```
        
7. **Termination**:
    
    - The algorithm returns the cost upon reaching BB. If BB is unreachable after processing all cities, it returns −1-1.

---

### **Example Walkthrough**

For the input:

```cpp
g_nodes = 4;
g_from = {1, 2, 2};
g_to = {2, 3, 4};
g_weight = {3, 1, 7};
arr = {3, 6, 2, 2};
A = 1;
B = 4;
```

Steps:

1. Start at City 1 (cost=0).
2. Process City 2 (cost=3×3=9).
3. Process City 3 (cost=9+1×6=15).
4. Process City 4 (cost=15+7×6=57).

Result: Minimum cost is 57. (not so great)

---

### **How to Explain Enhancements**

If asked how to improve the code:

- Propose adding dynamic tracking of the cheapest fuel cost along the path to allow for smarter fuel purchases, especially when future cities have lower prices.

This explanation provides a clear, step-by-step understanding of the code logic and demonstrates your thought process behind each component.


Improved Answer:

``` C++
#include <bits/stdc++.h>
using namespace std;

struct State {
    long long cost;
    int city;
    int price; // best encountered price so far

    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

long getMinCost(int g_nodes, const vector<int>& g_from, const vector<int>& g_to, const vector<int>& g_weight, const vector<int>& arr, int A, int B) {
    // Build graph
    vector<vector<pair<int,int>>> graph(g_nodes+1);
    for (int i = 0; i < (int)g_from.size(); ++i) {
        int u = g_from[i], v = g_to[i];
        int w = g_weight[i];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // Distances: key=(city, best_price), value=cost
    // best_price is the cheapest fuel cost encountered so far
    // We'll store only states we encounter, using a map.
    map<pair<int,int>, long long> dist;

    // Priority queue for Dijkstra: (cost, city, best_price)
    priority_queue<State, vector<State>, greater<>> pq;

    // Initial state: start at A, best_price=arr[A-1], cost=0
    dist[{A, arr[A-1]}] = 0;
    pq.push({0, A, arr[A-1]});

    while(!pq.empty()) {
        auto [current_cost, city, best_price] = pq.top();
        pq.pop();

        // If we've reached B, return the cost
        if (city == B) return current_cost;

        // If dist is outdated, skip
        if (dist[{city, best_price}] < current_cost) continue;

        // Explore neighbors
        for (auto &[nbr, w] : graph[city]) {
            // Buy fuel at the best_price encountered so far to cover this road
            long long new_cost = current_cost + (long long)best_price * w;
            int new_best = best_price;

            // If we arrive at nbr and it has cheaper fuel, update best_price
            if (arr[nbr-1] < new_best) {
                new_best = arr[nbr-1];
            }

            auto key = make_pair(nbr, new_best);
            if (!dist.count(key) || dist[key] > new_cost) {
                dist[key] = new_cost;
                pq.push({new_cost, nbr, new_best});
            }
        }
    }

    // If we cannot reach B, return -1
    return -1;
}

int main() {
    // Example from problem statement or other testing
    int g_nodes = 5;
    vector<int> g_from = {4,5,4,1,3,4,4};
    vector<int> g_to   = {1,3,5,5,1,2,3};
    vector<int> g_weight = {1,1,8,1,3,9,5};
    vector<int> arr = {9,11,3,2,10};
    int A = 3, B = 2;

    long result = getMinCost(g_nodes, g_from, g_to, g_weight, arr, A, B);
    cout << "Minimum travel cost from city " << A << " to city " << B << " is: " << result << "\n"; 

    return 0;
}
```

---
---

```python
import heapq
from math import inf

def getMinCost(g_nodes, g_from, g_to, g_weight, arr, A, B):
    # Build graph
    graph = [[] for _ in range(g_nodes + 1)]
    for u, v, w in zip(g_from, g_to, g_weight):
        graph[u].append((v, w))
        graph[v].append((u, w))

    # dist will map (city, best_price) -> cost
    dist = {}
    # Priority queue stores (cost, city, best_price)
    pq = []
    # Initial state: start at A with cost=0 and best_price=arr[A-1]
    initial_price = arr[A-1]
    dist[(A, initial_price)] = 0
    heapq.heappush(pq, (0, A, initial_price))

    while pq:
        current_cost, city, best_price = heapq.heappop(pq)

        # If we reached city B, return the cost
        if city == B:
            return current_cost

        # If this entry is outdated, skip
        if dist.get((city, best_price), inf) < current_cost:
            continue

        # Relax edges
        for neighbor, w in graph[city]:
            # Calculate travel cost using best_price encountered so far
            new_cost = current_cost + best_price * w
            # Update best_price if the neighbor city has cheaper fuel
            new_best = min(best_price, arr[neighbor - 1])

            # Check if this improves dist for (neighbor, new_best)
            if dist.get((neighbor, new_best), inf) > new_cost:
                dist[(neighbor, new_best)] = new_cost
                heapq.heappush(pq, (new_cost, neighbor, new_best))

    # If B is not reachable
    return -1


# Example usage:
if __name__ == "__main__":
    g_nodes = 5
    g_from = [4,5,4,1,3,4,4]
    g_to =   [1,3,5,5,1,2,3]
    g_weight = [1,1,8,1,3,9,5]
    arr = [9,11,3,2,10]
    A = 3
    B = 2

    # Expected: 27 based on the problem statement example
    result = getMinCost(g_nodes, g_from, g_to, g_weight, arr, A, B)
    print("Minimum travel cost from city {} to city {} is: {}".format(A, B, result))

```

Below is an explanation of the code line-by-line and the logic behind it. This code is a modified version of Dijkstra's algorithm to handle a scenario where you can buy fuel at different prices in each city, and carry that fuel infinitely.

```python
import heapq
from math import inf

def getMinCost(g_nodes, g_from, g_to, g_weight, arr, A, B):
```

- **Objective**: Find the minimum travel cost from city A to city B.
- `g_nodes`: number of cities.
- `g_from`, `g_to`, `g_weight`: define bidirectional roads between cities.
- `arr`: cost of fuel per unit in each city.
- `A`, `B`: start and end cities.

```python
    # Build graph
    graph = [[] for _ in range(g_nodes + 1)]
    for u, v, w in zip(g_from, g_to, g_weight):
        graph[u].append((v, w))
        graph[v].append((u, w))
```

- Builds an adjacency list representation of the graph.
- `graph[i]` will contain a list of `(neighbor, weight)` pairs.
- Each road is bidirectional, so it’s added twice: once from `u` to `v` and once from `v` to `u`.

```python
    # dist will map (city, best_price) -> cost
    dist = {}
```

- `dist` is a dictionary keyed by `(city, best_price)`:
    - `city` is the current city.
    - `best_price` is the cheapest fuel price encountered so far on the path taken to reach this state.
- `dist[(city, best_price)]` = the minimum cost to reach `city` when the cheapest fuel price seen so far is `best_price`.

```python
    # Priority queue stores (cost, city, best_price)
    pq = []
```

- A priority queue (min-heap) to select the next state with the lowest current cost.

```python
    # Initial state: start at A with cost=0 and best_price=arr[A-1]
    initial_price = arr[A-1]
    dist[(A, initial_price)] = 0
    heapq.heappush(pq, (0, A, initial_price))
```

- Starting from city A:
    - Initial cost = 0 (haven’t traveled yet).
    - Initial best_price = arr[A-1], since you’ve only seen city A’s fuel cost.
- Push `(0, A, initial_price)` into the priority queue and record `dist[(A, initial_price)] = 0`.

```python
    while pq:
        current_cost, city, best_price = heapq.heappop(pq)
```

- Extract the state with the smallest `current_cost`.
- `city`: where we currently are.
- `best_price`: cheapest fuel price encountered so far on our path.

```python
        # If we reached city B, return the cost
        if city == B:
            return current_cost
```

- If the current city is B, we've found a way to get there. Since we use a priority queue and always pick the lowest cost state first, `current_cost` is guaranteed to be the minimum cost to reach B.

```python
        # If this entry is outdated, skip
        if dist.get((city, best_price), inf) < current_cost:
            continue
```

- Check if this state is still valid. Because we might insert multiple states for the same `(city, best_price)` with different costs, some become outdated.
- If the recorded best cost in `dist` for `(city, best_price)` is less than `current_cost`, it means we’ve already found a cheaper way to get here, so skip this one.

```python
        # Relax edges
        for neighbor, w in graph[city]:
```

- Iterate over all roads `(city -> neighbor)` with fuel requirement `w`.

```python
            # Calculate travel cost using best_price encountered so far
            new_cost = current_cost + best_price * w
```

- The cost to travel this edge is `best_price * w` because we assume we buy all the needed fuel at the cheapest price encountered so far.
- Add this to `current_cost` to get the total cost if we choose this path.

```python
            # Update best_price if the neighbor city has cheaper fuel
            new_best = min(best_price, arr[neighbor - 1])
```

- If the `neighbor` city has a lower fuel price `arr[neighbor-1]` than our current `best_price`, then we set `new_best` to that lower value.
- This means, beyond this point, we can consider that we can buy fuel at `new_best` cost for future edges.

```python
            # Check if this improves dist for (neighbor, new_best)
            if dist.get((neighbor, new_best), inf) > new_cost:
                dist[(neighbor, new_best)] = new_cost
                heapq.heappush(pq, (new_cost, neighbor, new_best))
```

- If we haven’t found a cheaper way to reach `(neighbor, new_best)` before, update `dist` and push this new state into the priority queue.

```python
    # If B is not reachable
    return -1
```

- If the loop ends without reaching city B, then B is not reachable under any scenario. Return `-1`.

---

### Logical Explanation

- **What’s Different from Standard Dijkstra?**
    
    - Normally, Dijkstra’s algorithm tracks `(distance, node)` states. Here, we track `(cost, city, best_price)` states.
    - We do this because the cost of future edges depends on the minimum price we've seen so far, not just on the current location.
- **Why Does This Solve the Problem?**
    
    - It allows us to consider paths that might be more expensive initially but lead to a city with cheaper fuel, ultimately saving cost on future edges.
    - If we only tracked `(city)`, we’d lose information about the cheapest fuel price encountered, potentially missing the optimal path.

---

### Example

Consider the example from the prompt:

- After some exploration, the algorithm finds a path `(3 -> 5 -> 1 -> 4 -> 2)` where it first encounters a decent price at city 3 (price = 3), then finds even cheaper fuel at city 4 (price = 2).
- By carrying forward the idea that we can now buy fuel at `2` units cost, the algorithm computes edges beyond city 4 using `2` as the multiplier, resulting in the minimal possible total cost (`27`).

---

**In summary**, this code uses a clever adaptation of Dijkstra’s algorithm to handle dynamic fuel pricing by tracking and updating the best fuel price encountered. Each push to the priority queue captures a potentially better state, ensuring the final solution is indeed the minimum cost to reach city B.