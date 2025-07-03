class TicTacToe {
    constructor() {
        this.boxes = document.querySelectorAll(".box");
        this.result_text = document.querySelector("#results");
        this.play_again_btn = document.querySelector("#play-again");
        this.turn_bg = document.querySelector(".bg");

        this.current_player = "X";
        this.board = ["", "", "", "", "", "", "", "", ""];
        this.is_game_over = false;

        this.win_patterns = [
            [0, 1, 2],
            [3, 4, 5],
            [6, 7, 8],
            [0, 3, 6],
            [1, 4, 7],
            [2, 5, 8],
            [0, 4, 8],
            [2, 4, 6],
        ];

        this.initialize_game();
    }

    initialize_game() {
        this.boxes.forEach((box, index) => {
            box.innerHTML = "";
            box.addEventListener("click", () =>
                this.handle_cell_click(box, index)
            );
        });

        this.result_text.style.display = "none";
        this.play_again_btn.style.display = "none";

        this.play_again_btn.addEventListener("click", () => {
            location.reload();
        });
    }

    handle_cell_click(box, index) {
        if (this.board[index] !== "" || this.is_game_over) {
            return;
        }

        this.board[index] = this.current_player;
        box.innerHTML = this.current_player;

        if (this.is_win()) {
            this.is_game_over = true;
            this.show_result(false);
        } else if (this.is_draw()) {
            this.is_game_over = true;
            this.show_result(true);
        } else {
            this.switch_player();
        }
    }

    switch_player() {
        this.current_player = this.current_player === "X" ? "O" : "X";
        this.turn_bg.style.left = this.current_player === "X" ? "0" : "85px";
    }

    is_win() {
        for (const pattern of this.win_patterns) {
            const [a, b, c] = pattern;

            if (
                this.board[a] &&
                this.board[a] === this.board[b] &&
                this.board[a] === this.board[c]
            ) {
                return true;
            }
        }

        return false;
    }

    is_draw() {
        return this.board.every((cell) => cell !== "");
    }

    show_result(is_draw) {
        if (is_draw) {
            this.result_text.innerHTML = "It's a Draw!";
        } else {
            this.result_text.innerHTML = `${this.current_player} Wins!`;
        }

        this.result_text.style.display = "block";
        this.play_again_btn.style.display = "inline";
    }
}

new TicTacToe();
