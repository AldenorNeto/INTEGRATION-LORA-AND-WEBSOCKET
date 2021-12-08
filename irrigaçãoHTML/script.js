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

    
    document.querySelector('#envioForm').addEventListener('click', () => {
        var vet = []
        for(let check of document.querySelectorAll('.checkboxSemana1')){
            if(check.checked){
                vet.push(check.value);
            }
        }
            console.log(vet);
    })
    

    var mostraTime = () => {
        var nD = new Date();
        var dia = nD.getDate();
        var mes = (nD.getMonth() + 1);
        var ano = nD.getFullYear(); 
        var hora = nD.getHours();
        var minuto = nD.getMinutes();
        var semana = nD.getDay();
        
        if(dia < 10)dia = "0" + String(dia)
        if(mes < 10)mes = "0" + String(mes)
        if(hora < 10)hora = "0" + String(hora)
        if(minuto < 10)minuto = "0" + String(minuto)
        
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
    setInterval(getVal,2000)
    setInterval(mostraTime,10000)
})

