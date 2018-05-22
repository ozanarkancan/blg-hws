/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting.Elector;

/**
 *
 * @author bahti
 */
import itucs.blg361e.EVoting.BasePage;
import itucs.blg361e.EVoting.ElectionOrganizer;
import itucs.blg361e.EVoting.MySession;
import itucs.blg361e.EVoting.Province.Province;
import itucs.blg361e.EVoting.Province.ProvinceDM;
import java.text.SimpleDateFormat;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.basic.Label;

public final class ElectorPage extends BasePage {

    public ElectorPage() {
        Label label = new Label("name", "Welcome  " + ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getName() + "!");
        this.add(label);

        Label label1 = new Label("tc", "Your TC Number is:  " + ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getTCNumber());
        this.add(label1);

        Label label2 = new Label("provinceId", "Your Province is: " + ProvinceDM.getOneProvince(ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getProvinceID(), ElectionOrganizer.currentOrNextElection.getElectionID()).getName());
        this.add(label2);
        SimpleDateFormat df = new SimpleDateFormat("dd.MM.YYYY");
        Label label3 = new Label("birthday", "Your Birthday is:  " + df.format(ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getBirthday()));
        this.add(label3);

        Label label4 = new Label("profession", "Your Profession is:  " + ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getProfession());
        this.add(label4);

        Label label5 = new Label("education", "Your Education is:  " + ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getEducation());
        this.add(label5);

        Label label6 = new Label("address", "Your Address is:  " + ElectorDM.getOneElector(MySession.get()
                .getUser().getUsername()).getAddress());
        this.add(label6);



        Link electorUpdateLink = new Link("update_elector") {
            @Override
            public void onClick() {
                Elector e = new Elector();
                this.setResponsePage(new ElectorUpdatePage());
            }
        };
        this.add(electorUpdateLink);


    }
}