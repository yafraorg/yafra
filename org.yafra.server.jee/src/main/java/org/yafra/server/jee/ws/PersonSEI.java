package org.yafra.server.jee.ws;

import java.util.List;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebService;

import org.yafra.server.jee.xmlobjects.WSPerson;

@WebService
public interface PersonSEI {

	/* 
	 * 
	 */
	@WebMethod
	public List<String> getPersons();

	/* 
	 * 
	 */
	@WebMethod
	public void insertPerson(@WebParam(name = "person") WSPerson person);
}