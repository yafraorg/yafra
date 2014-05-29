<?php

/**
* Class to handle all db operations
* This class will have CRUD methods for database tables
*
* @author Ravi Tamada
* @link URL Tutorial link
*/
class DbHandler {

	private $conn;
	private $sql;
	
	function __construct() {
		require_once dirname(__FILE__) . '/DbConnect.php';
		// opening db connection
		$db = new DbConnect();
		$this->conn = $db->connect();
		}
	
	
	/* ------------- `Person` table method ------------------ */
	
	/**
	* Creating new task
	* @param String $user_id user id to whom task belongs to
	* @param String $task task text
	*/
	public function createPerson($user_id, $task) {
		$stmt = $this->conn->prepare("INSERT INTO Person(task) VALUES(?)");
		$stmt->bind_param("s", $task);
		$result = $stmt->execute();
		$stmt->close();
		
		if ($result) {
		// task row created
		// now assign the task to user
		$new_task_id = $this->conn->insert_id;
		$res = $this->createUserTask($user_id, $new_task_id);
		if ($res) {
		// task created successfully
		return $new_task_id;
		} else {
		// task failed to create
		return NULL;
		}
		} else {
		// task failed to create
		return NULL;
		}
		/*
		foreach ($dbh->query($sql) as $row)
			{
			print $row['animal_type'] .' - '. $row['animal_name'] . '<br />';
			}
		*/
		}
	
	/**
	* Fetching single task
	* @param String $task_id id of the task
	*/
	public function getPerson($personid) {
		$sql = "SELECT p.* FROM Person p WHERE p.pkPerson = $personid";
		$stmt = $this->conn->prepare($sql);
		$stmt->bind_param("ii", $task_id, $user_id);
		if ($stmt->execute()) {
		$res = array();
		$stmt->bind_result($id, $task, $status, $created_at);
		// TODO
		// $task = $stmt->get_result()->fetch_assoc();
		$stmt->fetch();
		$res["id"] = $id;
		$res["task"] = $task;
		$res["status"] = $status;
		$res["created_at"] = $created_at;
		$stmt->close();
		return $res;
		} else {
		return NULL;
		}
	}
	
	/**
	* Fetching all persons
	*/
	public function getAllPersons() {
		try {
			$stmt = $this->conn->query('SELECT p.* FROM Person p ORDER BY p.name');
			$persons = $stmt->fetchAll(PDO::FETCH_ASSOC);
			}
		catch (PDOException $e) {
			echo 'Verbindung fehlgeschlagen: ' . $e->getMessage();
			}
		return $persons;
		}
	
	/**
	* Fetching all logs for a specific person
	* @param String $personid id of the person
	*/
	public function getAllPersonLogs($personid) {
		try {
			$sql = "SELECT pl.* FROM PersonLog pl WHERE pl.fkPersonId = $personid ORDER BY pl.eventDate";
			$stmt = $this->conn->query($sql);
			$persons = $stmt->fetchAll(PDO::FETCH_ASSOC);
			}
		catch (PDOException $e) {
			echo 'Verbindung fehlgeschlagen: ' . $e->getMessage();
			}
		return $persons;
		}
	
	/**
	* Updating task
	* @param String $task_id id of the task
	* @param String $task task text
	* @param String $status task status
	*/
	public function updatePerson($user_id, $task_id, $task, $status) {
		$stmt = $this->conn->prepare("UPDATE tasks t, user_tasks ut set t.task = ?, t.status = ? WHERE t.id = ? AND t.id = ut.task_id AND ut.user_id = ?");
		$stmt->bind_param("siii", $task, $status, $task_id, $user_id);
		$stmt->execute();
		$num_affected_rows = $stmt->affected_rows;
		$stmt->close();
		return $num_affected_rows > 0;
		}
	
	/**
	* Deleting a task
	* @param String $task_id id of the task to delete
	*/
	public function deletePerson($user_id, $task_id) {
		$stmt = $this->conn->prepare("DELETE t FROM tasks t, user_tasks ut WHERE t.id = ? AND ut.task_id = t.id AND ut.user_id = ?");
		$stmt->bind_param("ii", $task_id, $user_id);
		$stmt->execute();
		$num_affected_rows = $stmt->affected_rows;
		$stmt->close();
		return $num_affected_rows > 0;
		}
	
}

?>
