const random = () => parseInt(Math.random()*30)+55
let varia
setInterval(() => {
  ind > 6 ? ind = 0: ind++
  Math.random() < 0.5 ? varia = 1 : varia = -1
  let rando = consumo[ind].data.datasets[0].data[0] + varia
  consumo[ind].data.datasets[0].data = [rando, -(rando)+100]
  consumo[ind].update();
},250);

const cosumindo = (cor,XXX) => {
    return {
        type: 'doughnut',
        data: {
        datasets: [{
            data: [XXX, -XXX+100],
            backgroundColor: [cor,"#0000000c"],
            borderColor: "#00000000",
            cutout: "70%",
          }]
      },
        options: {
            responsive: true,
          legend: {
            display: false
          }
        },
        plugins: [{
          id: "gaugeNeedle",
          afterDatasetDraw(chart) {
            const {
              ctx,
              data,
              chartArea: {width, height},
            } = chart
          
            ctx.restore();
            var fontSize = (height / 65).toFixed(2);
            ctx.font = fontSize + "em sans-serif";
            ctx.textBaseline = "middle";
          
            var text = data.datasets[0].data[0] + '%',
                textX = Math.round((width - ctx.measureText(text).width) / 2),
                textY = height / 1.7;
          
            ctx.fillStyle = cor;
            ctx.fillText(text, textX, textY);
            ctx.save();
          }
        }]
      }
}
let consumo = [,,,,,,,],ind = 0
consumo[4] = new Chart(document.getElementsByClassName("consumo1"),cosumindo("darkorange",random()));
consumo[3] = new Chart(document.getElementsByClassName("consumo2"),cosumindo("#b23f19",random()));
consumo[5] = new Chart(document.getElementsByClassName("consumo3"),cosumindo("#ce2a24",random()));
consumo[6] = new Chart(document.getElementsByClassName("consumo4"),cosumindo("#da3c4b",random()));
consumo[0] = new Chart(document.getElementsByClassName("consumo01"),cosumindo("darkorange",random()));
consumo[7] = new Chart(document.getElementsByClassName("consumo02"),cosumindo("#b23f19",random()));
consumo[1] = new Chart(document.getElementsByClassName("consumo03"),cosumindo("#ce2a24",random()));
consumo[2] = new Chart(document.getElementsByClassName("consumo04"),cosumindo("#da3c4b",random()));

