//============
//Webpage Code
//============
String webpageCode = R"***(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IRRIGAÇÃO</title>
    <style>
    #cabecalho td{
    background-color: #bdf0ff;
    padding: 5px 0px;
    height: 150%;
    max-width: min-content;
    font-size: calc(1vw + 5px);
}

#containerButton{
    display: flex;
    justify-content: space-between;
    position: absolute;
    width: 96%;
    left: 2%;
    bottom:10px;
    align-self: start;
    /*background-color: blueviolet;*/
    visibility:hidden
}

option{
    background-color: #00000036;
}

#containerButton *{
    color: white;
    font-size: 30px;
    width: 50px;
    height: 50px;
    border-radius: 50%;
    margin: 5px;
}


#containerButton #envioForm{
    background-image: linear-gradient(to bottom right, #00ff00 50%, #00db00 50%);
    font-weight: bold;
}

#containerButton #cancel{
    background-image: linear-gradient(to bottom right, red  50%, #c70000  50%);
}

table{
    position: relative;
    margin: 10px;
    justify-content: center;
    background-color: #fff;
    align-items: center;
    border-collapse: collapse;
    font-family: 'Trebuchet MS';
    min-width: 90%;
}

td{
    border: 2px solid rgb(114, 114, 114);
    text-align-last: center;
    align-items: center;
    justify-content: center;
    height: 50px;
    width: min-content;
    max-width: 15em;
    padding: -20px;
    width: min-content;
}

.container{
    min-width: 80%;
    display: flex;
    flex-direction: column;
    max-width: min-content;
}

.umidade, .estadoBomba input + div
{font-size: calc(2.7vw + 10px);
    padding: 0px 4px;}

.titulo, input[type="time"]{
    font-size: calc(2.6vw + 5px);
    white-space: nowrap;
    text-overflow: ellipsis;
    overflow: hidden !important;
}

body{
    display: flex;
    flex-direction: column;
    align-items: center;
    background-attachment: fixed;
    text-align-last: center;
    background-image: linear-gradient(#daf6ff 85%, #afffa1);
    min-height: 90%;
    justify-content: center;
    cursor: context-menu;
    border:3px double #afffa107;
}

h1{ 
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: end;
    color: darkcyan;
    font-size: calc(2.3vw + 7px);
    font-family: cursive;
    margin-top: -5px;
}

h1 span{
    color: darkblue;
    font-size: calc(2.3vw + 12px);
    font-family: Verdana;
    margin-bottom: 10px;
    margin-right: 10px;
}

h1 div{
    display: flex;
    align-items: center;
    margin: 5px;
    color: #19d700;
    margin-bottom: 12px;
}

.gg-drop-invert {
    box-sizing: border-box;
    position: absolute;
    display: block;
    transform: rotate(70deg) scale(var(--ggs,1));
    width: calc(2vw + 10px);
    height: calc(2vw + 10px);
    max-width: 32px;
    max-height: 32px;
    border-radius: 0px 100% 100% 100%;
    box-shadow: inset 0 0 0 5px;
    overflow: hidden
}
.gg-drop-invert::before {
    content: "";
    display: block;
    position: absolute;
    box-sizing: border-box;
    width: calc(1.4vw + 10px);
    height: calc(1.5vw + 10px);
    background: currentColor;
    transform: rotate(-65deg);
    border-radius: 50px 30px;
    right: 0px;
    top: -5px;
}

#estadoIrrigar{
    width: 100%;
    height: 100%;
    background-color: #ced2ff;
    padding: 0px;
}

select{height: 60px}

input[type="checkbox"]{display: none}

input[type="time"]{
    border: none;
    appearance: auto;
    width: 100%;
    height: 100%;
    padding: 2px 2px;
    cursor: text;
    background-color: #ffffff00;
}

input[type="time"]:hover{background-color: #bfbfbf50}

.estadoBomba input + div{
    display: flex;
    padding: 0px 4px;
    background-color: #c2c2c2;
    height: 100%;
    justify-content: center;
    align-items: center;
    cursor: pointer;
}

.estadoBomba input:checked + div{background-color: #09ff00}

.estadoBomba input + div:hover{background-color: #afafaf}

.estadoBomba input + div::after{content: "OFF"}

.estadoBomba input:checked + div:hover{background-color: #51ff4b}

.estadoBomba input:checked + div::after{content: "ON"}

@media screen and (min-width:600px){
    .dom::after{content: "OM"}
    .seg::after{content: "EG"}
    .ter::after{content: "ER"}
    .qua::after{content: "UA"}
    .qui::after{content: "UI"}
    .sex::after{content: "EX"}
    .sab::after{content: "AB"}
}

.semana label input + div{
    display: flex;
    justify-content: center;
    align-items: center;
    background-color: #dddddd;
    font-size: calc(1vw + 5px);
    height: min-content;
    max-height: 18px;
    border: 1px solid;
    margin: 0px calc(0.1vw + 0.5px);
    padding: 4% calc(0.5vw);
}

.semana label input + div:hover{background-color: #d0d0d0}

.semana label input:checked + div{
    font-weight: bold;
    background-color: #ffe600;
}

.semana{
    /*background-color: darkgoldenrod;*/
    display: flex;
    justify-content: space-around;
    height: max-content;
    width: min-content;
    align-items: center;
    margin: 1px 0px;
    
}

.DATA{

    display: flex;
    height: 80%; /*78px;*/
    width: 100%;
    position: relative;
    flex-direction: column;
    align-items: center;
    justify-content: space-around;
}

.DATA:hover{
    background-color: #fbff0018;
}

.irrigar{
    display: flex;
    width: 100%;
}

.relogio{
    display: flex;
    border: 1px solid;
    align-items: end;
    flex-direction: row;
    font-family: monospace ;
    font-weight: bold;
    padding: 3px 3px;
    background-color: #fff;
    margin: 10px;
    margin-top: 30px;
    margin-bottom: 30px;
    float: right;
}

.relogio div span{
    font-size: calc( 1vw + 10px);
    background-color: #ffff00;
    border: 1px solid;
    padding: 5px 10px;
    margin: 3px;
}

.relogio div{display: flex}

td span:hover{background-color: #00000003}

.titulo:hover{background-color: #53535314}

.titulo + div{
    display: flex;
    opacity: 0;
    position:absolute;
    font-size: 0px;
    left: 470px;
    background-color: #fff67ce6;
    border: solid 0px;
    padding: 0px;
}

table input{
    border: none;
    width: 100%;
    height: 100%;
}


    </style>
    <script defer>
setTimeout(() => {

    var getVal = () => {
        var POTvalRequest = new XMLHttpRequest();
        POTvalRequest.onreadystatechange = function(){
            if(this.readyState == 4 && this.status == 200){
                document.querySelector("#umidade1").innerHTML = this.responseText
            }
        }
        POTvalRequest.open("GET", "readPOT", true);
        POTvalRequest.send();
    }

    var vet1 = []
    var vet2 = []
    var vet3 = []
    var vet4 = []
    var vet5 = []

    const guardaVariaveis = (checkboxSemana,timeSemana) => {
        let vet = []
        for(let check of document.querySelectorAll(checkboxSemana)){
            if(check.checked){
                vet.push(check.value);
            }
        }
        vet.push(document.querySelector(timeSemana).value)

        return vet
    }

    const queDiaEHoje = valor => valor ==  new Date().getDay()

    const ligaBombaAutomatico = (vetor,bomba) => {
        let horarioAtual = String(new Date().getHours())
        if(horarioAtual[0]!= '0'){
            horarioAtual = 0 + horarioAtual;
        }
        //console.log(vetor[vetor.length - 1] , new Date().getHours()+":"+new Date().getMinutes());
        if((vetor.some(queDiaEHoje)) && (vetor[vetor.length - 1] == horarioAtual+":"+new Date().getMinutes())){
            document.querySelector(bomba).checked = true
        }else{
            document.querySelector(bomba).checked = false
        }
    }

    document.querySelector('#envioForm').addEventListener('click', () => {
        vet1 = guardaVariaveis('.checkboxSemana1','#timeSemana1')
        vet2 = guardaVariaveis('.checkboxSemana2','#timeSemana2')
        vet3 = guardaVariaveis('.checkboxSemana3','#timeSemana3')
        vet4 = guardaVariaveis('.checkboxSemana4','#timeSemana4')
        vet5 = guardaVariaveis('.checkboxSemana5','#timeSemana5')
        
        ligaBombaAutomatico(vet1,"#bomba1")
        ligaBombaAutomatico(vet2,"#bomba2")
        ligaBombaAutomatico(vet3,"#bomba3")
        ligaBombaAutomatico(vet4,"#bomba4")
        ligaBombaAutomatico(vet5,"#bomba5")
    })

    document.querySelector('#cancel').addEventListener('click', () => document.location.reload(true))
    
    const cbox = document.querySelectorAll("input");

    for (let i = 0; i < cbox.length; i++) {
        cbox[i].addEventListener("click", function() {
            document.querySelector('#containerButton').style.visibility = 'visible';
        });
    }
        
    
    var mostraTime = () => {
        var nD = new Date();
        var dia = nD.getDate();
        var mes = (nD.getMonth() + 1);
        var ano = nD.getFullYear(); 
        var hora = nD.getHours();
        var minuto = nD.getMinutes();
        var semana = nD.getDay();
        
        if(dia < 10)dia = "0" + dia
        if(mes < 10)mes = "0" + mes
        if(hora < 10)hora = "0" + hora
        if(minuto < 10)minuto = "0" + minuto
        
        if(semana == 0)StrigSemana = "Domingo"
        else if(semana == 1)StrigSemana = "Segunda"
        else if(semana == 2)StrigSemana = "Terça"
        else if(semana == 3)StrigSemana = "Quarta"
        else if(semana == 4)StrigSemana = "Quinta"
        else if(semana == 5)StrigSemana = "Sexta"
        else if(semana == 6)StrigSemana = "Sabado"
        
        document.querySelector("#relogioD").innerHTML = ("<span> "+dia+"/"+mes+"/"+ano+" </span>")
        document.querySelector("#relogioH").innerHTML = ("<span> "+hora+":"+minuto+" </span>")
        document.querySelector("#relogioS").innerHTML = ("<span> "+StrigSemana+" </span>")    
    }

    setTimeout(mostraTime,10)
    //setInterval(getVal,2000)
    setInterval(mostraTime,100)
    setInterval(() => {
        ligaBombaAutomatico(vet1,"#bomba1")
        ligaBombaAutomatico(vet2,"#bomba2")
        ligaBombaAutomatico(vet3,"#bomba3")
        ligaBombaAutomatico(vet4,"#bomba4")
        ligaBombaAutomatico(vet5,"#bomba5")
    },1000)
})

    
    </script>
</head>
<body onselectstart="return false">
    <div class="container">
        <h1><span>Grendene</span>IRRIGAÇÃO 4.0<div><i class="gg-drop-invert"></i></div></h1>
        <form method="get" action="/">
        <div id="containerButton">
            <input type="submit" id="envioForm" value="✓">
            <input type="submit" id="cancel" value="✖">
        </div>
        <TABLE>
            <tr id="cabecalho">
                <td>LOCAL</td>
                <td>DURAÇÃO</td>
                <td>HORARIO</td>
                <td>DIA</td>
                <td>UMIDADE</td>
                <td>IRRIGAR</td>
            </tr>
            <tr>
                <td class="titulo">Fab 01 jard esq</td>
                <td><select name="" id="" style="width: 100%; height: 100%; border: none; font-size: 25px;">
                    <option value="5">5:00</option>
                    <option value="10">10:00</option>
                    <option value="15">15:00</option>
                    <option value="20">20:00</option>
                    <option value="25">25:00</option>
                </select></td>
                <td><input type="time" id="timeSemana1"></div></td>
                <td>
                    <div  class="DATA">
                        <div  class="semana">
                            <label>
                                <input type="checkbox" value="0" name="S1">
                                <div class="dom">D</div>
                            </label>
                            <label>
                                <input type="checkbox" value="1" name="S1">
                                <div class="seg">S</div>
                            </label>
                            <label>
                                <input type="checkbox" value="2" name="S1">
                                <div class="ter">T</div>
                            </label>
                            <label>
                                <input type="checkbox" value="3" name="S1">
                                <div class="qua">Q</div>
                            </label>
                        </div>
                        <div  class="semana">
                            <label>
                                <input type="checkbox" value="4" name="S1">
                                <div class="qui">Q</div>
                            </label><label>
                                <input type="checkbox" value="5" name="S1">
                                <div class="sex">S</div>
                            </label><label>
                                <input type="checkbox" value="6" name="S1">
                                <div class="sab">S</div>
                            </label>
                        </div>
                    </div></div>
                </td>
                <td><span class="umidade" id="umidade1">0.69%</span></div></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" id="bomba1"><div></div>
                </label></td>
            </tr>
            <tr>
                <td class="titulo"><div>Fab 02</div></td>
                <td><select name="" id="" style="width: 100%; height: 100%; border: none; font-size: 25px;">
                    <option value="5">5:00</option>
                    <option value="10">10:00</option>
                    <option value="15">15:00</option>
                    <option value="20">20:00</option>
                    <option value="25">25:00</option>
                </select></td>
                <td><input type="time" id="timeSemana2"></td>
                <td><div  class="DATA">
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="0" name="S2">
                            <div class="dom">D</div>
                        </label>
                        <label>
                            <input type="checkbox" value="1" name="S2">
                            <div class="seg">S</div>
                        </label>
                        <label>
                            <input type="checkbox" value="2" name="S2">
                            <div class="ter">T</div>
                        </label>
                        <label>
                            <input type="checkbox" value="3" name="S2">
                            <div class="qua">Q</div>
                        </label>
                    </div>
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="4" name="S2">
                            <div class="qui">Q</div>
                        </label><label>
                            <input type="checkbox" value="5" name="S2">
                            <div class="sex">S</div>
                        </label><label>
                            <input type="checkbox" value="6" name="S2">
                            <div class="sab">S</div>
                        </label>
                    </div>
                </div></td>
                <td><span class="umidade">0.75%</span></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" id="bomba2"><div></div>
                </label></td>
            </tr>
            <tr>
                <td class="titulo"><div>Fab 03</div></td>
                <td><select name="" id="" style="width: 100%; height: 100%; border: none; font-size: 25px;">
                    <option value="5">5:00</option>
                    <option value="10">10:00</option>
                    <option value="15">15:00</option>
                    <option value="20">20:00</option>
                    <option value="25">25:00</option>
                </select></td>
                <td><input type="time" id="timeSemana3"></td>
                <td><div  class="DATA">
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="0" name="S3">
                            <div class="dom">D</div>
                        </label>
                        <label>
                            <input type="checkbox" value="1" name="S3">
                            <div class="seg">S</div>
                        </label>
                        <label>
                            <input type="checkbox" value="2" name="S3">
                            <div class="ter">T</div>
                        </label>
                        <label>
                            <input type="checkbox" value="3" name="S3">
                            <div class="qua">Q</div>
                        </label>
                    </div>
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="4" name="S3">
                            <div class="qui">Q</div>
                        </label><label>
                            <input type="checkbox" value="5" name="S3">
                            <div class="sex">S</div>
                        </label><label>
                            <input type="checkbox" value="6" name="S3">
                            <div class="sab">S</div>
                        </label>
                    </div>
                </div></td>
                <td><span class="umidade">0.73%</span></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" id="bomba3"><div></div>
                </label></td>
            </tr>
            <tr>
                <td class="titulo"><div>Fab 04</div></td>
                <td><select name="" id="" style="width: 100%; height: 100%; border: none; font-size: 25px;">
                    <option value="5">5:00</option>
                    <option value="10">10:00</option>
                    <option value="15">15:00</option>
                    <option value="20">20:00</option>
                    <option value="25">25:00</option>
                </select></td>
                <td><input type="time" id="timeSemana4"></td>
                <td><div  class="DATA">
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="0" name="S4">
                            <div class="dom">D</div>
                        </label>
                        <label>
                            <input type="checkbox" value="1" name="S4">
                            <div class="seg">S</div>
                        </label>
                        <label>
                            <input type="checkbox" value="2" name="S4">
                            <div class="ter">T</div>
                        </label>
                        <label>
                            <input type="checkbox" value="3" name="S4">
                            <div class="qua">Q</div>
                        </label>
                    </div>
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="4" name="S4">
                            <div class="qui">Q</div>
                        </label><label>
                            <input type="checkbox" value="5" name="S4">
                            <div class="sex">S</div>
                        </label><label>
                            <input type="checkbox" value="6" name="S4">
                            <div class="sab">S</div>
                        </label>
                    </div>
                </div></td>
                <td><span class="umidade">0.75%</span></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" id="bomba4"><div></div>
                </label></td>
            </tr>
            <tr> 
                <td class="titulo"><div>Fab 05</div></td>
                <td><select name="" id="" style="width: 100%; height: 100%; border: none; font-size: 25px;">
                    <option value="5">5:00</option>
                    <option value="10">10:00</option>
                    <option value="15">15:00</option>
                    <option value="20">20:00</option>
                    <option value="25">25:00</option>
                </select></td>
                <td><input type="time" id="timeSemana5"></td>
                <td><div  class="DATA">
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="0" name="S5">
                            <div class="dom">D</div>
                        </label>
                        <label>
                            <input type="checkbox" value="1" name="S5">
                            <div class="seg">S</div>
                        </label>
                        <label>
                            <input type="checkbox" value="2" name="S5">
                            <div class="ter">T</div>
                        </label>
                        <label>
                            <input type="checkbox" value="3" name="S5">
                            <div class="qua">Q</div>
                        </label>
                    </div>
                    <div  class="semana">
                        <label>
                            <input type="checkbox" value="4" name="S5">
                            <div class="qui">Q</div>
                        </label><label>
                            <input type="checkbox" value="5" name="S5">
                            <div class="sex">S</div>
                        </label><label>
                            <input type="checkbox" value="6" name="S5">
                            <div class="sab">S</div>
                        </label>
                    </div>
                </div></td>
                <td><span class="umidade">0.80%</span></td>
                <td><label class="estadoBomba">
                    <input type="checkbox" id="bomba5"><div></div>
                </label></td>
            </tr>
        </TABLE>
    </form>
        <div><div class="relogio">
            <div id="relogioD">Carregando...</div>
            <div id="relogioH"></div>
            <div id="relogioS"></div>
        </div></div>
    </div>

</body>
)***";
