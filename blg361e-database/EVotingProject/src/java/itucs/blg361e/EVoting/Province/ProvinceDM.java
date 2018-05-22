/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

import itucs.blg361e.EVoting.PostgreSqlManager;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.logging.Level;

import java.util.logging.Logger;

/**
 *
 * @author bahti
 */
public class ProvinceDM {

    private static transient Connection db;
    private static transient PostgreSqlManager psm;

    public ProvinceDM() {
        psm = new PostgreSqlManager();
    }

    public void connect() {
        ProvinceDM.psm = new PostgreSqlManager();
        ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
    }

    public static void createTable() {
        try {
            ProvinceDM.psm = new PostgreSqlManager();
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            if (!psm.doesTableExists("PROVINCE")) {
                Statement state = db.createStatement();
                String createTable = "CREATE TABLE PROVINCE(ID INTEGER NOT NULL,NAME VARCHAR(80),QUOTA INTEGER,ELECTIONID INTEGER REFERENCES ELECTION ON DELETE CASCADE,PRIMARY KEY(ID,ELECTIONID))";
                state.executeQuery(createTable);
                state.close();
                ProvinceDM.db.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void addProvince(Province p) {
        try {
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "INSERT INTO PROVINCE (ID,NAME, QUOTA,ELECTIONID) VALUES(?, ?, ?, ?)";
            PreparedStatement state = ProvinceDM.db.prepareStatement(query);
            state.setInt(1, p.getId());
            state.setString(2, p.getName());
            state.setInt(3, p.getQuota());
            state.setInt(4, p.getElectionId());
            state.executeUpdate();
            state.close();
            ProvinceDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    public static void deleteProvince(Province p) {
        try {
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "DELETE FROM PROVINCE WHERE(ID = ? AND ELECTIONID= ?)";
            PreparedStatement state = ProvinceDM.db.prepareStatement(query);
            state.setInt(1, p.getId());
            state.setInt(2, p.getElectionId());
            state.executeUpdate();
            state.close();
            ProvinceDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void updateProvince(Province p) {
        try {
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "UPDATE PROVINCE SET NAME = ? , QUOTA=? WHERE(ID=? AND ELECTIONID= ?)";
            PreparedStatement state = ProvinceDM.db.prepareStatement(query);
            state.setString(1, p.getName());
            state.setInt(2, p.getQuota());
            state.setInt(3, p.getId());
            state.setInt(4, p.getElectionId());
            state.executeUpdate();
            state.close();
            ProvinceDM.db.close();
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static ArrayList<Province> getProvince() {
        try {
            ProvinceDM.psm = new PostgreSqlManager();
            ArrayList<Province> provinces = new ArrayList<Province>();
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM PROVINCE";
            Statement statement = ProvinceDM.db.createStatement();
            ResultSet r = statement.executeQuery(query);
            while (r.next()) {
                Province p = new Province();
                p.setId(r.getInt("ID"));
                p.setName(r.getString("NAME"));
                p.setQuota(r.getInt("QUOTA"));
                p.setElectionId(r.getInt("ELECTIONID"));
                provinces.add(p);
            }
            r.close();
            statement.close();
            ProvinceDM.db.close();

            return provinces;
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }

    public static Province getOneProvince(Integer ID, Integer ElectionID) {
        Province province = null;

        try {
            ProvinceDM.psm = new PostgreSqlManager();
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM PROVINCE WHERE(ID = ? AND ELECTIONID=?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setInt(1, ID);
            statement.setInt(2, ElectionID);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                province = new Province();
                province.setId(rs.getInt("ID"));
                province.setElectionId(rs.getInt("ELECTIONID"));
                province.setName(rs.getString("NAME"));
                province.setQuota(rs.getInt("QUOTA"));
            }

            rs.close();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return province;
        }
    }

    public static Province getOneProvince(String Name, Integer ElectionID) {
        Province province = null;

        try {
            ProvinceDM.psm = new PostgreSqlManager();
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM PROVINCE WHERE(NAME = ? AND ELECTIONID=?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, Name);
            statement.setInt(2, ElectionID);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                province = new Province();
                province.setId(rs.getInt("ID"));
                province.setElectionId(rs.getInt("ELECTIONID"));
                province.setName(rs.getString("NAME"));
                province.setQuota(rs.getInt("QUOTA"));
            }

            rs.close();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return province;
        }
    }

    /**
     *
     * @return
     */
    public static ResultSet searchProvince() {
        try {
            ProvinceDM.psm = new PostgreSqlManager();
            ProvinceDM.db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");
            String query = "SELECT * FROM PROVINCE";
            Statement state;
            state = ProvinceDM.db.createStatement();
            state.executeQuery(query);
            ResultSet r = state.getResultSet();

            return r;
        } catch (SQLException ex) {
            Logger.getLogger(ProvinceDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
}