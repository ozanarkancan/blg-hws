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
public final class Party implements Serializable {

    private String title = null;
    private Integer year = null;
    private String partyleader = null;
    private String partyPrinciples = null;
    private Integer electionId = null;

    public Party() {
    }

    public Party(String newTitle, Integer newYear, String newPartyLeader, String newPartyPrinciples, Integer newElectionId) {
        this.title = newTitle;
        this.year = newYear;
        this.partyleader = newPartyLeader;
        this.partyPrinciples = newPartyPrinciples;
        this.electionId = newElectionId;
    }

    public Party(String aTitle) {
        this.setTitle(aTitle);
    }

    public void setTitle(String aTitle) {
        this.title = aTitle;
    }

    public String getTitle() {
        return this.title;
    }

    public void setYear(Integer aYear) {
        this.year = aYear;
    }

    public Integer getYear() {
        return this.year;
    }

    public void setElectionId(Integer aElectionID) {
        this.electionId = aElectionID;
    }

    public Integer getElectionId() {
        return this.electionId;
    }

    public String getPartyLeader() {
        return partyleader;
    }

    public void setPartyLeader(String partyLeader) {
        this.partyleader = partyLeader;
    }

    public String getPartyPrinciples() {
        return partyPrinciples;
    }

    public void setPartyPrinciples(String partyPrinciples) {
        this.partyPrinciples = partyPrinciples;
    }
}
