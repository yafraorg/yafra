/**
 * org.yafra.utils
 * check which operating system is running
 * $Id: WhichOS.java,v 1.2 2009-10-24 18:36:56 mwn Exp $
 */
package org.yafra.utils;

/**
 * @author mwn
 * 
 */
public final class WhichOS
{
	private static String OS = null;

	public final static String getOsName()
		{
		if (OS == null)
			{
			OS = System.getProperty("os.name");
			}
		return OS;
		}

	public final static boolean isWindows()
		{
		return getOsName().startsWith("Windows");
		}

	public final static boolean isUnix() // and so on
		{
		return getOsName().startsWith("Linux");
		}

}
