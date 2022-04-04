const randomInj = () => parseInt(Math.random()*10)

const randomInje = soma =>{
  let array = []
  for (let i = 0; i < 14; i++)array.push(randomInj()+soma)
  return array
}

var ctx = document.getElementById("injecao").getContext("2d");
ctx.canvas.height = 200;
new Chart(ctx,{
      type:'line',
      data:{
        labels: ['13','12','11','10','9','8','7','6','5','4','3','2','1','0'],
        datasets: [{
          label: "Ar Comprimido",
          borderColor:'#020067',
          backgroundColor:'#0026fb',
          pointRadius:4,
          pointBorderWidth:2,
          data: randomInje(20),
          fill: true
        }, {
          label: "Ag. Gelada",
          borderColor:'#095582',
          backgroundColor:'#00eff7',
          pointRadius:4,
          pointBorderWidth:2,
          data: randomInje(40),
          fill: true
        }, {
          label: "Ag. Industrial",
          borderColor:'#006b07',
          backgroundColor:'#c4f000',
          pointRadius:4,
          pointBorderWidth:2,
          data: randomInje(60),
          fill: true
        }]
      },
    options: { 
      
      plugins: {
        title: {
          display: true,
          text: 'CONSUMO DE FLUIDOS INJEÇÃO',
        color:'white'
        },
        legend: {
          display: false
      },
      },
      interaction: {
        mode: 'index',
        intersect: false
      },
      scales: {
        x: {
          display: true,
          title: {
            display: true,
            text: 'HORAS ATRÁS',
            color:'white'
          },
          ticks:{
              color:'white'
          },
          grid: {
            display: false
          }
        },
        y: {
          display: true,
          beginAtZero: true,
          ticks:{
              color:'white'
          },
          grid: {
            display: false
          }
        },
      }
    }
});
  
  
          
      