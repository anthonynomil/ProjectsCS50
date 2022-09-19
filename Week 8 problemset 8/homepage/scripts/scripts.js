function mario() {
  let inputHeight = document.querySelector('#inputHeight').value;
  let space = ' ';
  let hash = '#';
  var result = '';

  console.log('Input Height:', inputHeight);

  for (let i = 1; i <= inputHeight; ++i) {
    result += space.repeat(inputHeight - i);
    result += hash.repeat(i);
    result += space.repeat(2);
    result += hash.repeat(i);
    result += '\n';
  }
  document.getElementById('outputTextMario').textContent = result;
  console.log(result);
}
