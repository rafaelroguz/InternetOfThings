<?php

$con = pg_connect("host=ec2-23-21-106-241.compute-1.amazonaws.com dbname=d6v68e94ifsnb8 user=kseimhoaelfkuc password=5474616e45367e5491d89bba877e057af38f9f3633327c93d52456c8f37d4ae1") or die('No se puedo conectar con la BD' . pg_last_error());
$sql = "SELECT * FROM temperaturas ORDER BY tiempo DESC LIMIT 1";
$result = pg_query($sql) or die("La consulta a la BD falló ".pg_last_error());
$temp = array();

while ($data = pg_fetch_array($result, null, PGSQL_ASSOC)) {
    $temp[] = $data;
}

header("Content-type: text/json");
echo json_encode($temp[0]);

?>