#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#define _USE_MATH_DEFINES
#include <math.h>


float getRandPoint() {
    return ((double)rand() / (double)RAND_MAX);
}


float getPointInRange(float a, float b) {
    return (a + getRandPoint() * (b - a));
}

void estimatePi() {
    int maxPoints[30];
    double error[30];
    for (int i = 1; i < 31; i++) {
        maxPoints[i - 1] = i * 1000;
    }
    for (int i = 0; i < 30; i++) {
        int N = maxPoints[i];
        int c = 0;
        float* color = new float[N];
        float* x = new float[N];
        float* y = new float[N];

        for (int j = 0; j <= N; ++j) {
            x[j] = getRandPoint();
            y[j] = getRandPoint();
            if (sqrt(x[j] * x[j] + y[j] * y[j]) <= 1) {
                color[j] = 1;
                c++;
            }
            else color[j] = 2;
        }

        float piVal = 4 * (float)c / N;
        error[i] = fabs(M_PI - piVal);

        FILE* gnuplot = _popen("gnuplot -persist", "w");
        fprintf(gnuplot, "set title 'pi = %f     N = %i'\n", piVal, N);
        fprintf(gnuplot, "set xlabel 'x axis'\n");
        fprintf(gnuplot, "set ylabel 'y axis'\n");
        fprintf(gnuplot, "set xrange [-0.001:1.001]\n");
        fprintf(gnuplot, "set palette defined(0 'green', 3 'green', 4 'red', 5 'red');\n");
        fprintf(gnuplot, "plot sqrt(1 - x * x), '-' using 1:2:3 palette z\n");
        for (int i = 0; i <= N; i++) {
          fprintf(gnuplot, "%f %f %f\n", x[i], y[i], color[i]);
        }
        fprintf(gnuplot, "e\n");
        _pclose(gnuplot);

        printf("pi value = %f", 4 * (float)c / N);
    }

    FILE* gnuplot = _popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set title 'Error of Estimation\n");
    fprintf(gnuplot, "set xlabel 'x axis'\n");
    fprintf(gnuplot, "set ylabel 'y axis'\n");
    fprintf(gnuplot, "set yrange [-0.051:0.301]\n");
    fprintf(gnuplot, "  set style line 5 lt rgb 'blue' lw 3 pt 6\n");
    fprintf(gnuplot, "plot '-' using 1 with linespoints ls 5\n");
    for (int i = 0; i < 30; i++) {
        fprintf(gnuplot, "%f\n", error[i]);
    }
    fprintf(gnuplot, "e\n");
    _pclose(gnuplot);
}


void estimateIntegral() {
    int maxPoints[30];
    double error[30];
    for (int i = 1; i < 31; i++) {
        if (i < 10)
            maxPoints[i - 1] = i * 333;
        else if (i < 20)
            maxPoints[i - 1] = i * 3333;
        else
            maxPoints[i - 1] = i * 66666;
    }

    for (int j = 0; j < 30; j++) {
        int N = maxPoints[j];
        float a = -5;
        float b = 5;
        float sum = 0;
        float exact = 0.921930586097;

        for (int i = 0; i < N; i++) {
            double x = getPointInRange(a, b);
            double y = sin(2 * x + 1) * cos(5 * x - 1) * exp(0.3 * x);
            sum += y;
        }
        float estimation = (b - a) * sum / N;
        printf("%f\n", (b - a) * sum / N);

        error[j] = fabs(exact - estimation);
        printf("error = %f\n", error[j]);
    }
    FILE* gnuplot = _popen("gnuplot -persist", "w");
    fprintf(gnuplot, "set title 'Error of Estimation\n");
    fprintf(gnuplot, "set xlabel 'x axis'\n");
    fprintf(gnuplot, "set ylabel 'y axis'\n");
    fprintf(gnuplot, "set yrange [-0.051:0.301]\n");
    fprintf(gnuplot, "plot '-' using 1 with linespoints\n");
    for (int i = 0; i < 30; i++) {
        fprintf(gnuplot, "%f\n", error[i]);
    }
    fprintf(gnuplot, "e\n");
    _pclose(gnuplot);
}

int main()
{
    estimatePi();
    estimateIntegral();
    return 0;
}