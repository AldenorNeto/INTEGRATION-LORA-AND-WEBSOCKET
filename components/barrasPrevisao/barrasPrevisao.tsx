/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";
import style from './barrasPrevisao.module.scss'

export default function BarrasPrevisao(props:any): JSX.Element{
    
    const refCanvas = useRef<HTMLCanvasElement>(null);
    useLayoutEffect(() => BarrasParent(refCanvas.current))

return(
<div className={style.barras}><canvas ref={refCanvas}></canvas></div>
)

function BarrasParent(Elemento: HTMLCanvasElement | null) {

    const aleatorioSemana = () => Math.round(Math.random()*10)+50;
    var laco = [5, aleatorioSemana(), aleatorioSemana(), aleatorioSemana(), aleatorioSemana(), aleatorioSemana(), aleatorioSemana() - 10];

    laco[new Date().getDay()] = Math.round(Math.random()*4)+17;

    setInterval(() => {
        barras.data.datasets[0].data[new Date().getDay()] = Math.round(Math.random()*4)+17;
        barras.update();
    }, 1500);

    var barras = new Chart(Elemento, {
        type: 'bar',
        data: {
            labels: ['DOM', 'SEG', 'TER', 'QUA', 'QUI', 'SEX', 'SAB'],
            datasets: [{
                label: 'Consumo',
                data: laco,
                backgroundColor: ['aqua'],
                categoryPercentage: 0.5,
            },
            {
                label: 'Previsão',
                data: [4, 55, 53, 57, 53, 55, 45],
                backgroundColor: ['#ffbb00'],
                categoryPercentage: 0.6,
            }]
        },
        options: {
            scales: {
                x: {
                    stacked: true,
                    ticks: {
                        color: 'white'
                    },
                    grid: {
                        display: false
                    }
                },
                y: {
                    ticks: {
                        color: 'white'
                    },
                    grid: {
                        color: '#ffffff20'
                    }
                }
            },
            plugins: {
                title: {
                    display: true,
                    color: 'white',
                    font: 'sans-serif',
                    text: 'CONSUMO SEMANAL ÁGUA DE REÚSO (L)'
                },
                legend: {
                    align: 'end',
                    labels: {
                        usePointStyle: true,
                        color: 'white',
                        font: {
                            size: 9,
                        }
                    }
                }
            }
        }
    });
}}