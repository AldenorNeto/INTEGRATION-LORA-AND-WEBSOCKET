
const randomConsu = () => parseInt(Math.random()*100)

const randomConsuFor = () =>{
    let array = []
    for (let i = 0; i < 18; i++)array.push(randomConsu())
    return array
}

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
                grid: {
                  display: false
                }
            },
            y:{
                ticks:{
                    color:'white'
                },
                grid: {
                 color:'#ffffff40'
                }
            }
            
        }
    }}
}

new Chart(document.getElementsByClassName("AGelada"), linha('Água Gelada','cyan'))
new Chart(document.getElementsByClassName("AIndustrial"), linha('Água Industrial','blue'))
new Chart(document.getElementsByClassName("CBaixa"), linha('Compd. Alta P.','#00a600'))
new Chart(document.getElementsByClassName("CAlta"), linha('Compd. Baixa P.','#e1ff00'))
