int CardToInt (string card) {
	int convert = 0;
	switch (card[0]) {
		case 'C': break;
		case 'D': convert += 13; break;
		case 'H': convert += 26; break;
		case 'S': convert += 39; break;
	}
	
	switch (card[1]) {
		case 'T': convert += 8; break;
		case 'J': convert += 9; break;
		case 'Q': convert += 10; break;
		case 'K': convert += 11; break;
		case 'A': convert += 12; break;
		default: convert += card[1]-50; break;
	}

	return convert;
}

string IntToCard (int input) {
	char suit, num;
	switch (input/13) {
		case 0: suit = 'C'; break;
		case 1: suit = 'D'; break;
		case 2: suit = 'H'; break;
		case 3: suit = 'S'; break;
	}
	switch (input%13) {
		case 8: num = 'T'; break;
		case 9: num = 'J'; break;
		case 10: num = 'Q'; break;
		case 11: num = 'K'; break;
		case 12: num = 'A'; break;
		default: num = (input%13) + 50; break;
		
	}
	char convert[3] = {suit, num, '\0'};
	return string(convert);
}