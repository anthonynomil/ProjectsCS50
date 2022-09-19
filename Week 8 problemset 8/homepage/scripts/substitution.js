function convertText(text, cipher) {
  if ((text >= 'A' && text <= 'Z') || (text >= 'a' && text <= 'z')) {
    if (text === text.toUpperCase()) {
      return cipher[text.charCodeAt(0) - 65];
    }
    if (text === text.toLowerCase()) {
      return cipher[text.charCodeAt(0) - 97].toLowerCase();
    }
  } else {
    return text;
  }
}

function substitution() {
  var text = document.getElementById('inputText').value;
  var cipher = document.getElementById('inputCipher').value;
  var text_len = text.length;
  const dummy = [];

  for (let i = 0; i < text_len; ++i) {
    console.log(text[i]);
    if ((text >= 'A' && text <= 'Z') || (text >= 'a' && text <= 'z')) {
      dummy[i] = convertText(text[i], cipher);
    } else {
      dummy[i] = text[i];
    }
  }
  document.getElementById('outputText').textContent = dummy.join('');
}
