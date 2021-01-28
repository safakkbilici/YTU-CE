

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.table.DefaultTableModel;

class TDPanel extends JPanel{
    private final JLabel inputLbl   = new JLabel("Bir departman numarasi giriniz: ");
    private final JTextField txt    = new JTextField(2);
    private final JButton btn1      = new JButton("Dept. Bilgisi Goster");
    private final JButton btn2      = new JButton("Calisan Ekle");
    private final JButton btn3      = new JButton("Kapat");
    private final JLabel outputLbl  = new JLabel(" ");
    private final DefaultTableModel calisanlar;
    private Connection conne;
    
    public TDPanel(Connection conn){
		
	Object[] columnNames = {"Ad", "Soyad", "SSN", "DTarihi", "Address", "Cinsiyet", "Maas"};
	calisanlar = new DefaultTableModel(columnNames, 0);
	JTable tbl = new JTable(calisanlar);
	JScrollPane sp = new JScrollPane(tbl);
	add(inputLbl);	
        add(txt);	
        add(btn1);	
        add(btn2);	
        add(btn3);
	add(outputLbl); 
        add(sp);
		
	conne = conn;
	
		
	btn1.addActionListener(new ActionListener(){			
            public void actionPerformed(ActionEvent arg0) {
		goster();
            }			 
	});			
		
	btn2.addActionListener(new ActionListener(){			
            public void actionPerformed(ActionEvent arg0) {
		ekle();
            }			 
	});	
		
	btn3.addActionListener(new ActionListener(){			
            public void actionPerformed(ActionEvent arg0){
		try{
                    conne.close();
		}catch(SQLException e){
                    e.printStackTrace();
		}
		setVisible(false);
		System.exit(0);
            }			 
	});	
    }
		
    private void goster()  {
	int dnum = Integer.parseInt(txt.getText());
	String query ="SELECT dname, fname, lname FROM employee, department WHERE ssn = mgrssn AND dnumber = " + dnum;
	PreparedStatement p;
	
        try{
            p = conne.prepareStatement(query);
            ResultSet r;
            r = p.executeQuery();
            calisanlar.setRowCount(0);
	        
	    if (!r.next ()){
                outputLbl.setText("Boyle bir departman bulunmamaktadir! ");
            }else{
		String dname = r.getString(1);
		String y_fname = r.getString(2);
		String y_lname = r.getString(3);
		outputLbl.setText("Departman ismi: " + dname + " Yoneticisinin ismi: " + y_fname + " " + y_lname);
		p.close();
				
		String query2 = "SELECT * FROM employee WHERE dno = " + dnum;
		PreparedStatement p2 = conne.prepareStatement(query2);
		ResultSet r2 = p2.executeQuery();
				
		while (r2.next()){
		    String fname = r2.getString(1);
                    String lname = r2.getString(3);      	
		    String ssn = r2.getString(4);
		    String bdate = r2.getString(5);
		    String address = r2.getString(6);
		    String sex = r2.getString(7);
		    String salary = r2.getString(8);
		            
		    Object[] satir ={fname, lname, ssn, bdate, address, sex, salary};
		    calisanlar.addRow(satir);
		}
		p2.close();
            }
	}catch(SQLException e){
            e.printStackTrace();
	}				
    }
	
    private void ekle()  {
	String ad       = JOptionPane.showInputDialog("Calisan adini giriniz");
	String soyad    = JOptionPane.showInputDialog("Calisan soyadini giriniz");
	String ssn      = JOptionPane.showInputDialog("Calisan SSN sini giriniz");
	String dtarih   = JOptionPane.showInputDialog("Calisan dogum tarihini YYYY-MM-DD formatinda giriniz");
	String address  = JOptionPane.showInputDialog("Calisan adresini giriniz");
	String sex      = JOptionPane.showInputDialog("Calisan cinsiyetini giriniz");
	String maas     = JOptionPane.showInputDialog("Calisan maasini giriniz");
	String dno      = JOptionPane.showInputDialog("Calisanin departman numarasini giriniz");
		
	String query = "INSERT INTO employee(fname, lname, ssn, bdate, address, sex, salary, dno) " +
                       "VALUES( '" + ad + "', '" + soyad + "', '" + ssn + "' ,'" + dtarih + "', '" + address + 
                       "', '" + sex + "', " + maas + ", " + dno + " )";
                
        System.out.println(query);

	Statement s = null;
        try {
            s = conne.createStatement();
            s.executeUpdate(query);
            conne.setAutoCommit(false);
            conne.commit();
            s.close();
	}catch(SQLException e){
            e.printStackTrace();
	}	
    }
}