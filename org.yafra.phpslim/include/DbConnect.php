<?php

/**
 * Handling database connection
 *
 * @author Ravi Tamada
 * @link URL Tutorial link
 */
class DbConnect {

	private $conn;
	private $connstr;
	
	function __construct() {        
		}
	
	/**
	* Establishing database connection
	* @return database connection handler
	*/
	function connect() {
		include_once dirname(__FILE__) . '/Config.php';
		
		// Connecting to mysql database
		try {
			$connstr = printf("mysql:host=%s;dbname=%s;charset=utf8", DB_HOST, DB_USERNAME);
			$this->conn = new PDO($connstr, DB_USERNAME, DB_PASSWORD);
			}
		catch (PDOException $exception)
			{
			echo "YAFRA error: database connection error: " . $exception->getMessage();
			}
		
		// returing connection resource
		return $this->conn;
		}

}
?>
