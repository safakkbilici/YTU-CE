
import java.sql.*;
import java.io.*;
/**
 * @author furkan
 * Soru: "Chicago" da bulunan departman(lar)da calisan iscilerin isim ve maas bilgilerini yazdirin.
 */
public class Soru_2 {
    public static void main (String args []) throws SQLException, IOException {
        String user, pass;
        user = "postgres";
        pass = "1234";
        Connection conn =
	DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", user,pass);
                
        String query = "SELECT fname, lname, salary FROM employee e," +
                       " dept_locations dl WHERE e.dno = dl.dnumber AND dlocation = 'Chicago'";

        Statement s = conn.createStatement();
        ResultSet r = s.executeQuery(query);
        
        while (r.next()) {
            String fname = r.getString(1);
            String lname = r.getString(2);
            double salary = r.getDouble(3);
            System.out.println(fname + " " + lname + " " + salary);
        }
        
        s.close();
        conn.close();
    }          
}