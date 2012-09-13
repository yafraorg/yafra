using System;
using System.Data;

namespace org.swyn.foundation.utils
{
	/// <summary>
	/// Only static methods to provide some useful tools, fill a datatable to bind to a combox with id and desc.
	/// </summary>
	abstract public class preparecombo
	{
		static public void setcombodata(string [,] Asel, int Arows, DataTable Adt)
		{
			int i;

			Adt.Columns.Add("id", typeof(int));
			Adt.Columns.Add("desc");
			DataRow row;
			for (i=0; i<Arows; i++)
			{
				row = Adt.NewRow();
				row["id"]   = Convert.ToInt32(Asel[i,0]);
				row["desc"] = Asel[i,1];
				Adt.Rows.Add(row);
			}
		}
	}
}
