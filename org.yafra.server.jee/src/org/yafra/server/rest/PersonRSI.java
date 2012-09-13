package org.yafra.server.rest;

import javax.ws.rs.core.Response;

import org.yafra.server.jee.xmlobjects.WSPerson;

public interface PersonRSI {
    WSPerson getPerson( String id);
    
    Response updateCustomer(WSPerson customer);

	Response addCustomer(WSPerson customer);

	Response deleteCustomer( String id);
}
