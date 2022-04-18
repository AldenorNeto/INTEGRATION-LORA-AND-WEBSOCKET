/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";
import style from './doughnutCosumoFluido.module.scss'


export default function GauciEletrico(props:any): JSX.Element{
    
    const canvas = useRef<HTMLCanvasElement>(null);

    useLayoutEffect(() => consumoFluido(canvas.current))

return(
<>
<div className={style.doughDiv}><canvas ref={canvas}></canvas></div>
</>
)

function consumoFluido(Elemento: HTMLCanvasElement | null){
    
const randomD = () => Math.round(Math.random()*10)+4
//
const DOUG = () => [randomD(),randomD(),randomD(),randomD()]
let inde = 0,vari = 0, dough:any
setInterval(() => {
    inde>1?inde=0:inde++
    Math.random() < 0.55 ? vari = 1 : vari = -1
        dough.data.datasets[0].data[2] += vari
        dough.data.datasets[0].data[1] += vari
        dough.update();
},2000);

dough = new Chart(Elemento,{
        type: 'doughnut',
        data: {
            labels: ['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO'],
            datasets:[{
                data: DOUG(),
                backgroundColor:['#63f1b6','#0063f7','#fbff2b','#32dc32'],
                cutout: "30%"
            }]
        },
        options:{
            plugins: {
                title: {
                    display: true,
                    color:'white',
                    font:'sans-serif',
                    text:props.children,
                    position:'bottom'
                  },
                legend: {
                    display:false,
                }
            }
        }
    })

}

}