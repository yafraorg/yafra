#!/usr/bin/perl
#-------------------------------------------------------------------------------
# (c) Administrator yafra, yafra.org, 2002, Switzerland
#
# function: create schema files from an oracle schema for C#
#
# argument: none
#
# needed modules: DBI, XML
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 1.1 $
#-------------------------------------------------------------------------------
use DBI;
use IO;
use XML::Writer;

my $debugflag = 1;

&db_readtables;
&db_readviews;

# read all root tables for converting
sub db_readtables
{
	my $dbd = 'dbi:Oracle:web95';
	my $user = 'root';
	my $password = 'root';
	use vars qw($dbh);
	use vars qw($sth);
	use vars qw($sth2);
	use vars qw($output);
	use vars qw($writer);

	$dbh = DBI->connect($dbd,$user,$password) ||
		die "Error connecting $DBI::errstr\n";;

	# ORACLE
	# select table_name, owner from dba_tables where owner = 'ROOT'
	$stmt = "select table_name from dba_tables where owner = 'ROOT'";
	$sth = $dbh->prepare($stmt);
	$sth->execute();
	if ($DBI::err)
		{
		db_debug("error in selecting ROOT tables: $DBI::errstr");
		}

	db_debug("lese alle ROOT tabellen");
	while (($table) = $sth->fetchrow)
		{
		if ($DBI::err)
			{
			db_debug("error fetching for tables in dba_tables $DBI::errstr");
			}
		db_debug("- Tabelle: $table");
		$tblds = $table."ds";
		$outputfile = $table.".xsd";
		open(XSDFILE,">".$outputfile);
		print XSDFILE <<EOF;
<?xml version="1.0" standalone="yes" ?>
<xs:schema id="$tblds" xmlns="" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:msdata="urn:schemas-microsoft-com:xml-msdata">
	<xs:element name="$tblds" msdata:IsDataSet="true" msdata:Locale="de-CH">
		<xs:complexType>
			<xs:choice maxOccurs="unbounded">
				<xs:element name="$table">
					<xs:complexType>
						<xs:sequence>
EOF

		# pro table ein describe und dump in ein schema
		$stmt = "select COLUMN_NAME, DATA_TYPE, DATA_LENGTH from dba_tab_columns where TABLE_NAME = '$table'";
		$sth2 = $dbh->prepare($stmt);
		$sth2->execute();
		if ($DBI::err)
			{
			db_debug("error in describing table: $DBI::errstr");
			}
		db_debug("- Tabellendetails for $table");
		while (($name, $typ, $len) = $sth2->fetchrow)
			{
			if ($DBI::err)
				{
				db_debug("error fetching for tables in dba_tables $DBI::errstr");
				}
			db_debug("-    $name $typ $len");
			print XSDFILE "						<xs:element name=\"$name\"";
			if ($typ eq "NUMBER")
				{
				print XSDFILE ' type="xs:decimal" minOccurs="0" />';
				}
			elsif ($typ eq "FLOAT")
				{
				print XSDFILE ' type="xs:double" minOccurs="0" />';
				}
			elsif ($typ eq "DATE")
				{
				print XSDFILE ' type="xs:dateTime" minOccurs="0" />';
				}
			else
				{
				print XSDFILE ' type="xs:string" minOccurs="0" />';
				}
			print XSDFILE "\n";
			}
		$sth2->finish;
		print XSDFILE <<EOF;
						</xs:sequence>
					</xs:complexType>
				</xs:element>
			</xs:choice>
		</xs:complexType>
	</xs:element>
</xs:schema>
EOF

		close(XSDFILE);
		system("E:\\opt\\vsnet\\FrameworkSDK\\bin\\xsd.exe \/d \/l:CS $outputfile");
		}
	$sth->finish;
	$dbh->commit;

	# chek DBD driver
	db_debug("  closing db handle");

	# disconnect as SYSTEM user from the DB
	$dbh->disconnect;

	return;
}

# read all root tables for converting
sub db_readviews
{
	my $dbd = 'Oracle';
	my $dbname = 'mapo';
	my $user = 'root';
	my $password = 'root';
	use vars qw($dbh);
	use vars qw($sth);
	use vars qw($sth2);
	use vars qw($output);
	use vars qw($writer);

	$dbh = DBI->connect($dbname,$user,$password,$dbd) ||
		die "Error connecting $DBI::errstr\n";;

	# select table_name, owner from dba_tables where owner = 'ROOT'
	$stmt = "select view_name from dba_views where owner = 'ROOT'";
	$sth = $dbh->prepare($stmt);
	$sth->execute();
	if ($DBI::err)
		{
		db_debug("error in selecting ROOT views: $DBI::errstr");
		}

	db_debug("lese alle ROOT vies");
	while (($table) = $sth->fetchrow)
		{
		if ($DBI::err)
			{
			db_debug("error fetching for views in dba_views $DBI::errstr");
			}
		db_debug("- Views: $table");
		$tblds = $table."ds";
		$outputfile = $table.".xsd";
		open(XSDFILE,">".$outputfile);
		print XSDFILE <<EOF;
<?xml version="1.0" standalone="yes" ?>
<xs:schema id="$tblds" xmlns="" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:msdata="urn:schemas-microsoft-com:xml-msdata">
	<xs:element name="$tblds" msdata:IsDataSet="true" msdata:Locale="de-CH">
		<xs:complexType>
			<xs:choice maxOccurs="unbounded">
				<xs:element name="$table">
					<xs:complexType>
						<xs:sequence>
EOF

		# pro table ein describe und dump in ein schema
		$stmt = "select COLUMN_NAME, DATA_TYPE, DATA_LENGTH from dba_tab_columns where TABLE_NAME = '$table'";
		$sth2 = $dbh->prepare($stmt);
		$sth2->execute();
		if ($DBI::err)
			{
			db_debug("error in describing table: $DBI::errstr");
			}
		db_debug("- Tabellendetails for $table");
		while (($name, $typ, $len) = $sth2->fetchrow)
			{
			if ($DBI::err)
				{
				db_debug("error fetching for tables in dba_tables $DBI::errstr");
				}
			db_debug("-    $name $typ $len");
			print XSDFILE "						<xs:element name=\"$name\"";
			if ($typ eq "NUMBER")
				{
				print XSDFILE ' type="xs:decimal" minOccurs="0" />';
				}
			elsif ($typ eq "FLOAT")
				{
				print XSDFILE ' type="xs:double" minOccurs="0" />';
				}
			elsif ($typ eq "DATE")
				{
				print XSDFILE ' type="xs:dateTime" minOccurs="0" />';
				}
			else
				{
				print XSDFILE ' type="xs:string" minOccurs="0" />';
				}
			print XSDFILE "\n";
			}
		$sth2->finish;
		print XSDFILE <<EOF;
						</xs:sequence>
					</xs:complexType>
				</xs:element>
			</xs:choice>
		</xs:complexType>
	</xs:element>
</xs:schema>
EOF

		close(XSDFILE);
		system("E:\\opt\\vsnet\\FrameworkSDK\\bin\\xsd.exe \/d \/l:VB $outputfile");
		}
	$sth->finish;
	$dbh->commit;

	# chek DBD driver
	db_debug("  closing db handle");

	# disconnect as SYSTEM user from the DB
	$dbh->disconnect;

	return;
}


#----------------------------------------------------------
#
# INTERNAL functions
#
#----------------------------------------------------------
sub db_debug
{
	# read function arguments
	my ($message) = @_;

	if ($debugflag)
		{
		print "debug: $message\n";
		}
}
