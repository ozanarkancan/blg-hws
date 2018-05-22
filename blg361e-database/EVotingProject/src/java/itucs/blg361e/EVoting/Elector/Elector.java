/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

import java.io.Serializable;
import java.sql.Date;

/**
 *
 * @author Bahti
 */

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
public final class Elector implements Serializable {

    private String TCnumber = null;
    private Integer electionID = null;
    private Integer provinceID = null;
    private String name = null;
    private Date birthday = null;
    private String profession = null;
    private String education = null;
    private String address = null;
    private Boolean hasVoted = false;

    public Elector() {
    }

    public Elector(String TCnumber, Integer provinceid, String name, Date bday, String prof, String Edu, String ads) {

        this.setTC(TCnumber);
        this.setProvinceID(provinceid);
        this.setName(name);
        this.setBirthday(bday);
        this.setAddress(ads);
        this.setEducation(Edu);
        this.setProfession(prof);



    }

    public Integer getElectionID() {
        return electionID;
    }

    public void setElectionID(Integer electionID) {
        this.electionID = electionID;
    }

    public Boolean getHasVoted() {
        return hasVoted;
    }

    public void setHasVoted(Boolean hasVoted) {
        this.hasVoted = hasVoted;
    }

    public void setName(String nm) {

        this.name = nm;
    }

    public void setBirthday(Date bd) {

        this.birthday = bd;
    }

    public void setProfession(String p) {

        this.profession = p;
    }

    public void setTC(String tc) {
        this.TCnumber = tc;

    }

    public void setEducation(String e) {

        this.education = e;
    }

    public void setAddress(String a) {

        this.address = a;
    }

    public void setProvinceID(Integer p) {

        this.provinceID = p;
    }

    public String getName() {

        return this.name;
    }

    public String getAddress() {

        return this.address;
    }

    public Date getBirthday() {

        return this.birthday;
    }

    public String getProfession() {

        return this.profession;
    }

    public String getEducation() {

        return this.education;
    }

    public String getTCNumber() {
        return this.TCnumber;
    }

    public Integer getProvinceID() {
        return this.provinceID;
    }
}