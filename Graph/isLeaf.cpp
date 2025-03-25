void dfs(int vertex, int par = -1) {
    // Assume it's a leaf until we find a child that isn't the parent.
    bool isLeaf = true;
    
    for (auto child : g[vertex]) {
        if (child == par) continue;  // Skip the parent.
        isLeaf = false;              // Found at least one child.
        depth[child] = depth[vertex] + 1;
        dfs(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
    }
    
    // If it remains true, no valid child was found, so vertex is a leaf.
    if(isLeaf) {
        // For example, you can set height explicitly (if not already 0)
        height[vertex] = 0;
        // You can also perform any leaf-specific actions here.
    }
}



bool isLeaf(int vertex, int par = -1) {
    for (auto child : g[vertex]) {
        if (child == par) continue;
        // Found a valid child, so not a leaf.
        return false;
    }
    return true;
}
