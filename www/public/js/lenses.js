document.querySelectorAll('.lense__card').forEach((card) => {
  var id = card.id.substring(card.id.indexOf('-') + 1);
  card.onclick = () => {
    if(card.classList.contains('activelens')) {
      card.classList.remove('activelens');
      document.querySelector('#expcard-' + id).style.display = "none";
      document.querySelector('#expcard-' + id).parentElement.style.height = "0";
      document.querySelector('#expcard-' + id).parentElement.style.margin = "0";
    } else {
      document.querySelectorAll('div').forEach((div) => {
        div.classList.remove('activelens');
      });
      document.querySelectorAll('.exp-lense__card').forEach((expcard) => {
        expcard.style.display = "none";
        expcard.parentElement.style.height = "0";
        expcard.parentElement.style.margin = "0";
      });
      card.classList.add('activelens');
      document.querySelector('#expcard-' + id).style.display = "block";
      document.querySelector('#expcard-' + id).style.animation = ".5s fadein forwards";
      document.querySelector('#expcard-' + id).parentElement.style.height = "34.7rem";
      document.querySelector('#expcard-' + id).parentElement.style.margin = "0 0 5rem 0";
    }
  };
});