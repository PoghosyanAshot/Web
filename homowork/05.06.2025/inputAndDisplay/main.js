let inputField = document.getElementById("myInput");
let outputDiv = document.getElementById("myDiv");

inputField.addEventListener("input", function () {
  outputDiv.textContent = inputField.value;
});
