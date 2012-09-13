/**
 * org.yafra.utils
 * check which user is logged in
 * $Id: WhichUser.java,v 1.1 2009-10-24 18:36:56 mwn Exp $
 */
package org.yafra.utils;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author mwn
 * 
 */
public final class WhichUser
{
	private String User = null;
	
	/*
	 * get user from environment variables - not safe but quick
	 */
	public final String getEnvUser()
		{
		User = System.getProperty("user.name");
		return User;
		}
	
	/*
	 * get user from authentication system - safe but has a larger footprint
	 */
	public final String getUser()
		{
		try {
			String classNameToBeLoaded = null;
			Method myMethod = null;
			ClassLoader myClassLoader = ClassLoader.getSystemClassLoader();
			if (org.yafra.utils.WhichOS.isWindows() == true)
				classNameToBeLoaded = "com.sun.security.auth.module.NTSystem";
			else
				classNameToBeLoaded = "com.sun.security.auth.module.UnixSystem";
			Class myClass = myClassLoader.loadClass(classNameToBeLoaded);
			Object whatInstance = myClass.newInstance();
			if (org.yafra.utils.WhichOS.isWindows() == true)
				myMethod = myClass.getMethod("getName", new Class[] { });
			else
				myMethod = myClass.getMethod("getUsername", new Class[] { });
			User = (String) myMethod.invoke(whatInstance, new Object[] { });
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			} catch (InstantiationException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			}
		return User;
		}

	/*
	 * compare environemnt username and authentication username
	 */
	public final boolean isIdentical()
		{
		String EnvUser = System.getProperty("user.name");
		return EnvUser.equals(User);
		}
}
