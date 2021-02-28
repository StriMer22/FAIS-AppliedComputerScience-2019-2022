package ProbabilityAndStatistics.Task2;

public class Rand {
    public static double rand() {
        while (true) {
            double x = (1.0 - Math.random()) * 4 - 1;
            double y = Math.random() / 3;
            if (x > -1 && x <= 0) { // (-1, 0], y <= x/3 + 1/3
                if (y <= x / 3 + 1.0 / 3) return x;
            } else if (x > 2) { // (-2, 3], y <= -x/3 + 1
                if (y <= -x / 3 + 1.0) return x;
            } else // 0 < x <= 2
                return x;
        }
    }
    
}
