using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace tdbadmin
{
	/// <summary>
	/// Main user interface with menu bar and navigation - this ui is alway shown and active.
	/// TODO:
	/// - make reports to ODBC and reset login to ODBC login strings
	/// - datagrid for pricing
	/// - call external program (kapa update)
	/// - call a webpage in IE
	/// - read table types and status types from XML file and set class tabletypes
	/// - add logging and finish EventLog logging
	/// - add emptyflag (like in Gsta) to all tdbgui functions to handle -1/UNDEF
	/// </summary>
	public class FMain : System.Windows.Forms.Form
	{
		private System.Windows.Forms.MainMenu mainMenu1;
		private System.Windows.Forms.MenuItem Main_m_open;
		private System.Windows.Forms.MenuItem Main_m_save;
		private System.Windows.Forms.MenuItem Main_m_saveas;
		private System.Windows.Forms.MenuItem Main_m_print;
		private System.Windows.Forms.MenuItem Main_m_exit;
		private System.Windows.Forms.MenuItem Main_m_cpy;
		private System.Windows.Forms.MenuItem Main_m_cut;
		private System.Windows.Forms.MenuItem Main_m_paste;
		private System.Windows.Forms.MenuItem Main_m_opts;
		private System.Windows.Forms.MenuItem Main_m_hlpwww;
		private System.Windows.Forms.MenuItem Main_m_about;
		private System.Windows.Forms.MenuItem Main_mm_file;
        private System.Windows.Forms.MenuItem Main_mm_edit;
		private System.Windows.Forms.MenuItem Main_mm_core;
		private System.Windows.Forms.MenuItem Main_mm_admin;
		private System.Windows.Forms.MenuItem Main_mm_help;
		private System.Windows.Forms.Label Main_l_db;
        private System.Windows.Forms.StatusBar Main_sb;
		private System.Windows.Forms.MenuItem Main_m_pricing;
        private System.Windows.Forms.MenuItem Main_m_allot;
		private System.Windows.Forms.MenuItem Main_m_service;
		private System.Windows.Forms.MenuItem Main_m_arr;
		private System.Windows.Forms.MenuItem Main_m_prg;
		private System.Windows.Forms.MenuItem Main_sm_types;
		private System.Windows.Forms.MenuItem Main_m_tprice;
		private System.Windows.Forms.MenuItem Main_m_tdla;
		private System.Windows.Forms.MenuItem Main_m_tdlt;
		private System.Windows.Forms.MenuItem Main_sm_geo;
		private System.Windows.Forms.MenuItem Main_m_lang;
		private System.Windows.Forms.MenuItem Main_m_country;
        private System.Windows.Forms.MenuItem Main_m_cur;
		private System.Windows.Forms.MenuItem Main_m_prof;
		private System.Windows.Forms.MenuItem Main_sm_sup;
		private System.Windows.Forms.MenuItem Main_m_dlt;
        private System.Windows.Forms.MenuItem Main_m_cat;
		private System.Windows.Forms.Label Main_l_prg;
		private System.Windows.Forms.Label Main_l_sai;
		private System.Windows.Forms.Label Main_e_db;
		private System.Windows.Forms.Label Main_l_user;
		private System.Windows.Forms.Label Main_l_sec;
		private System.Windows.Forms.Label Main_e_user;
		private System.Windows.Forms.Label Main_e_office;
		private System.Windows.Forms.Label Main_e_sec;
		private System.Windows.Forms.Label Main_e_lang;
		private System.Windows.Forms.Label Main_l_bchst;
		private System.Windows.Forms.Label Main_l_lang;
        private System.Windows.Forms.Label Main_l_dlat;
		private System.Windows.Forms.MenuItem Main_m_stawerte;
		private System.Windows.Forms.MenuItem Main_sm_actions;
		private System.Windows.Forms.MenuItem Main_m_acttype;
		private System.Windows.Forms.MenuItem Main_m_act;
		private System.Windows.Forms.MenuItem Main_m_actgrp;
        private System.Windows.Forms.MenuItem Main_m_actd;
		private System.Windows.Forms.MenuItem Main_m_city;
		private System.Windows.Forms.Label Main_e_sai;
		private System.Windows.Forms.Label Main_e_prg;
		private System.Windows.Forms.Label Main_e_dlat;
		private const string rcsid = "$Id: Main.cs,v 1.12 2009-01-04 17:05:33 mwn Exp $";
		private const string tagid = "$Name:  $";
        private System.Windows.Forms.MenuItem Main_m_dla;
        private MenuItem Main_mm_book;
        private MenuItem Main_m_tcompany;
        private MenuItem Main_m_companies;
        private MenuItem Main_m_ttrav;
        private MenuItem Main_m_tgrp;
        private MenuItem Main_sm_finance;
        private MenuItem Main_m_debit;
        private MenuItem Main_m_credit;
        private MenuItem Main_m_troubleticket;
        private MenuItem Main_m_checkupd;
        private MenuItem menuItem11;
        private MenuItem Main_m_trav;
        private MenuItem Main_m_grp;
        private MenuItem Main_m_jobsched;
        private MenuItem Main_sm_mgmtext;
        private MenuItem Main_m_bez;
        private MenuItem Main_m_text;
        private MenuItem Main_m_labels;
        private MenuItem Main_m_msg;
        private MenuItem Main_m_help;
        private MenuItem Main_m_pagesetup;
        private PrintDialog tdb_print_dialog;
        private MenuItem Main_m_season;
        private MenuItem Main_m_gra;
        private MenuItem Main_sm_prods;
        private MenuItem Main_sm_mgtmm;
        private MenuItem Main_m_pics;
        private MenuItem Main_m_comm;
        private MenuItem Main_m_er;
        private MenuItem Main_m_so;
        private MenuItem Main_m_media;
        private MenuItem Main_m_reports;
        private IContainer components;

		public FMain()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//


			// set main fields
			this.Main_e_user.Text = tdb.User.Uname;
			this.Main_e_sec.Text = tdb.User.Useclevel.ToString();
			this.Main_e_db.Text = tdb.User.Udbname;
			this.Main_e_lang.Text = tdb.User.Ulang;
			this.Main_e_office.Text = tdb.User.Uoffice;
			this.Main_e_dlat.Text = tdb.User.Udlat;
			this.Main_e_prg.Text = tdb.User.Uprg;
			this.Main_e_sai.Text = tdb.User.Usai;


			// read typeconfigs
		}


		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}


		#region Main Application Entry
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			// start main windows
			Login Flogin = new Login();
			DialogResult cret = Flogin.ShowDialog();
			if(cret == DialogResult.Cancel )
				Application.Exit();
			else
				Application.Run(new FMain());
		}
		#endregion

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FMain));
            this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
            this.Main_mm_file = new System.Windows.Forms.MenuItem();
            this.Main_m_open = new System.Windows.Forms.MenuItem();
            this.Main_m_save = new System.Windows.Forms.MenuItem();
            this.Main_m_saveas = new System.Windows.Forms.MenuItem();
            this.Main_m_pagesetup = new System.Windows.Forms.MenuItem();
            this.Main_m_print = new System.Windows.Forms.MenuItem();
            this.Main_m_exit = new System.Windows.Forms.MenuItem();
            this.Main_mm_edit = new System.Windows.Forms.MenuItem();
            this.Main_m_cpy = new System.Windows.Forms.MenuItem();
            this.Main_m_cut = new System.Windows.Forms.MenuItem();
            this.Main_m_paste = new System.Windows.Forms.MenuItem();
            this.Main_m_opts = new System.Windows.Forms.MenuItem();
            this.Main_mm_book = new System.Windows.Forms.MenuItem();
            this.Main_m_companies = new System.Windows.Forms.MenuItem();
            this.Main_m_trav = new System.Windows.Forms.MenuItem();
            this.Main_m_grp = new System.Windows.Forms.MenuItem();
            this.Main_sm_prods = new System.Windows.Forms.MenuItem();
            this.Main_m_pricing = new System.Windows.Forms.MenuItem();
            this.Main_m_allot = new System.Windows.Forms.MenuItem();
            this.Main_m_comm = new System.Windows.Forms.MenuItem();
            this.Main_m_dla = new System.Windows.Forms.MenuItem();
            this.Main_m_so = new System.Windows.Forms.MenuItem();
            this.Main_m_service = new System.Windows.Forms.MenuItem();
            this.Main_m_arr = new System.Windows.Forms.MenuItem();
            this.Main_m_prg = new System.Windows.Forms.MenuItem();
            this.Main_m_season = new System.Windows.Forms.MenuItem();
            this.Main_mm_core = new System.Windows.Forms.MenuItem();
            this.Main_sm_sup = new System.Windows.Forms.MenuItem();
            this.Main_m_dlt = new System.Windows.Forms.MenuItem();
            this.Main_m_cat = new System.Windows.Forms.MenuItem();
            this.Main_m_gra = new System.Windows.Forms.MenuItem();
            this.Main_sm_types = new System.Windows.Forms.MenuItem();
            this.Main_m_tprice = new System.Windows.Forms.MenuItem();
            this.Main_m_tdla = new System.Windows.Forms.MenuItem();
            this.Main_m_tdlt = new System.Windows.Forms.MenuItem();
            this.Main_m_tcompany = new System.Windows.Forms.MenuItem();
            this.Main_m_ttrav = new System.Windows.Forms.MenuItem();
            this.Main_m_tgrp = new System.Windows.Forms.MenuItem();
            this.Main_sm_geo = new System.Windows.Forms.MenuItem();
            this.Main_m_lang = new System.Windows.Forms.MenuItem();
            this.Main_m_country = new System.Windows.Forms.MenuItem();
            this.Main_m_city = new System.Windows.Forms.MenuItem();
            this.Main_m_cur = new System.Windows.Forms.MenuItem();
            this.Main_sm_actions = new System.Windows.Forms.MenuItem();
            this.Main_m_acttype = new System.Windows.Forms.MenuItem();
            this.Main_m_act = new System.Windows.Forms.MenuItem();
            this.Main_m_actgrp = new System.Windows.Forms.MenuItem();
            this.Main_m_actd = new System.Windows.Forms.MenuItem();
            this.Main_m_jobsched = new System.Windows.Forms.MenuItem();
            this.Main_mm_admin = new System.Windows.Forms.MenuItem();
            this.Main_sm_finance = new System.Windows.Forms.MenuItem();
            this.Main_m_debit = new System.Windows.Forms.MenuItem();
            this.Main_m_credit = new System.Windows.Forms.MenuItem();
            this.Main_m_er = new System.Windows.Forms.MenuItem();
            this.Main_m_stawerte = new System.Windows.Forms.MenuItem();
            this.Main_m_prof = new System.Windows.Forms.MenuItem();
            this.Main_sm_mgmtext = new System.Windows.Forms.MenuItem();
            this.Main_m_bez = new System.Windows.Forms.MenuItem();
            this.Main_m_text = new System.Windows.Forms.MenuItem();
            this.Main_m_labels = new System.Windows.Forms.MenuItem();
            this.Main_m_msg = new System.Windows.Forms.MenuItem();
            this.Main_m_help = new System.Windows.Forms.MenuItem();
            this.Main_sm_mgtmm = new System.Windows.Forms.MenuItem();
            this.Main_m_pics = new System.Windows.Forms.MenuItem();
            this.Main_m_media = new System.Windows.Forms.MenuItem();
            this.Main_m_reports = new System.Windows.Forms.MenuItem();
            this.Main_mm_help = new System.Windows.Forms.MenuItem();
            this.Main_m_hlpwww = new System.Windows.Forms.MenuItem();
            this.Main_m_troubleticket = new System.Windows.Forms.MenuItem();
            this.Main_m_checkupd = new System.Windows.Forms.MenuItem();
            this.menuItem11 = new System.Windows.Forms.MenuItem();
            this.Main_m_about = new System.Windows.Forms.MenuItem();
            this.Main_sb = new System.Windows.Forms.StatusBar();
            this.Main_l_db = new System.Windows.Forms.Label();
            this.Main_l_bchst = new System.Windows.Forms.Label();
            this.Main_l_lang = new System.Windows.Forms.Label();
            this.Main_l_dlat = new System.Windows.Forms.Label();
            this.Main_l_prg = new System.Windows.Forms.Label();
            this.Main_l_sai = new System.Windows.Forms.Label();
            this.Main_e_db = new System.Windows.Forms.Label();
            this.Main_e_office = new System.Windows.Forms.Label();
            this.Main_e_lang = new System.Windows.Forms.Label();
            this.Main_l_user = new System.Windows.Forms.Label();
            this.Main_l_sec = new System.Windows.Forms.Label();
            this.Main_e_user = new System.Windows.Forms.Label();
            this.Main_e_sec = new System.Windows.Forms.Label();
            this.Main_e_sai = new System.Windows.Forms.Label();
            this.Main_e_prg = new System.Windows.Forms.Label();
            this.Main_e_dlat = new System.Windows.Forms.Label();
            this.tdb_print_dialog = new System.Windows.Forms.PrintDialog();
            this.SuspendLayout();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_mm_file,
            this.Main_mm_edit,
            this.Main_mm_book,
            this.Main_sm_prods,
            this.Main_mm_core,
            this.Main_mm_admin,
            this.Main_mm_help});
            // 
            // Main_mm_file
            // 
            this.Main_mm_file.Index = 0;
            this.Main_mm_file.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_open,
            this.Main_m_save,
            this.Main_m_saveas,
            this.Main_m_pagesetup,
            this.Main_m_print,
            this.Main_m_exit});
            this.Main_mm_file.Text = "File";
            // 
            // Main_m_open
            // 
            this.Main_m_open.Index = 0;
            this.Main_m_open.Text = "Open";
            // 
            // Main_m_save
            // 
            this.Main_m_save.Index = 1;
            this.Main_m_save.Text = "Save";
            // 
            // Main_m_saveas
            // 
            this.Main_m_saveas.Index = 2;
            this.Main_m_saveas.Text = "Save As ...";
            // 
            // Main_m_pagesetup
            // 
            this.Main_m_pagesetup.Index = 3;
            this.Main_m_pagesetup.Text = "Page setup";
            this.Main_m_pagesetup.Click += new System.EventHandler(this.Main_m_pagesetup_Click);
            // 
            // Main_m_print
            // 
            this.Main_m_print.Index = 4;
            this.Main_m_print.Text = "Print ...";
            this.Main_m_print.Click += new System.EventHandler(this.Main_m_print_Click);
            // 
            // Main_m_exit
            // 
            this.Main_m_exit.Index = 5;
            this.Main_m_exit.Text = "Exit";
            this.Main_m_exit.Click += new System.EventHandler(this.Main_m_exit_Click);
            // 
            // Main_mm_edit
            // 
            this.Main_mm_edit.Index = 1;
            this.Main_mm_edit.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_cpy,
            this.Main_m_cut,
            this.Main_m_paste,
            this.Main_m_opts});
            this.Main_mm_edit.Text = "Edit";
            // 
            // Main_m_cpy
            // 
            this.Main_m_cpy.Index = 0;
            this.Main_m_cpy.Text = "Copy";
            // 
            // Main_m_cut
            // 
            this.Main_m_cut.Index = 1;
            this.Main_m_cut.Text = "Cut";
            // 
            // Main_m_paste
            // 
            this.Main_m_paste.Index = 2;
            this.Main_m_paste.Text = "Paste";
            // 
            // Main_m_opts
            // 
            this.Main_m_opts.Index = 3;
            this.Main_m_opts.Text = "Options";
            this.Main_m_opts.Click += new System.EventHandler(this.Main_m_opts_Click);
            // 
            // Main_mm_book
            // 
            this.Main_mm_book.Index = 2;
            this.Main_mm_book.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_companies,
            this.Main_m_trav,
            this.Main_m_grp});
            this.Main_mm_book.Text = "Customers";
            // 
            // Main_m_companies
            // 
            this.Main_m_companies.Index = 0;
            this.Main_m_companies.Text = "Companies";
            this.Main_m_companies.Click += new System.EventHandler(this.Main_m_companies_Click);
            // 
            // Main_m_trav
            // 
            this.Main_m_trav.Index = 1;
            this.Main_m_trav.Text = "Travelers";
            this.Main_m_trav.Click += new System.EventHandler(this.Main_m_trav_Click);
            // 
            // Main_m_grp
            // 
            this.Main_m_grp.Index = 2;
            this.Main_m_grp.Text = "Groups";
            this.Main_m_grp.Click += new System.EventHandler(this.Main_m_grp_Click);
            // 
            // Main_sm_prods
            // 
            this.Main_sm_prods.Index = 3;
            this.Main_sm_prods.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_pricing,
            this.Main_m_allot,
            this.Main_m_comm,
            this.Main_m_dla,
            this.Main_m_so,
            this.Main_m_service,
            this.Main_m_arr,
            this.Main_m_prg,
            this.Main_m_season});
            this.Main_sm_prods.Text = "Products";
            // 
            // Main_m_pricing
            // 
            this.Main_m_pricing.Index = 0;
            this.Main_m_pricing.Text = "Pricing";
            this.Main_m_pricing.Click += new System.EventHandler(this.Main_m_pricing_Click);
            // 
            // Main_m_allot
            // 
            this.Main_m_allot.Index = 1;
            this.Main_m_allot.Text = "Allotments";
            this.Main_m_allot.Click += new System.EventHandler(this.Main_m_allot_Click);
            // 
            // Main_m_comm
            // 
            this.Main_m_comm.Index = 2;
            this.Main_m_comm.Text = "Commissions";
            this.Main_m_comm.Click += new System.EventHandler(this.Main_m_comm_Click);
            // 
            // Main_m_dla
            // 
            this.Main_m_dla.Index = 3;
            this.Main_m_dla.Text = "Offering";
            this.Main_m_dla.Click += new System.EventHandler(this.Main_m_dla_Click);
            // 
            // Main_m_so
            // 
            this.Main_m_so.Index = 4;
            this.Main_m_so.Text = "Service offering";
            this.Main_m_so.Click += new System.EventHandler(this.Main_m_so_Click);
            // 
            // Main_m_service
            // 
            this.Main_m_service.Index = 5;
            this.Main_m_service.Text = "Services";
            this.Main_m_service.Click += new System.EventHandler(this.Main_m_service_Click);
            // 
            // Main_m_arr
            // 
            this.Main_m_arr.Index = 6;
            this.Main_m_arr.Text = "Arrangements";
            this.Main_m_arr.Click += new System.EventHandler(this.Main_m_arr_Click);
            // 
            // Main_m_prg
            // 
            this.Main_m_prg.Index = 7;
            this.Main_m_prg.Text = "Programs";
            this.Main_m_prg.Click += new System.EventHandler(this.Main_m_prg_Click);
            // 
            // Main_m_season
            // 
            this.Main_m_season.Index = 8;
            this.Main_m_season.Text = "Season";
            this.Main_m_season.Click += new System.EventHandler(this.Main_m_season_Click);
            // 
            // Main_mm_core
            // 
            this.Main_mm_core.Index = 4;
            this.Main_mm_core.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_sm_sup,
            this.Main_sm_types,
            this.Main_sm_geo,
            this.Main_sm_actions});
            this.Main_mm_core.Text = "Core Data";
            // 
            // Main_sm_sup
            // 
            this.Main_sm_sup.Index = 0;
            this.Main_sm_sup.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_dlt,
            this.Main_m_cat,
            this.Main_m_gra});
            this.Main_sm_sup.Text = "Suppliers";
            // 
            // Main_m_dlt
            // 
            this.Main_m_dlt.Index = 0;
            this.Main_m_dlt.Text = "Suppliers";
            this.Main_m_dlt.Click += new System.EventHandler(this.Main_m_dlt_Click);
            // 
            // Main_m_cat
            // 
            this.Main_m_cat.Index = 1;
            this.Main_m_cat.Text = "Categories";
            this.Main_m_cat.Click += new System.EventHandler(this.Main_m_cat_Click);
            // 
            // Main_m_gra
            // 
            this.Main_m_gra.Index = 2;
            this.Main_m_gra.Text = "Graphics";
            this.Main_m_gra.Click += new System.EventHandler(this.Main_m_gra_Click);
            // 
            // Main_sm_types
            // 
            this.Main_sm_types.Index = 1;
            this.Main_sm_types.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_tprice,
            this.Main_m_tdla,
            this.Main_m_tdlt,
            this.Main_m_tcompany,
            this.Main_m_ttrav,
            this.Main_m_tgrp});
            this.Main_sm_types.Text = "Types";
            // 
            // Main_m_tprice
            // 
            this.Main_m_tprice.Index = 0;
            this.Main_m_tprice.Text = "Pricing";
            this.Main_m_tprice.Click += new System.EventHandler(this.Main_m_tprice_Click);
            // 
            // Main_m_tdla
            // 
            this.Main_m_tdla.Index = 1;
            this.Main_m_tdla.Text = "Offer";
            this.Main_m_tdla.Click += new System.EventHandler(this.Main_m_tdla_Click);
            // 
            // Main_m_tdlt
            // 
            this.Main_m_tdlt.Index = 2;
            this.Main_m_tdlt.Text = "Supplier";
            this.Main_m_tdlt.Click += new System.EventHandler(this.Main_m_tdlt_Click);
            // 
            // Main_m_tcompany
            // 
            this.Main_m_tcompany.Index = 3;
            this.Main_m_tcompany.Text = "Company";
            this.Main_m_tcompany.Click += new System.EventHandler(this.Main_m_tcompany_Click);
            // 
            // Main_m_ttrav
            // 
            this.Main_m_ttrav.Index = 4;
            this.Main_m_ttrav.Text = "Traveler";
            this.Main_m_ttrav.Click += new System.EventHandler(this.Main_m_ttrav_Click);
            // 
            // Main_m_tgrp
            // 
            this.Main_m_tgrp.Index = 5;
            this.Main_m_tgrp.Text = "Group";
            this.Main_m_tgrp.Click += new System.EventHandler(this.Main_m_tgrp_Click);
            // 
            // Main_sm_geo
            // 
            this.Main_sm_geo.Index = 2;
            this.Main_sm_geo.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_lang,
            this.Main_m_country,
            this.Main_m_city,
            this.Main_m_cur});
            this.Main_sm_geo.Text = "Geo";
            // 
            // Main_m_lang
            // 
            this.Main_m_lang.Index = 0;
            this.Main_m_lang.Text = "Languages";
            this.Main_m_lang.Click += new System.EventHandler(this.Main_m_lang_Click);
            // 
            // Main_m_country
            // 
            this.Main_m_country.Index = 1;
            this.Main_m_country.Text = "Countries";
            this.Main_m_country.Click += new System.EventHandler(this.Main_m_country_Click);
            // 
            // Main_m_city
            // 
            this.Main_m_city.Index = 2;
            this.Main_m_city.Text = "Cities";
            this.Main_m_city.Click += new System.EventHandler(this.Main_m_city_Click);
            // 
            // Main_m_cur
            // 
            this.Main_m_cur.Index = 3;
            this.Main_m_cur.Text = "Currencies";
            this.Main_m_cur.Click += new System.EventHandler(this.Main_m_cur_Click);
            // 
            // Main_sm_actions
            // 
            this.Main_sm_actions.Index = 3;
            this.Main_sm_actions.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_acttype,
            this.Main_m_act,
            this.Main_m_actgrp,
            this.Main_m_actd,
            this.Main_m_jobsched});
            this.Main_sm_actions.Text = "Actions";
            // 
            // Main_m_acttype
            // 
            this.Main_m_acttype.Index = 0;
            this.Main_m_acttype.Text = "Actiontype";
            this.Main_m_acttype.Click += new System.EventHandler(this.Main_m_acttype_Click);
            // 
            // Main_m_act
            // 
            this.Main_m_act.Index = 1;
            this.Main_m_act.Text = "Actions";
            this.Main_m_act.Click += new System.EventHandler(this.Main_m_act_Click);
            // 
            // Main_m_actgrp
            // 
            this.Main_m_actgrp.Index = 2;
            this.Main_m_actgrp.Text = "Actiongroups";
            this.Main_m_actgrp.Click += new System.EventHandler(this.Main_m_actgrp_Click);
            // 
            // Main_m_actd
            // 
            this.Main_m_actd.Index = 3;
            this.Main_m_actd.Text = "Actiondetails";
            this.Main_m_actd.Click += new System.EventHandler(this.Main_m_actd_Click);
            // 
            // Main_m_jobsched
            // 
            this.Main_m_jobsched.Index = 4;
            this.Main_m_jobsched.Text = "Schedule Jobs";
            this.Main_m_jobsched.Click += new System.EventHandler(this.Main_m_jobsched_Click);
            // 
            // Main_mm_admin
            // 
            this.Main_mm_admin.Index = 5;
            this.Main_mm_admin.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_sm_finance,
            this.Main_m_stawerte,
            this.Main_m_prof,
            this.Main_sm_mgmtext,
            this.Main_sm_mgtmm,
            this.Main_m_reports});
            this.Main_mm_admin.Text = "Administration";
            // 
            // Main_sm_finance
            // 
            this.Main_sm_finance.Index = 0;
            this.Main_sm_finance.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_debit,
            this.Main_m_credit,
            this.Main_m_er});
            this.Main_sm_finance.Text = "Finance";
            // 
            // Main_m_debit
            // 
            this.Main_m_debit.Index = 0;
            this.Main_m_debit.Text = "Accounts payable";
            this.Main_m_debit.Click += new System.EventHandler(this.Main_m_debit_Click);
            // 
            // Main_m_credit
            // 
            this.Main_m_credit.Index = 1;
            this.Main_m_credit.Text = "Accounts receivable";
            this.Main_m_credit.Click += new System.EventHandler(this.Main_m_credit_Click);
            // 
            // Main_m_er
            // 
            this.Main_m_er.Index = 2;
            this.Main_m_er.Text = "Exchange Rates";
            this.Main_m_er.Click += new System.EventHandler(this.Main_m_er_Click);
            // 
            // Main_m_stawerte
            // 
            this.Main_m_stawerte.Index = 1;
            this.Main_m_stawerte.Text = "Status values";
            this.Main_m_stawerte.Click += new System.EventHandler(this.Main_m_stawerte_Click);
            // 
            // Main_m_prof
            // 
            this.Main_m_prof.Index = 2;
            this.Main_m_prof.Text = "User Profile";
            this.Main_m_prof.Click += new System.EventHandler(this.Main_m_prof_Click);
            // 
            // Main_sm_mgmtext
            // 
            this.Main_sm_mgmtext.Index = 3;
            this.Main_sm_mgmtext.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_bez,
            this.Main_m_text,
            this.Main_m_labels,
            this.Main_m_msg,
            this.Main_m_help});
            this.Main_sm_mgmtext.Text = "Manage text";
            // 
            // Main_m_bez
            // 
            this.Main_m_bez.Index = 0;
            this.Main_m_bez.Text = "Descriptions";
            this.Main_m_bez.Click += new System.EventHandler(this.Main_m_bez_Click);
            // 
            // Main_m_text
            // 
            this.Main_m_text.Index = 1;
            this.Main_m_text.Text = "Long descriptions";
            this.Main_m_text.Click += new System.EventHandler(this.Main_m_text_Click);
            // 
            // Main_m_labels
            // 
            this.Main_m_labels.Index = 2;
            this.Main_m_labels.Text = "Labels";
            this.Main_m_labels.Click += new System.EventHandler(this.Main_m_labels_Click);
            // 
            // Main_m_msg
            // 
            this.Main_m_msg.Index = 3;
            this.Main_m_msg.Text = "Messages";
            this.Main_m_msg.Click += new System.EventHandler(this.Main_m_msg_Click);
            // 
            // Main_m_help
            // 
            this.Main_m_help.Index = 4;
            this.Main_m_help.Text = "Help";
            this.Main_m_help.Click += new System.EventHandler(this.Main_m_help_Click);
            // 
            // Main_sm_mgtmm
            // 
            this.Main_sm_mgtmm.Index = 4;
            this.Main_sm_mgtmm.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_pics,
            this.Main_m_media});
            this.Main_sm_mgtmm.Text = "Manage multimedia";
            // 
            // Main_m_pics
            // 
            this.Main_m_pics.Index = 0;
            this.Main_m_pics.Text = "Pictures";
            this.Main_m_pics.Click += new System.EventHandler(this.Main_m_pics_Click);
            // 
            // Main_m_media
            // 
            this.Main_m_media.Index = 1;
            this.Main_m_media.Text = "Media";
            this.Main_m_media.Click += new System.EventHandler(this.Main_m_media_Click);
            // 
            // Main_m_reports
            // 
            this.Main_m_reports.Index = 5;
            this.Main_m_reports.Text = "Reports";
            this.Main_m_reports.Click += new System.EventHandler(this.Main_m_reports_Click);
            // 
            // Main_mm_help
            // 
            this.Main_mm_help.Index = 6;
            this.Main_mm_help.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.Main_m_hlpwww,
            this.Main_m_troubleticket,
            this.Main_m_checkupd,
            this.menuItem11,
            this.Main_m_about});
            this.Main_mm_help.Text = "Help";
            // 
            // Main_m_hlpwww
            // 
            this.Main_m_hlpwww.Index = 0;
            this.Main_m_hlpwww.Text = "Help on the Web";
            this.Main_m_hlpwww.Click += new System.EventHandler(this.Main_m_hlpwww_Click);
            // 
            // Main_m_troubleticket
            // 
            this.Main_m_troubleticket.Index = 1;
            this.Main_m_troubleticket.Text = "Raise an issue ...";
            this.Main_m_troubleticket.Click += new System.EventHandler(this.Main_m_troubleticket_Click);
            // 
            // Main_m_checkupd
            // 
            this.Main_m_checkupd.Index = 2;
            this.Main_m_checkupd.Text = "Check for updates";
            this.Main_m_checkupd.Click += new System.EventHandler(this.Main_m_checkupd_Click);
            // 
            // menuItem11
            // 
            this.menuItem11.Index = 3;
            this.menuItem11.Text = "-";
            // 
            // Main_m_about
            // 
            this.Main_m_about.Index = 4;
            this.Main_m_about.Text = "About";
            this.Main_m_about.Click += new System.EventHandler(this.Main_m_about_Click);
            // 
            // Main_sb
            // 
            this.Main_sb.Location = new System.Drawing.Point(0, 213);
            this.Main_sb.Name = "Main_sb";
            this.Main_sb.Size = new System.Drawing.Size(462, 22);
            this.Main_sb.TabIndex = 1;
            this.Main_sb.Text = "Ready";
            // 
            // Main_l_db
            // 
            this.Main_l_db.Location = new System.Drawing.Point(16, 16);
            this.Main_l_db.Name = "Main_l_db";
            this.Main_l_db.Size = new System.Drawing.Size(100, 23);
            this.Main_l_db.TabIndex = 2;
            this.Main_l_db.Text = "Database:";
            // 
            // Main_l_bchst
            // 
            this.Main_l_bchst.Location = new System.Drawing.Point(16, 85);
            this.Main_l_bchst.Name = "Main_l_bchst";
            this.Main_l_bchst.Size = new System.Drawing.Size(100, 23);
            this.Main_l_bchst.TabIndex = 3;
            this.Main_l_bchst.Text = "Office";
            // 
            // Main_l_lang
            // 
            this.Main_l_lang.Location = new System.Drawing.Point(16, 109);
            this.Main_l_lang.Name = "Main_l_lang";
            this.Main_l_lang.Size = new System.Drawing.Size(100, 23);
            this.Main_l_lang.TabIndex = 4;
            this.Main_l_lang.Text = "Language";
            // 
            // Main_l_dlat
            // 
            this.Main_l_dlat.Location = new System.Drawing.Point(16, 136);
            this.Main_l_dlat.Name = "Main_l_dlat";
            this.Main_l_dlat.Size = new System.Drawing.Size(100, 23);
            this.Main_l_dlat.TabIndex = 5;
            this.Main_l_dlat.Text = "Servicetype";
            // 
            // Main_l_prg
            // 
            this.Main_l_prg.Location = new System.Drawing.Point(16, 160);
            this.Main_l_prg.Name = "Main_l_prg";
            this.Main_l_prg.Size = new System.Drawing.Size(100, 23);
            this.Main_l_prg.TabIndex = 6;
            this.Main_l_prg.Text = "Program";
            // 
            // Main_l_sai
            // 
            this.Main_l_sai.Location = new System.Drawing.Point(16, 184);
            this.Main_l_sai.Name = "Main_l_sai";
            this.Main_l_sai.Size = new System.Drawing.Size(100, 23);
            this.Main_l_sai.TabIndex = 7;
            this.Main_l_sai.Text = "Season";
            // 
            // Main_e_db
            // 
            this.Main_e_db.Location = new System.Drawing.Point(136, 19);
            this.Main_e_db.Name = "Main_e_db";
            this.Main_e_db.Size = new System.Drawing.Size(240, 23);
            this.Main_e_db.TabIndex = 10;
            // 
            // Main_e_office
            // 
            this.Main_e_office.Location = new System.Drawing.Point(136, 88);
            this.Main_e_office.Name = "Main_e_office";
            this.Main_e_office.Size = new System.Drawing.Size(240, 23);
            this.Main_e_office.TabIndex = 11;
            // 
            // Main_e_lang
            // 
            this.Main_e_lang.Location = new System.Drawing.Point(136, 112);
            this.Main_e_lang.Name = "Main_e_lang";
            this.Main_e_lang.Size = new System.Drawing.Size(240, 23);
            this.Main_e_lang.TabIndex = 13;
            // 
            // Main_l_user
            // 
            this.Main_l_user.Location = new System.Drawing.Point(16, 40);
            this.Main_l_user.Name = "Main_l_user";
            this.Main_l_user.Size = new System.Drawing.Size(100, 23);
            this.Main_l_user.TabIndex = 14;
            this.Main_l_user.Text = "User";
            // 
            // Main_l_sec
            // 
            this.Main_l_sec.Location = new System.Drawing.Point(16, 64);
            this.Main_l_sec.Name = "Main_l_sec";
            this.Main_l_sec.Size = new System.Drawing.Size(100, 23);
            this.Main_l_sec.TabIndex = 15;
            this.Main_l_sec.Text = "Security Level";
            // 
            // Main_e_user
            // 
            this.Main_e_user.Location = new System.Drawing.Point(136, 40);
            this.Main_e_user.Name = "Main_e_user";
            this.Main_e_user.Size = new System.Drawing.Size(240, 23);
            this.Main_e_user.TabIndex = 16;
            // 
            // Main_e_sec
            // 
            this.Main_e_sec.Location = new System.Drawing.Point(136, 64);
            this.Main_e_sec.Name = "Main_e_sec";
            this.Main_e_sec.Size = new System.Drawing.Size(240, 23);
            this.Main_e_sec.TabIndex = 17;
            // 
            // Main_e_sai
            // 
            this.Main_e_sai.Location = new System.Drawing.Point(136, 184);
            this.Main_e_sai.Name = "Main_e_sai";
            this.Main_e_sai.Size = new System.Drawing.Size(240, 23);
            this.Main_e_sai.TabIndex = 20;
            // 
            // Main_e_prg
            // 
            this.Main_e_prg.Location = new System.Drawing.Point(136, 160);
            this.Main_e_prg.Name = "Main_e_prg";
            this.Main_e_prg.Size = new System.Drawing.Size(240, 23);
            this.Main_e_prg.TabIndex = 21;
            // 
            // Main_e_dlat
            // 
            this.Main_e_dlat.Location = new System.Drawing.Point(136, 136);
            this.Main_e_dlat.Name = "Main_e_dlat";
            this.Main_e_dlat.Size = new System.Drawing.Size(240, 23);
            this.Main_e_dlat.TabIndex = 22;
            // 
            // tdb_print_dialog
            // 
            this.tdb_print_dialog.UseEXDialog = true;
            // 
            // FMain
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(462, 235);
            this.Controls.Add(this.Main_e_dlat);
            this.Controls.Add(this.Main_e_prg);
            this.Controls.Add(this.Main_e_sai);
            this.Controls.Add(this.Main_e_sec);
            this.Controls.Add(this.Main_e_user);
            this.Controls.Add(this.Main_l_sec);
            this.Controls.Add(this.Main_l_user);
            this.Controls.Add(this.Main_e_lang);
            this.Controls.Add(this.Main_e_office);
            this.Controls.Add(this.Main_e_db);
            this.Controls.Add(this.Main_l_sai);
            this.Controls.Add(this.Main_l_prg);
            this.Controls.Add(this.Main_l_dlat);
            this.Controls.Add(this.Main_l_lang);
            this.Controls.Add(this.Main_l_bchst);
            this.Controls.Add(this.Main_l_db);
            this.Controls.Add(this.Main_sb);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Menu = this.mainMenu1;
            this.Name = "FMain";
            this.Text = "Main";
            this.Closed += new System.EventHandler(this.Exit);
            this.Closing += new System.ComponentModel.CancelEventHandler(this.Exit);
            this.ResumeLayout(false);

		}
		#endregion

		#region Callback functions
		private void Exit(object sender, System.ComponentModel.CancelEventArgs e)
		{
			Main_m_exit_Click(sender, e);
		}

		private void Exit(object sender, System.EventArgs e)
		{
			Main_m_exit_Click(sender, e);
		}
		private void Main_m_exit_Click(object sender, System.EventArgs e)
		{
			Application.Exit();
		}

		private void Main_m_about_Click(object sender, System.EventArgs e)
		{
			About Fa = new About();
			Fa.ShowDialog();
		}

		private void Main_m_opts_Click(object sender, System.EventArgs e)
		{
			Options Fopt = new Options();
			Fopt.ShowDialog();
		}

		private void Main_m_prof_Click(object sender, System.EventArgs e)
		{
			GUIuser Fuserprof = new GUIuser();
			Fuserprof.ShowDialog();
		}
		
		private void Main_m_stawerte_Click(object sender, System.EventArgs e)
		{
			FSta FS = new FSta();
			FS.ShowDialog();
		}

		private void Main_m_lang_Click(object sender, System.EventArgs e)
		{
			FLang Fl = new FLang();
			Fl.ShowDialog();
		}

		private void Main_m_country_Click(object sender, System.EventArgs e)
		{
			FCountry Fc = new FCountry();
			Fc.ShowDialog();
		}

		private void Main_m_city_Click(object sender, System.EventArgs e)
		{
			FCity F = new FCity();
			F.ShowDialog();
		}

		private void Main_m_cur_Click(object sender, System.EventArgs e)
		{
			FCur F = new FCur();
			F.ShowDialog();
		}

		private void Main_m_prg_Click(object sender, System.EventArgs e)
		{
			FPrg Fpt = new FPrg();
			Fpt.ShowDialog();
		}
	
		private void Main_m_arr_Click(object sender, System.EventArgs e)
		{
			FArr F = new FArr();
			F.ShowDialog();
		}
	
		private void Main_m_tdla_Click(object sender, System.EventArgs e)
		{
			FOfferType Fot = new FOfferType();
			Fot.ShowDialog();
		}

        private void Main_m_tcompany_Click(object sender, System.EventArgs e)
		{
			FCustomType Fkt = new FCustomType();
			Fkt.ShowDialog();
		}

		private void Main_m_tdlt_Click(object sender, System.EventArgs e)
		{
			FSupType Fpt = new FSupType();
			Fpt.ShowDialog();
		}

        private void Main_m_ttrav_Click(object sender, System.EventArgs e)
		{
			FPersType Fpt = new FPersType();
			Fpt.ShowDialog();
		}

		private void Main_m_kolt_Click(object sender, System.EventArgs e)
		{	
			FGrpType Fpt = new FGrpType();
			Fpt.ShowDialog();
		}

		private void Main_m_tprice_Click(object sender, System.EventArgs e)
		{
            FPricetype Fpt = new FPricetype();
			Fpt.ShowDialog();
		}

		private void Main_m_acttype_Click(object sender, System.EventArgs e)
		{
			FActType Fat = new FActType();
			Fat.ShowDialog();
		}

		private void Main_m_currate_Click(object sender, System.EventArgs e)
		{
			Fer F = new Fer();
			F.ShowDialog();
		}

		private void Main_m_cat_Click(object sender, System.EventArgs e)
		{
			FCat F = new FCat();
			F.ShowDialog();
		}

		private void Main_m_dlt_Click(object sender, System.EventArgs e)
		{
			FSup F = new FSup();
			F.ShowDialog();
		}

		private void Main_m_act_Click(object sender, System.EventArgs e)
		{
			FAct Fa = new FAct();
			Fa.ShowDialog();
		}

		private void Main_m_dla_Click(object sender, System.EventArgs e)
		{
			FOffer F = new FOffer();
			F.ShowDialog();
		}

        private void Main_m_bez_Click(object sender, EventArgs e)
        {
            FBez F = new FBez();
            F.ShowDialog();
        }

        private void Main_m_service_Click(object sender, EventArgs e)
        {
            FService F = new FService();
            F.ShowDialog();
        }

        private void Main_m_companies_Click(object sender, EventArgs e)
        {
            FCustomer F = new FCustomer();
            F.ShowDialog();
        }

        private void Main_m_trav_Click(object sender, EventArgs e)
        {
            FTraveler F = new FTraveler();
            F.ShowDialog();
        }

        private void Main_m_tgrp_Click(object sender, EventArgs e)
        {
            FGrp F = new FGrp();
            F.ShowDialog();
        }

        private void Main_m_season_Click(object sender, EventArgs e)
        {
            FSeason F = new FSeason();
            F.ShowDialog();
        }

        private void Main_m_print_Click(object sender, EventArgs e)
        {
            tdb_print_dialog.ShowDialog();

        }

        private void Main_m_pagesetup_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_er_Click(object sender, EventArgs e)
        {
            Fer F = new Fer();
            F.ShowDialog();

        }

        private void Main_m_gra_Click(object sender, EventArgs e)
        {
            FGraphics F = new FGraphics();
            F.ShowDialog();
        }

        private void Main_m_so_Click(object sender, EventArgs e)
        {
            FServiceoffer F = new FServiceoffer();
            F.ShowDialog();
        }

        private void Main_m_grp_Click(object sender, EventArgs e)
        {
            FGrp F = new FGrp();
            F.ShowDialog();
        }

        private void Main_m_pricing_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_allot_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_comm_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_actgrp_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_actd_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_jobsched_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"\usr\local\bin\OUTkapaupdate.exe -D -U tdbadmin -d traveldb");

        }

        private void Main_m_debit_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_credit_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_text_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_labels_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_msg_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_help_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_pics_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_media_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_reports_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_hlpwww_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_troubleticket_Click(object sender, EventArgs e)
        {

        }

        private void Main_m_checkupd_Click(object sender, EventArgs e)
        {

        }
        #endregion

    }
}
