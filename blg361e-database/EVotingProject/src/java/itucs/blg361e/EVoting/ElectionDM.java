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
 * @author OZAN
 */
public class ElectionDM {
    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;
    
    public ElectionDM()
    {
        psm = new PostgreSqlManager();
    }
    
    public static void createElectionTable()
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            
            if(!psm.doesTableExists("ELECTION"))
            {
                Statement statement = dbConnection.createStatement();
                String createTable = "CREATE TABLE ELECTION(electionID INTEGER PRIMARY KEY,"
                        + "startDateOfElection TIMESTAMP NOT NULL,"
                        + "finishDateOfElection TIMESTAMP NOT NULL,"
                        + "lastDateOfAddingCandidate TIMESTAMP NOT NULL)";
                statement.executeQuery(createTable);
                statement.close();
                ElectionDM.dbConnection.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        }  
    }
    
    public static void addElection(Election election)
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String maxId = "(SELECT electionID from election ORDER BY electionID DESC)";
            Statement maxIDstatement = ElectionDM.dbConnection.createStatement();
            ResultSet rs = maxIDstatement.executeQuery(maxId);
            if(rs.next())
                election.setElectionID(rs.getInt("electionid") + 1);
            else
                election.setElectionID(1);
            rs.close();
            
            String query = "INSERT INTO ELECTION (electionID,"
                    + " startDateOfElection, finishDateOfElection, lastDateOfAddingCandidate)"
                    + " VALUES(?, ?, ?, ?)";
            PreparedStatement statement = ElectionDM.dbConnection.prepareStatement(query);
            statement.setInt(1, election.getElectionID());
            statement.setTimestamp(2, election.getStartDateOfElection());
            statement.setTimestamp(3, election.getFinishDateOfElection());
            statement.setTimestamp(4, election.getLastDateOfAddingCandidate());
            statement.executeUpdate();
            statement.close();
            ElectionDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void deleteElection(Election election)
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "DELETE FROM ELECTION WHERE (electionID = ?)";
            PreparedStatement statement = ElectionDM.dbConnection.prepareStatement(query);
            statement.setInt(1, election.getElectionID());
            statement.executeUpdate();
            statement.close();
            ElectionDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void updateElection(Election election)
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "UPDATE ELECTION SET startDateOfElection = ?,"
                    + " finishDateOfElection = ?, lastDateOfAddingCandidate = ?"
                    + " WHERE (electionID = ?)";
            PreparedStatement statement = ElectionDM.dbConnection.prepareStatement(query);
            statement.setTimestamp(1, election.getStartDateOfElection());
            statement.setTimestamp(2, election.getFinishDateOfElection());
            statement.setTimestamp(3, election.getLastDateOfAddingCandidate());
            statement.setInt(4, election.getElectionID());
            statement.executeUpdate();
            statement.close();
            ElectionDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static ArrayList<Election> getElections()
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ArrayList<Election> elections = new ArrayList<Election>();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "SELECT * FROM election";
            Statement statement = ElectionDM.dbConnection.createStatement();
            ResultSet rs = statement.executeQuery(query);
            while(rs.next())
            {
                Election election = new Election();
                election.setElectionID(rs.getInt("electionid"));
                election.setStartDateOfElection(rs.getTimestamp("startdateofelection"));
                election.setFinishDateOfElection(rs.getTimestamp("finishdateofelection"));
                election.setLastDateOfAddingCandidate(rs.getTimestamp("lastdateofaddingcandidate"));
                elections.add(election);
            }
            rs.close();
            statement.close();
            ElectionDM.dbConnection.close();
            
            return elections;
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    
    
    /* 
     * 0 for startDateOfElection
     * 1 for lastDateOfElection
     * 2 for lastDateOfAddingCandidate
    */
    public static ArrayList<Election> getElections(Timestamp currentDate, int queryForWhat, int ordering)
    {
        try {
            ElectionDM.psm = new PostgreSqlManager();
            ArrayList<Election> elections = new ArrayList<Election>();
            ElectionDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String whichDate = "";
            switch(queryForWhat)
            {
                case 0:
                    whichDate = "startDateOfElection";
                    break;
                case 1:
                    whichDate = "finishDateOfElection";
                    break;
                case 2:
                    whichDate = "lastDateOfAddingCandidate";
                    break;
                default:
                    whichDate = "startDateOfElection";
            }
            
            String order = (ordering == 0) ? "ASC" : "DESC";
            String query = "SELECT * FROM election WHERE(" + whichDate + " > ?) ORDER BY " 
                    + whichDate + " " + order;
            PreparedStatement statement = ElectionDM.dbConnection.prepareStatement(query);
            statement.setTimestamp(1, currentDate);
            ResultSet rs = statement.executeQuery();
            while(rs.next())
            {
                Election election = new Election();
                election.setElectionID(rs.getInt("electionid"));
                election.setStartDateOfElection(rs.getTimestamp("startdateofelection"));
                election.setFinishDateOfElection(rs.getTimestamp("finishdateofelection"));
                election.setLastDateOfAddingCandidate(rs.getTimestamp("lastdateofaddingcandidate"));
                elections.add(election);
            }
            rs.close();
            statement.close();
            ElectionDM.dbConnection.close();
            
            return elections;
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}
