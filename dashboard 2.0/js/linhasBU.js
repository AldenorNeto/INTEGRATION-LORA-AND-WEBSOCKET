
const randomConsu = () => parseInt(Math.random()*20)+40

const randomConsuFor = () =>{
    let array = []
    for(let i = 0; i<18; i++)array.push(randomConsu())
    return array
}

setInterval(() => {
    for(let index = 0; index < 4; index++){
      linhaBU[index].data.datasets[0].data.shift() 
      linhaBU[index].data.datasets[0].data.push(randomConsu()) 
      linhaBU[index].update('none');
    }
},4810);

const linha = (nome,cor) =>{
    return {type: 'line',
    data: {
        labels:['12:00','12:15','12:30','12:45','13:00','13:15','13:30','13:45','14:00','14:15','14:30','14:45','15:00','15:15','15:30','15:45','16:00'],
        datasets:[{
            label:nome,
            data: randomConsuFor(),
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
              text:nome
            },
            legend: {
              display: false
            }
        },
        scales:{
            x:{ 
                
                ticks:{
                    color:'white'
                },
                grid:{
                    display: false
                }
            },
            y:{
                beginAtZero: true,
                bounds:200,
                    
                ticks:{
                    color:'white',
                    sampleSize:200

                },
                grid:{
                    color:'#ffffff40'
                }
            }
            
        }
    }
}}
let linhaBU = [,,,]
linhaBU[0] = new Chart(document.getElementsByClassName("AGelada"), linha('Água Gelada','cyan'))
linhaBU[1] = new Chart(document.getElementsByClassName("AIndustrial"), linha('Água Industrial','blue'))
linhaBU[2] = new Chart(document.getElementsByClassName("CBaixa"), linha('Compd. Alta P.','#00a600'))
linhaBU[3] = new Chart(document.getElementsByClassName("CAlta"), linha('Compd. Baixa P.','#e1ff00'))