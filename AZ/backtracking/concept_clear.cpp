// take global ans = 0, when cond satisfies ans += 1;
// backtracking -> set, rec, unset -> keeps the whole array just like before after whole run(all became unset wheather that's a correct path or not)
// Time complexity thinks like a to generate all possibility time 
// (take, not take or no of subseq 2^n), all poss permutation(n!)



// f(int x) {
//     set;
//     f(x + 1);
//     print(x);
//     unset;
// }
// f(int x) {
//     set;
//     x += 1;
//     f(x);
//     print(x);
//     unset;
// }

// Diff output

// void f(int &x) {
//     set;
//     x += 1;
//     f(x);      // x is changed permanently
//     unset;
// }
// void f(int &x) {
//     set;
//     f(x + 1);  // only child sees increment
//     unset;
// }
// rec(1)
//  └─ rec(2)
//      └─ rec(3)
//      └─ unset(3) → return
//      └─ unset(2) → return
//  └─ unset(1) → return

// Return means go back to prev recursion
// Ankan Nayak: Hamiltonian prunning destroys and corner destryos
// When in deoth, so many eliminate
// Ankan Nayak: 4⁴⁸ to 2 ⁴⁸ to 1e6

