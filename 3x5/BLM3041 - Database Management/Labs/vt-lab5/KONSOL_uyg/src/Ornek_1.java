import java.sql.*;
import java.util.Scanner;
import java.io.*;
/**
 * @author furkan
 * bu ornekte, numarasi verilen bir calisanin isim ve maas bilgileri gosteriliyor
 */
public class Ornek_1 {
    public static void main (String args []) throws SQLException, IOException {

        Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", "postgres","1234");
        
        String query = "SELECT lname, salary FROM employee WHERE ssn = ?";
        PreparedStatement p = conn.prepareStatement(query);
        
        
        Scanner input = new Scanner(System.in); 
        System.out.print("Çalışanın SSN no'sunu giriniz: ");
        String ssn = input.nextLine(); 
        
        input.close();
       
        
        p.clearParameters();
        p.setString(1,ssn);
        
        ResultSet r = p.executeQuery();
        
        if (r.next ()) {
            String lname = r.getString(1);
            double salary = r.getDouble("salary"); //tablodaki sütun ismini yazdık.
            System.out.println(lname + " " + salary);
        }
        
        p.close();
        conn.close();
    }

    
}