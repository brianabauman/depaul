package test;

import java.sql.*;
import java.io.*;

public class ZipCode {
	
	
    public static void main(String[] args) throws java.sql.SQLException
    {	
	    try {
			//set up connection
			Class.forName("oracle.jdbc.driver.OracleDriver");
			String url = "jdbc:oracle:thin:@acadoradbprd01.dpu.depaul.edu:1521:ACADPRD0";
			Connection conn = DriverManager.getConnection(url, "BBAUMAN5", "cdm1901319");
			
	    	insertZipCodes(conn);
	    	retrieveRestaurantLocations(conn);
	    	
    		conn.close();
    	} catch (Exception ex) { ex.printStackTrace(); }
    }
    
    private static void insertZipCodes(Connection conn) {
    	try {		
    		//read input CSV for values
			String workingDir = System.getProperty("user.dir");
    		BufferedReader br = new BufferedReader(new FileReader(workingDir + "/ChIzipcode.csv"));
    		br.readLine();
    		String line = br.readLine(); //read twice to skip headers
    		
    		while (line != null) {
    			String[] values = line.replace("\"", "").split(",");
    			if (values.length != 7) throw new Exception("Row contains unexpected number of values: " + line + ".");
    			
    			//insert values into the ZipCode table
    			PreparedStatement insertStatement = conn.prepareStatement("INSERT INTO ZipCode VALUES (?, ?, ?, ?, ?, ?, ?)");
    			insertStatement.setInt(1, Integer.parseInt(values[0]));
    			insertStatement.setString(2, values[1]);
    			insertStatement.setString(3, values[2]);
    			insertStatement.setFloat(4,  Float.parseFloat(values[3]));
    			insertStatement.setFloat(5,  Float.parseFloat(values[4]));
    			insertStatement.setInt(6, Integer.parseInt(values[5]));
    			insertStatement.setInt(7,  Integer.parseInt(values[6]));
    			insertStatement.executeQuery();
    			
    			//read next line
    			line = br.readLine();
    		}
    		
    		br.close();
    	} catch (Exception ex) { ex.printStackTrace(); }
    }
    
    private static void retrieveRestaurantLocations(Connection conn) {
    	try {
    		String query = "SELECT A.name" + 
    				       "     , A.zipcode" + 
    				       "     , B.latitude" + 
    				       "     , B.longitude " + 
    				       "FROM Restaurant_Locations A" + 
    				       "   , ZipCode B " + 
    				       "WHERE B.zip = A.zipcode";
    		Statement selectStatement = conn.createStatement();
    		ResultSet results = selectStatement.executeQuery(query);
    		
    		while(results.next()) {
    			String name = results.getString("name");
    			int zipcode = results.getInt("zipcode");
    			float latitude = results.getFloat("latitude");
    			float longitude = results.getFloat("longitude");
    			
    			System.out.println(name + ", " + zipcode + ", \"" + latitude + ", \"" + longitude + "\"");
    		}
    		
    	} catch (Exception ex) { ex.printStackTrace(); }
    }
}
