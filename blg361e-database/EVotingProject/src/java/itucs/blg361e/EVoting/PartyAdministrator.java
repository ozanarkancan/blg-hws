/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import java.io.Serializable;

/**
 *
 * @author fikret
 */
public class PartyAdministrator implements Serializable {
    private String userName = null;
    private String partyTitle = null;
    private Integer electionId = null;

    public Integer getElectionId() {
        return electionId;
    }

    public void setElectionId(Integer electionId) {
        this.electionId = electionId;
    }
    
    public String getPartyTitle() {
        return partyTitle;
    }

    public void setPartyTitle(String partyTitle) {
        this.partyTitle = partyTitle;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }
    
    public PartyAdministrator(){
    }
    public PartyAdministrator(String newName, String newPartyTitle, Integer newElectionId)
    {
        this.userName = newName;
        this.partyTitle = newPartyTitle;
        this.electionId = newElectionId;
    }
    
}
