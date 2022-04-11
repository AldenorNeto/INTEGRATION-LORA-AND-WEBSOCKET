const randomD = () => parseInt(Math.random()*10)+4
const DOUG = () => [randomD(),randomD(),randomD(),randomD()]
let inde = 0,vari = 0
setInterval(() => {
    inde>1 ? inde=0:inde++
    Math.random() < 0.5 ? vari = 1 : vari = -1
    dough[inde].data.datasets[0].data[2] += vari
    dough[inde].data.datasets[0].data[1] += vari
    dough[inde].update();
},2000);

const doughnut = (dough,titulo) => {
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

var dough = [], coresDoung = ['#63f1b6','#0063f7','#fbff2b','#32dc32'], labelDoung = ['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO']
for (let index in coresDoung){
    $('.legendaDoug:eq('+index+')').css('background', coresDoung[index])
    console.log($('.legendaDoug:eq('+index+')').parent().children("span").text(labelDoung[index]))
    
}
dough[0] = new Chart($(".dough1"), doughnut(DOUG(),'PRIMEIRO TURNO'))
dough[1] = new Chart($(".dough2"), doughnut(DOUG(),'SEGUNDO TURNO'))
dough[2] = new Chart($(".dough3"), doughnut(DOUG(),'TERCEIRO TURNO'))