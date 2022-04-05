const randomD = () => parseInt(Math.random()*10)+1
const DOUG = () => [randomD(),randomD(),randomD(),randomD()]
let inde = 0
setInterval(() => {
    inde>1 ? inde=0:inde++
    Math.random() < 0.5 ? varia = 1 : varia = -1
    dough[inde].data.datasets[0].data[2] += varia
    dough[inde].data.datasets[0].data[1] += varia
    dough[inde].update();
},2000);

const doughnut = dough => {
    return {
        type: 'doughnut',
        data: {
            labels:['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO'],
            datasets:[{
                data: dough,
                backgroundColor:['#63f1b6','#2c2cc0','#ffea00','#32dc32'],
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

var dough = [,,]
dough[0] = new Chart(document.getElementsByClassName("dough1"), doughnut(DOUG()))
dough[1] = new Chart(document.getElementsByClassName("dough2"), doughnut(DOUG()))
dough[2] = new Chart(document.getElementsByClassName("dough3"), doughnut(DOUG()))