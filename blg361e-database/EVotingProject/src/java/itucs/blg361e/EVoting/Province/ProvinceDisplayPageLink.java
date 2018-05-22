/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

/**
 *
 * @author bahti
 */
import org.apache.wicket.markup.html.link.Link;

public class ProvinceDisplayPageLink extends Link {

    private Province province1;

    public ProvinceDisplayPageLink(String id, Province p) {
        super(id);
        this.province1 = p;
    }

    @Override
    public void onClick() {
        this.setResponsePage(new ProvincePage());
    }
}