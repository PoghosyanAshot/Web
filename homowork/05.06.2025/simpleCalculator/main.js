let firstOperand = "";
let secondOperand = "";
let operator = "";
let finish = false;
const digits = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "."];
const operators = ["+", "-", "X", "/"];

const out = document.querySelector(".calc-screen p");

function clearAll() {
  firstOperand = "";
  secondOperand = "";
  operator = "";
  finish = false;
  out.textContent = 0;
}

document.querySelector(".buttons").onclick = (event) => {
  if (!event.target.classList.contains("btn")) return;

  const key = event.target.textContent;

  if (key === "ac") {
    clearAll();
    return;
  }

  out.textContent = "";

  if (digits.includes(key)) {
    if (secondOperand === "" && operator === "") {
      firstOperand += key;
      out.textContent = firstOperand;
    } else if (firstOperand !== "" && operator !== "" && finish) {
      secondOperand = key;
      finish = false;
      out.textContent = secondOperand;
    } else {
      secondOperand += key;
      out.textContent = secondOperand;
    }

    return;
  }

  if (operators.includes(key)) {
    operator = key;
    out.textContent = operator;
    return;
  }

  if (key === "=") {
    if (secondOperand === "") secondOperand = firstOperand;

    switch (operator) {
      case "+":
        firstOperand = (+firstOperand + +secondOperand).toString();
        break;

      case "-":
        firstOperand = (+firstOperand - +secondOperand).toString();
        break;

      case "X":
        firstOperand = (+firstOperand * +secondOperand).toString();
        break;

      case "/":
        if (secondOperand === "0") {
          out.textContent = "ERROR";
          return;
        }

        firstOperand = (+firstOperand / +secondOperand).toString();
        break;
    }

    finish = true;
    out.textContent = firstOperand;
  }

  if (key === "+/-") {
    if (secondOperand === "" && operator === "") {
      firstOperand = (-parseFloat(firstOperand)).toString();
      out.textContent = firstOperand;
    } else if (secondOperand !== "" && !finish) {
      secondOperand = (-parseFloat(secondOperand)).toString();
      out.textContent = secondOperand;
    }

    return;
  }

  if (key === "%") {
    if (secondOperand === "" && operator === "") {
      firstOperand = (parseFloat(firstOperand) / 100).toString();
      out.textContent = firstOperand;
    }

    if (secondOperand !== "" && !finish) {
      secondOperand = (parseFloat(secondOperand) / 100).toString();
      out.textContent = secondOperand;
    }

    return;
  }
};
