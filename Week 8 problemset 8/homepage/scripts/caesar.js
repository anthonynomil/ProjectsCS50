function nextChar(c, cipher) {
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
    if (c === c.toUpperCase()) {
      console.log('c: ' + c);
      return String.fromCharCode(
        ((c.charCodeAt(0) + parseInt(cipher) - 65) % 26) + 65
      );
    }
    if (c === c.toLowerCase()) {
      return String.fromCharCode(
        ((c.charCodeAt(0) + parseInt(cipher) - 97) % 26) + 97
      );
    }
  } else {
    return c;
  }
}

function caesar() {
  var input_text = document.getElementById('inputText').value;
  var input_cipher = document.getElementById('inputCipher').value;
  var input_text_len = input_text.length;
  const text_dummy = [];

  for (let i = 0; i < input_text_len; ++i) {
    console.log('input: ' + input_text);
    text_dummy[i] = nextChar(input_text[i], input_cipher);
  }
  document.getElementById('outputText').textContent = text_dummy.join('');
}
