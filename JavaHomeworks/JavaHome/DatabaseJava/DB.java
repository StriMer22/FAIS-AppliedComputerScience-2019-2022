package JavaHome.DatabaseJava;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.*;

public class DB {
    private Connection conn = null;
    private Statement stmt = null;
    private ResultSet rs = null;
    private PreparedStatement pstmt = null;
    private final Book book = new Book();

    public void connect() {
        try {
            conn = DriverManager.getConnection("jdbc:mysql://db4free.net/javasql2020", "user", "password");

        } catch (SQLException ex) {
            // handle any errors
            System.out.println("SQLException: " + ex.getMessage());
            System.out.println("SQLState: " + ex.getSQLState());
            System.out.println("VendorError: " + ex.getErrorCode());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void listNames() throws NullPointerException {
        try {

            stmt = conn.createStatement();

            // Wyciagamy wszystkie pola z kolumny name
            // znajdujące się w tabeli users
            rs = stmt.executeQuery("SELECT author FROM books");

            while (rs.next()) {
                String name = rs.getString(1);
                System.out.println("Autor: " + name);
            }
        } catch (SQLException ex) {
            // handle any errors

        } finally {
            // zwalniamy zasoby, które nie będą potrzebne
            if (rs != null) {
                try {
                    rs.close();
                } catch (SQLException ignored) {
                } // ignore
                rs = null;
            }

            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException ignored) {
                } // ignore

                stmt = null;
            }
        }
    }

    public void addUser() {
        try {

            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

            System.out.println("Enter isbn, title, author and year");
            book.isbn = in.readLine();
            book.title = in.readLine();
            book.author = in.readLine();
            book.year = Integer.parseInt(in.readLine());

            pstmt = conn.prepareStatement("INSERT INTO books VALUES (?,?,?,?)");

            pstmt.setString(1, book.isbn);
            pstmt.setString(2, book.title);
            pstmt.setString(3, book.author);
            pstmt.setInt(4, book.year);

            int i = pstmt.executeUpdate();
            System.out.println(i + "records inserted");
        }catch (SQLException | IOException se){
            se.printStackTrace();
        }

    }

    public void displayBase(){
    try{
        stmt = conn.createStatement();
        rs = stmt.executeQuery("SELECT * from books");
        while (rs.next()){
            book.isbn = rs.getString("isbn");
            book.title = rs.getString("title");
            book.author = rs.getString("author");
            book.year = rs.getInt("YEAR");

            if (book.getTitle().length() < 35 && book.getAuthor().length() < 35){
                book.title += " ".repeat(35 - book.getTitle().length());
                book.author += " ".repeat(35 - book.getAuthor().length());
            }
            System.out.println("-".repeat(100));
            String s = String.format("%s \t\t%s %s %s " ,book.getIsbn(), book.getTitle(),book.getAuthor(),book.getYear());
            System.out.println(s);
            System.out.println("-".repeat(100));

        }

    }catch (SQLException se){
        se.printStackTrace();
        }
    }
    
    public void search() throws IOException, SQLException {
        System.out.println("Press 1 to search using isbn number\nPress 2 to search using lastname");
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String choice = in.readLine();

        switch (choice) {
            case "1" -> {
                System.out.println("Enter isbn:");
                String search = in.readLine();
                pstmt = conn.prepareStatement("SELECT * from books where isbn = ? ");
                pstmt.setString(1,search);

            } case "2" ->{
                System.out.println("Enter author's lastname:");
                String search = in.readLine();
                String ksearch = "'%"+search+"%'";
                pstmt = conn.prepareStatement("SELECT * from books where author like  " +ksearch );
                }
            }
        rs = pstmt.executeQuery();
        while(rs.next()) {
            book.author = rs.getString("author");
            book.title = rs.getString("title");
            book.isbn = rs.getString("isbn");
            book.year = rs.getInt("YEAR");
            System.out.println("-".repeat(50));
            System.out.println(book.author + "   " + book.title + "   " + book.isbn + "   " + book.year);
            System.out.println("-".repeat(50));
        }

        }

    public boolean isConnected(){
        try {
                if (!conn.isClosed() || conn!=null)
                    System.out.println("Database is connected;)");
                    return true;

        }catch (SQLException | NullPointerException se){
            se.printStackTrace();
        }
        System.out.println("Database disconected:(");
        return false;

    }

    public int checkConnection()
    {
        if (!isConnected()) {
            int i = 0;
            while (i < 3) {
                connect();
                i++;
            }
            if (!isConnected()) {
                return -1;
            }
        }
        return 1;
    }



}
