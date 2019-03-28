<?php
$con = pg_connect("host=ec2-54-235-90-0.compute-1.amazonaws.com dbname=d94n6uerkees6n user=zwpbbcgrvahhnu password=168c5333561f5ad0e886534d747f10cb5888f9b48ceb4b37c79eb54125430990")
or die('No se ha podido conectar: ' . pg_last_error());

	$query = "select * from temperatura ORDER BY idtemperatura DESC LIMIT 10";
	$result = pg_query($query) or die('La consulta fallo: ' . pg_last_error());
	$temp = array();
	while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
		$temp[] = $line;
		}
		header("Content-type: text/json");
	echo json_encode($temp);
?>