package JavaHomeworks.DatabaseJava;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.SQLException;

public class Main {

    public static void main(String[] args) throws IOException, SQLException {
       DB database = new DB();
       database.connect();
       database.checkConnection();
       int input = MenuData();
        while (input != -1){
            switch (input) {
                case 1 -> {
                    System.out.println("Listing authors...");
                    database.listNames();
                }
                case 2 -> {
                    System.out.println("Adding author...");
                    database.addUser();
                }
                case 3 -> {
                    System.out.println("Displaying database...");
                    database.displayBase();
                }
                case 4 -> database.search();

                default -> System.out.println("Invalid input");
            }
            input = MenuData();
        }

    }

    public static int MenuData() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Select your option:");
        System.out.println("-------------------\n");
        System.out.println("Display the list of all authors by pressing 1");
        System.out.println("Add User by pressing 2");
        System.out.println("Display Database by pressing 3");
        System.out.println("Search database by pressing 4");
        System.out.println("Selection:");
        return Integer.parseInt(br.readLine());
    }

}



