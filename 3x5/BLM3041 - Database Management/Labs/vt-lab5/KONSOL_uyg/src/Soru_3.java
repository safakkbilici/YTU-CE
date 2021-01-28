
import java.sql.*;
import java.io.*;
/**
 * @author furkan
 * Soru: Her bir departmandaki calisanlarin sayisini bulup departman ismine gore alfabetik olarak listeleyin.
 */
public class Soru_3 {
    public static void main (String args []) throws SQLException, IOException {
        String user, pass;
        user = "postgres";
        pass = "1234";
        Connection conn =
	DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", user,pass);
        
        String query = "SELECT dname, COUNT(*) FROM department d, employee e" +
                       " WHERE d.dnumber = e.dno GROUP BY dname ORDER BY dname";

        Statement s = conn.createStatement();
        ResultSet r = s.executeQuery(query);
        
        while (r.next()) {
            String dname = r.getString(1);
            int count = r.getInt(2);
            System.out.println(dname + " " + count);
        }
        
        s.close();
        conn.close();
    }               
}