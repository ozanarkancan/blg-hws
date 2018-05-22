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
public final class Candidate implements Serializable {
    
    private String TCnumber = null;
    private String name =null;
    private String partyTitle= null;
    private String userName = null;
    private Boolean isIndependent = null;
    private Integer electionId = null;


    private Integer provinceId = null;
    
    public Candidate() {
    }
    
    public Candidate(String new_TCnumber, String new_name, String new_partyTitle, String new_userName, Boolean new_isIndependent,Integer new_electionId , Integer new_provinceId)
    {
        this.TCnumber = new_TCnumber;
        this.name = new_name;
        this.partyTitle = new_partyTitle;
        this.userName = new_userName;
        this.isIndependent = new_isIndependent;
        this.electionId = new_electionId;
        this.provinceId = new_provinceId;
        
    }
    
    public Integer getElectionId() {
        return electionId;
    }

    public void setElectionId(Integer electionId) {
        this.electionId = electionId;
    }

    public Integer getProvinceId() {
        return provinceId;
    }

    public void setProvinceId(Integer provinceId) {
        this.provinceId = provinceId;
    }

    public String getTCnumber() {
        return TCnumber;
    }

    public void setTCnumber(String TCnumber) {
        this.TCnumber = TCnumber;
    }

    public Boolean getIsIndependent() {
        return isIndependent;
    }

    public void setIsIndependent(Boolean isIndependent) {
        this.isIndependent = isIndependent;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
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
    
  
    
}
