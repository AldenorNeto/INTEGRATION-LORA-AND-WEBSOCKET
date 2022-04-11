/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";

export default function Valocimetro(props:any): JSX.Element{
    
    const refCanvas = useRef<HTMLCanvasElement>(null);
    useLayoutEffect(() => velocimetroGauce(refCanvas.current))

return(
<>
<div id="acelera"><canvas ref={refCanvas}></canvas></div>
<div id="bombas">{props.children}</div>
</>
)


function velocimetroGauce(Elemento: HTMLCanvasElement | null) {

let variante = 0, Mathrandom = Math.random()
setInterval(() => {
  Mathrandom < 0.5 ? variante = 1 : variante = -1
  acelera.data.datasets[0].needleValue += variante
  acelera.update();
}, 1100);

setInterval(() => Mathrandom = Math.random(), 5000);

const velocimetro = (multi: any,angulo: any) => {
  return {
    type: "doughnut",
    data:{
      labels: ["OK","RISCO","ALTO RISCO"],
      datasets: [{
        data: [120, 50, 30],
        backgroundColor: ["#00fc15","yellow","red",],
        needleValue: angulo,
        borderColor: "white",
        borderWidth: 1,
        cutout: "70%",
        circumference: 180,
        rotation: 270,
      }],
  },
  options: {
    plugins: {
      legend: {
        display: false,
      },
    },
  },
  plugins: [{
    id: "gaugeNeedle",
    afterDatasetDraw(chart: { _metasets?: any; ctx?: any; data?: any; chartArea?: any; }) {
      const {ctx, data, chartArea: {width}} = chart;
      ctx.save();
      const needleValue = data.datasets[0].needleValue;

      if(needleValue <= 200) var angle = Math.PI + (1 / 200) * needleValue * Math.PI;
      else angle = 0;
      
      const cx = width / 2;
      const cy = chart._metasets[0].data[0].y;
  
      ctx.translate(cx, cy);
      ctx.rotate(angle);
      ctx.beginPath();
      ctx.moveTo(0, -15);
      ctx.lineTo(multi, 0);
      ctx.lineTo(0, 15);
      ctx.fillStyle = "#fff";
      ctx.fill();
  
      ctx.translate(-cx, -cy);
      ctx.beginPath();
      ctx.arc(cx, cy, 15, 0, 10);
      ctx.fill();
      ctx.restore();
  
      ctx.font = "20px sans-serif";
      ctx.fillStyle = "#fff";
      ctx.fillText(needleValue + " RPM", cx, cy + 50);
      ctx.font = "10px Ubuntu";
      ctx.fillText('0', 5, cy + 20);
      ctx.textAlign = "center";
      ctx.restore();
    },
  }],
  }
}

let acelera = new Chart(Elemento, velocimetro(135,55))

}}