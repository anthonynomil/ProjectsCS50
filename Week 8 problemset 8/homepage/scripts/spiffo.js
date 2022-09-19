function spiffo(nb) {
  if (nb == 1) {
    document.querySelector('#spiffopic').src = 'images/SpiffoTeach.png';
    document
      .querySelector('#spiffobtn1')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn2')
      .classList.replace('d-none', 'd-block');
    document
      .querySelector('#spiffobtn3')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn4')
      .classList.replace('d-none', 'd-block');
  } else if (nb == 2) {
    document.querySelector('#spiffopic').src = 'images/SpiffoHappy.png';
    document
      .querySelector('#spiffobtn1')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn2')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn3')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn4')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn5')
      .classList.replace('d-none', 'd-block');
    setTimeout(() => {
      window.location.replace('index.html');
    }, 2000);
  } else if (nb == 3) {
    document.querySelector('#spiffopic').src = 'images/SpiffoCaid.png';
    document
      .querySelector('#spiffobtn4')
      .classList.replace('d-block', 'd-none');
    document
      .querySelector('#spiffobtn2')
      .classList.replace('d-block', 'd-none');
    window.location.replace('https://www.youtube.com/watch?v=FaJJP_7jbxs');
    setTimeout(() => {
      window.location.replace('index.html');
    }, 1000);
  } else if (nb == 4) {
    setTimeout(() => {
      window.location.replace('index.html');
    }, 1000);
  } else if (nb == 0) {
    document.querySelector('#spiffopic').src = 'images/SpiffoPermission.png';
  }
}
