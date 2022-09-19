function readability() {
  // Initialize all the variables we are going to need
  // we start words at 1 to count the last word
  var input_sentence = document.getElementById('inputText').value;
  var sentences = 0;
  var words = 1;
  var letters = 0;
  var input_sentence_len = input_sentence.length;
  var L = 0;
  var S = 0;
  var index = 0;

  for (let i = 0; i < input_sentence_len; ++i) {
    if (
      input_sentence[i] === '.' ||
      input_sentence[i] === '?' ||
      input_sentence[i] === '!'
    ) {
      ++sentences;
    }
    if (input_sentence[i] === ' ') {
      ++words;
    }
    if (
      (input_sentence[i] >= 'A' && input_sentence[i] <= 'Z') ||
      (input_sentence[i] >= 'a' && input_sentence[i] <= 'z')
    ) {
      ++letters;
    }
  }

  L = (letters / words) * 100;
  S = (sentences / words) * 100;
  index = 0.0588 * L - 0.296 * S - 15.8;

  if (index < 1) {
    document.getElementById('outputText').textContent = 'Below Grade 1';
  } else if (index > 16) {
    document.getElementById('outputText').textContent = 'Above Grade 16';
  } else if (index >= 1 && index <= 16) {
    document.getElementById('outputText').textContent =
      'Grade ' + Math.round(index);
  }
}
