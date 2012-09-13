package org.yafra.gwt.admin.client;

import org.yafra.gwt.admin.shared.FieldVerifier;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.Command;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.HasHorizontalAlignment;
import com.google.gwt.user.client.ui.HasVerticalAlignment;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.MenuBar;
import com.google.gwt.user.client.ui.MenuItem;
import com.google.gwt.user.client.ui.PasswordTextBox;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.SimplePanel;
import com.google.gwt.user.client.ui.TextBox;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class AdminEntryPoint implements EntryPoint {
	public boolean doLogin;
	public Label lblWelcome = new Label();
	public Label lblStatus = new Label("OK");
	public HTML htmlStatus = new HTML("Status message here", true);
	SimplePanel panelData;
	/**
	 * Create a remote service proxy to talk to the server-side Greeting service.
	 */
	private final YafraAdminServiceAsync YafraAdminService = GWT
			.create(YafraAdminService.class);
	private RootPanel rootPanel_1;
	FlexTable flexTable;
	
	/**
	 * This is the entry point method.
	 */
	public void onModuleLoad() {
		
		rootPanel_1 = RootPanel.get();
		rootPanel_1.setSize("830", "700");

		MainPanel();
		LoginAdmin();
	}

	public void LoginAdmin() {
		doLogin = false;
		
		final DialogBox dialogBox = new DialogBox();
		dialogBox.setText("Yafra Login");
		dialogBox.setAnimationEnabled(true);
		FlexTable flexTable = new FlexTable();
		flexTable.setSize("100%", "100%");
		
		lblWelcome.setText("Login to yafra administrator");
		lblWelcome.setWordWrap(false);
		flexTable.setWidget(0, 0, lblWelcome);
		lblWelcome.setWidth("86px");
		
		Label lblUsername = new Label("Username");
		flexTable.setWidget(1, 0, lblUsername);
		
		final TextBox textBoxUsername = new TextBox();
		flexTable.setWidget(1, 1, textBoxUsername);
		textBoxUsername.setWidth("270px");
		// Focus the cursor on the name field when the app loads
		textBoxUsername.setFocus(true);
		textBoxUsername.selectAll();
		
		Label lblPassword = new Label("Password");
		flexTable.setWidget(2, 0, lblPassword);
		
		final PasswordTextBox textBoxPwd = new PasswordTextBox();
		flexTable.setWidget(2, 1, textBoxPwd);
		textBoxPwd.setWidth("270px");
		
		final Button btnOKLogin = new Button("OK");
		btnOKLogin.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				// First, we validate the input.
				String Username = textBoxUsername.getText();
				if (!FieldVerifier.isValidName(Username)) {
					lblWelcome.setText("Username / pwd is wrong or empty please use correct name and password - try again");
					return;
				}
				String Pwd = textBoxPwd.getText();
				sendLogin(Username, Pwd);
				btnOKLogin.setEnabled(true);
				btnOKLogin.setFocus(true);
				RootPanel.get().remove(dialogBox);
			}
		});
		flexTable.setWidget(3, 0, btnOKLogin);
		btnOKLogin.setWidth("51px");
		
		Button btnCancelLogin = new Button("Cancel");
		btnCancelLogin.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				lblWelcome.setText("Please try again or close this page/tab");
				// exit app or show standard text without login
			}
		});
		flexTable.setWidget(3, 1, btnCancelLogin);
		flexTable.getCellFormatter().setHorizontalAlignment(3, 0, HasHorizontalAlignment.ALIGN_RIGHT);
		flexTable.getFlexCellFormatter().setColSpan(0, 0, 2);
		dialogBox.add(flexTable);
		rootPanel_1.add(dialogBox, 140, 100);
	}
	
	public void MainPanel() {
		
		// app panel
		flexTable = new FlexTable();
		
		// header panel
		String html = "<div id='yafraheader' "
			+ "style='border:3px dotted blue;'>"
			+ "<p>Yafra Administration Application</p></div>";
		HTMLPanel panelHeader = new HTMLPanel(html);
		flexTable.setWidget(0, 0, panelHeader);
		flexTable.getCellFormatter().setHeight(0, 0, "35");
		panelHeader.setSize("100%", "100%");
		//panelHeader.addStyleName("yafra-header");
		
		// menu bar panel
		SimplePanel panelMenu = new SimplePanel();
		flexTable.setWidget(1, 0, panelMenu);
		panelMenu.setWidth("100%");
		
		MenuBar menuBar = new MenuBar(false);
		panelMenu.setWidget(menuBar);
		menuBar.setSize("100%", "100%");
		MenuBar menuBar_1 = new MenuBar(true);
		
		MenuItem mntmFile = new MenuItem("File", false, menuBar_1);
		
		MenuItem mntmImport = new MenuItem("Import", false, (Command) null);
		menuBar_1.addItem(mntmImport);
		
		MenuItem mntmExit = new MenuItem("Exit", false, new Command() {
			public void execute() {
				closeBrowser();
				// TODO do closing of application here - close browser windows if possible
			}
		});
		menuBar_1.addItem(mntmExit);
		menuBar.addItem(mntmFile);
		MenuBar menuBar_2 = new MenuBar(true);
		
		MenuItem mntmEdit = new MenuItem("Edit", false, menuBar_2);
		
		MenuItem mntmPreferences = new MenuItem("Preferences", false, (Command) null);
		menuBar_2.addItem(mntmPreferences);
		menuBar.addItem(mntmEdit);
		MenuBar menuBar_3 = new MenuBar(true);
		
		MenuItem mntmAdministration = new MenuItem("Administration", false, menuBar_3);
		
		MenuItem mntmUsers = new MenuItem("Users", false, new Command() {
			public void execute() {
				YuTable yudg = new YuTable();
				flexTable.clearCell(2, 0);
				flexTable.setWidget(2, 0, yudg.asWidget());
			}
		});
		menuBar_3.addItem(mntmUsers);
		menuBar.addItem(mntmAdministration);
		MenuBar menuBar_4 = new MenuBar(true);
		
		MenuItem mntmHelp = new MenuItem("Help", false, menuBar_4);
		
		MenuItem mntmOnlineHelp = new MenuItem("Online Help", false, (Command) null);
		menuBar_4.addItem(mntmOnlineHelp);
		
		MenuItem mntmAbout = new MenuItem("About", false, (Command) null);
		menuBar_4.addItem(mntmAbout);
		menuBar.addItem(mntmHelp);
		
		// Main panel //
		HTMLPanel panelWelcome = new HTMLPanel("Welcome to Yafra Administration<p>Please login and choose an action");
		flexTable.setWidget(2, 0, panelWelcome);
		flexTable.setSize("583px", "596px");
		
		// Footer panel //
		SimplePanel panelFooter = new SimplePanel();
		flexTable.setWidget(3, 0, panelFooter);
		panelFooter.setWidth("100%");
		
		HorizontalPanel panelFooterDetail = new HorizontalPanel();
		panelFooter.setWidget(panelFooterDetail);
		panelFooterDetail.setSize("100%", "100%");
		
		panelFooterDetail.add(htmlStatus);
		htmlStatus.setSize("616px", "21px");
		
		panelFooterDetail.add(lblStatus);
		lblStatus.setWidth("74px");
		flexTable.getCellFormatter().setVerticalAlignment(1, 0, HasVerticalAlignment.ALIGN_TOP);
		flexTable.getCellFormatter().setVerticalAlignment(3, 0, HasVerticalAlignment.ALIGN_BOTTOM);
		flexTable.setSize("782px", "587px");

		// add app panel to root //
		rootPanel_1.add(flexTable, 10, 10);
	}
	
	native  public static void closeBrowser()/*-{ 
	 $wnd.close(); 
	}-*/; 
	
	private void sendLogin(String user, String pwd) {

		// Then, we send the input to the server.
		YafraAdminService.doLogin(user, pwd,
				new AsyncCallback<String>() {
					public void onFailure(Throwable caught) {
						// Show the RPC error message to the user
						LoginAdmin();
						lblWelcome.setText("Login failed - please try again");
						htmlStatus.setHTML("Login error" + caught.toString());
					}

					public void onSuccess(String result) {
						doLogin = true;
						htmlStatus.setHTML(result);
						lblStatus.setText("Logged in - OK");
						
					}
				});
	}
}
