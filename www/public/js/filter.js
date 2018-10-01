// Show filter options for chosen filter method
// Hide filter options for other filter methods
var company = document.getElementById('company');
var filterCompany = document.getElementById('filterCompany');
company.onclick = () => {
  if(filterCompany.style.display = "none") {
    filterCompany.style.display = "block";
  } else {
    filterCompany.style.display = "none";
  }
}