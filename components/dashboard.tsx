/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import BarrasParent from './ts/barrasConsumo';
import injecaoLinhas from './ts/injecao';
import LinhasBU from './graficoLinhas/linhasBu';
import GauciEletrico from './gauciCosumoEletrico/gauciEletrico';
import Doughnut from './doughnut/doughnutCosumoFluido'
import Valocimetro from './velocimetroBomba/velocimetroBomba';

export default function dashboard(): JSX.Element{
    
    const BarrasCosumoSemana = useRef<HTMLCanvasElement>(null);
    const injecaoLinha = useRef<HTMLCanvasElement>(null);
    const setoresFabrica7 = {setor:['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO'],cor:['#63f1b6','#0063f7','#fbff2b','#32dc32']}
    
    useLayoutEffect(() => {
        BarrasParent(BarrasCosumoSemana.current)
        injecaoLinhas(injecaoLinha.current)
    })
    
return (
<>
    <div>
        <div id="graficoLinhas">
            <LinhasBU grandeza='Temperatura' media={4} cor='#00ffc8' unidade='ºc'>Água Gelada</LinhasBU>
            <div className='spaceBetween'></div>
            <LinhasBU grandeza='Temperatura' media={25} cor='#00a2ff' unidade='ºc'>Água Industrial</LinhasBU>
            <div className='spaceBetween'></div>
            <LinhasBU grandeza='Pressão' media={12} cor='#00a600' unidade='bar'>Compd. Alta P.</LinhasBU>
            <div className='spaceBetween'></div>
            <LinhasBU grandeza='Pressão' media={7} cor='#e1ff00' unidade='bar'>Compd. Baixa P.</LinhasBU>
        </div>
        <div style={{display: 'flex'}}>
            <div id="containerAcelera"><div id="bombasH1">ROTAÇÃO BOMBAS HIDRAULICAS</div>
                <Valocimetro>BOMBA 01</Valocimetro><Valocimetro>BOMBA 02</Valocimetro>
            </div>
            <div id="coluna2">
                <div id="barras"><canvas ref={BarrasCosumoSemana}></canvas></div>
                <div className="linhasInjec"><canvas  ref={injecaoLinha}></canvas></div>
            </div>
            <div style={{width: '100%', display: 'flex', flexDirection: 'column', justifyContent: 'space-around', maxHeight: '3wv'}}>
                <div id="rosquinhas"><div>CONSUMO DE FLUIDOS POR SETOR</div>
                    <legendaDoughnut />
                    <div style={{display: 'flex', justifyContent: 'space-evenly', width: '100%'}}>
                        <Doughnut>PRIMEIRO TURNO</Doughnut><Doughnut>SEGUNDO TURNO</Doughnut><Doughnut>TERCEIRO TURNO</Doughnut>
                    </div>
                </div>
                <div id="consumoParent">COSUMO ELÉTRICO POR SETOR
                    <div style={{display: 'flex', flexDirection: 'row', width: '100%', justifyContent: 'space-around', height: '100%'}}>
                        <GauciEletrico cor="#ff8c00" valorInit={55}>INJEÇÃO</GauciEletrico>
                        <GauciEletrico cor="#b23f19" valorInit={80}>2D</GauciEletrico>
                        <GauciEletrico cor="#ce2a24" valorInit={72}>MONTAGEM</GauciEletrico>
                        <GauciEletrico cor="#da3c4b" valorInit={65}>MANUTENÇÃO</GauciEletrico>
                    </div>
                </div>
            </div>
        </div>
    </div>
</>
)}
