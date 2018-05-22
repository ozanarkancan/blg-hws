/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Province;

/**
 *
 * @author bahti
 */
import itucs.blg361e.EVoting.AdminBasePage;
import itucs.blg361e.EVoting.Application;
import itucs.blg361e.EVoting.HomePageLink;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Date;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.basic.Label;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.ListView;
import org.apache.wicket.markup.html.list.PropertyListView;

public final class ProvincePage extends AdminBasePage {

    public ProvincePage() {

        ProvinceCollection collection = new ProvinceCollection();
        ProvinceDM dme = new ProvinceDM();
        ResultSet r = dme.searchProvince();
        try {
            while (r.next()) {
                Province p = new Province(r.getInt("ID"), r.getString("NAME"), r.getInt("QUOTA"), r.getInt("ELECTIONID"));
                collection.addProvince(p);
            }

        } catch (SQLException ex) {
            Logger.getLogger(ProvincePage.class.getName()).log(Level.SEVERE, null, ex);
        }
        List<Province> provinces = collection.getProvinces();
        PropertyListView provinceListView = new PropertyListView("province_list", provinces) {
            @Override
            protected void populateItem(ListItem item) {
                Province province = (Province) item.getModelObject();
                ProvinceDisplayPageLink provinceLink = new ProvinceDisplayPageLink("province_link", province);
                provinceLink.add(new Label("id"));
                provinceLink.add(new Label("name"));
                provinceLink.add(new Label("quota"));
                item.add(provinceLink);
            }
        };
        this.add(provinceListView);

    }
}