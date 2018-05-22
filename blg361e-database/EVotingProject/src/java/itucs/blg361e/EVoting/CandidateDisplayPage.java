/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.markup.html.WebPage;

/**
 *
 * @author cemil
 */
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.link.Link;

public final class CandidateDisplayPage extends BasePage {

    public CandidateDisplayPage(Candidate can) {
        this.add(new Label("TCnumber", can.getTCnumber().toString()));
        this.add(new Label("name", can.getName()));
        this.add(new Label("userName", can.getUserName()));
        this.add(new Label("partyTitle", can.getPartyTitle()));
        this.add(new Label("isIndependent", can.getIsIndependent().toString()));
        this.add(new Label("provinceId", can.getProvinceId().toString()));
    }
   
}
