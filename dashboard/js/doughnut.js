const randomD = () => parseInt(Math.random()*10)+1
const DOUG = () => [randomD(),randomD(),randomD(),randomD()]

const doughnut = dough => {
    return {
        type: 'doughnut',
        data: {
            labels:['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO'],
            datasets:[{
                data: dough,
                backgroundColor:['aqua','blue','yellow','lime'],
                cutout: "30%"
            }]
        },
        options:{
            plugins: {
                legend: {
                  display: false
                }
            }
        }
    }
}
var chartGraph = new Chart(document.getElementsByClassName("dough1"), doughnut(DOUG()))
var chartGraph = new Chart(document.getElementsByClassName("dough2"), doughnut(DOUG()))
var chartGraph = new Chart(document.getElementsByClassName("dough3"), doughnut(DOUG()))