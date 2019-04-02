window.onload = function () {
    var ctx = document.getElementById('myChart').getContext('2d');
    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'line',
        // The data for our dataset
        data: {
            labels: [],
            datasets: [{
                label: "Temperatura",
                borderColor: "#FF5733",
                data: [],
                fill: false,
                pointStyle: 'circle',
                backgroundColor: '#3498DB',
                pointRadius: 5,
                pointHoverRadius: 7,
                lineTension: 0,
            }]
        },
        // Configuration options go here
        options: {}
    });

    function updateChart() {
        $.getJSON("GetTemp.php", function (data) {
            let timeData = new Date(data["tiempo"] * 1000);
            let temp = data["temperatura"];
            let fullHour = timeData.getHours() + ":" + timeData.getMinutes() + ":" + timeData.getSeconds();
            let fullYear = timeData.getDate() + "/" + timeData.getMonth() + "/" + timeData.getFullYear();

            document.getElementById("temp-actual").innerHTML = temp;
            document.getElementById('date').innerHTML = fullYear;

            if(chart.data.labels.length != 15) {
                chart.data.labels.push(fullHour);

                chart.data.datasets.forEach((dataset) => {
                    dataset.data.push(temp);
                });
            } else {
                chart.data.labels.shift();
                chart.data.labels.push(fullHour);

                chart.data.datasets.forEach((dataset) => {
                    dataset.data.shift();
                    dataset.data.push(temp);
                });
            }

            chart.update();
        });

        setTimeout(function () {
            updateChart();
        }, 2000);
    }

    updateChart();
    /*socket.on('temp', function(data) { //As a temp data is received
        console.log(data.temp);
        document.getElementById("temp-actual").innerHTML = data.temp;
        document.getElementById('date').innerHTML = data.date; //update the date
        if(chart.data.labels.length != 15) { //If we have less than 15 data points in the graph
            chart.data.labels.push(data.time);  //Add time in x-asix
            chart.data.datasets.forEach((dataset) => {
                dataset.data.push(data.temp); //Add temp in y-axis
            });
        }
        else { //If there are already 15 data points in the graph.
            chart.data.labels.shift(); //Remove first time data
            chart.data.labels.push(data.time); //Insert latest time data
            chart.data.datasets.forEach((dataset) => {
                dataset.data.shift(); //Remove first temp data
                dataset.data.push(data.temp); //Insert latest temp data
            });
        }
        chart.update(); //Update the graph.
    });*/
}
