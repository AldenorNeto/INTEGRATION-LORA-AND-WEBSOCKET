let variante = 0
setInterval(() => {
  Math.random() < 0.5 ? variante = 1 : variante = -1
  acelera1.data.datasets[0].needleValue += variante
  acelera1.update();
}, 1100);

setInterval(() => {
  Math.random() < 0.5 ? variante = 1 : variante = -1
  acelera2.data.datasets[0].needleValue += variante
  acelera2.update();
}, 900);

const velocimetro = (multi,angulo) => {
  return {
    type: "doughnut",
    data:{
      labels: ["OK","RISCO","ALTO RISCO"],
      datasets: [{
        label: "Gauge",
        data: [120, 50, 30],
        backgroundColor: ["#00fc15","yellow","red",],
        needleValue: angulo,
        borderColor: "white",
        borderWidth: 1,
        cutout: "70%",
        circumference: 180,
        rotation: 270,
      }],
  },
  options: {
    plugins: {
      legend: {
        display: false,
      },
      tooltip: {
        yAlign: "bottom",
        displayColors: false,
        callbacks: {
          label: function(tooltipItem) {
            return tooltipItem.label;
          },
        },
      },
    },
  },
  plugins: [{
    id: "gaugeNeedle",
    afterDatasetDraw(chart) {
      const {
        ctx,
        data,
        chartArea: {width},
      } = chart;
      ctx.save();
      const needleValue = data.datasets[0].needleValue;
      
      if (needleValue <= 200) {
        var angle = Math.PI + (1 / 200) * needleValue * Math.PI;
      } else if (needleValue <= 10000) {
        var angle =
          Math.PI +
          (1 / 200) * 100 * Math.PI +
          ((1 / 200) * needleValue * Math.PI * 65) / 10000;
      } else if (needleValue <= 1000000) {
        var angle =
          Math.PI +
          (1 / 200) * 100 * Math.PI +
          ((1 / 200) * 10000 * Math.PI * 65) / 10000 +
          ((1 / 200) * needleValue * Math.PI * 35) / 1000000;
      } else {
        var angle = 0;
      }
  
      const cx = width / 2;
      const cy = chart._metasets[0].data[0].y;
  
      //needle
      ctx.translate(cx, cy);
      ctx.rotate(angle);
      ctx.beginPath();
      ctx.moveTo(0, -15);
      ctx.lineTo((ctx.canvas.offsetTop)*multi, 0); // change 160 value if the needle size gets changed
      ctx.lineTo(0, 15);
      ctx.fillStyle = "#fff";
      ctx.fill();
  
      ctx.translate(-cx, -cy);
      ctx.beginPath();
      ctx.arc(cx, cy, 15, 0, 10);
      ctx.fill();
      ctx.restore();
  
      ctx.font = "20px Ubuntu";
      ctx.fillStyle = "#fff";
      ctx.fillText(needleValue + " RPM", cx, cy + 50);
      ctx.font = "10px Ubuntu";
      ctx.fillText('0', 5, cy + 20);
      ctx.textAlign = "center";
      ctx.restore();
    },
  }],
  }
}

let acelera1 = new Chart(document.getElementsByClassName("acelera1"), velocimetro(0.9,55))
let acelera2 = new Chart(document.getElementsByClassName("acelera2"), velocimetro(0.3,120))