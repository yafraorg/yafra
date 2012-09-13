using System;

namespace org.swyn.foundation.utils
{
	/// <summary>
	/// converts from / to a UNIX/ANSIC time() integer from a .NET DateTime
	/// </summary>
	abstract public class datetime
	{
	private const long ticks1970 = 621355968000000000; // .NET ticks for 1970

		static public int ToUnix(DateTime Adt)
		{
			int retux = 0;
			DateTime dt70 = new DateTime( 1970, 1, 1, 0, 0, 0, 0 );
			// long ticks1970 = dt70.Ticks;
			retux = (int) ((Adt.Ticks - ticks1970 ) / 10000000L);
			return(retux);
		}
		static public DateTime FromUnix(int Auxtime)
		{
			DateTime newDt = new DateTime( ticks1970 + Auxtime * 10000000L );
			return(newDt);
		}
	}
}
