const random = () => parseInt(Math.random()*30)+55


let varia
setInterval(() => {
  ind > 2 ? ind = 0: ind++
  Math.random() < 0.5 ? varia = 1 : varia = -1
  let rando = consumo[ind].data.datasets[0].data[0] + varia
  rando > 100 ? rando = 100 : 0
  $("#numerico"+(ind+1)).text((consumo[ind].data.datasets[0].data[0]*aleatorio[ind]).toFixed(1))
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
            borderRadius: 10
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

let consumo = [,,,,,,,],ind = 0, cores = ["darkorange","#b23f19","#ce2a24","#da3c4b"], aleatorio = [1.458,2.792,1.989,1.112]
consumo[2] = new Chart(document.getElementsByClassName("consumo1"),cosumindo(cores[0],random()));
consumo[1] = new Chart(document.getElementsByClassName("consumo2"),cosumindo(cores[1],random()));
consumo[3] = new Chart(document.getElementsByClassName("consumo3"),cosumindo(cores[2],random()));
consumo[0] = new Chart(document.getElementsByClassName("consumo4"),cosumindo(cores[3],random()));

$("#numerico1").text((consumo[0].data.datasets[0].data[0]*aleatorio[0]).toFixed(1))
$("#numerico1").parent().css('color',cores[0])
$("#numerico2").text((consumo[1].data.datasets[0].data[0]*aleatorio[1]).toFixed(1))
$("#numerico2").parent().css('color',cores[1])
$("#numerico3").text((consumo[2].data.datasets[0].data[0]*aleatorio[2]).toFixed(1))
$("#numerico3").parent().css('color',cores[2])
$("#numerico4").text((consumo[3].data.datasets[0].data[0]*aleatorio[3]).toFixed(1))
$("#numerico4").parent().css('color',cores[3])