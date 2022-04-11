import Chart from "./SRCcharts";

const randomD = () => Math.round(Math.random()*10)+4
const DOUG = () => [randomD(),randomD(),randomD(),randomD()]
let inde = 0,vari = 0
setInterval(() => {
    inde>1 ? inde=0:inde++
    Math.random() < 0.5 ? vari = 1 : vari = -1
    dough[inde].data.datasets[0].data[2] += vari
    dough[inde].data.datasets[0].data[1] += vari
    dough[inde].update();
},2000);

const doughnut = (dough: number[],titulo: string) => {
    return {
        type: 'doughnut',
        data: {
            labels: labelDoung,
            datasets:[{
                data: dough,
                backgroundColor:coresDoung,
                cutout: "30%"
            }]
        },
        options:{
            plugins: {
                title: {
                    display: true,
                    color:'white',
                    font:'sans-serif',
                    text:titulo,
                    position:'bottom'
                  },
                legend: {
                    display:false,
                }
            }
        }
    }
}

var coresDoung = ['#63f1b6','#0063f7','#fbff2b','#32dc32'], labelDoung = ['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO']

let dough = new Chart($(".dough1"), doughnut(DOUG(),'PRIMEIRO TURNO'))
