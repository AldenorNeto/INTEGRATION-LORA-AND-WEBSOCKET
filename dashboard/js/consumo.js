const random = () => parseInt(Math.random()*40)+55

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
        afterDatasetDraw(chart, args, options) {
          const {
            ctx,
            config,
            data,
            chartArea: { top, right, bottom, left, width, height },
          } = chart
      
          ctx.restore();
          var fontSize = (height / 65).toFixed(2);
          ctx.font = fontSize + "em sans-serif";
          ctx.textBaseline = "middle";
      
          var text = XXX + '%',
              textX = Math.round((width - ctx.measureText(text).width) / 2),
              textY = height / 1.7;
      
          ctx.fillStyle = cor;
          ctx.fillText(text, textX, textY);
          ctx.save();
        }
      }]
      }
}

new Chart(document.getElementsByClassName("consumo"),cosumindo("darkorange",random()));
new Chart(document.getElementsByClassName("consumo2"),cosumindo("#b23f19",random()));
new Chart(document.getElementsByClassName("consumo3"),cosumindo("#ce2a24",random()));
new Chart(document.getElementsByClassName("consumo4"),cosumindo("#da3c4b",random()));

