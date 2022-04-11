/* eslint-disable react-hooks/rules-of-hooks */
import {useRef, useLayoutEffect} from 'react';
import Chart from "../SRCcharts";


export default function legendaDoughnut(props:any): JSX.Element{
    
return(
<>
<div style={{display: 'flex', width: '98%'}}>
    <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug" style={{backgroundColor: props.label.cor[0]}}></div><span></span></section>
    <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug" style={{backgroundColor: props.label.cor[1]}}></div><span></span></section>
    <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug" style={{backgroundColor: props.label.cor[2]}}></div><span></span></section>
    <section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug" style={{backgroundColor: props.label.cor[3]}}></div><span></span></section>
</div>
</>
)
}
