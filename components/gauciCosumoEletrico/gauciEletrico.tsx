/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";
import style from './gauciEletrico.module.scss'

export default function GauciEletrico(props:any): JSX.Element{
    
    const consumo = useRef<HTMLCanvasElement>(null);
    const consumoNumero = useRef<HTMLSpanElement>(null);

    useLayoutEffect(() => {
        consumoEletrico(consumo.current,consumoNumero.current)
    })

return(
<>
<div className={style.consu}>{props.children}<canvas ref={consumo}></canvas><div className={style.consuNumerico}><span ref={consumoNumero}></span> KVa</div></div>
</>
)

function consumoEletrico(Elemento: HTMLCanvasElement | null,elementoNumero: any) {

    let varia
    setInterval(() => {
      Math.random() < 0.5 ? varia = 1 : varia = -1
      let rando = consumo.data.datasets[0].data[0] + varia
      consumo.data.datasets[0].data = [rando, -(rando)+100]
      consumo.update();
      if(elementoNumero)elementoNumero.innerText = (consumo.data.datasets[0].data[0]*2.34).toFixed(1)
    },800+(Math.random()*500));

    let consumo = new Chart(Elemento,{
        type: 'doughnut',
        data: {
        datasets: [{
            data: [props.valorInit, -props.valorInit+100],
            backgroundColor: [props.cor,"#0000000c"],
            borderColor: "#00000000",
            cutout: "70%",
            borderRadius: 100
            }]
        },
        options: {
              responsive: true,
          legend: {
              display: false
          }
        },
        plugins: [{
          id: "gaugeNeedle",
          afterDatasetDraw(chart:any){
              const {ctx,data,chartArea: {width, height}} = chart
              ctx.restore();
              var fontSize = (height / 65).toFixed(2);
              ctx.font = fontSize + "em sans-serif";
              ctx.textBaseline = "middle";
            
              var text = data.datasets[0].data[0] + '%',
                  textX = Math.round((width - ctx.measureText(text).width) / 2),
                  textY = height / 1.7;
            
              ctx.fillStyle = props.cor;
              ctx.fillText(text, textX, textY);
              ctx.save();
              }
        }]

    })

    elementoNumero.innerText = (consumo.data.datasets[0].data[0]*3.24).toFixed(1)
    elementoNumero.parentElement.style.color = props.cor;
    }
}