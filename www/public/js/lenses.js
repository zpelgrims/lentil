var card = document.querySelector('.lenses__card');

card.onclick = () => {
  var expcard = document.getElementById(card.id);
  expcard.style.display = 'block';
}