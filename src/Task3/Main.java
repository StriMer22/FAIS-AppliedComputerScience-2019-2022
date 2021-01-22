package Task3;

public class Main {
    public static void main(String[] args) {
        PoissonArrival poissonArrival = new PoissonArrival();
        System.out.println("Wpisz lambde: ");
        double mean = poissonArrival.N();
        System.out.println("Wpisz N liczb: ");
        int n = poissonArrival.N();
        for (int i = 0; i < n; i++){
            System.out.println(poissonArrival.poisson(mean));
        }
    }
}