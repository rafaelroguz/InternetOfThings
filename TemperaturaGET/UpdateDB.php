<?php

if (isset($_GET["temp"]) && $_GET["temp"] !== "") {
    $temperatura = $_GET["temp"];
    $con = pg_connect("host=ec2-23-21-106-241.compute-1.amazonaws.com dbname=d6v68e94ifsnb8 user=kseimhoaelfkuc password=5474616e45367e5491d89bba877e057af38f9f3633327c93d52456c8f37d4ae1") or die('No se puedo conectar con la BD' . pg_last_error());
    $timestamp = new DateTime();
    $sql = "INSERT INTO temperaturas (temperatura, tiempo) VALUES(".$temperatura.", ".$timestamp->getTimestamp().")";
    $result = pg_query($sql) or die("Falló la inserción a la BD: ".pg_last_error());

    echo "Se insertó la temperatura en la BD correctamente";
} else {
    echo "No se ha recibido temperatura";
}

?>