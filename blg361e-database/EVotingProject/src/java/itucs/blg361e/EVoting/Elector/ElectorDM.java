/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

/**
 *
 * @author Bahti
 */
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import itucs.blg361e.EVoting.PostgreSqlManager;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.ArrayList;

public class ElectorDM {

    private static transient Connection db;
    private static transient PostgreSqlManager psm;

    public ElectorDM() {
        psm = new PostgreSqlManager();
    }

    public void connect() {
        ElectorDM.psm = new PostgreSqlManager();
        ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
    }

    public static void createTable() {
        try {
            ElectorDM.psm = new PostgreSqlManager();
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            if (!psm.doesTableExists("ELECTOR")) {
                Statement state = db.createStatement();
                String createTable = "CREATE TABLE ELECTOR(TC VARCHAR(11) PRIMARY KEY NOT NULL,PROVINCEID INTEGER,ELECTIONID INTEGER, NAME VARCHAR(80),BIRTHDAY DATE,PROFESSION VARCHAR(80),EDUCATION VARCHAR(80),ADDRESS VARCHAR(160),HASVOTED BOOLEAN, FOREIGN KEY(PROVINCEID,ELECTIONID) REFERENCES PROVINCE(ID,ELECTIONID) ON UPDATE NO ACTION ON DELETE CASCADE )";
                state.executeQuery(createTable);
                state.close();
                ElectorDM.db.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void addElector(Elector e) {
        try {
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "INSERT INTO ELECTOR (TC, PROVINCEID, ELECTIONID, NAME, BIRTHDAY, PROFESSION, EDUCATION, ADDRESS,HASVOTED) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement state = ElectorDM.db.prepareStatement(query);
            state.setString(1, e.getTCNumber());
            state.setInt(2, e.getProvinceID());
            state.setInt(3, e.getElectionID());
            state.setString(4, e.getName());
            state.setDate(5, e.getBirthday());
            state.setString(6, e.getProfession());
            state.setString(7, e.getEducation());
            state.setString(8, e.getAddress());
            state.setBoolean(9, e.getHasVoted());
            state.executeUpdate();
            state.close();
            ElectorDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    public static void deleteElector(Elector e) {
        try {
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "DELETE FROM ELECTOR WHERE(TC = ?)";
            PreparedStatement state = ElectorDM.db.prepareStatement(query);
            state.setString(1, e.getTCNumber());
            state.executeUpdate();
            state.close();
            ElectorDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void updateElector(Elector e) {
        try {
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "UPDATE ELECTOR SET PROVINCEID=? , NAME = ? , BIRTHDAY=?, PROFESSION=?, EDUCATION=?, ADDRESS=? , HASVOTED=? WHERE(TC=?)";
            PreparedStatement state = ElectorDM.db.prepareStatement(query);
            state.setInt(1, e.getProvinceID());
            state.setString(2, e.getName());
            state.setDate(3, e.getBirthday());
            state.setString(4, e.getProfession());
            state.setString(5, e.getEducation());
            state.setString(6, e.getAddress());
            state.setBoolean(7, e.getHasVoted());
            state.setString(8, e.getTCNumber());
            state.executeUpdate();
            state.close();
            ElectorDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static ArrayList<Elector> getElector() {
        try {
            ElectorDM.psm = new PostgreSqlManager();
            ArrayList<Elector> electors = new ArrayList<Elector>();
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM ELECTOR";
            Statement statement = ElectorDM.db.createStatement();
            ResultSet rs = statement.executeQuery(query);
            while (rs.next()) {
                Elector e = new Elector();
                e.setName(rs.getString("NAME"));
                e.setTC(rs.getString("TC"));
                e.setProvinceID(rs.getInt("PROVINCEID"));
                e.setBirthday(rs.getDate("BIRTHDAY"));
                e.setProfession(rs.getString("PROFESSION"));
                e.setEducation(rs.getString("EDUCATION"));
                e.setAddress(rs.getString("ADDRESS"));
                e.setHasVoted(rs.getBoolean("HASVOTED"));
            }
            rs.close();
            statement.close();
            ElectorDM.db.close();

            return electors;
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static Elector getOneElector(String TC) {
        Elector elector = null;

        try {
            ElectorDM.psm = new PostgreSqlManager();
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM ELECTOR WHERE(TC = ?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, TC);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                elector = new Elector();
                elector.setTC(rs.getString("TC"));
                elector.setProvinceID(rs.getInt("PROVINCEID"));
                elector.setName(rs.getString("NAME"));
                elector.setBirthday(rs.getDate("BIRTHDAY"));
                elector.setProfession(rs.getString("PROFESSION"));
                elector.setEducation(rs.getString("EDUCATION"));
                elector.setAddress(rs.getString("ADDRESS"));
                elector.setHasVoted(rs.getBoolean("HASVOTED"));
            }

            rs.close();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return elector;
        }
    }

    public static ResultSet searchElector() {
        try {
            ElectorDM.psm = new PostgreSqlManager();
            ElectorDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM ELECTOR";
            Statement state;
            state = ElectorDM.db.createStatement();
            state.executeQuery(query);
            ResultSet r = state.getResultSet();

            return r;
        } catch (SQLException ex) {
            Logger.getLogger(ElectorDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}