#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void swap(double *a, double *b)
{
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

_Bool gauss_jordan(int n, double matrix[][n*2])
{
    for (int i=0; i<n; ++i)
    {
        if (*(*(matrix+i)+i) == 0)
            for (int j=i+1; j<n; ++j)
                if (*(*(matrix+j)+i) != 0)
                {
                    /*
                    printf("\ni= %d,j= %d\n",i,j);
                    putchar('\n');
                    for (int k=0; k<n; k++){
                        for (int h=0; h<2*n; h++)
                            printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
                    }
                    */
/*
 0.000  3.000  9.000  9.000  9.000  1.000  0.000  0.000  0.000  0.000 --i
 2.000  5.000  1.000  5.000  5.000  0.000  1.000  0.000  0.000  0.000 --j
 3.000  2.000  5.000  2.000  7.000  0.000  0.000  1.000  0.000  0.000
 2.000  5.000  6.000  2.000  7.000  0.000  0.000  0.000  1.000  0.000
 5.000  6.000  1.000  8.000  4.000  0.000  0.000  0.000  0.000  1.000

 2.000  5.000  1.000  5.000  5.000  0.000  1.000  0.000  0.000  0.000 --j
 0.000  3.000  9.000  9.000  9.000  1.000  0.000  0.000  0.000  0.000 --i
 3.000  2.000  5.000  2.000  7.000  0.000  0.000  1.000  0.000  0.000
 2.000  5.000  6.000  2.000  7.000  0.000  0.000  0.000  1.000  0.000
 5.000  6.000  1.000  8.000  4.000  0.000  0.000  0.000  0.000  1.000
 */
                    for (int k=i; k<n*2; ++k) swap((*(matrix+i)+k), (*(matrix+j)+k));
                    /*
                    putchar('\n');
                    for (int k=0; k<n; k++){
                        for (int h=0; h<2*n; h++)
                            printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
                    }
*/
                    break;
                }

        // 反矩陣不存在
        if (*(*(matrix+i)+i) == 0) return false;
        /*
        putchar('\n');
        for (int k=0; k<n; k++){
            for (int h=0; h<2*n; h++) printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
            }
            putchar('\n');
        putchar('\n');
        */
        double t = *(*(matrix+i)+i);
        for (int k=i; k<n*2; ++k) *(*(matrix+i)+k) /= t;
        /*
        putchar('\n');
        for (int k=0; k<n; k++){
            for (int h=0; h<2*n; h++) printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
            }
            putchar('\n');
        putchar('\n');
        */
        // 消去時，所有橫條通通消去
        /*
        printf("\ni= %d\n",i);
        putchar('\n');
        for (int k=0; k<n; k++){
            for (int h=0; h<2*n; h++) printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
            }
            putchar('\n');
        putchar('\n');
        */
/*
 1.000  0.222  1.000  0.111  0.000  0.000
 5.000  0.000  1.000  0.000  1.000  0.000
 0.000  0.000  5.000  0.000  0.000  1.000



 1.000  0.222  1.000  0.111  0.000  0.000
 0.000 -1.111 -4.000 -0.556  1.000  0.000
 0.000  0.000  5.000  0.000  0.000  1.000
 */
        for (int j=0; j<n; ++j)
            if (i != j && *(*(matrix+j)+i) != 0)
            {
                double t = *(*(matrix+j)+i);
                //printf("\nt= %f\n",t);
                for (int k=i; k<n*2; ++k) *(*(matrix+j)+k) -= *(*(matrix+i)+k) * t;
            }
        /*
        putchar('\n');
        for (int k=0; k<n; k++){
            for (int h=0; h<2*n; h++) printf("%6.3f ", *(*(matrix+k)+h));
                        putchar('\n');
            }
            putchar('\n');
        putchar('\n');
        */
    }
    return true;
}

int main()
{
    srand(time(NULL));
    int n;
    scanf("%d",&n);
    double a[n][2*n], b[n][n], c[n][n];

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            *(*(c+i)+j) = 0;
            *(*(a+i)+j) = *(*(b+i)+j) = rand()%10;
            *(*(a+i)+j+n) = (j == i) ? 1 : 0;
            printf("%6.f ", *(*(a+i)+j));
        }
        putchar('\n');
    }

    // 做高斯
    if (!gauss_jordan(n, a)){printf("\n沒有反矩陣!\n");return 0;}

    printf("\n\tX\n\n");
    // 顯示反矩陣
    for (int i=0; i<n; i++){
        for (int j=n; j<2*n; j++){
            printf("%6.3f ", *(*(a+i)+j));
        }
        putchar('\n');
    }

    printf("\n\t||\n\n");
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                //printf("%f \n",*(*(b+i)+k)* *(*(a+k)+n+j));
                *(*(c+i)+j) += *(*(b+i)+k) * *(*(a+k)+n+j);
            }
        }

        for (int j=0; j<n; j++){
            printf("%6.3f ", *(*(c+i)+j));
        }
        putchar('\n');
    }
    return 0;
}
