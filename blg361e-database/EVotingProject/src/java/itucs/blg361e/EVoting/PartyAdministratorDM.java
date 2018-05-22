/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;



/**
 *
 * @author Fikret
 */
public class PartyAdministratorDM {
    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;
    
    public PartyAdministratorDM()
    {
        psm = new PostgreSqlManager();
    }
    
    public static void connect(){
    PartyAdministratorDM.psm = new PostgreSqlManager();
    PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
    }
    public static void createTable(){
        try{
                connect();
                if(!psm.doesTableExists("PARTYADMINISTRATOR"))
                {
                    Statement state = PartyAdministratorDM.dbConnection.createStatement();
                    String query= "CREATE TABLE PARTYADMINISTRATOR (USERNAME VARCHAR(80) PRIMARY KEY REFERENCES USERS(USERNAME) ON DELETE CASCADE ON UPDATE CASCADE,"
                            + "PARTYTITLE VARCHAR(80),"
                            + "ELECTIONID INTEGER,"
                            + "FOREIGN KEY(PARTYTITLE,ELECTIONID) REFERENCES PARTY(TITLE,ELECTIONID) ON UPDATE CASCADE)";                    
                    state.executeQuery(query);
                    state.close(); 
                    PartyAdministratorDM.dbConnection.close();
                }
            } catch (SQLException ex) {
                Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
            }catch(Exception ex){
                Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
        }    
    }
     public static void addPartyAdmin(PartyAdministrator admin){
        
        try{
            connect();
            String query= "INSERT INTO PARTYADMINISTRATOR (USERNAME, PARTYTITLE, ELECTIONID) VALUES(?, ?, ?)";
            PreparedStatement state = PartyAdministratorDM.dbConnection.prepareStatement(query);
            state.setString(1,admin.getUserName());
            state.setString(2, admin.getPartyTitle());
            state.setInt(3,admin.getElectionId());
            state.executeUpdate();
            PartyAdministratorDM.dbConnection.close();
        }  
        catch(SQLException except){
            throw new UnsupportedOperationException(except.getMessage());
        }
    }
     public static void deletePartyAdmin(PartyAdministrator admin){
        try{
            PartyAdministratorDM.psm = new PostgreSqlManager();
            PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query= "DELETE FROM PARTYADMINISTRATOR WHERE(USERNAME = ?)";
            PreparedStatement state = PartyAdministratorDM.dbConnection.prepareStatement(query);
            state.setString(1,admin.getUserName());
            state.executeUpdate();   
            state.close();
            PartyAdministratorDM.dbConnection.close();
        }  
        catch(SQLException except){
            throw new UnsupportedOperationException(except.getMessage());
        }    
    }
    public static void updatePartyAdmin(PartyAdministrator admin) {
        try{
            PartyAdministratorDM.psm = new PostgreSqlManager();
            PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query= "UPDATE PARTYADMINISTRATOR SET PARTYTITLE = ?, ELECTIONID = ? WHERE(USERNAME=?)";
            PreparedStatement state = PartyAdministratorDM.dbConnection.prepareStatement(query);
            state.setString(1, admin.getPartyTitle());
            state.setInt(2, admin.getElectionId());
            state.setString(3,admin.getUserName());
            state.executeUpdate();   
            state.close();
            PartyAdministratorDM.dbConnection.close();
        }  
        catch(SQLException e){
            throw new UnsupportedOperationException(e.getMessage());
        }    
    }
    public static ArrayList<PartyAdministrator> getPartyAdministrator() {
        try {
            PartyAdministratorDM.psm = new PostgreSqlManager();
            ArrayList<PartyAdministrator> partyAdmin = new ArrayList<PartyAdministrator>();
            PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "SELECT * FROM PARTYADMINISTRATOR";
            Statement statement = PartyAdministratorDM.dbConnection.createStatement();
            ResultSet rs = statement.executeQuery(query);
            while(rs.next())
            {
                PartyAdministrator admin = new PartyAdministrator();
                admin.setUserName(rs.getString("USERNAME"));
                admin.setPartyTitle(rs.getString("PARTYTITLE"));
                admin.setElectionId(rs.getInt("ELECTIONID"));
                partyAdmin.add(admin);
            }
            rs.close();
            statement.close();
            PartyAdministratorDM.dbConnection.close();
            
            return partyAdmin;
        } catch (SQLException ex) {
            Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    
    public static PartyAdministrator getOneAdmin(String userName) {
        PartyAdministrator admin = null;

        try {
            PartyAdministratorDM.psm = new PostgreSqlManager();
            PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");

            String query = "SELECT * FROM PARTYADMINISTRATOR WHERE(USERNAME = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, userName);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                admin = new PartyAdministrator();
                admin.setUserName(rs.getString("USERNAME"));
                admin.setPartyTitle(rs.getString("PARTYTITLE"));
                admin.setElectionId(rs.getInt("ELECTIONID"));
            }

            rs.close();
            statement.close();
            dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return admin;
        }
    }
    
    public ResultSet searchPartyAdmin() {
        try{
        connect();
        String query= "SELECT * FROM PARTYADMINISTRATOR";
        Statement state;
        state = this.dbConnection.createStatement();
        state.executeQuery(query);
        ResultSet r = state.getResultSet(); 


        //this.db.close();
        return r;
        }catch (SQLException ex) {
                Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
                return null;
        } 
    }
    public static ArrayList<PartyAdministrator> getPartyAdministratorWithParty(String partyTitle, Integer electionId) {
        try {
            PartyAdministratorDM.psm = new PostgreSqlManager();
            ArrayList<PartyAdministrator> partyAdmin = new ArrayList<PartyAdministrator>();
            PartyAdministratorDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "SELECT * FROM PARTYADMINISTRATOR WHERE(PARTYTITLE = ? AND ELECTIONID = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, partyTitle);
            statement.setInt(2, electionId);
            ResultSet rs = statement.executeQuery();
            while(rs.next())
            {
                PartyAdministrator admin = new PartyAdministrator();
                admin.setUserName(rs.getString("USERNAME"));
                admin.setPartyTitle(rs.getString("PARTYTITLE"));
                admin.setElectionId(rs.getInt("ELECTIONID"));
                partyAdmin.add(admin);                
            }
            rs.close();
            statement.close();
            PartyAdministratorDM.dbConnection.close();
            
            return partyAdmin;
        } catch (SQLException ex) {
            Logger.getLogger(PartyAdministratorDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}
