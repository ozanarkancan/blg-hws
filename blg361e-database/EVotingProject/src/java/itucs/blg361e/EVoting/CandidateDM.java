package itucs.blg361e.EVoting;

import java.sql.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author fikret
 */
public class CandidateDM {

    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;

    public CandidateDM() {
        psm = new PostgreSqlManager();
    }

    public static void connect() {
        CandidateDM.psm = new PostgreSqlManager();
        CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
    }

    public static void createCandidateTable() {
        try {
            connect();
            Statement state = CandidateDM.dbConnection.createStatement();
            String query = "CREATE TABLE CANDIDATE (TCNUMBER VARCHAR(15) PRIMARY KEY NOT NULL,"
                    + "NAME VARCHAR(80),"
                    + "USERNAME VARCHAR(80) REFERENCES USERS(USERNAME) ON UPDATE CASCADE,"
                    + "PARTYTITLE VARCHAR(80),"
                    + "ISINDEPENDENT BOOLEAN,"
                    + "ELECTIONID INTEGER,"
                    + "PROVINCEID INTEGER,"
                    + "FOREIGN KEY(PROVINCEID, ELECTIONID) REFERENCES PROVINCE(ID,ELECTIONID))";
            state.executeQuery(query);
            state.close();
            CandidateDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void addCan(Candidate can) {
        try {
            connect();
            String query = "INSERT INTO CANDIDATE (TCNUMBER,NAME,USERNAME,PARTYTITLE,ISINDEPENDENT,ELECTIONID,PROVINCEID) VALUES(?,?,?,?,?,?,?)";
            PreparedStatement state = CandidateDM.dbConnection.prepareStatement(query);
            state.setString(1, can.getTCnumber());
            state.setString(2, can.getName());
            state.setString(3, can.getUserName());
            state.setString(4, can.getPartyTitle());
            state.setBoolean(5, can.getIsIndependent());
            state.setInt(6, can.getElectionId());
            state.setInt(7, can.getProvinceId());
            state.executeUpdate();
            CandidateDM.dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }

    public static void deleteCan(Candidate can) {
        try {
            connect();
            String query = "DELETE FROM CANDIDATE WHERE(TCNUMBER = ?)";
            PreparedStatement state = CandidateDM.dbConnection.prepareStatement(query);
            state.setString(1, can.getTCnumber());
            state.executeUpdate();
            state.close();
            CandidateDM.dbConnection.close();
        } catch (SQLException except) {
            throw new UnsupportedOperationException(except.getMessage());
        }
    }

    public static void updateCan(Candidate can) {
        try {
            CandidateDM.psm = new PostgreSqlManager();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "UPDATE CANDIDATE SET NAME = ? , USERNAME=?, PARTYTITLE=?, ISINDEPENDENT=?, ELECTIONID=?,PROVINCEID=?  WHERE(TCNUMBER=?)";
            PreparedStatement state = CandidateDM.dbConnection.prepareStatement(query);
            state.setString(1, can.getName());
            state.setString(2, can.getUserName());
            state.setString(3, can.getPartyTitle());
            state.setBoolean(4, can.getIsIndependent());
            state.setInt(5, can.getElectionId());
            state.setInt(6, can.getProvinceId());
            state.setString(7, can.getTCnumber());
            state.executeUpdate();
            state.close();
            CandidateDM.dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        }
    }

    public static ArrayList<Candidate> getCandidate() {
        try {
            CandidateDM.psm = new PostgreSqlManager();
            ArrayList<Candidate> candidates = new ArrayList<Candidate>();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM CANDIDATE";
            Statement statement = CandidateDM.dbConnection.createStatement();
            ResultSet rs = statement.executeQuery(query);
            while (rs.next()) {
                Candidate can = new Candidate();
                can.setTCnumber(rs.getString("TCNUMBER"));
                can.setName(rs.getString("NAME"));
                can.setUserName(rs.getString("USERNAME"));
                can.setPartyTitle(rs.getString("PARTYTITLE"));
                can.setIsIndependent(rs.getBoolean("ISINDEPENDENT"));
                can.setElectionId(rs.getInt("ELECTIONID"));
                can.setProvinceId(rs.getInt("PROVINCEID"));
                candidates.add(can);
            }
            rs.close();
            statement.close();
            CandidateDM.dbConnection.close();

            return candidates;
        } catch (SQLException ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static Candidate getOneCandidate(String TCnumber) {
        Candidate candidate = null;

        try {
            CandidateDM.psm = new PostgreSqlManager();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM CANDIDATE WHERE(TCNUMBER = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, TCnumber);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                candidate = new Candidate();
                candidate.setTCnumber(rs.getString("TCNUMBER"));
                candidate.setName(rs.getString("NAME"));
                candidate.setUserName(rs.getString("USERNAME"));
                candidate.setPartyTitle(rs.getString("PARTYTITLE"));
                candidate.setIsIndependent(rs.getBoolean("ISINDEPENDENT"));
                candidate.setElectionId(rs.getInt("ELECTIONID"));
                candidate.setProvinceId(rs.getInt("PROVINCEID"));
            }

            rs.close();
            statement.close();
            dbConnection.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return candidate;
        }
    }

    public ResultSet searchCandidate() {
        try {
            connect();
            String query = "SELECT * FROM CANDIDATE";
            Statement state;
            state = this.dbConnection.createStatement();
            state.executeQuery(query);
            ResultSet r = state.getResultSet();
            return r;
        } catch (SQLException ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static ArrayList<Candidate> getCandidatesForProvince(Integer provinceID, Integer electionID, Integer isIndependent) {
        try {
            CandidateDM.psm = new PostgreSqlManager();
            ArrayList<Candidate> candidates = new ArrayList<Candidate>();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM CANDIDATE WHERE(PROVINCEID = ? AND ELECTIONID = ? AND ISINDEPENDENT = ?)";

            if (isIndependent == 2) {
                query = "SELECT * FROM CANDIDATE WHERE(PROVINCEID = ? AND ELECTIONID = ?)";
            }
            PreparedStatement statement = dbConnection.prepareStatement(query);

            statement.setInt(1, provinceID);
            statement.setInt(2, electionID);
            if (isIndependent != 2) {
                statement.setBoolean(3, isIndependent == 1);
            }



            ResultSet rs = statement.executeQuery();
            while (rs.next()) {
                Candidate can = new Candidate();
                can.setTCnumber(rs.getString("TCNUMBER"));
                can.setName(rs.getString("NAME"));
                can.setUserName(rs.getString("USERNAME"));
                can.setPartyTitle(rs.getString("PARTYTITLE"));
                can.setIsIndependent(rs.getBoolean("ISINDEPENDENT"));
                can.setElectionId(rs.getInt("ELECTIONID"));
                can.setProvinceId(rs.getInt("PROVINCEID"));
                candidates.add(can);
            }
            rs.close();
            statement.close();
            CandidateDM.dbConnection.close();

            return candidates;
        } catch (SQLException ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static ArrayList<Candidate> getCandidateWithPartyTitle(String partyTitle) {

        try {
            CandidateDM.psm = new PostgreSqlManager();
            ArrayList<Candidate> candidates = new ArrayList<Candidate>();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM CANDIDATE WHERE(PARTYTITLE = ?) ";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, partyTitle);
            ResultSet rs = statement.executeQuery();
            while (rs.next()) {
                Candidate can = new Candidate();
                can.setTCnumber(rs.getString("TCNUMBER"));
                can.setName(rs.getString("NAME"));
                can.setUserName(rs.getString("USERNAME"));
                can.setPartyTitle(rs.getString("PARTYTITLE"));
                can.setIsIndependent(rs.getBoolean("ISINDEPENDENT"));
                can.setElectionId(rs.getInt("ELECTIONID"));
                can.setProvinceId(rs.getInt("PROVINCEID"));
                candidates.add(can);
            }
            rs.close();
            statement.close();
            CandidateDM.dbConnection.close();

            return candidates;
        } catch (SQLException ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static Boolean getCandidateWithName(String name, Integer electionID) {
        try {
            CandidateDM.psm = new PostgreSqlManager();
            CandidateDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM CANDIDATE WHERE(NAME = ? AND ELECTIONID = ?)";
            PreparedStatement statement = dbConnection.prepareStatement(query);
            statement.setString(1, name);
            statement.setInt(2, electionID);
            ResultSet rs = statement.executeQuery();

            if (rs.next()) {
                rs.close();
                statement.close();
                dbConnection.close();
                return true;
            } else {
                rs.close();
                statement.close();
                dbConnection.close();
                return false;
            }


        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(CandidateDM.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }finally{
            
        }
    }
}
