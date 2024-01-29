const displayValue = document.querySelector(".outputContent");

document.querySelectorAll(".b").forEach(button => {
    button.addEventListener('click', () => handleButtonClick(button));
});

function handleButtonClick(button) {
    const type = button.getAttribute('data-type');
    const content = button.textContent;

    switch (type) {
        case 'number':
        case 'operator':
        case 'decimal':
            addToOutputBox(content);
            break;
        case 'equal':
            calculateAndDisplayResult();
            break;
        case 'clear':
            clearOutputBox();
            break;
        case 'delete':
            backspaceLastDigit();
            break;
        default:
            console.error("Unknown button type");
    }
}

function adjustFontSize() {
    const outputContent = document.querySelector('.outputContent');
    let fontSize = 30; // Starting font size
    const maxWidth = outputContent.parentElement.offsetWidth;

    outputContent.style.fontSize = fontSize + 'px';

    while (outputContent.scrollWidth > maxWidth && fontSize > 10) {
        fontSize--;
        outputContent.style.fontSize = fontSize + 'px';
    }
}

function addToOutputBox(content) {
    console.log("Add to Ouput Box called");
    displayValue.textContent += content;
    adjustFontSize();
}

function clearOutputBox() {
    console.log("Clear called");
    displayValue.textContent = '';
    adjustFontSize();
}

function backspaceLastDigit() {
    console.log("Backspace called");
    displayValue.textContent = displayValue.textContent.slice(0, -1);
    adjustFontSize();
}

function calculateAndDisplayResult() {
    const currentExpression = displayValue.textContent;
    const operatorRegex = /[\+\-\*\/]/g;
    const operators = currentExpression.match(operatorRegex);


    if (operators && operators.length === 1) {
        console.log("Simple calc called");
        const regex = /(\d+(\.\d+)?)([\+\-\*\/])(\d+(\.\d+)?)/;
        const match = currentExpression.match(regex);
        if (match) {
            let firstVar = parseFloat(match[1]);
            let operator = match[3];
            let secondVar = parseFloat(match[4]);

            currentResult = operate(firstVar, operator, secondVar);
            displayValue.textContent = currentResult;
            operatorUsed = false;
        }
    } else {
        console.log("Complex calc called");
        try {
            currentResult = eval(currentExpression);
            displayValue.textContent = currentResult;
            operatorUsed = false;
        } catch (error) {
            displayValue.textContent = "Error";
        }
    }
}

function operate(firstVar, operator, secondVar){
    let result;
    if (operator == "+") {
        result = add(firstVar, secondVar);
    }
    else if (operator == "-") {
        result = subtract(firstVar, secondVar);
    }
    else if (operator == "*") {
        result = multiply(firstVar, secondVar);
    }
    else if (operator == "/") {
        result = divide(firstVar, secondVar);
    }
    else{
        return console.error("Invalid operator");
    }
    return Number(result.toFixed(4));
}

function add(firstNum, secondNum){
    return firstNum + secondNum;
}

function subtract(firstNum, secondNum) {
    return firstNum - secondNum;
}

function multiply(firstNum, secondNum){
    return firstNum * secondNum;
}

function divide(firstNum, secondNum){
    return firstNum/secondNum;
}