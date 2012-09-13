
// ===============================================================================
// Microsoft Data Access Application Block for .NET 3.0
//
// Oracle.cs
//
// This file contains the implementations of the AdoHelper supporting Oracle.
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
using System.Data.OracleClient; 
using System.Xml;
using System.IO;

namespace org.swyn.foundation.db
{
	/// <summary>
	/// The Oracle class is intended to encapsulate high performance, scalable best practices for 
	/// common uses of the Oracle ADO.NET provider.  It is created using the abstract factory in AdoHelper.
	/// </summary>
	public class Oracle : AdoHelper 
	{ 
		/// <summary>
		/// Create an Oracle Helper.  Needs to be a default constructor so that the Factory can create it
		/// </summary>
		public Oracle() 
		{ 
		} 

		#region Overrides
		/// <summary>
		/// Returns an array of OracleParameters of the specified size
		/// </summary>
		/// <param name="size">size of the array</param>
		/// <returns>The array of OracleParameters</returns>
		protected override IDataParameter[] GetDataParameters(int size)
		{
			return new OracleParameter[size];
		}

		/// <summary>
		/// Returns an OracleConnection object for the given connection string
		/// </summary>
		/// <param name="connectionString">The connection string to be used to create the connection</param>
		/// <returns>An OracleConnection object</returns>
		public override IDbConnection GetConnection(string connectionString) 
		{ 
			return new OracleConnection (connectionString ); 
		} 

		/// <summary>
		/// Returns an OracleDataAdapter object
		/// </summary>
		/// <returns>The OracleDataAdapter</returns>
		public override IDbDataAdapter GetDataAdapter() 
		{ 
			return new OracleDataAdapter(); 
		} 

		/// <summary>
		/// Calls the CommandBuilder.DeriveParameters method for the specified provider, doing any setup and cleanup necessary
		/// </summary>
		/// <param name="cmd">The IDbCommand referencing the stored procedure from which the parameter information is to be derived. The derived parameters are added to the Parameters collection of the IDbCommand. </param>
		public override void DeriveParameters( IDbCommand cmd ) 
		{ 
			bool mustCloseConnection = false;

			if( !( cmd is OracleCommand ) ) 
				throw new ArgumentException( "The command provided is not an OracleCommand instance.", "cmd" ); 
			
			if (cmd.Connection.State != ConnectionState.Open) 
			{
				cmd.Connection.Open();
				mustCloseConnection = true;
			}
			
			OracleCommandBuilder.DeriveParameters( (OracleCommand)cmd ); 
			
			if (mustCloseConnection)
			{
				cmd.Connection.Close();
			}
		} 

		/// <summary>
		/// Returns an OracleParameter object
		/// </summary>
		/// <returns>The OracleParameter object</returns>
		public override IDataParameter GetParameter()
		{
			OracleParameter parameter = new OracleParameter();
			parameter.Size = 255;
			return parameter;
		}

		/// <summary>
		/// Get an IDataParameter for use in a SQL command
		/// </summary>
		/// <param name="parameterName">The name of the parameter to create</param>
		/// <param name="value">The value of the specified parameter</param>
		/// <returns>An IDataParameter object</returns>
		public override IDataParameter GetParameter( string parameterName, object value )
		{ 
			OracleParameter parameter = new OracleParameter(); 
			parameter.ParameterName = parameterName; 
			parameter.Value = value;          
			parameter.Size = GetParameterSize(parameterName); 
			return parameter; 
		} 

		/// <summary> 
		/// This function will get and assemble the parameter's size dynamically from db or cache 
		/// </summary> 
		/// <param name="name">The parameter name</param> 
		/// <returns>The size</returns> 
		private int GetParameterSize(string name) 
		{ 
			int Size=255; 
			return Size; 
		} 
		
		/// <summary>
		/// This cleans up the parameter syntax for an Oracle call.  This was split out from PrepareCommand so that it could be called independently.
		/// </summary>
		/// <param name="command">An IDbCommand object containing the CommandText to clean.</param>
		public override void CleanParameterSyntax(IDbCommand command)
		{
			if (command.CommandType == CommandType.Text) 
			{
				command.CommandText = command.CommandText.Replace("@", ":");
			}

			if (command.Parameters.Count > 0) 
			{
				foreach (OracleParameter parameter in command.Parameters)
				{
					parameter.ParameterName = parameter.ParameterName.Replace("@", ":");
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

			OracleDataAdapter da = new OracleDataAdapter((OracleCommand)command);
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
				((OracleDataAdapter)dataAdapter).RowUpdating += new OracleRowUpdatingEventHandler(RowUpdating);
			}

			if (rowUpdatedHandler != null)
			{
				this.m_rowUpdated = rowUpdatedHandler;
				((OracleDataAdapter)dataAdapter).RowUpdated += new OracleRowUpdatedEventHandler(RowUpdated);
			}
		}

		/// <summary>
		/// Handles the RowUpdating event
		/// </summary>
		/// <param name="obj">The object that published the event</param>
		/// <param name="e">The OracleRowUpdatingEventArgs</param>
		protected void RowUpdating(object obj, OracleRowUpdatingEventArgs e)
		{
			base.RowUpdating(obj, e);
		}

		/// <summary>
		/// Handles the RowUpdated event
		/// </summary>
		/// <param name="obj">The object that published the event</param>
		/// <param name="e">The OracleRowUpdatedEventArgs</param>
		protected void RowUpdated(object obj, OracleRowUpdatedEventArgs e)
		{
			base.RowUpdated(obj, e);
		}
		
		/// <summary>
		/// Handle any provider-specific issues with BLOBs here by "washing" the IDataParameter and returning a new one that is set up appropriately for the provider.
		/// See MS KnowledgeBase article: http://support.microsoft.com/default.aspx?scid=kb;en-us;322796
		/// </summary>
		/// <param name="connection">The IDbConnection to use in cleansing the parameter</param>
		/// <param name="p">The parameter before cleansing</param>
		/// <returns>The parameter after it's been cleansed.</returns>
		protected override IDataParameter GetBlobParameter(IDbConnection connection, IDataParameter p)
		{
			OracleConnection clonedConnection = (OracleConnection)(((ICloneable)connection).Clone());

			clonedConnection.Open();

			OracleCommand cmd = clonedConnection.CreateCommand();
			cmd.CommandText = "declare xx blob; begin dbms_lob.createtemporary(xx, false, 0); :tempblob := xx; end;";
			cmd.Parameters.Add(new OracleParameter("tempblob", OracleType.Blob)).Direction = ParameterDirection.Output;
			cmd.ExecuteNonQuery();

			OracleLob tempLob;
			tempLob = (OracleLob)(cmd.Parameters[0].Value);
			tempLob.BeginBatch(OracleLobOpenMode.ReadWrite);
			tempLob.Write((byte [])(p.Value), 0, System.Runtime.InteropServices.Marshal.SizeOf(p.Value));
			tempLob.EndBatch();

			OracleParameter op = new OracleParameter(p.ParameterName, OracleType.Blob);
			op.Value = tempLob;

			clonedConnection.Close();

			return op;
		}
		#endregion
	} 
}
