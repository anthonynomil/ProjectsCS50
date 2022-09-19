function cash() {
  // Start by initializing every variable we'll need
  var pennies = 0;
  var nickels = 0;
  var dimes = 0;
  var quarters = 0;
  var total_coins = 0;
  var total_amount = document.getElementById('inputText').value;

  // All of this remove the amount each coins is worth and
  // add to the counter of the type of coin and the total amount of coins
  while (total_amount >= 25) {
    total_amount -= 25;
    ++quarters, ++total_coins;
  }
  while (total_amount >= 10) {
    total_amount -= 10;
    ++dimes, ++total_coins;
  }
  while (total_amount >= 5) {
    total_amount -= 5;
    ++nickels, ++total_coins;
  }
  while (total_amount >= 1) {
    total_amount -= 1;
    ++pennies, ++total_coins;
  }

  // Send the values to the p tag where the id is 'outputText'
  document.getElementById('outputText').textContent =
    'Total amount of coins: ' +
    total_coins +
    '\n' +
    'Number of quarters: ' +
    quarters +
    '\n' +
    'Number of dimes: ' +
    dimes +
    '\n' +
    'Number of nickels: ' +
    nickels +
    '\n' +
    'Number of pennies: ' +
    pennies +
    '\n';
}
