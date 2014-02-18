/**
 * org.yafra.utils
 * unix date conversion utilities - facilities to convert from to unix timestamp to java date
 * $Id: UnixDate.java,v 1.2 2009-10-24 18:36:56 mwn Exp $
 */
package org.yafra.utils;

import java.util.Date;
import java.util.GregorianCalendar;

/**
 * @author mwn
 * 
 */
public class UnixDate
{

	public static Date setPSDate(int mapot)
		{
		if (mapot != -1) return new Date(((long) mapot) * 1000);
		else return new Date(-1);
		}

	public static GregorianCalendar setCal(int mapot)
		{
		Date using = new Date();
		GregorianCalendar cal = new GregorianCalendar();
		if (mapot != -1)
			{
			using = new Date(((long) mapot) * 1000);
			}
		else
			{
			using = new Date(-1);
			}
		cal.setTime(using);
		return cal;
		}

	public static int getPSDate(Date st)
		{
		if (st.getTime() != -1) return (int) (st.getTime() / 1000);
		else return -1;
		}

	public static int getPSCal(GregorianCalendar cal)
		{
		if (cal.getTime().getTime() != -1) return (int) cal.getTime().getTime() / 1000;
		else return -1;
		}
}
