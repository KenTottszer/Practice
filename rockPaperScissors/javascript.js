const rockButton = document.querySelector('#rockButton');
const scissorButton = document.querySelector('#scissorButton');
const paperButton = document.querySelector('#paperButton');

const div = document.createElement('div');
document.body.appendChild(div);

const scoreDiv = document.createElement('div');
document.body.appendChild(scoreDiv);

let playerScore = 0;
let computerScore = 0;
let roundCount = 0;

rockButton.addEventListener('click', () => playRound('rock'));
scissorButton.addEventListener('click', () => playRound('scissors')); 
paperButton.addEventListener('click', () => playRound('paper'));

function playRound(playerChoice) {
    if (roundCount >= 5) {
        displayFinalResults();
        return;
    }
    const computerChoice = getComputerChoice();
    const outcomes = {
        rock: { winsAgainst: 'scissors', losesTo: 'paper' },
        scissors: { winsAgainst: 'paper', losesTo: 'rock' }, 
        paper: { winsAgainst: 'rock', losesTo: 'scissors' } 
    };

    if (playerChoice === computerChoice) {
        div.textContent = `You tie as ${playerChoice} ties with ${computerChoice}. 1 point each.`;


    } else if (outcomes[playerChoice].winsAgainst === computerChoice) {
        div.textContent = `You win as ${playerChoice} beats ${computerChoice}. One point to you!`;
        playerScore++;
        roundCount++;
        
    } else if (outcomes[playerChoice].losesTo === computerChoice) {
        div.textContent = `You lose as ${computerChoice} beats ${playerChoice}. One point to the computer!`;
        computerScore++;
        roundCount++;
        
    }
    
    updateScoreDisplay();

    if (roundCount >= 5) {
        displayFinalResults();
    }
}

function getComputerChoice(){
    const arr = ["rock", "paper", "scissors"];
    return arr[Math.floor(Math.random() * arr.length)];
}
function updateScoreDisplay() {
    scoreDiv.textContent = `Player Score: ${playerScore}, Computer Score: ${computerScore}`;
}


function displayFinalResults() {
    if (playerScore > computerScore) {
        scoreDiv.textContent += ' - You win the game!';
    } else if (computerScore > playerScore) {
        scoreDiv.textContent += ' - Computer wins the game!';
    } else {
        scoreDiv.textContent += ' - The game is a tie!';
    }
    playerScore = 0;
    computerScore = 0;
    roundCount = 0;
}
