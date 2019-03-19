window.onload = function () {
  var dataPoints = []
  var xVal = 0, maxTemp, minTemp
  var chart
  var dataLength = 20 // num máximo de valores en el gráfico, el valor más antiguo es reemplazado

  $.getJSON('./maxTemp.php', function (hot) {
    maxTemp = hot[0].muestratemp
    $('#hot').html(hot[0].muestratemp + '°C')
    $('#hotDate').html(hot[0].fechamuestra)
  })

  $.getJSON('./minTemp.php', function (cold) {
    minTemp = cold[0].muestratemp
    $('#cold').html(cold[0].muestratemp + '°C')
    $('#coldDate').html(cold[0].fechamuestra)
  })

  $.getJSON('./chart.php', function (data) {
    document.getElementById('temp').innerHTML = '9i9i9i9'
    // $('#temp').html(data[0].muestratemp);
    dataPoints.push({
      x: xVal,
      y: data[0].muestratemp
    })
    xVal++
    chart = new CanvasJS.Chart('chartContainer', {
      title: {
        text: 'Temperatura actual'
      },
      axisY: {
        title: 'Temperatura'
      },
      data: [{
        type: 'line',
        dataPoints: dataPoints
      }]
    })
    if (dataPoints.length > dataLength) { // quitar si se quieren ver todos los valores obtenidos en la sesión
      dataPoints.shift()
    }
    chart.render()
    updateChart()
  })

  function updateChart () {
    $.getJSON('./temperaturas.php', function (temperatura) {
      $('#tablaTemperatura').html('<tr><th>° C</th><th>Fecha</th><th>Hora</th></tr>')
      for (var i = 0; i < temperatura.length; i++) {
        var time = temperatura[i].horamuestra.split(' ')
        $('#tablaTemperatura').append('<tr><td>' + temperatura[i].muestratemp + '</td>' + '<td>' + temperatura[i].fechamuestra + '</td><td>' + time[1] + '</td></tr>')
      }
    })

    $.getJSON('./chart.php', function (data) {
      // Si hay nueva temperatura más alta
      if (data > maxTemp) {
        $('#hot').html(data[0].muestratemp + '°C')
        $('#hotDate').html(data[0].fechamuestra)
      }

      // si hay nueva temperatura más baja
      if (data < minTemp) {
        $('#cold').html(data[0].muestratemp + '°C')
        $('#coldDate').html(data[0].fechamuestra)
      }

      $('#temp').html(data[0].muestratemp + '°C')
      dataPoints.push({
        x: xVal,
        y: parseFloat(data[0].muestratemp)
      })
      xVal++
      // es necesario lo comentado?
      // chart = new CanvasJS.Chart('chartContainer', {
      //   title: {
      //     text: 'Temperatura actual: ' + data[0].muestratemp + '°C'
      //   },
      //   axisY: {
      //     title: 'Temperatura'
      //   },
      //   data: [{
      //     type: 'line',
      //     dataPoints: dataPoints
      //   }]
      // });

      if (dataPoints.length > dataLength) { // quitar si se quieren ver todos los valores obtenidos en la sesión
        dataPoints.shift() // si hay más de <dataLength> borra el último valor, manteniendo siempre la misma cantidad de datos en el gráfico
      }

      chart.render()
      setTimeout(function () {
        updateChart()
      }, 1000)
    })
  }
}
