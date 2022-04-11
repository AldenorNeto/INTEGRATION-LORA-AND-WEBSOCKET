/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";

export default function LinhasBU(props:any): JSX.Element{
    
    const refCanvas = useRef<HTMLCanvasElement>(null);
    const refLegenda = useRef<HTMLCanvasElement>(null);

    useLayoutEffect(() => montaGrafico(refCanvas.current,refLegenda.current))

return(
<>
    <div className="linhaBUPai"><div className="linhas"><canvas ref={refCanvas}></canvas></div>
    <div className="mediaSemana"><div>{props.grandeza}:<div className="valorlinhaBU"><section ref={refLegenda}></section><div>{props.unidade}</div></div></div>
    <div>Média Semanal:<div className="valorlinhaBUmedia">{(props.media + Math.random()).toFixed(1)+' '+props.unidade}</div></div></div></div>
</>
)


function montaGrafico(Elemento: HTMLCanvasElement | null, Legenda: any, ){

    const randomConsu = (pesoindex: number) => (Math.random()*((pesoindex/5)))+pesoindex
    const randomConsuFor = (pesoInd: number) =>{
        let array = []
        for(let i=0;i<18;i++)array.push(randomConsu(pesoInd))
        return array
    }
    let randomConsumo
    
    for(let index = 0; index < 4; index++){
        Legenda.innerText = randomConsu(props.media).toFixed(0)
    }
    
    setInterval(() => {
        randomConsumo = randomConsu(props.media)
        linhaBU.data.datasets[0].data.shift() 
        linhaBU.data.datasets[0].data.push(randomConsumo)
        Legenda.innerText = randomConsumo.toFixed(0)
        linhaBU.update('none');
    },4810);

    let linhaBU = new Chart(Elemento, {
        type: 'line',
        data: {
            labels:['12:00','12:15','12:30','12:45','13:00','13:15','13:30','13:45','14:00','14:15','14:30','14:45','15:00','15:15','15:30','15:45','16:00','16:15'],
            datasets:[{
                label:props.children,
                data: randomConsuFor(props.media),
                borderColor:props.cor,
                backgroundColor:props.cor,
                pointRadius:2
            }],
        },
        options: {
            plugins: {
                title: {
                  display: true,
                  color:'white',
                  font:'sans-serif',
                  text:props.children
                },
                legend: {
                  display: false
                }
            },
            scales:{
                x:{
                    ticks:{
                        font: {
                            size: 8
                        },
                        color:'white'
                    },
                    grid:{
                        display: false
                    }
                },
                y:{
                    beginAtZero: true,
                    max:props.media+5,
                    ticks:{
                        color:'white',
                        sampleSize:2,
                        font: {
                            size: 8
                        }
                    },
                    grid:{
                        color:'#ffffff40'
                    }
                }
            }
        }
    })
    
   
    
}
}

