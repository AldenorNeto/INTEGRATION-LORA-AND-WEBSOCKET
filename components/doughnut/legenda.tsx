export default function legendaDoughnut(props:any): JSX.Element{ 
return(
<div style={{display: 'flex', width: '98%'}}>
    {props.label.setor.map((propriedade:any, indice: any)=>(<section style={{display:'flex',alignItems:'center',fontSize:'10px'}}><div className="legendaDoug" style={{backgroundColor: props.label.cor[indice]}}></div><span>{propriedade}</span></section>))}
</div>
)
}
