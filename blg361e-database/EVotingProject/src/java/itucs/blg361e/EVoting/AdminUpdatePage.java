/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.AttributeModifier;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author coskun
 */
public final class AdminUpdatePage extends AdminBasePage {

    User user = new User();

    public AdminUpdatePage() {
        super();

        Form admin_update_form = new Form("admin_update_form");
        add(admin_update_form);

        final RequiredTextField usernameField = new RequiredTextField("username",
                new PropertyModel<String>(user, "username"));
        admin_update_form.add(usernameField);

        final TextField passwordField = new TextField("password",
                new PropertyModel<String>(user, "password"));
        admin_update_form.add(passwordField);

        final TextField userTypeField = new TextField("user_type",
                new PropertyModel<String>(user, "userType"));
        admin_update_form.add(userTypeField);

        Button get_user_button = new Button("get_admin_info") {
            @Override
            public void onSubmit() {

                if (UserDM.getUser(user.getUsername()) != null) {
                    usernameField.add(AttributeModifier.replace("readonly", "readonly"));
                    passwordField.add(new AttributeModifier("value", UserDM.getUser(user.getUsername()).getPassword()));
                    userTypeField.add(new AttributeModifier("value", UserDM.getUser(user.getUsername()).getUserType()));
                } else {
                    error("Requested admin does not exist in database!");
                }
            }
        };
        admin_update_form.add(get_user_button);

        Button update_admin_button = new Button("update_admin") {
            @Override
            public void onSubmit() {

                if (UserDM.getUser(user.getUsername()) != null && 
                    UserDM.getUser(user.getUsername()).getUserType() == 0) {

                    UserDM.updateUser(user);

                    info("Specified admin was updated successfully");
                }
            }
        };
        admin_update_form.add(update_admin_button);

        FeedbackPanel feedback = new FeedbackPanel("update_admin_feedback");
        this.add(feedback);
    }
}
