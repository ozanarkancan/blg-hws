/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author coskun
 */
public class UserDM {

    private static Connection db;
    private static PostgreSqlManager psm;

    public UserDM() {
        psm = new PostgreSqlManager();
    }

    public static void createTable() {
        try {
            psm = new PostgreSqlManager();
            db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            if (!psm.doesTableExists("USERS")) {
                String query = "CREATE TABLE USERS (USERNAME VARCHAR(80) PRIMARY KEY, PASSWORD VARCHAR(80), USERTYPE INTEGER)";
                Statement statement = db.createStatement();
                statement.executeQuery(query);
                statement.close();
                db.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void addUser(User new_user) {
        try {
            psm = new PostgreSqlManager();
            db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "INSERT INTO USERS (USERNAME, PASSWORD, USERTYPE) VALUES(?, ?, ?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, new_user.getUsername());
            statement.setString(2, new_user.getPassword());
            statement.setInt(3, new_user.getUserType());
            statement.executeUpdate();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void deleteUser(User will_deleted) {
        try {
            psm = new PostgreSqlManager();
            db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "DELETE FROM USERS WHERE (USERNAME = ?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, will_deleted.getUsername());
            statement.executeUpdate();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void updateUser(User will_updated) {
        try {
            psm = new PostgreSqlManager();
            db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "UPDATE USERS SET PASSWORD = ?, USERTYPE = ? WHERE(USERNAME = ?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, will_updated.getPassword());
            statement.setInt(2, will_updated.getUserType());
            statement.setString(3, will_updated.getUsername());
            statement.executeUpdate();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static User getUser(String username) {
        User user = null;

        try {
            psm = new PostgreSqlManager();
            db = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting", "postgres", "123456");

            String query = "SELECT * FROM USERS WHERE(USERNAME = ?)";
            PreparedStatement statement = db.prepareStatement(query);
            statement.setString(1, username);
            ResultSet rs = statement.executeQuery();
            if (rs.next()) {
                user = new User();
                user.setUsername(rs.getString("USERNAME"));
                user.setPassword(rs.getString("PASSWORD"));
                user.setUserType(rs.getInt("USERTYPE"));
            }

            rs.close();
            statement.close();
            db.close();
        } catch (SQLException e) {
            throw new UnsupportedOperationException(e.getMessage());
        } catch (Exception ex) {
            Logger.getLogger(UserDM.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            return user;
        }
    }
}