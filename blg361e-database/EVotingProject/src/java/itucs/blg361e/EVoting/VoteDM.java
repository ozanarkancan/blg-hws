/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.sql.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author OZAN
 */
public class VoteDM {
    private static transient PostgreSqlManager psm;
    private static transient Connection dbConnection;
    
    public VoteDM()
    {
        psm = new PostgreSqlManager();
    }
    
    public static void createVoteTable()
    {
        try {
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            
            if(!psm.doesTableExists("VOTE"))
            {
                Statement statement = dbConnection.createStatement();
                String createTable = "CREATE TABLE VOTE(voteId SERIAL PRIMARY KEY,"
                        + "electionId INTEGER NOT NULL,"
                        + "partyTitle VARCHAR(80),"
                        + "provinceId INTEGER NOT NULL,"
                        + "voteTime TIMESTAMP NOT NULL)";
                statement.executeQuery(createTable);
                statement.close();
                VoteDM.dbConnection.close();
            }
        } catch (SQLException ex) {
            Logger.getLogger(VoteDM.class.getName()).log(Level.SEVERE, null, ex);
        } catch (Exception ex) {
            Logger.getLogger(VoteDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void addVote(Vote vote)
    {
        try{
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "INSERT INTO VOTE (partyTitle, electionId, provinceId, voteTime)"
                    + " VALUES(?, ?, ?, ?)";
            PreparedStatement statement = VoteDM.dbConnection.prepareStatement(query);
            statement.setString(1, vote.getPartyTitle());
            statement.setInt(2, vote.getElectionId());
            statement.setInt(3, vote.getProvinceId());
            statement.setTimestamp(4, vote.getVoteTime());
            statement.executeUpdate();
            statement.close();
            VoteDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(VoteDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void deleteVote(Vote vote)
    {
        try {
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "DELETE FROM VOTE WHERE (voteId = ?)";
            PreparedStatement statement = VoteDM.dbConnection.prepareStatement(query);
            statement.setInt(1, vote.getVoteId());
            statement.executeUpdate();
            statement.close();
            VoteDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(VoteDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void updateVote(Vote vote)
    {
        try {
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            String query = "UPDATE VOTE SET partyTitle = ?, electionId = ?,"
                    + " provinceId = ?, voteTime = ?"
                    + " WHERE (electionID = ?)";
            PreparedStatement statement = VoteDM.dbConnection.prepareStatement(query);
            statement.setString(1, vote.getPartyTitle());
            statement.setInt(2, vote.getElectionId());
            statement.setInt(3, vote.getProvinceId());
            statement.setTimestamp(4, vote.getVoteTime());
            statement.executeUpdate();
            statement.close();
            VoteDM.dbConnection.close();
        } catch (SQLException ex) {
            Logger.getLogger(VoteDM.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static ArrayList<Vote> getAllVotesForElection(int electionId, int provinceId)
    {
        try{
            ArrayList<Vote> votes = new ArrayList<Vote>();
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            PreparedStatement statement = null;
            String query = "";
            
            if(provinceId == 0)
            {
                query = "SELECT * FROM VOTE WHERE (electionId = ?)";
                statement = VoteDM.dbConnection.prepareStatement(query);
                statement.setInt(1, electionId);
            }
            else
            {
                query = "SELECT * FROM VOTE WHERE (electionId = ? AND provinceId = ?)";
                statement = VoteDM.dbConnection.prepareStatement(query);
                statement.setInt(1, electionId);
                statement.setInt(2, provinceId);
            }
            
            ResultSet rs = statement.executeQuery();
            
            while(rs.next())
            {
                Vote vote = new Vote();
                vote.setVoteId(rs.getInt("voteId"));
                vote.setPartyTitle(rs.getString("partyTitle"));
                vote.setElectionId(rs.getInt("electionId"));
                vote.setProvinceId(rs.getInt("provinceId"));
                vote.setVoteTime(rs.getTimestamp("voteTime"));
            }            
            rs.close();
            statement.close();
            VoteDM.dbConnection.close();
            
            return votes;
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    
    public static HashMap<String, Integer> getVotesForAProvince(int electionId, int provinceId)
    {
        try{
            HashMap<String, Integer> votes = new HashMap<String, Integer>();
            VoteDM.psm = new PostgreSqlManager();
            VoteDM.dbConnection = psm.getConnection("jdbc:postgresql://localhost:5432/EVoting","postgres","123456");
            PreparedStatement statement = null;
            String query = "";
            
            if (provinceId != 0) {
                query = "SELECT partytitle, COUNT(*) FROM VOTE WHERE (electionId = ? AND provinceId = ?) GROUP BY partytitle";
                statement = VoteDM.dbConnection.prepareStatement(query);
                statement.setInt(1, electionId);
                statement.setInt(2, provinceId);
            } else {
                query = "SELECT partytitle, COUNT(*) FROM VOTE WHERE (electionId = ?) GROUP BY partytitle";
                statement = VoteDM.dbConnection.prepareStatement(query);
                statement.setInt(1, electionId);
            }
            
            ResultSet rs = statement.executeQuery();
            
            while(rs.next())
                votes.put(rs.getString(1), rs.getInt(2));
            rs.close();
            statement.close();
            VoteDM.dbConnection.close();
            
            return votes;
        } catch (SQLException ex) {
            Logger.getLogger(ElectionDM.class.getName()).log(Level.SEVERE, null, ex);
            return null;
        }
    }
    
    public static Map<String, Integer> getVotesOfOverTresholdParties(int electionId, double treshold)
    {
        Map<String, Integer> votes = new HashMap<String, Integer>();
        HashMap<String, Integer> allVotes = VoteDM.getVotesForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(),0);
        
        double total = 0;
        
        for(String title : allVotes.keySet())
            total += allVotes.get(title).doubleValue();
        for(String title : allVotes.keySet())
        {
            if(allVotes.get(title).doubleValue() / total >= treshold)
                votes.put(title, allVotes.get(title));
        }      
        
        return votes;
    }
    
    public static Map<String, Integer> getCandidateDistributionForAProvince(int electionId, int provinceId)
    {
        Map<String, Integer> distribution = new HashMap<String, Integer>();
        Map<String, Double> mapForCalculation = new HashMap<String, Double>();
        Map<String, Integer> votesForProvince = VoteDM.getVotesForAProvince(ElectionOrganizer.currentOrNextElection.getElectionID(),provinceId);
        Map<String, Integer> overTresholdParties = VoteDM.getVotesOfOverTresholdParties(electionId, 0.1);
        int quota = ProvinceDM.getOneProvince(provinceId, electionId).getQuota();
        
        
        for(String title : votesForProvince.keySet())
        {
            if(!title.equals(""))
            {
                if(CandidateDM.getCandidateWithName(title, electionId))
                    mapForCalculation.put(title, votesForProvince.get(title).doubleValue());
                else
                {
                    if(overTresholdParties.containsKey(title))
                    {
                        for(int i = 1; i <= quota; i++)
                            mapForCalculation.put(title + "-" + Integer.toString(i), votesForProvince.get(title).doubleValue() / i);//solves duplicate keys problem
                    }
                }
            }
        }
        
        mapForCalculation = VoteDM.sortByComparator(mapForCalculation);
        
        int i = 1;
        
        for(String title : mapForCalculation.keySet())
        {
            if(i > quota)
                break;
            else
            {
                String originalTitle = title.split("-")[0];
                if(!distribution.containsKey(originalTitle))
                    distribution.put(originalTitle, 1);
                else
                    distribution.put(originalTitle, distribution.get(originalTitle) + 1);
                i++;
            }
        }
        
        return distribution;
    }
    
    public static Map sortByComparator(Map<String, Double> unsortMap) {

        List list = new LinkedList(unsortMap.entrySet());

        // sort list based on comparator
        Collections.sort(list, new Comparator() {

            public int compare(Object o1, Object o2) {
                return -(((Comparable) ((Map.Entry) (o1)).getValue()).compareTo(((Map.Entry) (o2)).getValue()));
            }
        });

        Map sortedMap = new LinkedHashMap();
        for (Iterator it = list.iterator(); it.hasNext();) {
            Map.Entry entry = (Map.Entry) it.next();
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }
    
}
