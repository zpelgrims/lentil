const navMenu = document.querySelector('.nav__menu');
const navDrawer = document.querySelector('.nav__drawer');
const navClose = document.querySelector('.nav__close-area');

navClose.addEventListener('click', () => {
  toggleNav();
});

navMenu.addEventListener('click', () => {
  toggleNav();
});

function toggleNav() {
  navMenu.classList.toggle('nav__menu--active');
  navDrawer.classList.toggle('nav__drawer--active');
}