// Show filter options for chosen filter method
// Hide filter options for other filter methods
document.getElementById('company').onclick = () => {
  document.getElementById('filterCompany').style.visibility = "visible";
  document.getElementById('filterYear').style.visibility = "hidden";
  document.getElementById('filterFocal').style.visibility = "hidden";
}
document.getElementById('year').onclick = () => {
  document.getElementById('filterYear').style.visibility = "visible";
  document.getElementById('filterCompany').style.visibility = "hidden";
  document.getElementById('filterFocal').style.visibility = "hidden";
}
document.getElementById('focal').onclick = () => {
  document.getElementById('filterFocal').style.visibility = "visible";
  document.getElementById('filterYear').style.visibility = "hidden";
  document.getElementById('filterCompany').style.visibility = "hidden";
}