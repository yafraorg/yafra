package org.yafra.gwt.admin.client;

import org.yafra.model.MYafraUser;

import com.google.gwt.user.cellview.client.DataGrid;
import com.google.gwt.user.cellview.client.HasKeyboardSelectionPolicy.KeyboardSelectionPolicy;
import com.google.gwt.user.cellview.client.SimplePager;
import com.google.gwt.user.cellview.client.TextColumn;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HasHorizontalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.TabPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.view.client.SelectionChangeEvent;
import com.google.gwt.view.client.SingleSelectionModel;

public class YuTable extends Composite {

	public DataGrid<MYafraUser> dataGrid;
	public FlexTable flexTable;
	
	public YuTable() {

		flexTable = new FlexTable();
		initWidget(flexTable);
		flexTable.setSize("583px", "512px");
		
		VerticalPanel simplePanel = new VerticalPanel();
		flexTable.setWidget(0, 0, simplePanel);
		simplePanel.setWidth("100%");
		

		TabPanel tabPanel = new TabPanel();
		flexTable.setWidget(1, 0, tabPanel);
		tabPanel.setSize("100%", "204px");
		
		FlexTable flexTabEdit = new FlexTable();
		tabPanel.add(flexTabEdit, "Edit", false);
		flexTabEdit.setSize("489px", "3cm");
		
		Label lblUserId = new Label("User ID:");
		flexTabEdit.setWidget(0, 0, lblUserId);
		lblUserId.setWidth("100%");
		
		TextBox textBox_1 = new TextBox();
		flexTabEdit.setWidget(0, 1, textBox_1);
		
		Label lblNewLabel_1 = new Label("New label");
		flexTabEdit.setWidget(1, 0, lblNewLabel_1);
		
		TextBox textBox = new TextBox();
		flexTabEdit.setWidget(1, 1, textBox);
		
		Label lblNewLabel_2 = new Label("New label");
		flexTabEdit.setWidget(2, 0, lblNewLabel_2);
		
		Label lblUrl = new Label("URL");
		flexTabEdit.setWidget(2, 1, lblUrl);
		
		FlexTable flexTabLinks = new FlexTable();
		tabPanel.add(flexTabLinks, "Links", false);
		flexTabLinks.setSize("5cm", "3cm");
		
		FlexTable flexTabExtras = new FlexTable();
		tabPanel.add(flexTabExtras, "Extras", false);
		flexTabExtras.setSize("5cm", "3cm");
		
		HorizontalPanel horizontalPanel = new HorizontalPanel();
		flexTable.setWidget(2, 0, horizontalPanel);
		horizontalPanel.setSize("100%", "100%");
		
		Button btnOK = new Button("OK");
		horizontalPanel.add(btnOK);
		btnOK.setWidth("70px");
		horizontalPanel.setCellHorizontalAlignment(btnOK, HasHorizontalAlignment.ALIGN_CENTER);
		
		Button btnCancel = new Button("Cancel");
		horizontalPanel.add(btnCancel);
		btnCancel.setWidth("70px");
		horizontalPanel.setCellHorizontalAlignment(btnCancel, HasHorizontalAlignment.ALIGN_CENTER);

		dataGrid = new DataGrid<MYafraUser>();
		dataGrid.setEmptyTableWidget(new Label("leer"));
		dataGrid.setKeyboardSelectionPolicy(KeyboardSelectionPolicy.ENABLED);
		TextColumn<MYafraUser> nameColumn = new TextColumn<MYafraUser>() {
			@Override
			public String getValue(MYafraUser object) {
				return object.getName();
			}
		};
		dataGrid.addColumn(nameColumn, "Name");
		TextColumn<MYafraUser> uidColumn = new TextColumn<MYafraUser>() {
			@Override
			public String getValue(MYafraUser object) {
				return object.getUserid();
			}
		};
		dataGrid.addColumn(uidColumn, "User ID");
		TextColumn<MYafraUser> addressColumn = new TextColumn<MYafraUser>() {
			@Override
			public String getValue(MYafraUser object) {
				return object.getPicturelink();
			}
		};
		dataGrid.addColumn(addressColumn, "Avatar URL");
	    // Create a data provider.
	    YuDataProvider dataProvider = new YuDataProvider();
	    // Add the cellList to the dataProvider.
	    dataProvider.addDataDisplay(dataGrid);

	    // Create paging controls.
	    SimplePager pager = new SimplePager();
	    pager.setDisplay(dataGrid);
		pager.setWidth("574px");
		pager.setPageSize(dataProvider.getPageSize());

		final SingleSelectionModel<MYafraUser> selectionModel = new SingleSelectionModel<MYafraUser>();
		dataGrid.setSelectionModel(selectionModel);
		selectionModel
				.addSelectionChangeHandler(new SelectionChangeEvent.Handler() {
					public void onSelectionChange(SelectionChangeEvent event) {
						MYafraUser selected = selectionModel.getSelectedObject();
						if (selected != null) {
							Window.alert("You selected: " + selected.getName());
						}
					}
				});

		//dataGrid.setRowCount(TESTDATA.size(), true);
		//dataGrid.setRowData(0, TESTDATA);	
		dataGrid.flush();
		dataGrid.redraw();
		dataGrid.setTitle("Data Table");
		dataGrid.setSize("100%", "215px");
		simplePanel.add(dataGrid);
		simplePanel.add(pager);
	}
}
