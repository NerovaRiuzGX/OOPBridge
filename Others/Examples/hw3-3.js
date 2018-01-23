
//Create a Poker Deck
var Deck = new Array(0);
for (i=0; i<4; i++){
	var color = '';
	switch (i) {
		case 0: color = 'S'; break;
		case 1: color = 'H'; break;
		case 2: color = 'D'; break;
		case 3: color = 'C'; break;
	}
	for (j=1; j<=13; j++){
		switch(j) {
			case 10: Deck.push(color + 'X'); break;
			case 11: Deck.push(color + 'J'); break;
			case 12: Deck.push(color + 'Q'); break;
			case 13: Deck.push(color + 'K'); break;
			default: Deck.push(color + j); break;
		}
	}
}

//Make a Mirror Deck
var Deck_Shuffled = new Array(0);

//Random function
var rand = function (a, b) {
	return Math.floor(Math.random() * (b-a+1) + a);
}

//Shuffle
var Shuffle = function () {
	for (i=51; i>=0; i--) {
		var number = rand (0, i);
		Deck_Shuffled.push(Deck[number]);
		Deck.splice(number, 1); 
	}
}

Shuffle();

//output
var tostring = "";
for(i = 0; i < Deck_Shuffled.length; i++) {
    tostring += Deck_Shuffled[i] + ", ";
    if ((i+1) % 13 == 0) {
        tostring += "\n";
    }
}
console.log(tostring);
//console.log(Deck_Shuffled.toString());
