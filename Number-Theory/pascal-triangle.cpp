void pascalTriangle(int n) {
    for (int i = 0; i < n; i++) {
        int val = 1;
        for (int j = 0; j <= i; j++) {
            cout << val << ' '; 
            val = val * (i - j) / (j + 1); // Compute next binomial coefficient
        }
        cout << endl;
    }
}
// table make i = n, j = r, => ncr = table[i][j]