void print_M(int n, int m, float M[n][n+m]);
void print_X(int n, int m, float X[n][m]);
void resolution_tri(int n, float M[n][n+1], float X[n]);
void invert(int n, int m, float M[n][n+m], int k, int p);
void swap (float * a, float * b);
int ligne_pivot(int n, float M[n][n+1], int k);
float triangulation(int n, int m, float M[n][n+m]);
float det(int n, float M[n][n+1]);
void tabX(int n, int m, float M[n][n+m], float X[n][m]);

