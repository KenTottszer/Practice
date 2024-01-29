
let title = document.createElement('h1');
title.style.display = 'flex';
title.style.justifyContent = 'center';
title.textContent =  "ETCH A SKETCH";

document.body.appendChild(title);

let introText = document.createElement('p');
introText.textContent = 'To utilise this website you are to type in a number between 1 to 100 in the input box and press Enter. This will lead the program to generate a "your number" by "your number" grid which you can draw on.';

document.body.appendChild(introText);



let inputContainer = document.createElement('div');
inputContainer.style.display = 'flex';
inputContainer.style.justifyContent = 'center';
inputContainer.style.marginBottom = '30px';



let input = document.createElement('input');
input.style.marginRight = '10px';
input.style.marginLeft = '10px';



let button = document.createElement('button');
button.textContent = 'Enter';
button.addEventListener('click', getUserInput)


inputContainer.appendChild(input);
inputContainer.appendChild(button);
document.body.appendChild(inputContainer);



function getUserInput(){
    let inputValue = input.value;
    if(inputValue >= 1 && inputValue <= 100){
        printGrid(inputValue);
    }
    else {
    alert("Please enter a number between 1 and 100.");
}

}

let container = document.createElement('div');
container.style.display = 'flex';
container.style.flexDirection = 'column';
container.style.alignItems = 'center';

function onMouseEnter() {
    if (!this.style.backgroundColor) {
        const red = Math.floor(Math.random() * 256);
        const green = Math.floor(Math.random() * 256);
        const blue = Math.floor(Math.random() * 256);
        const randomColour = `rgb(${red}, ${green}, ${blue})`;
        this.style.backgroundColor = randomColour;
    }
}

function onMouseLeave(){
    this.style.backgroundColor = '';
}

function printGrid(squaresPerSide) {
    container.innerHTML = ''; // Clear the container before adding a new grid

    const borderSize = 1; // Adjusted for a 1px border on each side
    const totalBorderSize = borderSize * 2; // Total border size for each square
    const squareSize = (960 - (squaresPerSide * totalBorderSize)) / squaresPerSide + 'px'; // Calculate size and convert to string

    for (let rowIndex = 0; rowIndex < squaresPerSide; rowIndex++) {
        let row = document.createElement('div');
        row.style.display = 'flex';

        for (let squareIndex = 0; squareIndex < squaresPerSide; squareIndex++) { // Corrected variable name
            let square = document.createElement('div');
            square.style.borderColor = 'black';
            square.style.borderStyle = 'solid';
            square.style.borderWidth = `${borderSize}px`;
            square.style.width = squareSize; // Use calculated size
            square.style.height = squareSize; // Use calculated size
            square.addEventListener('mouseenter', onMouseEnter);
            // square.addEventListener('mouseleave', onMouseLeave);

            row.appendChild(square);
        }
        container.appendChild(row);
    }

    // Append the container only if it's not already in the document body
    if (!container.parentElement) {
        document.body.appendChild(container);
    }
}


