const random3 = () => parseInt(Math.random()*60)+20
const laco = [random3(),random3(),random3(),random3(),random3(),random3(),random3()]

new Chart(document.getElementsByClassName("barras"), {
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
            data: [45,55,50,60,50,55,45],
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