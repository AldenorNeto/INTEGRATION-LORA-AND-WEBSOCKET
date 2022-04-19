$(document).ready(() => {
    var fruta = ['4', '2', '2', '7', '9', '0', '6', '2', '5', '8']
    var entradaAnalogica = [55,77,99,33,11]
    const ajaxValues = link => {
        
        //$.get(link, function(data){
            var data = "4227906258 3147649 433684552 2139226109"
            var arr = data.split();          //['xxxxxxxxxxx xxxxxxxx xxxxxxxxxx xxxxx']
            arr = arr[0].split(' ');          //['xxxxxxxxxxx', 'xxxxxxxx', 'xxxxxxxxxx', 'xxxxx']

                

                fruta[parseInt(Math.random()*10)] = parseInt(Math.random()*10) + ''
                arr[0] = fruta.join('')
                arr[1] = fruta.join('')
                arr[2] = fruta.join('')
                arr[3] = fruta.join('')



            var quantidadeUDInt = arr.length        //4 ou 6
            var arrayArmazenaEmBool = []
            for(let n = 0; n < quantidadeUDInt; n++){
                arrayArmazenaEmBool.push(parseInt(arr[n]).toString(2))        //['1010100110101', '110100010', '101011110010', '10110']
            }

            for (var UDInt10dig = 0; UDInt10dig < quantidadeUDInt; UDInt10dig++) {
                arrayArmazenaEmBool[UDInt10dig] = (arrayArmazenaEmBool[UDInt10dig]).split('');     //[['1','0','1','0','1','0','0','1','1'...
                for (var x = 0; x < arrayArmazenaEmBool[UDInt10dig].length; x++) {
                    arrayArmazenaEmBool[UDInt10dig][x] = parseInt(arrayArmazenaEmBool[UDInt10dig][x])      //[[1,0,1,0,1,0,0,1,1,0,1,0,1], ...
                }
                while(arrayArmazenaEmBool[UDInt10dig].length < 32){
                    arrayArmazenaEmBool[UDInt10dig].unshift(0);          //[[0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,1], [0,0,0,0,1,1,0,1,0,1...
                }
                arrayArmazenaEmBool[UDInt10dig].reverse()          //[[1,0,1,1,0,0,1,0,1,0,1,0,0,0,0,0], [1,0,1,1,0,1...
            }

            var i = 0
            for(let n = 0; n < quantidadeUDInt; n++){
                for (let cont = 0; cont < 32; cont++) {
                    entradasESaidasConcatenadas[i] = arrayArmazenaEmBool[n][[cont]]         //[1,0,1,1,0,0,1,0,1,0,1,0,0,0,0,0,1...
                    i++
                }
            }
        //})
        
    }

    var todosIDs = []
    var todosWrd = []

    /*var tagNomes = () => {
        var tag
        var wrd
        let texto
        for(let n = 0; n < 20; n++){
            texto = $(".wrd:eq(" + n +")").next().text()
            if(texto){
                tag = ($(".wrd:eq(" + n +")").next().next().attr("id")) 
                todosIDs.push(wrd)
            }
            else{
                $(".wrd:eq(" + n +")").parent().removeClass().addClass('class')
            }
        }
        for(let n = 0; n < 500; n++){
            texto = $(".tag:eq(" + n +")").next().text()
            if(texto){
                tag = ($(".tag:eq(" + n +")").next().next().attr("id")) 
                todosIDs.push(tag)
            }
            else{
                $(".tag:eq(" + n +")").parent().removeClass().addClass('class')
            }
        }
    }

    tagNomes();*/

    
    
    var invalidaVariveisVazias = valorClass => {
        let tag
        let wrd
        let texto
        var _valorClassEQ = id => $("."+valorClass+":eq(" + id +")")
        var numerosDeElementoDaClass = $("."+valorClass).length
        for(let n = 0; n < numerosDeElementoDaClass; n++){
            texto = _valorClassEQ(n).next().text()
            if(texto){
                if(valorClass == "tag"){
                    tag = _valorClassEQ(n).next().next().attr("id")
                    todosIDs.push(tag)
                }
                if(valorClass == "wrd"){
                    wrd = _valorClassEQ(n).next().next().attr("id")
                    todosWrd.push(wrd)
                }
            }
            else{
                _valorClassEQ(n).parent().removeClass().addClass('class')
            }
        } 
    }
    invalidaVariveisVazias("tag")
    invalidaVariveisVazias("wrd")
    


    var _todosIDs = id => "#" + todosIDs[id]
    var _todosWrd = id => "#" + todosWrd[id]
    console.log(todosIDs);
    console.log(todosWrd);


    var quantidadesDeIO = todosIDs.length      //127 ou 200

    var entradasESaidasConcatenadas = []
    var tempoEmON = []

    for(let n = 0; n < quantidadesDeIO; n++){
        tempoEmON.push(0)
        entradasESaidasConcatenadas.push(0)
    }


    var SensCilGiraMesaAvancado
    var cartaoMin = 0
    var cartaoMax = 14


    var variaveisEstado = () => {

        for(let n = 0; n < quantidadesDeIO; n++){
            if(entradasESaidasConcatenadas[n]){
                tempoEmON[n]++
            }  
        }

        if(moduloDeMonutoramento == "IDENTIFICACAO_RAPIDA"){
            for(let n = 0; n < quantidadesDeIO; n++){
                if(entradasESaidasConcatenadas[n]){
                    $(_todosIDs(n)).css('background-color','#00ff00')
                }else{  
                    $(_todosIDs(n)).css('background-color','#dbdbdb')
                } 
                mostraTempo($(_todosIDs(n)),n)
            }
        }


        if(moduloDeMonutoramento == "temposDeCiclo"){ // PREENCHE A BARRA DE TRACE DA VARIAVEL n

            $("input[type='radio']").change(() => {
                identificaCartao($("input[type='radio']:checked").val())
                for(let n = cartaoMin; n < cartaoMax; n++){
                    $(_todosIDs(n) + " div").remove()
                }
            })

            for(let n = cartaoMin; n < cartaoMax; n++){
                $(_todosIDs(n)).append("<div class='estado'></div>");
                    if(entradasESaidasConcatenadas[n]){
                        $(_todosIDs(n) + " div:last-child").css('background-color','#00ff00');
                    }
                    else{
                        $(_todosIDs(n) + " div:last-child").css('background-color','#e2e2e2');
                    }
                if($(_todosIDs(n)).children().length >= 300){
                    $(_todosIDs(n) + " div:eq(0)").remove();
                }
            }
console.log("hhhhh");

            $(".tamanho").css('height',parseInt(Math.random()*250)+'px')


        }


        
        if((SensCilGiraMesaAvancado == 0) && (entradasESaidasConcatenadas[1] == 1)){ // ATUALIZA CONTADOR DE VARIAVEL DENTRO A CADA CICLO
            for(let n = 0; n < quantidadesDeIO ; n++){
                if(moduloDeMonutoramento == "temposDeCiclo"){
                    mostraTempo($(_todosIDs(n)).parent().find(".tempoFinal"),n)  // ATUALIZA CONTADOR EM TEMPOS DE CICLO QUANDO O CICLO ACABA
                }
                tempoEmON[n] = 0
            }
        }
        SensCilGiraMesaAvancado = entradasESaidasConcatenadas[1]
    }

    var i = 0

    setInterval(variaveisEstado);

    var cpuSelecionado = 0

    if(cpuSelecionado){
        setInterval(() => ajaxValues("http://10.2.65.150/awp/index.html"), 1100)
    }else{
        setInterval(() => ajaxValues("http://10.2.65.150/awp/index.html"), 1100)
    }
    $("#device").change(() => {
        if(($("#device option:selected").val() == "CPU")){
            window.location.replace("http://10.2.65.150/awp/injetore.html")
            cpuSelecionado = 0
        }
        if(($("#device option:selected").val() == "REMOTA")){
            window.location.replace("http://10.2.65.150/awp/remota.html")
            cpuSelecionado = 1
        }
    })


    var moduloDeMonutoramento = "IDENTIFICACAO_RAPIDA"

    $("#exibicao").change(() => {

        if(($("#exibicao option:selected").val() == "IDENTIFICACAO_RAPIDA")){
            $(".IDEN").attr('id','IDENTIFICACAO_RAPIDA')
            moduloDeMonutoramento = "IDENTIFICACAO_RAPIDA"
            for(let n = 0; n < quantidadesDeIO; n++){
                $(".tempoFinal").remove()
                $(_todosIDs(n)).text("")  
            }
        }

        if(($("#exibicao option:selected").val() == "temposDeCiclo")){
            $(".IDEN").attr('id','temposDeCiclo')
            moduloDeMonutoramento = "temposDeCiclo"
            for(let n = 0; n < quantidadesDeIO; n++){
                $(_todosIDs(n)).parent().append("<div class='tempoFinal'>0.0s</div>")
                $(_todosIDs(n)).text("")
                $(_todosIDs(n)).css('background-color','#e2e2e2')
            }

        }

    })


    var identificaCartao = cart => {
        cart == "c2" ? (cartaoMin = 0, cartaoMax = 14) : cart == "c3" ? (cartaoMin = 14, cartaoMax = 30) : cart == "c4" ? (cartaoMin = 30, cartaoMax = 37) : cart == "c5"
        cart == "c5" ? (cartaoMin = 37, cartaoMax = 43) : cart == "c6" ? (cartaoMin = 43, cartaoMax = 51) : cart == "c7" ? (cartaoMin = 51, cartaoMax = 67) : cart == "c8"
        cart == "c8" ? (cartaoMin = 67, cartaoMax = 83) : cart == "c9" ? (cartaoMin = 83, cartaoMax = 99) : cart == "c14" ? (cartaoMin = 100, cartaoMax = 107) : cart == "c15"
        cart == "c15" ? (cartaoMin = 107, cartaoMax = 115) : cart == "c16" ? (cartaoMin = 115, cartaoMax = 119) : cart == "c17" ? (cartaoMin = 119, cartaoMax = 123) : cart == "c18"
        if (cart == "c18") {(cartaoMin = 123, cartaoMax = 127)}

        if(cart == "c10") {(cartaoMin = 0, cartaoMax = 4)}
    }

    var mostraTempo = (local,IO) => {
            var dezena = tempoEmON[IO] /100
            local.text(dezena.toFixed(1) + " s") 
    }



})