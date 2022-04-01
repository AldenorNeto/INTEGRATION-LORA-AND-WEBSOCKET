const baseUrl = 'https://pokeapi.co/api/v2/pokemon/',	// API endpoint 
    container = document.querySelector('.pokemon'),	// Get Element pokemon 
    span = document.querySelector('span'),
    mostraIndex = index => span.innerHTML=index-20+1+' - '+index;

var pokemon, armazena = '',Armazena,vinte=20,pokemonId=0; // Responsavel por guardar os dados recebidos da API

function requestPokeInfo(url, name){ // Função responsavel por fazer requisições para a API e inserir as respostas na variavel pokemon
    fetch(url + name)
        .then(response => response.json())
        .then(data => {
            pokemonId = data.id
            pokemon = data
            if(pokemonId <= vinte)startApp(pokemonId+1)
            else container.innerHTML = armazena;
    })
    .catch(err => console.log(err));
}

function createCard () { // Função responsavel por montar o HTML exibido na pagina
    card = `
    <div class="cardPoke">
        <div class="pokemon-picture">
            <img src="${pokemon.sprites.front_default}" alt="Sprite of ${pokemon.name}">
        </div>
        <div class="pokemon-info">
            <p><b>Name:</b> ${pokemon.name}</p>
            <p><b>Type:</b> ${pokemon.types.map(item => item.type.name).toString()}</p>
            <p><b>Number:</b> ${pokemonId}</p>
        </div>
    </div>`;
    return card;
}

let startApp = pokeName => { // Função que faz a chamada das principais funções e inicia o app
    requestPokeInfo(baseUrl, pokeName);
    Armazena = createCard();
    armazena += Armazena;
}

if(!pokemonId)startApp(1);

function verMais(){
    startApp(vinte+1)
    vinte += 20
    armazena = '';
    mostraIndex(vinte);
}

function verMenos(){
    if(vinte > 21){
        startApp(vinte-40+1)
        vinte -= 20
        armazena = '';
        mostraIndex(vinte);
    }
}
