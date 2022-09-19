function credit() {
  // Create all the variables we're going to need
  card_number_input = document.getElementById('inputText').value;
  card_number_input = card_number_input.replace(/-/g, '');
  card_number_len = card_number_input.length;
  const card_dummy = [];
  card_luhn = 0;
  card_valid = false;

  // Transfer the credit card numbers to the empty array
  for (let i = 0; i < card_number_len; ++i) {
    card_dummy[i] = parseInt(card_number_input[i]);
    console.log(card_dummy[i]);
  }

  // Check every odd number and multiply it by 2 as per luhn algorithm
  for (let i = card_number_len - 2; i >= 0; i -= 2) {
    if (i < 0) {
      break;
    }
    card_dummy[i] *= 2;
    if (card_dummy[i] > 9) {
      card_dummy[i] -= 9;
    }
  }
  console.log(card_dummy);

  // Add every number in the card and check if the rest is 0 when we divide it by 10
  card_dummy_len = card_dummy.length;
  for (let i = 0; i < card_dummy_len; ++i) {
    card_luhn += parseInt(card_dummy[i]);
  }
  if (card_luhn % 10 == 0) {
    card_valid = true;
  }
  console.log(card_luhn);

  // Check the type of card and whether it's valid or not
  if (card_number_len == 15 && card_valid == true) {
    document.getElementById('outputText').textContent =
      'Card type: American Express' + '\n' + 'Card: Valid';
  } else if (
    card_number_len == 16 &&
    card_valid == true &&
    card_number_input[0] == 2
  ) {
    document.getElementById('outputText').textContent =
      'Card type: Mastercard' + '\n' + 'Card: Valid';
  } else if (
    (card_number_len == 13 || card_number_len == 16) &&
    card_number_input[0] == 4 &&
    card_valid == true
  ) {
    document.getElementById('outputText').textContent =
      'Card type: VISA' + '\n' + 'Card: Valid';
  } else if (card_valid == true) {
    document.getElementById('outputText').textContent =
      'Card type: Unknown' + '\n' + 'Card: Valid';
  } else {
    document.getElementById('outputText').textContent =
      'This card is not valid';
  }
}
