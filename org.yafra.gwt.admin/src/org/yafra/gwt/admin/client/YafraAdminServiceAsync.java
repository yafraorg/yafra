package org.yafra.gwt.admin.client;

import java.util.List;

import org.yafra.model.MYafraUser;

import com.google.gwt.user.client.rpc.AsyncCallback;

/**
 * The async counterpart of <code>GreetingService</code>.
 */
public interface YafraAdminServiceAsync {
	void doLogin(String name, String pwd, AsyncCallback<String> callback)
			throws IllegalArgumentException;
	void getUserList(int location, AsyncCallback<List<MYafraUser>> callback) throws IllegalArgumentException;
	void getUser(String UserId, AsyncCallback<MYafraUser> callback);
	void changeUser(MYafraUser myu, int operation, AsyncCallback<Integer> callback);
}
