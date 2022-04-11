import Chart from "./SRCcharts";

export default function consumoEletrico(Elemento: HTMLCanvasElement | null,elementoNumero: any) {

const random = () => Math.round(Math.random()*30)+55
let varia
setInterval(() => {
  Math.random() < 0.5 ? varia = 1 : varia = -1
  let rando = consumo.data.datasets[0].data[0] + varia
  elementoNumero.innerText = (consumo.data.datasets[0].data[0]*aleatorio[ind]).toFixed(1)
  consumo.data.datasets[0].data = [rando, -(rando)+100]
  consumo.update();
},1000);

const cosumindo = (cor: string,XXX: number) => {
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
          afterDatasetDraw(chart:any){
            const {ctx,data,chartArea: {width, height}} = chart
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

let ind = 0, cores = ["darkorange","#b23f19","#ce2a24","#da3c4b"], aleatorio = [1.458,2.792,1.989,1.112]
let consumo = new Chart(Elemento,cosumindo(cores[0],random()));

elementoNumero.innerText = (consumo.data.datasets[0].data[0]*aleatorio[0]).toFixed(1)
elementoNumero.parentElement.style.color = cores[0];
}