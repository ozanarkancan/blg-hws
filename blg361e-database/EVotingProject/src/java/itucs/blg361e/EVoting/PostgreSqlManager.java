/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author OZAN
 */
public class PostgreSqlManager {
    private static Connection connection;
    
    public PostgreSqlManager()
    {
        connection = null;
    }
    public Connection getConnection()
    {
        try {
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection("jdbc:postgresql://localhost:5432/testdb", "user","password");
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(PostgreSqlManager.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(PostgreSqlManager.class.getName()).log(Level.SEVERE, null, ex);
        }
        return connection;   
    }
    
    public Connection getConnection(String url, String user, String password)
    {
        try {
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection(url, user, password);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(PostgreSqlManager.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(PostgreSqlManager.class.getName()).log(Level.SEVERE, null, ex);
        }
        return connection;
    }
    
    public boolean doesTableExists(String table) throws Exception
    {
        if(connection == null)
            throw new Exception("There is no connection.");
        else
        {
            try {
                boolean result = false;
                Statement statement = connection.createStatement();
                String tables = "SELECT * FROM pg_tables WHERE schemaname='public'";
                ResultSet results = statement.executeQuery(tables);
                while(results.next())
                {
                    if(table.equals(results.getString(2)))
                    {
                        result = true;
                        break;
                    }
                }
                results.close();
                statement.close();
                return result;
            } catch (SQLException ex) {
                Logger.getLogger(PostgreSqlManager.class.getName()).log(Level.SEVERE, null, ex);
                throw new Exception(ex.getMessage());
            }
        }
    }
}
