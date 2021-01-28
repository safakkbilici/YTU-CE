
import java.sql.*;
import java.io.*;
/**
 * @author furkan
 * Soru: "ProductX" projesinde kac kisinin calistigini ve bu calisanlarin ortalama maasini bulunuz.
 */
public class Soru_4 {

    public static void main (String args []) throws SQLException, IOException {
        String user, pass;
        user = "postgres";
        pass = "1234";
        Connection conn =
	DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", user,pass);
        
               
        String query =  "SELECT COUNT(*), AVG(salary) FROM employee e, project p, works_on w" +
                        " WHERE e.ssn = w.essn AND p.pnumber = w.pno AND pname = 'ProductX'";

        Statement s = conn.createStatement();
        ResultSet r = s.executeQuery(query);
        
        while (r.next()) {
            int count = r.getInt(1);
            double ort_maas = r.getDouble(2);
            System.out.println(count + " " + ort_maas);
        }
        
        s.close();
        conn.close();
    }               
}