/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";
import style from './linhaTripla.module.scss'

export default function LinhaTripla(props:any): JSX.Element{
    
    const refCanvas = useRef<HTMLCanvasElement>(null);

    useLayoutEffect(() => injecaoLinhas(refCanvas.current))

return(
    <div className={style.linhasInjec}><canvas ref={refCanvas}></canvas></div>
)

function injecaoLinhas(Elemento: HTMLCanvasElement | null){
    const randomInj = () => Math.round(Math.random()*10)
    
    const randomInje = (somatorio: number) =>{
      let array = []
      for (let i=0;i<14;i++)array.push(randomInj()+somatorio)
      return array
    }
    
    setInterval(() => {
      for (let index=0;index<3;index++){
          injecao.data.datasets[index].data.shift() 
          injecao.data.datasets[index].data.push(randomInj()+(20*(index+1))) 
          injecao.update('none');
      }
    },3000);
    
    var ctx = Elemento?.getContext("2d");
    if(ctx)ctx.canvas.height = 200;
    let injecao = new Chart(ctx,{
        type:'line',
        data:{
            labels: ['13','12','11','10','9','8','7','6','5','4','3','2','1','0'],
            datasets: [{
              label: "Ar Comprimido",
              borderColor:'#020067',
              backgroundColor:'#0026fb',
              pointRadius:4,
              pointBorderWidth:2,
              data: randomInje(20),
              fill: true
            }, {
              label: "Ag. Gelada",
              borderColor:'#095582',
              backgroundColor:'#00eff7',
              pointRadius:4,
              pointBorderWidth:2,
              data: randomInje(40),
              fill: true
            }, {
              label: "Ag. Industrial",
              borderColor:'#006b07',
              backgroundColor:'#c4f000',
              pointRadius:4,
              pointBorderWidth:2,
              data: randomInje(60),
              fill: true
            }]
          },
        options: { 
          plugins: {
            title: {
              display: true,
              font:'sans-serif',
              text: 'CONSUMO DE FLUIDOS INJEÇÃO',
              color:'white'
            },
            legend: {
              display: false
          },
          },
          interaction: {
            mode: 'index',
            intersect: false
          },
          scales: {
            x: {
              display: true,
              title: {
                display: true,
                text: 'MINUTOS PASSADOS',
                color:'white'
              },
              ticks:{
                  color:'white'
              },
              grid: {
                display: false
              }
            },
            y: {
              display: true,
              beginAtZero: true,
              ticks:{
                  color:'white'
              },
              grid: {
                display: false
              }
            },
          }
        }
    });
}
}