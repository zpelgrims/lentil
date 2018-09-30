// Show filter options for chosen filter method
// Hide filter options for other filter methods
document.getElementById('company').onclick = () => {
  document.getElementById('filterCompany').style.display = "block";
  document.getElementById('filterFilter').style.display = "none";
}
document.getElementById('filter').onclick = () => {
  document.getElementById('filterFilter').style.display = "block";
  document.getElementById('filterCompany').style.display = "none";
}