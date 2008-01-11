#ifndef __GOMOKU_H__
# define __GOMOKU_H__

# include <vector>
# include <iostream>
# include "Move.h"
# include "defines.h"
# include "../Button.h"
# include "../AlgorithmType.h"
# include "Player.h"
# include "IA.h"

typedef	enum
{
	IN_PROGRESS,
    VICTORY_PLAYER1,
    VICTORY_PLAYER2,
    ALLOWED,
    FORBIDDEN,
    BOARD_FULL
}	GameState;

typedef enum
{
	WAITING_PLAYER_ACTION,
	DONE
}	MoveState;

class Gomoku
{
    private:
        static				int dx[4];
        static				int dy[4];
        static Gomoku		*instance;

    private:
        int					size;
		Player				*players[2];
        Button				***board;
        AlgorithmType		algo;

        int					stones;
        unsigned int		nb_moves;
        GameState			state;
		int					nextPlayerNum;



    private:
        Gomoku();
		~Gomoku();

    public:
        static Gomoku       *GetInstance();
        static void         DestroyInstance();

    public:
        void			    SetSize(int size);
		void				SetPlayer(int playerNum, PlayerType type);
        void			    SetBoard(Button ***button);
        void			    SetAlgorithm(AlgorithmType algo);

		MoveState			DoNextMove();

		bool                isCorrect(int x, int y) const;
        void	            dump(std::ostream& o) const;
        int                 GetNbMoves();
        void                ResetGame();
		void				CheckGameState(unsigned int x, unsigned int y, unsigned int p);
        unsigned int        evaluate() const;
        unsigned int        getPlayerToMove() const;
        GameState        	getState() const;
        std::vector<Move *> getCorrectMoves() const;
        std::vector<Move *> initAlgo(unsigned int x = 0) const;

    public:
        void				commitMove(const Move *move, bool setState);
        void				undoMove(const Move *move);
};

#endif //!__GOMOKU_H__
