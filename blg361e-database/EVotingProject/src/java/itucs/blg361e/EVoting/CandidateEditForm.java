/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

/**
 *
 * @author cemil 
 */

import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.model.CompoundPropertyModel;

public class CandidateEditForm extends Form {

    public CandidateEditForm(String id, Candidate can) {
        super(id);

        CompoundPropertyModel model = new CompoundPropertyModel(can);
        this.setModel(model);

        this.add(new TextField("name"));
        this.add(new TextField("partyname"));
    }

    @Override
    public void onSubmit() {
        Candidate can = (Candidate) this.getModelObject();
        Application app = (Application) this.getApplication();
        CandidateCollection collection = app.getCollection2();
        collection.addCandidate(can);
        this.setResponsePage(new CandidateDisplayPage(can));
    }
}