<!DOCTYPE html>
<html lang="en">

<head>

    <title>Poker in PHP</title></head>

<body>
<div>
    <?php

    enum Suit: string
    {
        case Clubs = '♣';
        case Diamonds = '♦';
        case Hearts = '♥';
        case Spades = '♠';
    }

    enum Rank: int
    {
        case Ace = 1;
        case Two = 2;
        case Three = 3;
        case Four = 4;
        case Five = 5;
        case Six = 6;
        case Seven = 7;
        case Eight = 8;
        case Nine = 9;
        case Ten = 10;
        case Jack = 11;
        case Queen = 12;
        case King = 13;

        public function label(): string
        {
            return Rank::getLabel($this);
        }

        public static function getLabel(self $value): string
        {
            return match ($value) {
                Rank::Ace => 'A',
                Rank::Two => '2',
                Rank::Three => '3',
                Rank::Four => '4',
                Rank::Five => '5',
                Rank::Six => '6',
                Rank::Seven => '7',
                Rank::Eight => '8',
                Rank::Nine => '9',
                Rank::Ten => '10',
                Rank::Jack => 'J',
                Rank::Queen => 'Q',
                Rank::King => 'K',
            };
        }
    }

    class Card
    {
        public Suit $suit;
        public Rank $rank;


        public function __construct($suit, $rank)
        {
            $this->suit = $suit;
            $this->rank = $rank;
        }

        public function echoValues(): void
        {
            echo $this->suit->value;
            echo " ";
            echo $this->rank->label();
        }
    }

    class Player
    {
        private String $name;
        private Card $fstCard;
        private Card $sndCard;

        function __construct($name, Card $fstCard, Card $sndCard)
        {
            $this->name = $name;
            $this->fstCard = $fstCard;
            $this->sndCard = $sndCard;
        }

        function getCards(): array
        {
            return [$this->fstCard, $this->sndCard];
        }

        function getName(): string
        {
            return $this->name;
        }
    }

    class Game
    {
        private array $deck;
        private int $deckSize;
        private array $usedCards;

        private array $revealedCards = [];

        private array $players = [];

        private function getStandardDeck(): array
        {
            $retArr = [];
            foreach (Suit::cases() as $suit) {
                foreach (Rank::cases() as $rank) {
                    array_push($retArr, new Card($suit, $rank));
                }
            }
            return $retArr;
        }

        function __construct()
        {
            $this->deck = $this->getStandardDeck();
            $this->deckSize = count($this->deck);
            $this->usedCards = array_fill(0, $this->deckSize, false);
        }

        public function addPlayer($name): void
        {
            $fstCard = $this->deck[$this->getAndUpdateUnusedCardIndex()];
            $sndCard = $this->deck[$this->getAndUpdateUnusedCardIndex()];
            $newPlayer = new Player($name, $fstCard, $sndCard);
            array_push($this->players, $newPlayer);
        }

        private function getAndUpdateUnusedCardIndex(): int
        {
            $randIndex = -1;

            do {
                $randIndex = rand(0, $this->deckSize - 1);
            } while ($this->usedCards[$randIndex]);

            $this->usedCards[$randIndex] = true;

            return $randIndex;
        }

        public function revealNextCard(): bool
        {
            if (count($this->revealedCards) > 4) {
                return false;
            }

            $nextCard = $this->deck[$this->getAndUpdateUnusedCardIndex()];
            array_push($this->revealedCards, $nextCard);
            return true;
        }

        public function printCurrentState(): void
        {
            foreach ($this->players as $player) {
                echo $player->getName();
                echo " ";

                $cards = $player->getCards();

                echo $cards[0]->echoValues();
                echo " ";
                echo $cards[1]->echoValues();
                echo "<br>";
            }
            foreach ($this->revealedCards as $card) {
                echo $card->echoValues();
                echo " ";
            }
            echo "<br>";
        }
    }

    $game = new Game();

    $game->addPlayer("Mark");
    $game->addPlayer("Greg");

    $game->revealNextCard();

    $game->printCurrentState();

    $game->revealNextCard();
    $game->revealNextCard();
    $game->revealNextCard();

    $game->printCurrentState();

    $game->revealNextCard();
    $game->revealNextCard();

    $game->printCurrentState();

    ?>
</div>

</body>

</html>