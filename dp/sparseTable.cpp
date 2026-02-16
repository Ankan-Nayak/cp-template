int table[1000000][25];
void buildSparseTable(int arr[], int n) { 
  for (int i = 0; i < n; i++) 
    table[i][0] = arr[i]; 

  for (int j = 1; j <= log2(n); j++) 
    for (int i = 0; i <= n - (1 << j); i++) 
      table[i][j] = __gcd(table[i][j - 1], 
        table[i + (1 << (j - 1))][j - 1]); 
} 
int query(int L, int R) { 
  int j = (int)log2(R - L + 1); 
  return __gcd(table[L][j], table[R - (1 << j) + 1][j]); 
} 

/*
query->
i want _1 [_2 _3 _4 _5 _6] _7
can do this min([2, 3, 4, 5], [3, 4, 5, 6])  overlap just low power
*/




int table[1000000][25];

void buildSparseTable(int arr[], int n) { 
    for (int i = 0; i < n; i++) 
        table[i][0] = arr[i]; 

    for (int j = 1; (1 << j) <= n; j++) 
        for (int i = 0; i + (1 << j) <= n; i++) 
            table[i][j] = min(table[i][j - 1],
                              table[i + (1 << (j - 1))][j - 1]);
}
