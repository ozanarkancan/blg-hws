/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package itucs.blg361e.EVoting;

import org.apache.wicket.Session;
import org.apache.wicket.protocol.http.WebSession;
import org.apache.wicket.request.Request;

/**
 *
 * @author coskun
 */
public class MySession extends WebSession {

    private User user;

    public MySession(Request request) {
        super(request);
    }

    public static MySession get() {
        return (MySession) Session.get();
    }

    public synchronized void setUser(User user) {
        this.user = user;
    }

    public synchronized User getUser() {
        return user;
    }

    public synchronized boolean isLoggedIn() {
        return (user != null);
    }

    public synchronized boolean isAuthenticated(User user) {
        User result_user = UserDM.getUser(user.getUsername());
        boolean result = false;

        if (result_user != null) {
            result = result_user.getPassword().equals(user.getPassword());
            setUser(result_user);
        }

        return result;
    }
}
