/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

import java.io.Serializable;

/**
 *
 * @author bahti
 */
public class Province implements Serializable {

    private Integer id = null;
    private String name = null;
    private Integer quota = null;
    private Integer electionId = null;

    public Province() {
    }

    public Province(Integer id, String Name, Integer limit, Integer electionId) {
        this.setName(Name);
        this.setQuota(limit);
        this.setId(id);
        this.setElectionId(electionId);
    }

    public void setId(Integer a) {
        this.id = a;
    }

    public Integer getId() {
        return id;
    }

    public void setElectionId(Integer i) {
        this.electionId = i;
    }

    public Integer getElectionId() {
        return electionId;
    }

    public void setName(String Name) {
        this.name = Name;
    }

    public String getName() {
        return this.name;
    }

    public void setQuota(Integer number) {
        this.quota = number;
    }

    public Integer getQuota() {
        return this.quota;
    }
}
