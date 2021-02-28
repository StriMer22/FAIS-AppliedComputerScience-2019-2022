package Task1;
import java.util.Formatter;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public interface Card {
    Rand rand = new Rand();
    Formatter formatter = new Formatter();
    double prob = 0.413;
    BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
    String[] suit = {"Diamonds", "Hearts", "Spades", "Clubs"};
    String[] facevalue = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    String[] drawnCards = new String[52];
}
