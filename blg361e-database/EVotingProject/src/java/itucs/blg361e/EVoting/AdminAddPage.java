/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author coskun
 */
public class AdminAddPage extends AdminBasePage {

    User user = new User();

    public AdminAddPage() {
        super();

        Form admin_add_form = new Form("admin_add_form");
        add(admin_add_form);

        RequiredTextField usernameField = new RequiredTextField("username",
                new PropertyModel<String>(user, "username"));
        admin_add_form.add(usernameField);

        user.setPassword(PasswordGenerator.getPassword());
        user.setUserType(0);

        Button add_admin_button = new Button("add_admin") {
            @Override
            public void onSubmit() {
                
                if(UserDM.getUser(user.getUsername()) == null) {
                    UserDM.addUser(user);
                    
                    info("Admin was added successfully");
                }
                else{
                    error("There is an admin with same username!");
                }
            }
        };
        admin_add_form.add(add_admin_button);

        FeedbackPanel feedback = new FeedbackPanel("add_admin_feedback");
        this.add(feedback);
    }
}
