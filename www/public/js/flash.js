var x = document.querySelector('.flash__x');
var flash = document.querySelector('.flash');

x.onclick = () => {
  flash.style.animation = ".3s slideout forwards";
}