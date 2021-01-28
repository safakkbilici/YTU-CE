

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import javax.swing.*;

public class DepInfo {
    
    public static void main (String args []) throws SQLException, IOException {
        String user, pass;
	user = "postgres";
        pass = "1234";
        Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/company_db", user,pass);
        
	JFrame frame = new TDFrame(conn);
	frame.setVisible(true);
    }
}