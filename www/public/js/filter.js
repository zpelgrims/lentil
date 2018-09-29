// Show filter options for chosen filter method
// Hide filter options for other filter methods
document.getElementById('company').onclick = () => {
  document.getElementById('filterCompany').style.visibility = "visible";
  document.getElementById('filterFilter').style.visibility = "hidden";
}
document.getElementById('filter').onclick = () => {
  document.getElementById('filterFilter').style.visibility = "visible";
  document.getElementById('filterCompany').style.visibility = "hidden";
}