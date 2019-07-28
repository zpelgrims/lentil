var x = document.querySelector('.flash__x');
var flash = document.querySelector('.flash');

if(flash.length > 1) {
  x.onclick = () => {
    flash.style.animation = ".3s slideout forwards";
  }
}