package Task1;

public class Main {
    public static void main(String[] args) {
        Rand rand = new Rand();
        Cards cards = new Cards();
        // Podpunkt A
        for (int i = 0; i < 5; i++){
            System.out.println(rand.randomize());
        }
        System.out.println();
        // Podpunkt B
        for (int i = 1; i <= 3; i++){
            System.out.println("Draw the " + i + " card: " + cards.getCard());
        }
        System.out.println();
        // Podpunkt C
            cards.frequency();
    }
}
