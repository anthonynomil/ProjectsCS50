function marioMore() {
  var inputHeight = document.getElementById('inputText').value;
  var result = '';
  if (inputHeight > 0 && inputHeight <= 20) {
    for (let i = 1; i <= inputHeight; ++i) {
      result += ' '.repeat(inputHeight - i);
      result += '#'.repeat(i);
      result += ' '.repeat(2);
      result += '#'.repeat(i);
      result += '\n';
    }
    document.getElementById('outputText').textContent = result;
  } else {
    document.getElementById('outputText').textContent =
      'Please choose a height between 0 and 20';
  }
}
