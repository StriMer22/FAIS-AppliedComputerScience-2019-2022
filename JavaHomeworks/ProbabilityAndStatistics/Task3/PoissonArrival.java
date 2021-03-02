package ProbabilityAndStatistics.Task3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

public class PoissonArrival {
    int N() {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        int number = 0;
        try {
            number = Integer.parseInt(bf.readLine());
        } catch (IOException ioException){
            ioException.printStackTrace();
        }
        return number;
    }

    int poisson(double mean) {
        Random random = new Random();
        int k = 0;
        double q = Math.exp(-mean);
        double s = q; double p = q;
        double u = random.nextDouble();
        while (u > s) {
            k++;
            p *= mean / k;
            s += p;
        }
        return k;
    }
}
