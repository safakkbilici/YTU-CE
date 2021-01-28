
import java.sql.*;
import java.io.*;
/**
 * @author furkan
 * Soru: "DatabaseSystems" projesinde calisan kadin iscilerin ad, soyad ve maaslarını listeleyin.
 */
public class Soru_1 {
    public static void main (String args []) throws SQLException, IOException {
        String user, pass;
        user = "postgres";
        pass = "1234";
        Connection conn =
	DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", user,pass);
        
               
        String query = "SELECT fname, lname, salary FROM employee e, works_on w, project p" 
                     + " WHERE w.essn=e.ssn AND w.pno=p.pnumber AND e.sex='F' AND"
                     + " pname='DatabaseSystems'";
        
             

        Statement s = conn.createStatement();
        ResultSet r = s.executeQuery(query);
        
        while (r.next()) {
            String fname = r.getString("fname");
            String lname = r.getString(2);
            double salary = r.getDouble(3);
            System.out.println(fname + " " + lname + " " + salary);
        }
        s.close();
        conn.close();
    }          
}