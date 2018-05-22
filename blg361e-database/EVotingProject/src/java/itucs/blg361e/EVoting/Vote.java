/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.io.Serializable;
import java.sql.Timestamp;

/**
 *
 * @author OZAN
 */
public final class Vote implements Serializable{
    
    private int voteId;
    private String partyTitle;
    private int electionId;
    private int provinceId;
    private Timestamp voteTime;
    
    public int getVoteId()
    {
        return this.voteId;
    }
    
    public void setVoteId(int id)
    {
        this.voteId = id;
    }
    
    public Timestamp getVoteTime()
    {
        return this.voteTime;
    }
    
    public void setVoteTime(Timestamp voteTime)
    {
        this.voteTime = voteTime;
    }
    
    public String getPartyTitle()
    {
        return this.partyTitle;
    }
    
    public void setPartyTitle(String partyTitle)
    {
        this.partyTitle = partyTitle;
    }
    
    public int getElectionId()
    {
        return this.electionId;
    }
    
    public void setElectionId(int id)
    {
        this.electionId = id;
    }
    
    public int getProvinceId()
    {
        return this.provinceId;
    }
    
    public void setProvinceId(int id)
    {
        this.provinceId = id;
    }
}


