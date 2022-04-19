$(document).ready(() => {
    
    const ajaxValues = () => {
        $.get("messages.json",function(data){
            //var data = " \n    4227906258 \n    3147649 \n    433684552 \n    2139226109 \n "
            var date = data.split()
            date.join()
            veto = date[0].split(" ")
            var filtro = ["\n", ""]   
            var arrayFiltrado = veto.filter( elemento => !filtro.includes(elemento));
            veto = arrayFiltrado
            veto = [parseInt(veto[0]).toString(2),parseInt(veto[1]).toString(2),parseInt(veto[2]).toString(2),parseInt(veto[3]).toString(2)]
            for (var j = 0; j < 4; j++) {
                veto[j] = (veto[j]).split('');
                var x = 0
                while(x < veto[j].length){
                    veto[j][x] = parseInt(veto[j][x])
                    x++;
                }
                while(veto[j].length < 32){
                    veto[j].unshift(0);
                }
                veto[j].reverse()
            }
        })
    }


    /*var variaveisVazias = () => {
        var v = "I"
        for(let n = 0; n < 3; n++){
            for (let cont = 0; cont < 95; cont++) {
                for (let i = 0; i < 8; i++) {
                    let texto = $("div#" + v + cont + i).parent().find("nav").next().text()
                    if((texto == '') || (texto == ' ')){
                        $("div#" + v + cont + i).parent().css('background-color', '#ffffff50')
                        $("div#" + v + cont + i).css({'background-color': '#ffffff00',
                        'border': '1px solid #ffffff00'})
                    }
                }
            }
            if(n == 1){
                v = "S"
            } 
            if(n == 0){
                v = "Q"
            }
        }
    }*/
    

    var vet = []
    var tagNomes = () => {
        var tag
        let texto
        for(let n = 0; n < 200; n++){
            texto = $(".tag:eq(" + n +")").next().text()
            if(texto){
                tag = ($(".tag:eq(" + n +")").next().next().attr("id")) 
                vet.push(tag)
            }
            else{
                $(".tag:eq(" + n +")").parent().removeClass().addClass('class')
            }
        }
    }

   
    var veto = []
    var vetor = []
    pose = 0
    for(let n = 0; n < 128; n++){
        vetor.push(0)
    }
    var vetpass
    var variaveisEstado = () => {
        veto = veto[0].concat(veto[1],veto[2],veto[3])
        for(let n = 0; n < 128; n++){
            if(veto[n]){
                $("#IDENTIFICACAO_RAPIDA #" + vet[n]).css('background-color','#00ff00')
            }else{  
                $("#IDENTIFICACAO_RAPIDA #" + vet[n]).css('background-color','#dbdbdb')
            }   
        }

        for(let n = 0; n < 128; n++){
            if(veto[n]){
               vetor[n]++
               $("#" + vet[n] + " div:eq("+pose+")").css('background-color','#00ff00')
            }
            else{
                $("#" + vet[n] + " div:eq("+pose+")").css('background-color','#e2e2e2')
            }
        }
        if($("#exibicao option:selected").val() == "IDENTIFICACAO_RAPIDA"){
            for(let n = 0; n < 128; n++){
                var dezena = vetor[n] / 10
                var unidade =   vetor[n] - (parseInt( dezena)*10)
                $("#" + vet[n]).text(parseInt( dezena) + "." +  unidade + "s")
            }
        }
        pose++
        if((vetpass == 0) && (veto[1] == 1)){
            pose = 0
            for(let n = 0; n < 128; n++){
                if($("#exibicao option:selected").val() == "temposDeCiclo"){
                        var dezena = vetor[n] / 10
                        var unidade =   vetor[n] - (parseInt( dezena)*10)
                        $("#" + vet[n]).parent().find(".tempoFinal").text(parseInt( dezena) + "." +  unidade + "s")
                }
                vetor[n] = 0
            }
        }
        vetpass = veto[1]
    }
    

    /*var mostraTempo = () => {
            for(let n = 0; n < 128; n++){
                if(n > 0){
                    if(vet[n][1] != vet[n - 1][1]){
                        $("#temposDeCiclo").append("<br>")
                    }
                }
                let texto = $("#" + vet[n]).parent().find("nav").next().text()
                if(vet[n][0] == "I"){
                    $("#temposDeCiclo").append("<nav class='Imp'><div>%" + vet[n][0] + vet[n][1] + "." + vet[n][2] + "</div><div style='background-color: #aaaaaa;'>23.3s</div><article class='art' id='T" + vet[n] + "'>" + /*texto +*/ /*"</article></nav><br>")
                /*}
                if(vet[n][0] == "Q"){
                    $("#temposDeCiclo").append("<nav class='Out'><div>%" + vet[n][0] + vet[n][1] + "." + vet[n][2] + "</div><div style='background-color: #aaaaaa;'>23.3s</div><article class='art' id='T" + vet[n] + "'>" + /*texto +*/ /*"</article></nav><br>")
                /*}
                if(vet[n][0] == "S"){
                    $("#temposDeCiclo").append("<nav class='Seg'><div>%" + vet[n][0] + vet[n][1] + "." + vet[n][2] + "</div><div style='background-color: #aaaaaa;'>23.3s</div><article class='art' id='T" + vet[n] + "'>" + /*texto +*/ /*"</article></nav><br>")
                /*}
                var ran = parseInt(Math.random()*100)
                for (let t = 0; t < 100; t++) {
                    if(t < ran){
                        $("#T" + vet[n]).append("<div></div>")
                    }else{
                        $("#T" + vet[n]).append("<div style='background-color: #aaaaaa;'></div>")
                    }
                }
            }
    }*/
    

    
    /*$("select").click(() => {
        if($("#device option:selected").val() == "CPU"){
            if(($("#exibicao option:selected").val() == "tempoDeCiclo") && (estadoAnterior != "CPU tempoDeCiclo")){
                $("#CPU").css('display','none')
                //mostraTempo();
                $('#all').attr('id', 'tutis');
                estadoAnterior = "CPU tempoDeCiclo"
            }
            if(($("#exibicao option:selected").val() == "IDENTIFICACÃO RAPIDA") && (estadoAnterior != "CPU IDENTIFICACÃO RAPIDA")){
                $("#CPU").css('display','flex')

                estadoAnterior = "CPU IDENTIFICACÃO RAPIDA"
            }
        }
        if($("#device option:selected").val() == "REMOTA"){
            
        }
    });*/


    tagNomes()
    //variaveisVazias()
    setInterval(variaveisEstado, 100)
    setInterval(ajaxValues, 100)

    $("#device").change(() => {
        if(($("#device option:selected").val() == "CPU")){
            window.location.replace("file://clfssob/Novtec/5_Estagi%C3%A1rios/Neto/index/interfaceinjecao/injetore.html")
        }
        if(($("#device option:selected").val() == "REMOTA")){
            window.location.replace("file://clfssob/Novtec/5_Estagi%C3%A1rios/Neto/index/interfaceinjecao/remota.html")
        }
        
    
    })

    $("#exibicao").change(() => {
        if(($("#exibicao option:selected").val() == "IDENTIFICACAO_RAPIDA")){
            $(".IDEN").attr('id','IDENTIFICACAO_RAPIDA')
            for(let n = 0; n < 128; n++){
                $(".tempoFinal").remove()
                $("#" + vet[n]).text("")  
            }
        }
        if(($("#exibicao option:selected").val() == "temposDeCiclo")){
            $(".IDEN").attr('id','temposDeCiclo')
            for(let n = 0; n < 128; n++){
                $("#" + vet[n]).parent().append("<div class='tempoFinal'>0.0s</div>")
                $("#" + vet[n]).text("")
                for(let m = 0; m < 100; m++){
                    $("#" + vet[n]).append("<div class='estado'></div>") 
                }
            }
        }
    })


})