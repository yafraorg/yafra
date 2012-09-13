package org.yafra.gwt.admin.client;

import java.util.ArrayList;
import java.util.List;

import org.yafra.model.MYafraUser;

import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.view.client.AsyncDataProvider;
import com.google.gwt.view.client.HasData;
import com.google.gwt.view.client.Range;

public class YuDataProvider extends AsyncDataProvider<MYafraUser> implements AsyncCallback<List<MYafraUser>> {

	public static int PAGESIZE = 10;
    private final YafraAdminServiceAsync YafraAdminService = GWT.create(YafraAdminService.class);
    List<MYafraUser> cache = null;
    private int lastVisible = 0;
    private int start = 0;
    
    @Override
    protected void onRangeChanged(HasData<MYafraUser> display) {
    	final Range range = display.getVisibleRange();          
        start = range.getStart();
        //if (cache == null)
        	getData(lastVisible);
    }

    public void onFailure(Throwable caught) {
        Window.alert(caught.getMessage());
    }

    public void onSuccess(List<MYafraUser> result) {
        if (result.isEmpty()) {
            //display a warning
            return;
        }
        for (MYafraUser a : result) {
            if (cache.indexOf(a) == -1)
                cache.add(a);
        }
        updateRowData(cache.indexOf(result.get(0)), result);
        updateRowCount(cache.size(), result.size() < PAGESIZE);
    }

    public int getPageSize() {
    	return PAGESIZE;
    }
    
    public int getLastVisible() {
    	return lastVisible;
    }
    
	private void getData(Integer location) {

		// Then, we send the input to the server.
		YafraAdminService.getUserList(location,
				new AsyncCallback<List<MYafraUser>>() {
					public void onFailure(Throwable caught) {
						// Show the RPC error message to the user
					}

					public void onSuccess(List<MYafraUser> result) {
						cache = result;
						updateRowData(start, cache);
					}
				});
	}
}
