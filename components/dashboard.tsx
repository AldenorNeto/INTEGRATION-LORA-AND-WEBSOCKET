import LinhasBU from './linhaComMedia/linhasBu';
import GauciEletrico from './gauciCosumoEletrico/gauciEletrico';
import Doughnut from './doughnut/doughnutCosumoFluido'
import LegendaDoughnut from './doughnut/legenda'
import Valocimetro from './velocimetroBomba/velocimetroBomba';
import BarrasPrevisao from './barrasPrevisao/barrasPrevisao';
import LinhaTripla from './linhaTripla/linhaTripla';
import Space from './espaco/espaco';
import Parent from './parenteGrafico/parentGrafico';

export default function dashboard(): JSX.Element{
    const setoresFabrica7 = {setor:['INJEÇÃO','2D','MONTAGEM','MANUTENÇÃO'],cor:['#63f1b6','#0063f7','#fbff2b','#32dc32']}   
    return (
<>
<div>
    <div id="graficoLinhas">
        <LinhasBU grandeza='Temperatura' media={4} cor='#00ffc8' unidade='ºc'>Água Gelada</LinhasBU>
        <Space/>
        <LinhasBU grandeza='Temperatura' media={25} cor='#00a2ff' unidade='ºc'>Água Industrial</LinhasBU>
        <Space/>
        <LinhasBU grandeza='Pressão' media={12} cor='#00a600' unidade='bar'>Compd. Alta P.</LinhasBU>
        <Space/>
        <LinhasBU grandeza='Pressão' media={7} cor='#e1ff00' unidade='bar'>Compd. Baixa P.</LinhasBU>
    </div>
    <div id='bodyDahsboard'>
        <Parent idName={'corpoVelocimetro'} titulo={'ROTAÇÃO BOMBAS HIDRAULICAS'}> 
            <Valocimetro>BOMBA 01</Valocimetro><Valocimetro>BOMBA 02</Valocimetro>
        </Parent>
        <div id="coluna2">
            <BarrasPrevisao/>
            <Space/>
            <LinhaTripla/>
        </div>
        <div id="coluna3">
            <Parent idName={'DoughnutCorpo'} titulo={['CONSUMO DE FLUIDOS POR SETOR',<LegendaDoughnut label={setoresFabrica7}/>]}> 
                <Doughnut>PRIMEIRO TURNO</Doughnut><Doughnut>SEGUNDO TURNO</Doughnut><Doughnut>TERCEIRO TURNO</Doughnut>
            </Parent>
            <Space/>
            <Parent idName={'gauceContainer'} titulo={'COSUMO ELÉTRICO POR SETOR'}> 
                <GauciEletrico cor="#ff8c00" valorInit={55}>INJEÇÃO</GauciEletrico>
                <GauciEletrico cor="#b23f19" valorInit={80}>2D</GauciEletrico>
                <GauciEletrico cor="#ce2a24" valorInit={72}>MONTAGEM</GauciEletrico>
                <GauciEletrico cor="#da3c4b" valorInit={65}>MANUTENÇÃO</GauciEletrico>
            </Parent>
        </div>
    </div>
</div>
</>
)}
