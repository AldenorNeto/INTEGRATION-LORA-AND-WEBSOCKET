/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import BarrasParent from './ts/barrasConsumo';
import injecaoLinhas from './ts/injecao';
import velocimetro from './ts/velocimetro';
import LinhasBU from './graficoLinhas/linhasBu';
import GauciEletrico from './gauciCosumoEletrico/gauciEletrico';

export default function dashboard(): JSX.Element{
    
    const BarrasCosumoSemana = useRef<HTMLCanvasElement>(null);
    const injecaoLinha = useRef<HTMLCanvasElement>(null);
    const acelera1 = useRef<HTMLCanvasElement>(null);
    
    useLayoutEffect(() => {
        BarrasParent(BarrasCosumoSemana.current)
        injecaoLinhas(injecaoLinha.current)
        velocimetro(acelera1.current)
        //linhasBU(AGelada.current,LAGelada.current)
    })
    
return (
<>
    <div>
        <div id="graficoLinhas">
        <LinhasBU titulo='Água Gelada' grandeza='Temperatura' media={4} cor='#00ffc8' unidade='ºc'/>
        <div className='spaceBetween'></div>
        <LinhasBU titulo='Água Industrial' grandeza='Temperatura' media={25} cor='#00a2ff' unidade='ºc'/>
        <div className='spaceBetween'></div>
        <LinhasBU titulo='Compd. Alta P.' grandeza='Pressão' media={12} cor='#00a600' unidade='bar'/>
        <div className='spaceBetween'></div>
        <LinhasBU titulo='Compd. Baixa P.' grandeza='Pressão' media={7} cor='#e1ff00' unidade='bar'/>
        </div>
        <div style={{display: 'flex'}}>
            <div id="containerAcelera"><div id="bombasH1">ROTAÇÃO BOMBAS HIDRAULICAS</div>
                <div id="acelera"><canvas ref={acelera1}></canvas></div>
                <div id="bombas">BOMBA 01</div>
                <div id="acelera"><canvas className="acelera2"></canvas></div>
                <div id="bombas">BOMBA 02</div>
            </div>
            <div id="coluna2">
                <div id="barras"><canvas ref={BarrasCosumoSemana}></canvas></div>
                <div className="linhasInjec"><canvas  ref={injecaoLinha}></canvas></div>
            </div>
            <div style={{width: '45%', display: 'flex', flexDirection: 'column', justifyContent: 'space-around', maxHeight: '3wv'}}>
                <div id="rosquinhas"><div>CONSUMO DE FLUIDOS POR SETOR</div>
                    <div style={{display: 'flex', width: '98%'}}>
                        <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug"></div><span></span></section>
                        <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug"></div><span></span></section>
                        <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug"></div><span></span></section>
                        <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug"></div><span></span></section>
                    </div>
                    <div style={{display: 'flex', justifyContent: 'space-evenly', width: '100%'}}>
                        <div className="doughDiv"><canvas className="dough1"></canvas></div>
                        <div className="doughDiv"><canvas className="dough2"></canvas></div>
                        <div className="doughDiv"><canvas className="dough3"></canvas></div>
                    </div>
                </div>
                <div id="consumoParent">COSUMO ELÉTRICO POR SETOR
                    <div style={{display: 'flex', flexDirection: 'row', width: '100%', justifyContent: 'space-around', height: '100%'}}>
                        <GauciEletrico /><GauciEletrico /><GauciEletrico /><GauciEletrico />
                    </div>
                </div>
            </div>
        </div>
    </div>
</>
)}
