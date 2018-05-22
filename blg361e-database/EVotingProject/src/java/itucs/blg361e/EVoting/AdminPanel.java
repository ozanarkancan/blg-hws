/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Elector.ElectorDeletePage;
import itucs.blg361e.EVoting.Elector.ElectorEditPage;
import itucs.blg361e.EVoting.Province.ProvinceDeletePage;
import itucs.blg361e.EVoting.Province.ProvinceEditPage;
import itucs.blg361e.EVoting.Province.ProvinceUpdatePage;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.panel.Panel;


/**
 *
 * @author coskun
 */
public class AdminPanel extends Panel {

    public AdminPanel(String id) {
        super(id);
        
        /* Links for add operations */
        Link userAddLink = new Link("add_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new AdminAddPage());
            }
        };
        this.add(userAddLink);

        Link partyAddLink = new Link("add_party") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyEditPage(new Party()));
            }
        };
        this.add(partyAddLink);

        Link partyAdminAddLink = new Link("add_party_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyAdministratorEditPage(new PartyAdministrator()));
            }
        };
        this.add(partyAdminAddLink);

        Link electorAddLink = new Link("add_elector") {
            @Override
            public void onClick() {
                this.setResponsePage(new ElectorEditPage());
            }
        };
        this.add(electorAddLink);

        Link provinceAddLink = new Link("add_province") {
            @Override
            public void onClick() {
                this.setResponsePage(new ProvinceEditPage());
            }
        };
        this.add(provinceAddLink);
        
        Link independentAddLink = new Link("add_independent") {
            @Override
            public void onClick() {
                this.setResponsePage(new IndependentAddPage());
            }
        };
        this.add(independentAddLink);

        Link electionAddLink = new Link("add_edit_election") {
            @Override
            public void onClick() {
                this.setResponsePage(new ElectionEditorPage());
            }
        };
        this.add(electionAddLink);
        
        /* Links for delete operations */
        Link adminDeleteLink = new Link("delete_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new AdminDeletePage());
            }
        };
        this.add(adminDeleteLink);
       
        Link partyDeleteLink = new Link("delete_party") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyDeletePage(new Party()));
            }
        };
        this.add(partyDeleteLink);
        
        Link partyAdminDeleteLink = new Link("delete_party_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyAdministratorDeletePage(new PartyAdministrator()));
            }
        };
        this.add(partyAdminDeleteLink);
        
        Link electorDeleteLink = new Link("delete_elector") {
            @Override
            public void onClick() {
                this.setResponsePage(new ElectorDeletePage());
            }
        };
        this.add(electorDeleteLink);
        
        Link provinceDeleteLink = new Link("delete_province") {
            @Override
            public void onClick() {
                this.setResponsePage(new ProvinceDeletePage());
            }
        };
        this.add(provinceDeleteLink);        

        /* Links for update operations */
        Link adminUpdateLink = new Link("update_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new AdminUpdatePage());
            }
        };
        this.add(adminUpdateLink);
  
        Link partyUpdateLink = new Link("update_party") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyUpdatePage());
            }
        };
        this.add(partyUpdateLink);
        
        Link partyAdminUpdateLink = new Link("update_party_admin") {
            @Override
            public void onClick() {
                this.setResponsePage(new PartyAdministratorUpdatePage());
            }
        };
        this.add(partyAdminUpdateLink);
                
        Link provinceUpdateLink = new Link("update_province") {
            @Override
            public void onClick() {
                this.setResponsePage(new ProvinceUpdatePage());
            }
        };
        this.add(provinceUpdateLink); 
    
    }
}
