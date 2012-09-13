/**
 * org.yafra.utils
 * object identifier utilities - facilities to select an object
 * mainly used for transfer between tiers
 * $Id: ObjSelection.java,v 1.2 2009-10-24 18:36:56 mwn Exp $
 */
package org.yafra.utils;

import java.io.Serializable;
import java.util.Date;

/**
 * @author mwn
 * 
 */
public class ObjSelection implements Serializable
{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * ID of object (a primary key)
	 */
	private int Id;

	public int getId()
		{
		return Id;
		}

	public void setId(int id)
		{
		Id = id;
		}

	/**
	 * the description field in the selected language
	 */
	private String Desc;

	public String getDesc()
		{
		return Desc;
		}

	public void setDesc(String desc)
		{
		Desc = desc;
		}

	/**
	 * date time from or main
	 */
	private Date Date1;

	public Date getDate1()
		{
		return Date1;
		}

	public void setDate1(Date date1)
		{
		Date1 = date1;
		}

	/**
	 * date time to (only needed for time span)
	 */
	private Date Date2;

	public Date getDate2()
		{
		return Date2;
		}

	public void setDate2(Date date2)
		{
		Date2 = date2;
		}

	/**
	 * code, special text, parent description, ...
	 */
	private String Addon;

	public String getAddon()
		{
		return Addon;
		}

	public void setAddon(String addon)
		{
		Addon = addon;
		}

	/**
	 * init function
	 */
	public ObjSelection()
		{
		Id = -1;
		Desc = null;
		Date1 = null;
		Date2 = null;
		Addon = null;
		}
}
