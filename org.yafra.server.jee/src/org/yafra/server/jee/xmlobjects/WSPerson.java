package org.yafra.server.jee.xmlobjects;

import java.io.Serializable;

import javax.xml.bind.annotation.XmlRootElement;

import org.yafra.model.MPerson;

@XmlRootElement(name = "WSPerson")
public class WSPerson extends MPerson implements Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 3476637390155293642L;

	public WSPerson() {
		// TODO Auto-generated constructor stub
	}

}
