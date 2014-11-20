
double calcPiParallel() {
    const long n = 10000000;

    int i;
    double x, sum = 0.0;
    double h = 1.0 / (double) n;
#pragma omp parallel default(none) private(i,x) shared(h) reduction(+:sum)
    {
#pragma omp for schedule (auto)
        for (i = 0; i < n; ++i) {
//            printf("i: %d, thread: %d\n", i, omp_get_thread_num());
            x = (i + 0.5) * h;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }
    return h * sum;
}

double calcPi() {
    const long num_steps = 10000000;

    int i;
    double x, pi, sum = 0.0;
    double step = 1.0 / (double) num_steps;
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    return step * sum;
}