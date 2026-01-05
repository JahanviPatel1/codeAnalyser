int main() {
    int unused_var = 99;
    int used_var = 1;
    
    if (used_var > 0) {
        while (used_var < 10) {
            if (used_var == 5) {
                if (used_var > 2) {
                    // Deep nesting (Level 4)
                    return 1;
                }
            }
            used_var = used_var + 1;
        }
    }
    
    int another_unused = 0;
    return 0;
}
