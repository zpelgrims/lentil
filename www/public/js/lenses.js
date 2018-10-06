document.querySelectorAll('.lense__card').forEach((card) => {
  var id = card.id.substring(card.id.indexOf('-') + 1);
  card.onclick = () => {
    if(card.classList.contains('activelens')) {
      card.classList.remove('activelens');
      document.querySelector('#expcard-' + id).style.display = "none";
    } else {
      card.classList.add('activelens');
      document.querySelector('#expcard-' + id).style.display = "block";
    }
  };
});