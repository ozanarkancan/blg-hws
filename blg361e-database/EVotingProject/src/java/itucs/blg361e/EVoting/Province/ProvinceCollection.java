/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

/**
 *
 * @author bahti
 */
import java.util.LinkedList;
import java.util.List;

public class ProvinceCollection {

    private List<Province> province;

    public ProvinceCollection() {
        this.province = new LinkedList<Province>();
    }

    public List<Province> getProvinces() {
        return this.province;
    }

    public void addProvince(Province p) {
        this.province.add(p);
    }

    public void deleteProvince(Province p) {
        this.province.remove(p);
    }
}