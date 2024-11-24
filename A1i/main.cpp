#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <algorithm>


struct Circle {
    double x, y, r;
};

bool isInsideCircle(double x, double y, const Circle& circle) {
    return (pow(x - circle.x, 2) + pow(y - circle.y, 2)) <= pow(circle.r, 2);
}

double monteCarloEstimate(const Circle& c1, const Circle& c2, const Circle& c3, int N) {
    int M = 0;
    double minX = std::min({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
    double maxX = std::max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
    double minY = std::min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
    double maxY = std::max({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});

    double S_rec = (maxX - minX) * (maxY - minY);

    for (int i = 0; i < N; ++i) {
        double x = minX + (rand() / double(RAND_MAX)) * (maxX - minX);
        double y = minY + (rand() / double(RAND_MAX)) * (maxY - minY);

        if (isInsideCircle(x, y, c1) && isInsideCircle(x, y, c2) && isInsideCircle(x, y, c3)) {
            ++M;
        }
    }

    return (M / double(N)) * S_rec;
}

int main() {
    srand(time(0));

    Circle c1, c2, c3;
    std::cin >> c1.x >> c1.y >> c1.r;
    std::cin >> c2.x >> c2.y >> c2.r;
    std::cin >> c3.x >> c3.y >> c3.r;

    double estimatedArea = 0.0;
    int N = 1000000;
    estimatedArea = monteCarloEstimate(c1, c2, c3, N);

    std::cout << std::fixed << std::setprecision(6) << estimatedArea << std::endl;

    return 0;
}