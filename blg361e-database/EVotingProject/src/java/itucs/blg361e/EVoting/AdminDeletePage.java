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
public final class AdminDeletePage extends AdminBasePage {
    
    User user = new User();
    
    public AdminDeletePage() {
        super();

        Form admin_delete_form = new Form("admin_delete_form");
        add(admin_delete_form);

        RequiredTextField usernameField = new RequiredTextField("username",
                new PropertyModel<String>(user, "username"));
        admin_delete_form.add(usernameField);
        
        Button delete_admin_button = new Button("delete_admin") {
            @Override
            public void onSubmit() {
                
                if(UserDM.getUser(user.getUsername()) != null && 
                   UserDM.getUser(user.getUsername()).getUserType() == 0) {
                    
                    UserDM.deleteUser(user);
                    
                    info("Specified admin was deleted successfully");
                }
                else {
                    error("Requested admin does not exist in database!");
                }
            }
        };
        admin_delete_form.add(delete_admin_button);

        FeedbackPanel feedback = new FeedbackPanel("delete_admin_feedback");
        this.add(feedback);
    }
}
