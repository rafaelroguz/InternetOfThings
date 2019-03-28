<?php
/**
 * Created by PhpStorm.
 * User: Mariana
 * Date: 02/10/2018
 * Time: 07:36 AM
 *
 * Get the last stored value on DB to insert into the chart.
 */
$con = pg_connect("host=ec2-54-235-90-0.compute-1.amazonaws.com dbname=d94n6uerkees6n user=zwpbbcgrvahhnu password=168c5333561f5ad0e886534d747f10cb5888f9b48ceb4b37c79eb54125430990")
or die('No se ha podido conectar: ' . pg_last_error());
$query = "SELECT muestraTemp, idTemperatura  FROM temperatura ORDER BY idTemperatura DESC LIMIT 1";
$result = pg_query($query) or die('La consulta fallo: ' . pg_last_error());
$chart = array();
while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
    $chart[] = $line;
  }
header("Content-type: text/json");
echo json_encode($chart);
?>