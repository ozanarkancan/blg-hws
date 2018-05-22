/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Elector.ElectorDM;
import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author OZAN
 */
public class DatabaseDemoCreator {
    
    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;
    
    public static void initializeDemo()
    {
        createTables();
        loadTable("ELECTION");
        loadTable("PROVINCE");
        loadTable("USERS");
        loadTable("PARTY");
        loadTable("PARTYADMINISTRATOR");
        loadTable("CANDIDATE");
        loadTable("ELECTOR");
        loadTable("VOTE");
    }
    
    public static void createTables()
    {
        ElectionDM.createElectionTable();
        ProvinceDM.createTable();
        UserDM.createTable();
        PartyDM.createTable();
        PartyAdministratorDM.createTable();
        CandidateDM.createCandidateTable();    
        ElectorDM.createTable();
        VoteDM.createVoteTable();
    }
    
    public static void loadTable(String table)
    {
        try {
            DatabaseDemoCreator.psm = new PostgreSqlManager();
            DatabaseDemoCreator.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            
            Statement statement = DatabaseDemoCreator.dbConnection.createStatement();
            
            String query = "COPY " + table + " FROM 'C:\\Users\\OZAN\\Desktop\\BLG361E\\project\\EVotingProject\\src\\java\\itucs\\blg361e\\EVoting\\demoData\\" + table + ".txt'";
            
            statement.executeQuery(query);
            statement.close();
            DatabaseDemoCreator.dbConnection.close();            
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
        }  
    }
    
}
