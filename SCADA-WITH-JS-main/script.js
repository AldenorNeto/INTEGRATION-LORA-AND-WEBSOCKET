setTimeout(() => {
    const ajaxValues = link => {
        //$.get("http://10.2.65.129/awp/index.html", data => {
            let arrayArmazenaEmBool = [data][0].split(' ').reduce((acumulado, indice) => acumulado.concat(parseInt(indice).toString(2)),[]) //['1010100110101', '110100010', '101011110010', '10110']
            arrayArmazenaEmBool = arrayArmazenaEmBool.map((value) => value.padStart(32,0)).map((value) => value = Array.from(value,Math.abs).reverse()) 
            return arrayArmazenaEmBool.reduce((total, indice) => total.concat(indice), [])
        //})
        //return *****
    }

    let todosIDs = []
    let todosWrd = []
    const _todosIDs = id => "#" + todosIDs[id]
    const _todosWrd = id => "#" + todosWrd[id]
    
    const invalidaVariveisVazias = valorClass => {
        let array = []
        const _valorClassEQ = id => $("."+valorClass+":eq("+ id +")")
        const ElementoDaClass = $("."+valorClass)
        for(let n in ElementoDaClass){
            if(_valorClassEQ(n).next().text()) array.push(_valorClassEQ(n).next().next().attr("id"))
            else adicionaClasseAosCartoes(_valorClassEQ(n),'class')
        }
        return array
    }

    const adicionaClasseAosCartoes = (address,classe) => address.parent().removeClass().addClass(classe) 

    const backgroundcolor = (address,cor) => $(address).css('background-color',cor)

    const somaMaisUmSeVariavelDentro = (arrayDeReferencia) => {
        for(let n in todosIDs){if(arrayDeReferencia[n])tempoEmON[n]++}
    }

    const pintaIdentificacaoRapida = (VariveisQueSeramPintadas,tempoEmON) => {
        for(let n in todosIDs){
            VariveisQueSeramPintadas[n] ? backgroundcolor(_todosIDs(n),'#00ff00') : backgroundcolor(_todosIDs(n),'#dbdbdb')
            mostraTempo($(_todosIDs(n)),tempoEmON[n])
        }
    }
    
    const trocaAsBarrasAoTrocarOCartao = () => {
        tamanhoCartao = identificaCartao($(".lupa:checked").val())
        for(let n = tamanhoCartao.min; n < tamanhoCartao.max; n++){
            $(_todosIDs(n) + " div").remove()
        }
        return tamanhoCartao
    }
    
    const preencheBarraTemposDeCiclo = (tamanhoCartao,veriaveisEmTrueAtualmente) => {
        for(let n = tamanhoCartao.min; n < tamanhoCartao.max; n++){
            $(_todosIDs(n)).append("<div class='estado'></div>");
            veriaveisEmTrueAtualmente[n] ? backgroundcolor(_todosIDs(n) + " div:last-child",'#00ff00') : backgroundcolor(_todosIDs(n) + " div:last-child",'#dbdbdb')
            if($(_todosIDs(n)).children().length >= 300){
                $(_todosIDs(n) + " div:eq(0)").remove();
            }
        }
    }
    
    const pintaAnalogicasTemposDeCiclo = () => {
        for(let n in entradaAnalogica){
            entradaAnalogica[n] = Math.abs(entradaAnalogica[n] + parseInt((Math.random() - 0.5)*10))
            entradaAnalogica[n] > 190 ? entradaAnalogica[n] = 190 : entradaAnalogica[n] * 1
            $(_todosWrd(n) + " .tamanho").css('height',entradaAnalogica[n])
        }
    }

    const identificaCartao = (cart = "c2") => {
        let  min, max
        const endCartao = (cartao,mi,ma) => {if(cart == cartao) {min=mi, max=ma}}
        endCartao("c2",0,14);
        endCartao("c3",14,30);
        endCartao("c4",30,37);
        endCartao("c5",37,43);
        endCartao("c6",43,51);
        endCartao("c7",51,67);
        return {min, max}
    }

    const mostraTempo = (local,IO) => {
        local.text((IO /100).toFixed(1) + " s") 
    }

    const mudaDePagDevice = () => {
        const addressToDevice = "http://10.2.65.150/awp/"
        let linkCompleto
        $("#device option:selected").val() == "CPU" ? linkCompleto = addressToDevice + "index.html" : linkCompleto = addressToDevice + "index2.html";
        return linkCompleto
    }

    class objGravaBorda {
        constructor(bool, id) {
            this.bool = bool
            this.id = id.substring(0, id.length - 1) + '.' + id[id.length - 1]
        }
    }

    const arrayGravaBordaCicloCompleto = {array: []}

    const gravaBorda = (armazenaBorda, IO) => {
        if (armazenaBorda == undefined) armazenaBorda = IO
        let arrayApagar = []

        if(todosIDs.length > 0)for(let n in armazenaBorda){
            if(armazenaBorda[n] != IO[n] && todosIDs[n][0] == "I") arrayApagar.push(new objGravaBorda(IO[n],todosIDs[n]))
        }
        if(arrayApagar.length > 0){
            arrayGravaBordaCicloCompleto.array.push(arrayApagar)
        }
        return IO
    }

    const preencheBordaGrid = array => {
        $("#ordemDasVariaveis > *").remove()
        for(let n in array){
            for(let m in array[n]){
                let bool
                array[n][m].bool ? bool = 'subida' :  bool = 'descida'
                $("#ordemDasVariaveis").append('<nav class='+bool+'><i class="ceta"></i>'+array[n][m].id+'</nav>')
            }
        }
        return []
    }


    const MainIdentificacaoRapida = () => {

        let entradasESaidasConcatenadas
        let bordaEntradasESaidas
        let armazenaBorda

        tempoEmON = Array(todosIDs.length).fill(0)

        $(".tempoFinal").remove()
        $(".IDEN").attr('id','IDENTIFICACAO_RAPIDA')

        todosIDs = invalidaVariveisVazias("tag")
        todosWrd = invalidaVariveisVazias("wrd")

        let loop = () => {
            entradasESaidasConcatenadas = ajaxValues(mudaDePagDevice())
            bordaEntradasESaidas = gravaBorda(bordaEntradasESaidas,entradasESaidasConcatenadas)
            somaMaisUmSeVariavelDentro(entradasESaidasConcatenadas)
            if(entradasESaidasConcatenadas[1] && !armazenaBorda){
                tempoEmON = Array(todosIDs.length).fill(0)
                arrayGravaBordaCicloCompleto.array = preencheBordaGrid(arrayGravaBordaCicloCompleto.array)
            }
            armazenaBorda = entradasESaidasConcatenadas[1]
            pintaIdentificacaoRapida(entradasESaidasConcatenadas,tempoEmON)
        }
        clearInterval(cleanLoop)
        cleanLoop = setInterval(loop)
        
        $("#device").change(() => link = mudaDePagDevice())
    }

    const MainTemposDeCiclo = () => {

        let entradasESaidasConcatenadas
        $(".IDEN").attr('id','temposDeCiclo')
        todosIDs = invalidaVariveisVazias("tag")
        todosWrd = invalidaVariveisVazias("wrd")

        for(let n in todosIDs){
            $(_todosIDs(n)).parent().append("<div class='tempoFinal'>0.0s</div>")
            $(_todosIDs(n)).text("")
            backgroundcolor(_todosIDs(n),'#e2e2e2')
        }
        let tamanhoCartao = identificaCartao($(".lupa:checked").val())
        $(".lupa").change(() => tamanhoCartao = trocaAsBarrasAoTrocarOCartao())

        let armazenaBorda
        let loop = () => { 
            entradasESaidasConcatenadas = ajaxValues(mudaDePagDevice())
            preencheBarraTemposDeCiclo(tamanhoCartao,entradasESaidasConcatenadas)
            somaMaisUmSeVariavelDentro(entradasESaidasConcatenadas)
            if(entradasESaidasConcatenadas[1] && !armazenaBorda){for(let n in todosIDs){mostraTempo($(_todosIDs(n)).parent().find(".tempoFinal"),tempoEmON[n])}tempoEmON = Array(todosIDs.length).fill(0)}
            armazenaBorda = entradasESaidasConcatenadas[1]  // ATUALIZA CONTADOR 
            pintaAnalogicasTemposDeCiclo()
        }
        clearInterval(cleanLoop)
        cleanLoop = setInterval(loop)

        $("#device").change(() => link = mudaDePagDevice())
    }

    $("#exibicao").change(() => selecionaValor("#exibicao","IDENTIFICACAO_RAPIDA") ? MainIdentificacaoRapida() : MainTemposDeCiclo())

    const selecionaValor = (nome,valor) => $(nome+" option:selected").val() == valor
    let cleanLoop
    let tempoEmON
    mudaDePagDevice()
    MainIdentificacaoRapida()
})