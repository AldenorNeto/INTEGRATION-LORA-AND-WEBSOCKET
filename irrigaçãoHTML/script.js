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
        console.log(vetor[vetor.length - 1],horarioAtual+":"+new Date().getMinutes());
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
        cbox[i].style.color = "red";
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

