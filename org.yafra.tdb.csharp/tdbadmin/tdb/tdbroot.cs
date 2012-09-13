using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Abstraction of all tdb table objects.
	/// </summary>
	public abstract class tdbroot : DBtools
	{
		protected int id;
		protected string code;
		protected string bez;
		protected int bez_id;
		protected int text_id;
		protected string text;
		protected int typ;
		protected bool optional;

		public tdbroot():base(tdb.User.Uhelper, tdb.User.Udbcon)
		{
			//
			// TODO: Add constructor logic here
			//
			typ = 0;
			id = -1;
			bez_id = -1;
			text_id = -1;
			optional = false;
		}

		public virtual int ObjId { get {return id;} set {id = value;} }
		public virtual string ObjBez { get {return bez;} set {bez = value;} }
		public virtual string ObjCode { get {return code;} set {code = value;} }
		public virtual int ObjBezId { get {return bez_id;} set {bez_id = value;} }
		public virtual int ObjTextId { get {return text_id;} set {text_id = value;} }
		public virtual string ObjText { get {return text;} set {text = value;} }
		public virtual int ObjTyp { get {return typ;} set {typ = value;} }
		public bool ObjOptional { get {return optional;} set {optional = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public abstract void Get(int Aid, ref int Arows);
		public abstract string GetBez(int Aid);
		public abstract string[,] Sel(ref int Arows);
		public virtual void SelTree(object Atv)
		{
		}
		public virtual int InsUpd()
		{
			return(-1);
		}
		public virtual void Delete()
		{
		}
		public virtual int GetText()
		{
			string sql;
			TexteDS textDS;
			textDS = new TexteDS();
			sql = String.Format("Select * from tdbadmin.texte where textid = {0} and s_id = {1} and textnr = 1 and typ = {2}", text_id, tdb.User.Ulangid, typ);
			FillDS(textDS, sql, new string[] { "texte" });
			TexteDS.texteRow Rwork = textDS.texte[0];
			text = Rwork.TEXT;
			return(textDS.texte.Rows.Count);
		}
		public virtual int InsText()
		{
			string sql;
			int rows = 0;
			if (!text.Equals(""))
			{
				text_id = NewID("texte", "TEXTID");
				sql = String.Format("insert into tdbadmin.texte values({0}, {1}, 1, '{2}', {3})", text_id, User.Ulangid, text, typ);
				rows = DBcmd(sql);
			}
			return(rows);
		}
		public virtual int UpdText()
		{
			string sql;
			int rows = 0;
			if (!text.Equals("") && text_id == -1)
			{
				text_id = NewID("texte", "TEXTID");
				sql = String.Format("insert into tdbadmin.texte values({0}, {1}, 1, '{2}', {3})", text_id, User.Ulangid, text, typ);
				rows = DBcmd(sql);
			}
			else if ((!text.Equals(""))&& (text_id > 0))
			{
				sql = String.Format("update tdbadmin.texte set text = '{0}' where textid = {1} and s_id = {2} and typ = {3} and textnr = 1", text, text_id, User.Ulangid, typ);
				rows = DBcmd(sql);
			}
			return(rows);
		}
		public virtual int InsBez()
		{
			string sql;
			bez_id = NewID("bezeichnung", "BEZ_ID");
			sql = String.Format("insert into tdbadmin.bezeichnung values({0}, {1}, '{2}', {3})", bez_id, User.Ulangid, bez, typ);
			return(DBcmd(sql));
		}
		public virtual int UpdBez()
		{
			string sql;
			sql = String.Format("update tdbadmin.bezeichnung set bez = '{0}' where bez_id = {1} and s_id = {2} and typ = {3}", bez, bez_id, User.Ulangid, typ);
			return(DBcmd(sql));
		}
		#endregion
	}
}
