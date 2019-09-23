const lensCard = document.querySelectorAll('.lense__card');
const expLensCard = document.querySelectorAll('.exp-lense__card');

lensCard.forEach((card) => {
  var id = card.id.substring(card.id.indexOf('-') + 1);
  const expCard = document.querySelector('#expcard-' + id)
  card.onclick = () => {
    if(card.classList.contains('activelens')) {
      card.classList.remove('activelens');
      expCard.style.display = "none";
      expCard.parentElement.style.height = "0";
      expCard.parentElement.style.margin = "0";
    } else {
      lensCard.forEach(card => {
        card.classList.remove('activelens');
      });
      expLensCard.forEach((expcard) => {
        expcard.style.display = "none";
        expcard.parentElement.style.height = "0";
        expcard.parentElement.style.margin = "0";
        expcard.style.transform = "translate(-50%) scale(1)";
      });
      card.classList.add('activelens');
      expCard.style.display = "block";
      expCard.style.animation = ".5s fadein forwards";
      expCard.parentElement.style.height = "30.8rem";
      expCard.parentElement.style.margin = "0 0 5rem 0";
    }
  };
});