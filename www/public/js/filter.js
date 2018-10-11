// Show filter options for chosen filter method
// Hide filter options for other filter methods
var title = document.querySelector('.dropdown__title');
var list = document.querySelector('.dropdown__list');
var filter = document.querySelector('.filter__filter__dropdown');
var all = document.querySelector('#all');
var boxes = document.querySelectorAll('.checkbox');

title.onclick = () => {
  if(list.style.display == "none") {
    list.style.display = "block";
  } else {
    list.style.display = "none";
  }
}

filter.onclick = () => {
  list.style.display = "none";
}

all.onclick = () => {
  if(all.checked == true) {
    boxes.forEach((box) => {
      box.checked = true;
    });
  } else {
    boxes.forEach((box) => {
      box.checked = false;
    });
  }
}