/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.sql.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Fikret
 */
public class PartyDM {

    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;

    public PartyDM() {
        psm = new PostgreSqlManager();
    }

    public static void connect() {
        PartyDM.psm = new PostgreSqlManager();
        PartyDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
    }

    public static void createTable() {
        try {
            connect();
            if (!psm.doesTableExists("PARTY")) {
                Statement state = PartyDM.dbConnection.createStatement();
                String query = "CREATE TABLE PARTY (TITLE VARCHAR(80) NOT NULL, YEAR NUMERIC(4), PARTYLEADER VARCHAR(80) NOT NULL, PARTYPRINCIPLE VARCHAR(5000) ,ELECTIONID INTEGER, PRIMARY KEY(TITLE,ELECTIONID))";
                state.executeQuery(query);
                state.close();
                PartyDM.dbConnection.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void addParty(Party admin) {

        try {
            connect();
            String query = "INSERT INTO PARTY (TITLE,YEAR,PARTYLEADER,PARTYPRINCIPLE,ELECTIONID) VALUES(?,?,?,?,?)";
            PreparedStatement state = PartyDM.dbConnection.prepareStatement(query);
            state.setString(1, admin.getTitle());
            state.setInt(2, admin.getYear());
            state.setString(3, admin.getPartyLeader());
            state.setString(4, admin.getPartyPrinciples());
            state.setInt(5, admin.getElectionId());
            state.executeUpdate();
            PartyDM.dbConnection.close();
        } catch (SQLException except) {
            throw new UnsupportedOperationException(except.getMessage());
        }
    }

    public static void deleteParty(Party admin) {
        try {
            connect();
            String query = "DELETE FROM PARTY WHERE(TITLE = ? AND ELECTIONID = ?)";
            PreparedStatement state = PartyDM.dbConnection.prepareStatement(query);
            state.setString(1, admin.getTitle());
            state.setInt(2, admin.getElectionId());
            state.executeUpdate();
            state.close();
            PartyDM.dbConnection.close();
        } catch (SQLException except) {
            throw new UnsupportedOperationException(except.getMessage());
        }
    }

    public static void updateParty(Party admin) {
        try {
            PartyDM.psm = new PostgreSqlManager();
            PartyDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "UPDATE PARTY SET YEAR = ?, PARTYLEADER = ?, PARTYPRINCIPLE=? WHERE(TITLE=? AND ELECTIONID = ?)";
            PreparedStatement state = PartyDM.dbConnection.prepareStatement(query);
            state.setInt(1, admin.getYear());
            state.setString(2, admin.getPartyLeader());
            state.setString(3, admin.getPartyPrinciples());
            state.setString(4, admin.getTitle());
            state.setInt(5, admin.getElectionId());
            state.executeUpdate();
            state.close();
            PartyDM.dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }

    public static ArrayList<Party> getParty() {
        try {
            PartyDM.psm = new PostgreSqlManager();
            ArrayList<Party> partys = new ArrayList<Party>();
            PartyDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM PARTY";
            Statement statement = PartyDM.dbConnection.createStatement();
            ResultSet rs = statement.executeQuery(query);
            while (rs.next()) {
                Party party = new Party();
                party.setTitle(rs.getString("TITLE"));
                party.setYear(rs.getInt("YEAR"));
                party.setPartyLeader(rs.getString("PARTYLEADER"));
                party.setPartyPrinciples(rs.getString("PARTYPRINCIPLE"));
                party.setElectionId(rs.getInt("ELECTIONID"));
                partys.add(party);
            }
            rs.close();
            statement.close();
            PartyDM.dbConnection.close();

            return partys;
        } catch (SQLException ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static Party getOneParty(String title, Integer electionId) {
        Party party = null;

        try {
            PartyDM.psm = new PostgreSqlManager();
            PartyDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM PARTY WHERE(TITLE = ? AND ELECTIONID = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, title);
            statement.setInt(2, electionId);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                party = new Party();
                party.setTitle(rs.getString("TITLE"));
                party.setYear(rs.getInt("YEAR"));
                party.setPartyLeader(rs.getString("PARTYLEADER"));
                party.setPartyPrinciples(rs.getString("PARTYPRINCIPLE"));
                party.setElectionId(rs.getInt("ELECTIONID"));
            }

            rs.close();
            statement.close();
            dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return party;
        }
    }

    public ResultSet searchParty() {
        try {
            connect();
            String query = "SELECT * FROM PARTY";
            Statement state;
            state = this.dbConnection.createStatement();
            state.executeQuery(query);
            ResultSet r = state.getResultSet();


            //this.db.close();
            return r;
        } catch (SQLException ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static ArrayList<Party> getPartiesWithElectionId(Integer electionId) {

        try {
            PartyDM.psm = new PostgreSqlManager();
            ArrayList<Party> parties = new ArrayList<Party>();
            PartyDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM PARTY WHERE(ELECTIONID = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setInt(1, electionId);
            ResultSet rs = statement.executeQuery();
            while (rs.next()) {
                Party party = new Party();
                party.setTitle(rs.getString("TITLE"));
                party.setYear(rs.getInt("YEAR"));
                party.setPartyLeader(rs.getString("PARTYLEADER"));
                party.setPartyPrinciples(rs.getString("PARTYPRINCIPLE"));
                party.setElectionId(rs.getInt("ELECTIONID"));
                parties.add(party);
            }
            rs.close();
            statement.close();
            PartyDM.dbConnection.close();

            return parties;
        } catch (SQLException ex) {
            Logger.getLogger(PartyDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}
