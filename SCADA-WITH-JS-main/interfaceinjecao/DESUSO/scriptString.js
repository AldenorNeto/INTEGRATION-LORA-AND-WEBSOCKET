$(document).ready(() => {
    
    const ajaxValues = () => {
        $.get("http://localhost:8080/messages.json",function(data){
            
            var laco = data.split('')
            var filtro = ["'"]
            
            var arrayFiltrado = laco.filter( elemento => !filtro.includes(elemento));
            laco = arrayFiltrado
            
            laco = laco.join('')
            laco = laco.split(' ')
            filtro = [""]
            arrayFiltrado = laco.filter( elemento => !filtro.includes(elemento));
           
            momento[3] = [parseInt(arrayFiltrado[0]).toString(2),parseInt(arrayFiltrado[1]).toString(2),parseInt(arrayFiltrado[2]).toString(2),parseInt(arrayFiltrado[3]).toString(2)]
            momento[2] = [parseInt(arrayFiltrado[4]).toString(2),parseInt(arrayFiltrado[5]).toString(2),parseInt(arrayFiltrado[6]).toString(2),parseInt(arrayFiltrado[7]).toString(2)]
            momento[1] = [parseInt(arrayFiltrado[8]).toString(2),parseInt(arrayFiltrado[9]).toString(2),parseInt(arrayFiltrado[10]).toString(2),parseInt(arrayFiltrado[11]).toString(2)]
            momento[0] = [parseInt(arrayFiltrado[12]).toString(2),parseInt(arrayFiltrado[13]).toString(2),parseInt(arrayFiltrado[14]).toString(2),parseInt(arrayFiltrado[15]).toString(2)]

            for (var i = 0; i < 4; i++) {
                for (var j = 0; j < 4; j++) {
                    momento[i][j] = (momento[i][j]).split('');
                    var x = 0
                    while(x < momento[i][j].length){
                        momento[i][j][x] = parseInt(momento[i][j][x])
                        

                        x++;
                    }
                    while(momento[i][j].length < 32){
                        momento[i][j].unshift(0);
                    }
                    momento[i][j].reverse()
                    
                }
            }
        });
    }
    

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



    var vet = []
    var tag
    for(let n = 0; n < 200; n++){
        let texto = $(".tag:eq(" + n +")").next().text()
                if(texto){
                    tag = ($(".tag:eq(" + n +")").next().next().attr("id")) 
                    vet.push(tag)
                }
    }  



    $("#device").click(() => {
        var seletor = $("#device option:selected").val()
        if(seletor == "REMOTA"){
            $("#CPU *").css('display','none')
            $("#REMOTA *").css('display','flex')
        }
        if(seletor == "CPU"){
            $("#CPU *").css('display','flex')
            $("#REMOTA *").css('display','none')
        }
    })



    var momento = []
    var passMomento = []
    var i = 3
    var com
    var com0
    var tec

    var atribui = () => {
        /*if(tec){
            i--
        }
        if(i < 0){
            i = 3
            tec = 0
        }*/
        i = 3
        var conc0 = momento[i][0]
        var conc1 = momento[i][1]
        var conc2 = momento[i][2]
        var conc3 = momento[i][3]

        com = conc0.concat(conc1,conc2,conc3);

        /*if(i == 3){
            com0 = com
        }

        for(let n = 0; n < 128; n++){
            if(com0[n] != passMomento[n]){
                tec = 1
                i = 3
            }
        }
        
        passMomento = com0*/
        
        console.log(i)
        for(let n = 0; n < 128; n++){
            if(com[n]){
                
                $("#" + vet[n]).css('background-color','#00ff00')
            }else{
                
                $("#" + vet[n]).css('background-color','#dbdbdb')
            }   
        }
    }


    var vetor = []
    for(let n = 0; n < 128; n++){
        vetor.push(0)
    }

    setInterval(() => {
        for(let n = 0; n < 128; n++){
            if(com[n]){
               vetor[n]++
            }
            if(com[0]){
                vetor[n]=0
            }
        }
        for(let n = 0; n < 128; n++){
            var dezena = vetor[n] / 10
            var unidade =   vetor[n] - (parseInt( dezena)*10)
            $("#" + vet[n]).text(parseInt( dezena) + "." +  unidade + "s")
        }
    },100)
        


    setInterval(atribui,140)
    setInterval(ajaxValues,10)


})