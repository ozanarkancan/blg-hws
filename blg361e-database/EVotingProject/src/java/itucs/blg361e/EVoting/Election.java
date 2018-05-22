/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Province.Province;
import java.io.Serializable;
import java.sql.Timestamp;
import java.util.ArrayList;

/**
 *
 * @author OZAN
 */
public class Election implements Serializable{
    private Timestamp startDateOfElection;
    private Timestamp finishDateOfElection;
    private Timestamp lastDateOfAddingCandidate;
    public  transient ArrayList<Province> provinces;
    public  transient ArrayList<Party> parties;
    private int electionID;
    private transient ArrayList<Vote> votes;//After vote class is implemented uncomment this and related functions
    
    public Election()
    {
        provinces = new ArrayList<Province>();
        parties = new ArrayList<Party>();
    }
    
    public Object getObject()
    {
        return this;
    }
    public Timestamp getStartDateOfElection()
    {
        return this.startDateOfElection;
    }
    
    public void setStartDateOfElection(Timestamp date)
    {
        this.startDateOfElection = date;
    }
    
    public Timestamp getFinishDateOfElection()
    {
        return this.finishDateOfElection;
    }
    
    public void setFinishDateOfElection(Timestamp date)
    {
        this.finishDateOfElection = date;
    }
    
    public Timestamp getLastDateOfAddingCandidate()
    {
        return this.lastDateOfAddingCandidate;
    }
    
    public void setLastDateOfAddingCandidate(Timestamp date)
    {
        this.lastDateOfAddingCandidate = date;
    }
    
    public ArrayList<Province> getProvinces()
    {
        return this.provinces;
    }
    
    public void setProvinces(ArrayList<Province> provinces)
    {
        this.provinces = provinces;
    }
    
    public void addProvince(Province province)
    {
        this.provinces.add(province);
    }
    
    public ArrayList<Party> getParty()
    {
        return this.parties;
    }
    
    public void setParties(ArrayList<Party> parties)
    {
        this.parties = parties;
    }
    
    public void addParty(Party party)
    {
        this.addParty(party);
    }
    
    public int getElectionID()
    {
        return this.electionID;
    }
    
    public void setElectionID(int id)
    {
        this.electionID = id;
    }
    
    @Override
    public String toString()
    {
        String result = "";
        result = "ID : " + Integer.toString(electionID) + " - ";
        result += "Start Date : " + startDateOfElection.toString();
        return result;
    }

    public ArrayList<Vote> getVotes()
    {
        return this.votes;
    }
    
    public void setVotes(ArrayList<Vote> votes)
    {
        this.votes = votes;
    }
    
    public void addVote(Vote vote)
    {
        votes.add(vote);
    }
}
