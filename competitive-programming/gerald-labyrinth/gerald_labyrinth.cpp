#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

/**
 * Gerald of Rivia's Labyrinth Challenge
 * 
 * Problem: Gerald needs to clear as many rooms as possible while ensuring that 
 * for any two consecutively cleared rooms with A and B monsters, gcd(A, B) > 1.
 * Gerald can skip rooms, but must preserve the original room order.
 * 
 * Algorithm: Dynamic Programming with Prime Factorization
 * 1. Precompute prime numbers up to sqrt(10^7) for efficient factorization
 * 2. For each room, factorize the monster count to get distinct prime factors
 * 3. Use DP where dp[i] = maximum rooms clearable ending at room i
 * 4. For room i with monster count A[i], dp[i] = 1 + max(dp[j]) where gcd(A[i], A[j]) > 1
 * 5. Two numbers share a common factor if they have at least one common prime factor
 * 6. Special case: rooms with monster count = 1 have no prime factors
 */

class GeraldLabyrinth {
private:
    vector<int> primes;
    unordered_map<int, int> prime_to_max_dp;
    
    // Sieve of Eratosthenes to precompute primes up to sqrt(10^7)
    void sievePrimes(int limit) {
        vector<bool> is_prime(limit + 1, true);
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i * i <= limit; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= limit; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        for (int i = 2; i <= limit; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }
    }
    
    // Get distinct prime factors of a number
    vector<int> getPrimeFactors(int num) {
        vector<int> factors;
        
        // Handle factor 2 separately
        if (num % 2 == 0) {
            factors.push_back(2);
            while (num % 2 == 0) {
                num /= 2;
            }
        }
        
        // Check odd factors up to sqrt(num)
        for (size_t i = 1; i < primes.size() && primes[i] * primes[i] <= num; ++i) {
            if (num % primes[i] == 0) {
                factors.push_back(primes[i]);
                while (num % primes[i] == 0) {
                    num /= primes[i];
                }
            }
        }
        
        // If num is still > 1, then it's a prime factor
        if (num > 1) {
            factors.push_back(num);
        }
        
        return factors;
    }
    
public:
    int maxRoomsClearable(vector<int>& monsters) {
        int n = monsters.size();
        if (n == 0) return 0;
        
        // Precompute primes up to sqrt(10^7) ≈ 3162
        sievePrimes(3162);
        
        int max_rooms = 0;
        prime_to_max_dp.clear();
        
        for (int i = 0; i < n; ++i) {
            int current_dp = 1; // At least we can clear this room alone
            
            if (monsters[i] == 1) {
                // Special case: monster count = 1 has no prime factors
                // Can only be cleared alone, cannot chain with other rooms
                max_rooms = max(max_rooms, 1);
                continue;
            }
            
            // Get prime factors of current monster count
            vector<int> factors = getPrimeFactors(monsters[i]);
            
            // Find maximum dp value among all prime factors
            int max_prev_dp = 0;
            for (int factor : factors) {
                if (prime_to_max_dp.count(factor)) {
                    max_prev_dp = max(max_prev_dp, prime_to_max_dp[factor]);
                }
            }
            
            current_dp = max_prev_dp + 1;
            
            // Update the maximum dp value for all prime factors of current room
            for (int factor : factors) {
                prime_to_max_dp[factor] = max(prime_to_max_dp[factor], current_dp);
            }
            
            max_rooms = max(max_rooms, current_dp);
        }
        
        return max_rooms;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> monsters(n);
    for (int i = 0; i < n; ++i) {
        cin >> monsters[i];
    }
    
    GeraldLabyrinth solution;
    int result = solution.maxRoomsClearable(monsters);
    
    cout << result << endl;
    
    return 0;
}