// ===============================================================================
// Microsoft Data Access Application Block for .NET 3.0
//
// Odbc.cs
//
// This file contains the implementations of the AdoHelper supporting Odbc.
//
// For more information see the Documentation. 
// ===============================================================================
// Release history
// VERSION	DESCRIPTION
//   2.0	Added support for FillDataset, UpdateDataset and "Param" helper methods
//   3.0	New abstract class supporting the same methods using ADO.NET interfaces
//
// ===============================================================================
// Copyright (C) 2000-2001 Microsoft Corporation
// All rights reserved.
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
// FITNESS FOR A PARTICULAR PURPOSE.
// ==============================================================================

using System;
using System.Collections;
using System.Data;
using System.Data.Common;
using System.Data.Odbc;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.IO;

namespace org.swyn.foundation.db
{
	/// <summary>
	/// The Odbc class is intended to encapsulate high performance, scalable best practices for 
	/// common uses of the Odbc ADO.NET provider.  It is created using the abstract factory in AdoHelper
	/// </summary>
	public class Odbc : AdoHelper
	{
		// used for correcting Call syntax for stored procedures in ODBC
		static Regex _regExpr = new Regex( @"\{.*call|CALL\s\w+.*}", RegexOptions.Compiled );
		
		/// <summary>
		/// Create an Odbc Helper.  Needs to be a default constructor so that the Factory can create it
		/// </summary>
		public Odbc()
		{
		}

		#region Overrides
		/// <summary>
		/// Returns an array of OdbcParameters of the specified size
		/// </summary>
		/// <param name="size">size of the array</param>
		/// <returns>The array of OdbcParameters</returns>
		protected override IDataParameter[] GetDataParameters(int size)
		{
			return new OdbcParameter[size];
		}

		/// <summary>
		/// Returns an OdbcConnection object for the given connection string
		/// </summary>
		/// <param name="connectionString">The connection string to be used to create the connection</param>
		/// <returns>An OdbcConnection object</returns>
		public override IDbConnection GetConnection( string connectionString )
		{
			return new OdbcConnection( connectionString );
		}

		/// <summary>
		/// Returns an OdbcDataAdapter object
		/// </summary>
		/// <returns>The OdbcDataAdapter</returns>
		public override IDbDataAdapter GetDataAdapter()
		{
			return new OdbcDataAdapter(); 
		}

		/// <summary>
		/// Calls the CommandBuilder.DeriveParameters method for the specified provider, doing any setup and cleanup necessary
		/// </summary>
		/// <param name="cmd">The IDbCommand referencing the stored procedure from which the parameter information is to be derived. The derived parameters are added to the Parameters collection of the IDbCommand. </param>
		public override void DeriveParameters( IDbCommand cmd )
		{
			bool mustCloseConnection = false;

			if( !( cmd is OdbcCommand ) )
				throw new ArgumentException( "The command provided is not a OdbcCommand instance.", "cmd" );
			if (cmd.Connection.State != ConnectionState.Open) 
			{
				cmd.Connection.Open();
				mustCloseConnection = true;
			}

			OdbcCommandBuilder.DeriveParameters( (OdbcCommand)cmd );

			if (mustCloseConnection)
			{
				cmd.Connection.Close();
			}
		}

		/// <summary>
		/// Returns an OdbcParameter object
		/// </summary>
		/// <returns>The OdbcParameter object</returns>
		public override IDataParameter GetParameter()
		{
			return new OdbcParameter(); 
		}
		
		/// <summary>
		/// This cleans up the parameter syntax for an ODBC call.  This was split out from PrepareCommand so that it could be called independently.
		/// </summary>
		/// <param name="command">An IDbCommand object containing the CommandText to clean.</param>
		public override void CleanParameterSyntax(IDbCommand command)
		{
			string call = " call ";

			if( command.CommandType == CommandType.StoredProcedure )
			{
				if( !_regExpr.Match( command.CommandText ).Success && // It does not like like { call sp_name() }
					command.CommandText.Trim().IndexOf( " " ) == -1 ) // If there's only a stored procedure name
				{
					// If there's only a stored procedure name
                    StringBuilder par = new StringBuilder();
					if( command.Parameters.Count != 0 )
					{
						bool isFirst = true;
						bool hasParameters = false;

						for( int i = 0; i < command.Parameters.Count; i++ )
						{
							OdbcParameter p = command.Parameters[i] as OdbcParameter;
							if( p.Direction != ParameterDirection.ReturnValue )
							{
								if( isFirst )
								{
									isFirst = false;
									par.Append( "(?" );
								}
								else
								{
									par.Append( ",?" );
								}
								hasParameters = true;
							}
							else
							{
								call = " ? = call ";
							}
						}
						if (hasParameters)
						{
							par.Append( ")" );
						}
					}
					command.CommandText = "{" + call + command.CommandText + par.ToString() + " }";
				}
			}
		}

		/// <summary>
		/// Execute an IDbCommand (that returns a resultset) against the provided IDbConnection. 
		/// </summary>
		/// <example>
		/// <code>
		/// XmlReader r = helper.ExecuteXmlReader(command);
		/// </code></example>
		/// <param name="command">The IDbCommand to execute</param>
		/// <returns>An XmlReader containing the resultset generated by the command</returns>
		public override XmlReader ExecuteXmlReader(IDbCommand command)
		{
			bool mustCloseConnection = false;

			if (command.Connection.State != ConnectionState.Open) 
			{
				command.Connection.Open();
				mustCloseConnection = true;
			}

			CleanParameterSyntax(command);

			OdbcDataAdapter da = new OdbcDataAdapter((OdbcCommand)command);
			DataSet ds = new DataSet();

			da.MissingSchemaAction = MissingSchemaAction.AddWithKey;
			da.Fill(ds);

			StringReader stream = new StringReader(ds.GetXml());
			
			if (mustCloseConnection)
			{
				command.Connection.Close();
			}

			return new XmlTextReader(stream);
		}

		/// <summary>
		/// Provider specific code to set up the updating/ed event handlers used by UpdateDataset
		/// </summary>
		/// <param name="dataAdapter">DataAdapter to attach the event handlers to</param>
		/// <param name="rowUpdatingHandler">The handler to be called when a row is updating</param>
		/// <param name="rowUpdatedHandler">The handler to be called when a row is updated</param>
		protected override void AddUpdateEventHandlers(IDbDataAdapter dataAdapter, RowUpdatingHandler rowUpdatingHandler, RowUpdatedHandler rowUpdatedHandler)
		{
			if (rowUpdatingHandler != null)
			{
				this.m_rowUpdating = rowUpdatingHandler;
				((OdbcDataAdapter)dataAdapter).RowUpdating +=  new OdbcRowUpdatingEventHandler(RowUpdating);
			}

			if (rowUpdatedHandler != null)
			{
				this.m_rowUpdated = rowUpdatedHandler;
				((OdbcDataAdapter)dataAdapter).RowUpdated +=  new OdbcRowUpdatedEventHandler(RowUpdated);
			}
		}

		/// <summary>
		/// Handles the RowUpdating event
		/// </summary>
		/// <param name="obj">The object that published the event</param>
		/// <param name="e">The OdbcRowUpdatingEventArgs</param>
		protected void RowUpdating(object obj, OdbcRowUpdatingEventArgs e)
		{
			base.RowUpdating(obj, e);
		}

		/// <summary>
		/// Handles the RowUpdated event
		/// </summary>
		/// <param name="obj">The object that published the event</param>
		/// <param name="e">The OdbcRowUpdatedEventArgs</param>
		protected void RowUpdated(object obj, OdbcRowUpdatedEventArgs e)
		{
			base.RowUpdated(obj, e);
		}
		
		/// <summary>
		/// Handle any provider-specific issues with BLOBs here by "washing" the IDataParameter and returning a new one that is set up appropriately for the provider.
		/// </summary>
		/// <param name="connection">The IDbConnection to use in cleansing the parameter</param>
		/// <param name="p">The parameter before cleansing</param>
		/// <returns>The parameter after it's been cleansed.</returns>
		protected override IDataParameter GetBlobParameter(IDbConnection connection, IDataParameter p)
		{
			// nothing special needed for ODBC...so far as we know now.
			return p;
		}
		#endregion
	}
}