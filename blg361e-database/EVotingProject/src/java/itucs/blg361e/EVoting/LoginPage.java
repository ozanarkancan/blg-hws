/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import itucs.blg361e.EVoting.Elector.ElectorPage;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.PasswordTextField;
import org.apache.wicket.markup.html.form.RequiredTextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.PropertyModel;

/**
 *
 * @author coskun
 */
public final class LoginPage extends BasePage {

    User user = new User();

    public LoginPage() {
        super();

        Form loginform = new Form("login_form");
        add(loginform);

        RequiredTextField usernameField = new RequiredTextField("username",
                new PropertyModel<String>(user, "username"));
        loginform.add(usernameField);

        PasswordTextField passwordField = new PasswordTextField("password",
                new PropertyModel<String>(user, "password"));
        loginform.add(passwordField);

        Button login = new Button("login") {
            @Override
            public void onSubmit() {

                MySession session = MySession.get();
                if (session.isAuthenticated(user)) {
                    Integer user_kind = UserDM.getUser(user.getUsername()).getUserType();

                    if (user_kind == 0) {
                        this.setResponsePage(new AdminPage());
                    } else if (user_kind == 1) {
                        this.setResponsePage(new PartyAdministratorPage());
                    } else if (user_kind == 2) {
                        this.setResponsePage(new ElectorPage());
                    } else if (user_kind == 3) {
                        this.setResponsePage(new CandidatePage());
                    } else {
                        error("There is no such user type");
                    }
                } else {
                    error("Invalid username or password");
                }
            }
        };
        loginform.add(login);

        FeedbackPanel feedback = new FeedbackPanel("login_feedback");
        this.add(feedback);
    }
}
