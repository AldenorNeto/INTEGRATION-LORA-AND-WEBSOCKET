import style from './parent.module.scss'
export default function Parent(props:any): JSX.Element{
return(
<>
<div className={style.containerComTitulo}>{props.titulo}
    <div id={props.idName} >
        {props.children}
    </div>
</div>
</>
)}
