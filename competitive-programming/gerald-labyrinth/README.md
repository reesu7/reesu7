# Gerald of Rivia's Labyrinth Challenge

## Problem Description

Gerald needs to clear as many rooms as possible from a labyrinth while following a specific constraint: for any two consecutively cleared rooms with A and B monsters, the greatest common divisor (gcd(A, B)) must be greater than 1.

Gerald can choose to skip rooms, but the order in which rooms are cleared must preserve the original room order.

## Algorithm

The solution uses dynamic programming with prime factorization:

1. **Prime Precomputation**: Generate all prime numbers up to √(10^7) ≈ 3162 using the Sieve of Eratosthenes
2. **Prime Factorization**: For each room's monster count, find all distinct prime factors
3. **Dynamic Programming**: 
   - `dp[i]` = maximum number of rooms clearable ending at room i
   - For room i with monster count A[i], `dp[i] = 1 + max(dp[j])` where gcd(A[i], A[j]) > 1
   - Two numbers share a common factor if they have at least one common prime factor
4. **Special Case**: Rooms with monster count = 1 have no prime factors and can only be cleared alone

## Key Insights

- Two numbers have gcd > 1 if and only if they share at least one common prime factor
- We maintain the maximum dp value for each prime factor seen so far
- When processing a room, we look at all its prime factors to find the best previous room to chain with

## Complexity

- **Time Complexity**: O(n * √m) where n is the number of rooms and m is the maximum monster count
- **Space Complexity**: O(π(√m)) for storing primes, where π is the prime counting function

## Compilation and Usage

```bash
g++ -o gerald_labyrinth gerald_labyrinth.cpp
./gerald_labyrinth < input.txt
```

## Input Format

```
n
monsters[0] monsters[1] ... monsters[n-1]
```

Where:
- n is the number of rooms
- monsters[i] is the number of monsters in room i

## Example

**Input:**
```
5
6 10 15 21 14
```

**Output:**
```
4
```

**Explanation:**
- Room 0: 6 = 2 × 3
- Room 1: 10 = 2 × 5  
- Room 2: 15 = 3 × 5
- Room 3: 21 = 3 × 7
- Room 4: 14 = 2 × 7

Gerald can clear rooms 0, 1, 2, 3 (or other valid sequences) since:
- gcd(6, 10) = 2 > 1
- gcd(10, 15) = 5 > 1  
- gcd(15, 21) = 3 > 1