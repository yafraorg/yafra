package org.yafra.gwt.admin.client;

import java.util.List;

import org.yafra.model.MYafraUser;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

/**
 * The client side stub for the RPC service.
 */
@RemoteServiceRelativePath("admin")
public interface YafraAdminService extends RemoteService {
	String doLogin(String name, String pwd) throws IllegalArgumentException;
	List<MYafraUser> getUserList(int location) throws IllegalArgumentException;
	MYafraUser getUser(String UserId) throws IllegalArgumentException;
	Integer changeUser(MYafraUser myu, int operation) throws IllegalArgumentException;
}
