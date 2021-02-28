package Task1;
import java.io.IOException;

public class Cards implements Card{
    int count = 0;
    int numberOfCardsDrawn = 0;

    String drawCard(){
        String card;
        int cardValue = (int) (rand.randomize()*13);
        int cardSuit = (int) (rand.randomize()*4);
        card = facevalue[cardValue] + " of " + suit[cardSuit];
        return card;
    }

    boolean checkCard (String card) {
        for(String drawnCard : drawnCards) {
            if(card.equals(drawnCard)) { // if this is true, then both strings are the same
                return true;
            }
        }
        return false; // if the code reaches this point, then the card has not been drawn yet
    }

    String getCard () {
        String card = drawCard();
        while (checkCard(card)) { // keep drawing until an undrawn card is found
            card = drawCard(); // draw a new card
        }
        drawnCards[numberOfCardsDrawn] = card;
        numberOfCardsDrawn++;
        return card;
    }

    void frequency(){
        double counter = 0;
        int N = 0;
        try {
            System.out.println("Enter the total number of draws: ");
            N = Integer.parseInt(bf.readLine());
        }catch (IOException ioException){
            ioException.printStackTrace();
        }
        String[] array = new String[3];
        for (double j = 1; j <= N; j++) {
            for (int i = 0; i < array.length; i++) {
                array[i] = getCard();
            }
            numberOfCardsDrawn = 0;
            for (String i : array) {
                if (i.contains("Clubs")) {
                    counter = 0;
                    break;
                } else {
                    counter = 1;
                }
            }
            count += counter;
            if (Math.abs(prob - (count/j)) < 0.001) {
                formatter.format("%.4f",(count/j));
                System.out.println("It takes " + (int)j + " draws to get probability of no clubs in 3 cards drawn equal to " + formatter);
                break;
            } else if (j == N){
                System.out.println("No such number of draws equal to probability " + prob + "\n" + "Repeat " + N + " draws");
                j = 1;
                count = 0;
            }
        }
    }
}