const randomConsu = pesoindex => (Math.random()*((pesoindex/5)))+pesoindex

const randomConsuFor = pesoInd =>{
    let array = []
    for(let i = 0; i<18; i++)array.push(randomConsu(pesoInd))
    return array
}
let peso = [4,25,12,7], randomConsumo

for(let index = 0; index < 4; index++){
    randomConsumo = randomConsu(peso[index])
    $(".valorlinhaBU:eq("+index+") section").text(randomConsu(peso[index]).toFixed(0))
}

setInterval(() => {
    for(let index = 0; index < 4; index++){
        randomConsumo = randomConsu(peso[index])
        linhaBU[index].data.datasets[0].data.shift() 
        linhaBU[index].data.datasets[0].data.push(randomConsumo)
        $(".valorlinhaBU:eq("+index+") section").text(randomConsumo.toFixed(0))
        linhaBU[index].update('none');
    }
},4810);

const linha = (nome,cor,pesoInd) =>{
    return {type: 'line',
    data: {
        labels:['12:00','12:15','12:30','12:45','13:00','13:15','13:30','13:45','14:00','14:15','14:30','14:45','15:00','15:15','15:30','15:45','16:00','16:15'],
        datasets:[{
            label:nome,
            data: randomConsuFor(peso[pesoInd]),
            borderColor:cor,
            backgroundColor:cor,
            pointRadius:2
        }],
    },
    options: {
        plugins: {
            title: {
              display: true,
              color:'white',
              font:'sans-serif',
              text:nome
            },
            legend: {
              display: false
            }
        },
        scales:{
            x:{
                ticks:{
                    font: {
                        size: 8
                    },
                    color:'white'
                },
                grid:{
                    display: false
                }
            },
            y:{
                beginAtZero: true,
                max:peso[pesoInd]+5,
                ticks:{
                    color:'white',
                    sampleSize:2,
                    font: {
                        size: 8
                    }
                },
                grid:{
                    color:'#ffffff40'
                }
            }
            
        }
    }
}}
let linhaBU = []
linhaBU[0] = new Chart(document.getElementsByClassName("AGelada"), linha('Água Gelada','#00ffc8',0))
linhaBU[1] = new Chart(document.getElementsByClassName("AIndustrial"), linha('Água Industrial','#00a2ff',1))
linhaBU[2] = new Chart(document.getElementsByClassName("CBaixa"), linha('Compd. Alta P.','#00a600',2))
linhaBU[3] = new Chart(document.getElementsByClassName("CAlta"), linha('Compd. Baixa P.','#e1ff00',3))