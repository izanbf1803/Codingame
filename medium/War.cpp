#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class Game {
    
    enum Val { J = 11, Q = 12, K = 13, A = 14 };
    enum Suit { D, H, C, S };
    
    typedef struct {
        int val;
        Suit suit;
    } Card;
    
    public:
        Game();
        ~Game();
        void addCard(string card, int player);
        void start();
    private:
        Card* getCard(queue<Card*>* p);
        void giveCardsTo(queue<Card*>* p);
        void moveQueueTo(queue<Card*>* source, queue<Card*>* dest);
        void freeQueue(queue<Card*>* q);
        void playRound();
        void battle();
        void war();
    
        int rounds = 0;
        bool pat = false;
        queue<Card*>* p1;   // player 1
        queue<Card*>* p2;   // player 2
        queue<Card*>* pile1;
        queue<Card*>* pile2;
    
};

Game::Game() {
    p1 = new queue<Card*>; 
    p2 = new queue<Card*>;    
    pile1 = new queue<Card*>;    
    pile2 = new queue<Card*>;    
}

Game::~Game() {
    freeQueue(p1);
    freeQueue(p2);
    freeQueue(pile1);
    freeQueue(pile2);
}

void Game::addCard(string card, int player)
{
    Card* c = new Card;
    
    for (int i = 0; i < card.size()-1; i++) {
        switch (card[i]) {
            case 'J':
                c->val = J;
                break;
            case 'Q':
                c->val = Q;
                break;
            case 'K':
                c->val = K;
                break;
            case 'A':
                c->val = A;
                break;
            case '0':
                c->val = 10;
                break;
            default:
                c->val = card[i] - '0';
        }
    }
    
    switch (card[card.size()-1]) {
        case 'D':
            c->suit = D;
            break;
        case 'H':
            c->suit = H;
            break;
        case 'C':
            c->suit = C;
            break;
        case 'S':
            c->suit = S;
            break;
    }
    
    queue<Card*>* p = (player == 1 ? p1 : p2);
    p->push(c);
}

void Game::start() 
{
    while (!p1->empty() && !p2->empty() && !pat) playRound();   
    
    if (pat) {
        cout << "PAT" << endl;
    }
    else {
        if (p1->empty()) {
            cout << 2;
        }
        else {
            cout << 1;
        }
        
        cout << ' ' << rounds << endl;
    }
}

Game::Card* Game::getCard(queue<Card*>* p)
{
    int player = (p == p1 ? 1 : 2);
    Card* c = p->front();
    p->pop();
    queue<Card*>* pile = (player == 1 ? pile1 : pile2);
    pile->push(c);
    
    return c;
}

void Game::giveCardsTo(queue<Card*>* p)
{
    moveQueueTo(p, pile1);
    moveQueueTo(p, pile2);
}

void Game::moveQueueTo(queue<Card*>* dest, queue<Card*>* source)
{
    while (!source->empty()) {
        dest->push(source->front());
        source->pop();
    }
}

void Game::freeQueue(queue<Card*>* q)
{
    while (!q->empty()) {
        delete q->front();
        q->pop();   
    }
    
    delete q;
}

void Game::playRound() 
{
    rounds++;
    battle();
}

void Game::battle()
{
    Card* cp1 = getCard(p1);
    Card* cp2 = getCard(p2);
    
    if (cp1->val > cp2->val) giveCardsTo(p1);
    else if (cp2->val > cp1->val) giveCardsTo(p2);
    else war();
}

void Game::war()
{
    if (p1->size() < 3 || p2->size() < 3) {
        pat = true;
        return;
    }
    
    for (int i = 0; i < 3; i++) {
        getCard(p1);
        getCard(p2);
    }
    
    battle();
}

int main()
{
    Game* game = new Game;
    
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        game->addCard(cardp1, 1);
    }
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        game->addCard(cardp2, 2);
    }

    game->start();
    
    delete game;
}
