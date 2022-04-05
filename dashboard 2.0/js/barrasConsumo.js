const random3 = () => parseInt(Math.random()*10)+50
var laco = [5,random3(),random3(),random3(),random3(),random3(),random3()-10]

laco[new Date().getDay()] = parseInt(Math.random()*4)+17

setInterval(() => {
    barras.data.datasets[0].data[new Date().getDay()] = parseInt(Math.random()*4)+17
    barras.update();
}, 1500);

var barras = new Chart(document.getElementsByClassName("barras"), {
    type: 'bar',
    data: {
        labels:['DOM','SEG','TER','QUA','QUI','SEX','SAB'],
        datasets:[{
            label:'Consumo',
            data: laco,
            backgroundColor:['aqua'],
            categoryPercentage:0.5,
        },
        {
            label:'Previsão',
            data: [4,55,53,57,53,55,45],
            backgroundColor:['#ffbb00'],
            categoryPercentage:0.6,
        }]
    },
    options:{
        scales:{
            x:{
                stacked:true,
                ticks:{
                    color:'white'
                },
                grid: {
                  display: false
                }
            },
            y:{
                ticks:{
                    color:'white'
                },
                grid: {
                 color:'#ffffff20'
                }
            }
        },
        plugins: {
            title: {
              display: true,
              color:'white',
              text:'CONSUMO SEMANAL DE ÁGUA TRATADA (L)'
            },
            legend: {
              display: false
            }
        }
    }
})