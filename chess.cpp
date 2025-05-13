//#include <iostream>
//#include <sstream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//using namespace std;
//using namespace sf;
//
//enum PieceColor
//{
//    NONE,
//    WHITE,
//    BLACK
//};
//
//PieceColor getPieceColor(int piece)
//{
//    if (piece > 0)
//    {
//        return PieceColor::WHITE;
//    }
//    else if (piece < 0)
//    {
//        return PieceColor::BLACK;
//    }
//    else
//    {
//        return PieceColor::NONE;
//    }
//}
//
//class Button
//{
//
//private:
//    RectangleShape m_shape;
//    Text m_text;
//    Vector2f m_position;
//
//public:
//
//    Button(const Vector2f& position, const string& text, Font& font) : m_position(position)
//    {
//        m_shape.setSize(Vector2f(400, 80));
//        m_shape.setFillColor(Color::Cyan);
//        m_shape.setPosition(position);
//
//        m_text.setFont(font);
//        m_text.setString(text);
//        m_text.setCharacterSize(60);
//        m_text.setFillColor(Color::Black);
//
//        FloatRect textRect = m_text.getLocalBounds();
//        m_text.setOrigin(textRect.left + textRect.width / 2.0f,
//            textRect.top + textRect.height / 2.0f);
//        m_text.setPosition(position.x + 200, position.y + 45);
//    }
//
//    void draw(RenderWindow& window)
//    {
//        window.draw(m_shape);
//        window.draw(m_text);
//    }
//
//    bool isMouseOver(const RenderWindow& window) const
//    {
//        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//        return m_shape.getGlobalBounds().contains(mousePos);
//    }
//};
//
//void checkMateWindowWhite();
//void checkMateWindowBlack();
//
//void setTextProperties(Text& text, const Font& font, const Color& fillColor, const Vector2f& position, const string& str, unsigned int characterSize)
//{
//    text.setFont(font);
//    text.setFillColor(fillColor);
//    text.setPosition(position);
//    text.setString(str);
//    text.setCharacterSize(characterSize);
//}
//
//Vector2f offset;
//const int LENGHT = 0;
//const int WHITE_PAWN = 1;
//const int BLACK_PAWN = -1;
//const int WHITE_BISHOP = 2;
//const int BLACK_BISHOP = -2;
//const int WHITE_KNIGHT = 3;
//const int BLACK_KNIGHT = -3;
//const int WHITE_ROOK = 4;
//const int BLACK_ROOK = -4;
//const int WHITE_QUEEN = 5;
//const int BLACK_QUEEN = -5;
//const int WHITE_KING = 6;
//const int BLACK_KING = -6;
//const int TIME_LIMIT = 60;
//
//int SIZE = 101;
//
//int ChessBoard[8][8] = { {-4,-3,-2,-5, -6,-2,-3,-4,},
//                         {-1,-1,-1,-1,-1,-1,-1,-1,},
//                         {0, 0, 0, 0, 0, 0, 0, 0,},
//                         {0, 0, 0, 0, 0, 0, 0, 0,},
//                         {0, 0, 0, 0, 0, 0, 0, 0,},
//                         {0, 0, 0, 0, 0, 0, 0, 0,},
//                         {1, 1, 1, 1, 1, 1, 1, 1,},
//                         {4, 3, 2, 5, 6, 2, 3, 4,},
//};
//
//bool isValidMove(int file, int rank, int destFile, int destRank) {
//    int piece = ChessBoard[file][rank];
//    int destPiece = ChessBoard[destFile][destRank];
//
//    if (piece == 0 || (destPiece * piece > 0)) {
//        return false; // Empty square or same color piece
//    }
//
//    int color = piece > 0 ? 1 : -1;
//
//    switch (abs(piece)) {
//    case WHITE_PAWN:
//    case BLACK_PAWN:
//        // Pawn moves
//        if (piece == WHITE_PAWN && destFile == file - 1 && destRank == rank && destPiece == 0) {
//            return true; // Move one square forward
//        }
//        else if (piece == WHITE_PAWN && file == 6 && destFile == 4 && destRank == rank && ChessBoard[5][rank] == 0 && destPiece == 0) {
//            return true; // Move two squares forward from starting position
//        }
//        else if (piece == BLACK_PAWN && destFile == file + 1 && destRank == rank && destPiece == 0) {
//            return true; // Move one square forward
//        }
//        else if (piece == BLACK_PAWN && file == 1 && destFile == 3 && destRank == rank && ChessBoard[2][rank] == 0 && destPiece == 0) {
//            return true; // Move two squares forward from starting position
//        }
//        else if (abs(destRank - rank) == 1 && ((piece == WHITE_PAWN && destFile == file - 1) || (piece == BLACK_PAWN && destFile == file + 1)) && destPiece * color < 0) {
//            return true; // Capture diagonally
//        }
//        break;
//
//    case WHITE_BISHOP:
//    case BLACK_BISHOP:
//        // Bishop moves
//        if (abs(destRank - rank) == abs(destFile - file)) {
//            int dirFile = (destFile - file) > 0 ? 1 : -1;
//            int dirRank = (destRank - rank) > 0 ? 1 : -1;
//            int i = file + dirFile;
//            int j = rank + dirRank;
//            while (i != destFile && j != destRank) {
//                if (ChessBoard[i][j] != 0) {
//                    return false; // Path blocked
//                }
//                i += dirFile;
//                j += dirRank;
//            }
//            return true;
//        }
//        break;
//
//    case WHITE_KNIGHT:
//    case BLACK_KNIGHT:
//        // Knight moves
//        if (((abs(destRank - rank) == 2 && abs(destFile - file) == 1) ||
//            (abs(destRank - rank) == 1 && abs(destFile - file) == 2)) &&
//            !(destFile == file && destRank == rank) && (destPiece * color <= 0)) {
//            return true;
//        }
//        break;
//
//    case WHITE_ROOK:
//    case BLACK_ROOK:
//        // Rook moves
//        if ((destFile == file || destRank == rank)) {
//            if (destFile == file) {
//                int dirRank = (destRank - rank) > 0 ? 1 : -1;
//                int j = rank + dirRank;
//                while (j != destRank) {
//                    if (ChessBoard[file][j] != 0) {
//                        return false; // Path blocked
//                    }
//                    j += dirRank;
//                }
//                return true;
//            }
//            else {
//                int dirFile = (destFile - file) > 0 ? 1 : -1;
//                int i = file + dirFile;
//                while (i != destFile) {
//                    if (ChessBoard[i][rank] != 0) {
//                        return false; // Path blocked
//                    }
//                    i += dirFile;
//                }
//                return true;
//            }
//        }
//        break;
//
//    case WHITE_QUEEN:
//    case BLACK_QUEEN:
//        // Queen moves (combination of rook and bishop)
//        if ((destFile == file || destRank == rank) || (abs(destRank - rank) == abs(destFile - file))) {
//            if (destFile == file) {
//                int dirRank = (destRank - rank) > 0 ? 1 : -1;
//                int j = rank + dirRank;
//                while (j != destRank) {
//                    if (ChessBoard[file][j] != 0) {
//                        return false; // Path blocked
//                    }
//                    j += dirRank;
//                }
//                return true;
//            }
//            else if (destRank == rank) {
//                int dirFile = (destFile - file) > 0 ? 1 : -1;
//                int i = file + dirFile;
//                while (i != destFile) {
//                    if (ChessBoard[i][rank] != 0) {
//                        return false; // Path blocked
//                    }
//                    i += dirFile;
//                }
//                return true;
//            }
//            else {
//                int dirFile = (destFile - file) > 0 ? 1 : -1;
//                int dirRank = (destRank - rank) > 0 ? 1 : -1;
//                int i = file + dirFile;
//                int j = rank + dirRank;
//                while (i != destFile && j != destRank) {
//                    if (ChessBoard[i][j] != 0) {
//                        return false; // Path blocked
//                    }
//                    i += dirFile;
//                    j += dirRank;
//                }
//                return true;
//            }
//        }
//        break;
//
//    case WHITE_KING:
//    case BLACK_KING:
//        // King moves
//        if ((abs(destRank - rank) <= 1 && abs(destFile - file) <= 1) && !(destFile == file && destRank == rank) && (destPiece * color <= 0)) {
//            return true;
//        }
//        break;
//
//    default:
//        return false;
//    }
//
//    return false;
//}
//
//bool isCheck(int kingFile, int kingRank, int kingColor)
//{
//    for (int file = 0; file < 8; file++)
//    {
//        for (int rank = 0; rank < 8; rank++)
//        {
//            if (ChessBoard[file][rank] * kingColor < 0)
//            {
//                if (isValidMove(file, rank, kingFile, kingRank))
//                {
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}
//
//bool isCheckmate(int kingFile, int kingRank, int kingColor)
//{
//    // Check if the king is in check
//    if (isCheck(kingFile, kingRank, kingColor))
//    {
//        // Check if the king has no legal moves to get out of check
//        for (int file = 0; file < 8; file++)
//        {
//            for (int rank = 0; rank < 8; rank++)
//            {
//                if (ChessBoard[file][rank] * kingColor > 0)
//                {
//                    for (int destFile = 0; destFile < 8; destFile++)
//                    {
//                        for (int destRank = 0; destRank < 8; destRank++)
//                        {
//                            if (isValidMove(file, rank, destFile, destRank))
//                            {
//                                int tmp = ChessBoard[destFile][destRank];
//                                ChessBoard[destFile][destRank] = ChessBoard[file][rank];
//                                ChessBoard[file][rank] = 0;
//
//                                bool isCheckAfterMove = isCheck(kingFile, kingRank, kingColor);
//
//                                ChessBoard[file][rank] = ChessBoard[destFile][destRank];
//                                ChessBoard[destFile][destRank] = tmp;
//
//                                if (!isCheckAfterMove)
//                                {
//                                    return false;
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        return true;
//    }
//    return false;
//}
//
//void promotePawn(int file, int rank, int pawnType)
//{
//    RenderWindow window(VideoMode(800, 800), "Promotion Window");
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        cerr << "Error loading font" << endl;
//        return;
//    }
//
//    Text promotionText;
//    promotionText.setFont(font);
//    promotionText.setFillColor(Color::Cyan);
//    promotionText.setPosition(170, 100);
//    promotionText.setString("CLICK TO PROMOTE");
//    promotionText.setCharacterSize(50);
//
//
//    Button QueenButton(Vector2f(200, 200), "Queen", font);
//    Button RookButton(Vector2f(200, 300), "Rook", font);
//    Button BishopButton(Vector2f(200, 400), "Bishop", font);
//    Button KnightButton(Vector2f(200, 500), "Knight", font);
//
//    int choice = 0;
//
//    while (window.isOpen() && choice == 0)
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//                return;
//            }
//            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//            {
//                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//                if (QueenButton.isMouseOver(window))
//                {
//                    choice = 1;
//                }
//                else if (RookButton.isMouseOver(window))
//                {
//                    choice = 2;
//                }
//                else if (BishopButton.isMouseOver(window))
//                {
//                    choice = 3;
//                }
//                else if (KnightButton.isMouseOver(window))
//                {
//                    choice = 4;
//                }
//            }
//        }
//
//        window.clear(Color::Black);
//        window.draw(promotionText);
//
//        QueenButton.draw(window);
//        RookButton.draw(window);
//        BishopButton.draw(window);
//        KnightButton.draw(window);
//
//        window.display();
//    }
//
//    if (pawnType == WHITE_PAWN)
//    {
//        switch (choice)
//        {
//        case 1:
//            ChessBoard[file][rank] = WHITE_QUEEN;
//            break;
//        case 2:
//            ChessBoard[file][rank] = WHITE_ROOK;
//            break;
//        case 3:
//            ChessBoard[file][rank] = WHITE_BISHOP;
//            break;
//        case 4:
//            ChessBoard[file][rank] = WHITE_KNIGHT;
//            break;
//        default:
//            cout << "Invalid choice. Promoting to Queen by default." << endl;
//            ChessBoard[file][rank] = WHITE_QUEEN;
//        }
//    }
//
//    else if (pawnType == BLACK_PAWN)
//    {
//        switch (choice)
//        {
//        case 1:
//            ChessBoard[file][rank] = BLACK_QUEEN;
//            break;
//        case 2:
//            ChessBoard[file][rank] = BLACK_ROOK;
//            break;
//        case 3:
//            ChessBoard[file][rank] = BLACK_BISHOP;
//            break;
//        case 4:
//            ChessBoard[file][rank] = BLACK_KNIGHT;
//            break;
//        default:
//            cout << "Invalid choice. Promoting to Queen by default." << endl;
//            ChessBoard[file][rank] = BLACK_QUEEN;
//        }
//    }
//}
//
//bool WhiteWon()
//{
//    bool kingAlive = false;
//
//    for (int i = 0; i < 8; i++)
//    {
//        for (int j = 0; j < 8; j++)
//        {
//            if (ChessBoard[i][j] == -6)
//            {
//                kingAlive = true;
//            }
//        }
//    }
//
//    if (kingAlive == false)
//    {
//        return true;
//    }
//
//    else
//    {
//        return false;
//    }
//
//}
//
//bool BlackWon()
//{
//    bool kingAlive = false;
//
//    for (int i = 0; i < 8; i++)
//    {
//        for (int j = 0; j < 8; j++)
//        {
//            if (ChessBoard[i][j] == 6)
//            {
//                kingAlive = true;
//            }
//        }
//    }
//
//    if (kingAlive == false)
//    {
//        return true;
//    }
//
//    else
//    {
//        return false;
//    }
//
//}
//
//void PlayGame()
//{
//    RenderWindow window(VideoMode(1300, 800), "Chess");
//
//    int selectedPiece = 0;
//    int selectedFile = -1;
//    int selectedRank = -1;
//    int moveColor = 1; // 1 for white, -1 for black
//
//    bool moveMade = false;
//    bool piececanMove = true;
//    bool kingcanMove = true;
//
//
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return;
//    }
//
//    // Set the icon
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Text whiteTimerText;
//    Text blackTimerText;
//    Text player2;
//    Text player1;
//
//    setTextProperties(player2, font, Color::Black, Vector2f(850, 100), "PLAYER 2", 50);
//    setTextProperties(blackTimerText, font, Color::Black, Vector2f(850, 160), "", 30);
//
//    setTextProperties(player1, font, Color::White, Vector2f(850, 600), "PlAYER 1", 50);
//    setTextProperties(whiteTimerText, font, Color::White, Vector2f(850, 660), "", 30);
//
//
//
//    Clock whiteClock;
//    Clock blackClock;
//
//    Time whiteTime = seconds(300);
//    Time blackTime = seconds(300);
//
//    SoundBuffer win;
//    SoundBuffer move;
//
//    win.loadFromFile("externals/win.wav");
//    move.loadFromFile("externals/move.wav");
//
//    Sound victorySound;
//    Sound moveSound;
//
//    victorySound.setBuffer(win);
//    moveSound.setBuffer(move);
//
//
//    Texture board;
//    Texture side;
//    Texture wp, bp, wb, bb, wn, bn, wr, br, wq, bq, wk, bk;
//
//    side.loadFromFile("externals/sidePanel.png");
//    board.loadFromFile("externals/_board.jpg");
//    wp.loadFromFile("externals/white pawn.png");
//    bp.loadFromFile("externals/black pawn.png");
//    wb.loadFromFile("externals/white bishop.png");
//    bb.loadFromFile("externals/black bishop.png");
//    wn.loadFromFile("externals/white knight.png");
//    bn.loadFromFile("externals/black knight.png");
//    wr.loadFromFile("externals/white rook.png");
//    br.loadFromFile("externals/black rook.png");
//    wq.loadFromFile("externals/white queen.png");
//    bq.loadFromFile("externals/black queen.png");
//    wk.loadFromFile("externals/white king.png");
//    bk.loadFromFile("externals/black king.png");
//
//    Sprite Board(board);
//    Sprite SidePanel(side);
//
//    Board.setScale(0.69, 0.69);
//    SidePanel.setScale(1, 1.5);
//    SidePanel.setPosition(806, 0);
//
//    Sprite WhitePawn(wp);
//    Sprite BlackPawn(bp);
//    Sprite WhiteBishop(wb);
//    Sprite BlackBishop(bb);
//    Sprite WhiteKnight(wn);
//    Sprite BlackKnight(bn);
//    Sprite WhiteRook(wr);
//    Sprite BlackRook(br);
//    Sprite WhiteQueen(wq);
//    Sprite BlackQueen(bq);
//    Sprite WhiteKing(wk);
//    Sprite BlackKing(bk);
//
//    while (window.isOpen())
//    {
//        Vector2i mousePos = Mouse::getPosition(window);
//
//        int MousePosX = mousePos.x / SIZE;
//        int MousePosY = mousePos.y / SIZE;
//
//        while (window.isOpen())
//        {
//            Vector2i mousePos = Mouse::getPosition(window);
//
//            int MousePosX = mousePos.x / SIZE;
//            int MousePosY = mousePos.y / SIZE;
//
//            Event e;
//            while (window.pollEvent(e))
//            {
//                if (e.type == Event::Closed)
//                {
//                    window.close();
//                }
//                else if (e.type == Event::MouseButtonPressed)
//                {
//                    if (MousePosX >= 0 && MousePosX < 8 && MousePosY >= 0 && MousePosY < 8)
//                    {
//                        if (ChessBoard[MousePosY][MousePosX] * moveColor > 0)
//                        {
//                            selectedPiece = ChessBoard[MousePosY][MousePosX];
//                            selectedFile = MousePosY;
//                            selectedRank = MousePosX;
//                        }
//                    }
//                }
//                else if (e.type == Event::MouseButtonReleased)
//                {
//                    if (selectedPiece != 0)
//                    {
//                        int destFile = MousePosY;
//                        int destRank = MousePosX;
//
//                        switch (selectedPiece)
//                        {
//                            //LEGAL MOVES FOR PAWN
//                            if (piececanMove == true)
//                            {
//                        case WHITE_PAWN:
//                            if (destRank == selectedRank && destFile == selectedFile - 1 && ChessBoard[destFile][destRank] == 0)
//                            {
//                                // Move one square forward
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//
//                                if (destFile == 0)
//                                {
//                                    promotePawn(destFile, destRank, WHITE_PAWN);
//                                }
//                            }
//                            else if (selectedFile == 6 && destRank == selectedRank && destFile == selectedFile - 2 && ChessBoard[selectedFile - 1][destRank] == 0 && ChessBoard[destFile][destRank] == 0) {
//                                // Move two squares forward from starting position
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//                            }
//                            else if ((destRank == selectedRank - 1 || destRank == selectedRank + 1) && destFile == selectedFile - 1 && ChessBoard[destFile][destRank] < 0) {
//                                // Capture diagonally
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//
//                                if (destFile == 0)
//                                {
//                                    promotePawn(destFile, destRank, WHITE_PAWN);
//                                }
//                            }
//                            break;
//
//                        case BLACK_PAWN:
//                            if (destRank == selectedRank && destFile == selectedFile + 1 && ChessBoard[destFile][destRank] == 0) {
//                                // Move one square forward
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//                                if (destFile == 7)
//                                {
//                                    promotePawn(destFile, destRank, BLACK_PAWN);
//                                }
//                            }
//                            else if (selectedFile == 1 && destRank == selectedRank && destFile == selectedFile + 2 && ChessBoard[selectedFile + 1][destRank] == 0 && ChessBoard[destFile][destRank] == 0) {
//                                // Move two squares forward from starting position
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//                            }
//                            else if ((destRank == selectedRank - 1 || destRank == selectedRank + 1) && destFile == selectedFile + 1 && ChessBoard[destFile][destRank] > 0) {
//                                // Capture diagonally
//                                ChessBoard[destFile][destRank] = selectedPiece;
//                                moveMade = true;
//                                ChessBoard[selectedFile][selectedRank] = 0;
//                                if (destFile == 7)
//                                {
//                                    promotePawn(destFile, destRank, BLACK_PAWN);
//                                }
//                            }
//                            break;
//
//                            //LEGAL MOVES FOR BISHOP
//                        case WHITE_BISHOP:
//                        case BLACK_BISHOP:
//                            if (abs(destRank - selectedRank) == abs(destFile - selectedFile))
//                            {
//                                int dirFile = (destFile - selectedFile) > 0 ? 1 : -1;
//                                int dirRank = (destRank - selectedRank) > 0 ? 1 : -1;
//                                int i = selectedFile + dirFile;
//                                int j = selectedRank + dirRank;
//                                bool obstacle = false;
//                                while (i != destFile && j != destRank) {
//                                    if (ChessBoard[i][j] != 0) {
//                                        obstacle = true;
//                                        break;
//                                    }
//                                    i += dirFile;
//                                    j += dirRank;
//                                }
//                                if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                    ChessBoard[destFile][destRank] = selectedPiece;
//                                    moveMade = true;
//                                    ChessBoard[selectedFile][selectedRank] = 0;
//                                }
//                            }
//                            break;
//
//                            //LEGAL MOVES FOR KNIGHT
//                        case WHITE_KNIGHT:
//                        case BLACK_KNIGHT:
//                            if (((abs(destRank - selectedRank) == 2 && abs(destFile - selectedFile) == 1) ||
//                                (abs(destRank - selectedRank) == 1 && abs(destFile - selectedFile) == 2)) &&
//                                !(destFile == selectedFile && destRank == selectedRank)) {
//                                // Check if the destination square is not occupied by a piece of the same color
//                                if ((ChessBoard[destFile][destRank] == 0) ||
//                                    (selectedPiece > 0 && ChessBoard[destFile][destRank] < 0) ||
//                                    (selectedPiece < 0 && ChessBoard[destFile][destRank] > 0)) {
//                                    ChessBoard[destFile][destRank] = selectedPiece;
//                                    moveMade = true;
//                                    ChessBoard[selectedFile][selectedRank] = 0;
//                                }
//                            }
//                            break;
//
//
//                            //LEGAL MOVES FOR THE ROOK
//                        case WHITE_ROOK:
//                        case BLACK_ROOK:
//                            if (destFile == selectedFile || destRank == selectedRank) {
//                                if (destFile == selectedFile) {
//                                    int dirRank = (destRank - selectedRank) > 0 ? 1 : -1;
//                                    int j = selectedRank + dirRank;
//                                    bool obstacle = false;
//                                    while (j != destRank) {
//                                        if (ChessBoard[selectedFile][j] != 0) {
//                                            obstacle = true;
//                                            break;
//                                        }
//                                        j += dirRank;
//                                    }
//                                    if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                        ChessBoard[destFile][destRank] = selectedPiece;
//                                        moveMade = true;
//                                        ChessBoard[selectedFile][selectedRank] = 0;
//                                    }
//                                }
//                                else
//                                {
//                                    int dirFile = (destFile - selectedFile) > 0 ? 1 : -1;
//                                    int i = selectedFile + dirFile;
//                                    bool obstacle = false;
//                                    while (i != destFile) {
//                                        if (ChessBoard[i][selectedRank] != 0) {
//                                            obstacle = true;
//                                            break;
//                                        }
//                                        i += dirFile;
//                                    }
//                                    if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                        ChessBoard[destFile][destRank] = selectedPiece;
//                                        moveMade = true;
//                                        ChessBoard[selectedFile][selectedRank] = 0;
//                                    }
//                                }
//                            }
//                            break;
//
//                            //LEGAL MOVES FOR QUEEN
//                        case WHITE_QUEEN:
//                        case BLACK_QUEEN:
//                            if ((destFile == selectedFile || destRank == selectedRank) ||
//                                (abs(destRank - selectedRank) == abs(destFile - selectedFile))) {
//                                if (destFile == selectedFile) {
//                                    int dirRank = (destRank - selectedRank) > 0 ? 1 : -1;
//                                    int j = selectedRank + dirRank;
//                                    bool obstacle = false;
//                                    while (j != destRank) {
//                                        if (ChessBoard[selectedFile][j] != 0) {
//                                            obstacle = true;
//                                            break;
//                                        }
//                                        j += dirRank;
//                                    }
//                                    if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                        ChessBoard[destFile][destRank] = selectedPiece;
//                                        moveMade = true;
//                                        ChessBoard[selectedFile][selectedRank] = 0;
//                                    }
//                                }
//                                else if (destRank == selectedRank) {
//                                    int dirFile = (destFile - selectedFile) > 0 ? 1 : -1;
//                                    int i = selectedFile + dirFile;
//                                    bool obstacle = false;
//                                    while (i != destFile) {
//                                        if (ChessBoard[i][selectedRank] != 0) {
//                                            obstacle = true;
//                                            break;
//                                        }
//                                        i += dirFile;
//                                    }
//                                    if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                        ChessBoard[destFile][destRank] = selectedPiece;
//                                        moveMade = true;
//                                        ChessBoard[selectedFile][selectedRank] = 0;
//                                    }
//                                }
//                                else {
//                                    int dirFile = (destFile - selectedFile) > 0 ? 1 : -1;
//                                    int dirRank = (destRank - selectedRank) > 0 ? 1 : -1;
//                                    int i = selectedFile + dirFile;
//                                    int j = selectedRank + dirRank;
//                                    bool obstacle = false;
//                                    while (i != destFile && j != destRank) {
//                                        if (ChessBoard[i][j] != 0) {
//                                            obstacle = true;
//                                            break;
//                                        }
//                                        i += dirFile;
//                                        j += dirRank;
//                                    }
//                                    if (!obstacle && (ChessBoard[destFile][destRank] == 0 || getPieceColor(ChessBoard[destFile][destRank]) != getPieceColor(selectedPiece))) {
//                                        ChessBoard[destFile][destRank] = selectedPiece;
//                                        moveMade = true;
//                                        ChessBoard[selectedFile][selectedRank] = 0;
//                                    }
//                                }
//                            }
//                            break;
//                            }
//
//                            if (kingcanMove == true)
//                            {
//                                //LEGAL MOVES FOR KING
//                        case WHITE_KING:
//                        case BLACK_KING:
//                            if ((abs(destRank - selectedRank) <= 1 && abs(destFile - selectedFile) <= 1) &&
//                                !(destFile == selectedFile && destRank == selectedRank))
//                            {
//                                // Check if the destination square is not occupied by a piece of the same color
//                                if ((ChessBoard[destFile][destRank] == 0) ||
//                                    (selectedPiece > 0 && ChessBoard[destFile][destRank] < 0) ||
//                                    (selectedPiece < 0 && ChessBoard[destFile][destRank] > 0))
//                                {
//                                    // Temporarily move the king to the destination square
//                                    int tmp = ChessBoard[destFile][destRank];
//                                    ChessBoard[destFile][destRank] = selectedPiece;
//                                    ChessBoard[selectedFile][selectedRank] = 0;
//
//                                    // Check if the king is in check after the move
//                                    if (!isCheck(destFile, destRank, selectedPiece))
//                                    {
//                                        // Move is valid
//                                        moveMade = true;
//                                    }
//                                    else
//                                    {
//                                        // Move puts the king in check, undo the move
//                                        ChessBoard[selectedFile][selectedRank] = selectedPiece;
//                                        ChessBoard[destFile][destRank] = tmp;
//                                    }
//
//                                    // Check for checkmate
//                                    bool check = isCheck(destFile, destRank, selectedPiece);
//                                    bool checkmate = isCheckmate(destFile, destRank, selectedPiece);
//
//                                    if (check && !checkmate)
//                                    {
//                                        // Only the king can move
//                                        piececanMove = false;
//                                        kingcanMove = true;
//                                    }
//                                    else if (check && checkmate)
//                                    {
//                                        // Display checkmate message
//                                        piececanMove = false;
//                                        kingcanMove = false;
//                                    }
//                                }
//                            }
//                            break;
//
//                            }
//                        }
//
//                        moveSound.play();
//
//                        if (moveColor == 1)
//                        {
//                            whiteTime -= whiteClock.restart();
//                            if (whiteTime <= Time::Zero)
//                            {
//                                checkMateWindowWhite();
//                                window.close();
//                            }
//                        }
//                        else if (moveColor == -1)
//                        {
//                            blackTime -= blackClock.restart();
//                            if (blackTime <= Time::Zero)
//                            {
//                                checkMateWindowBlack();
//                                window.close();
//                            }
//                        }
//
//                        // Update timer text
//                        stringstream whiteTimeStream;
//                        whiteTimeStream << "White: " << static_cast<int>(whiteTime.asSeconds()) << "s";
//                        whiteTimerText.setString(whiteTimeStream.str());
//
//                        stringstream blackTimeStream;
//                        blackTimeStream << "Black: " << static_cast<int>(blackTime.asSeconds()) << "s";
//                        blackTimerText.setString(blackTimeStream.str());
//
//                        if (WhiteWon() == true)
//                        {
//                            victorySound.play();
//                            checkMateWindowWhite();
//                            exit(1);
//                        }
//
//                        if (BlackWon() == true)
//                        {
//                            victorySound.play();
//                            checkMateWindowBlack();
//                            exit(1);
//                        }
//
//
//                        selectedPiece = 0;
//                        selectedFile = -1;
//                        selectedRank = -1;
//
//                        // Switch to the other player's turn
//                        if (moveMade == true)
//                            moveColor *= -1; moveMade = false;
//                    }
//                }
//            }
//
//            window.clear();
//            window.draw(Board);
//            window.draw(SidePanel);
//            window.draw(player1);
//            window.draw(player2);
//            window.draw(whiteTimerText);
//            window.draw(blackTimerText);
//
//            //Displaying all the pieces
//            for (int file = 0; file < 8; file++)
//            {
//                for (int rank = 0; rank < 8; rank++)
//                {
//                    if (ChessBoard[file][rank] != 0)
//                    {
//                        switch (ChessBoard[file][rank])
//                        {
//                        case WHITE_PAWN:
//                            WhitePawn.setPosition(rank * SIZE, file * SIZE);
//                            WhitePawn.setScale(0.9, 0.9);
//                            window.draw(WhitePawn);
//                            break;
//
//                        case BLACK_PAWN:
//                            BlackPawn.setPosition(rank * SIZE, file * SIZE);
//                            BlackPawn.setScale(0.9, 0.9);
//                            window.draw(BlackPawn);
//                            break;
//
//                        case WHITE_BISHOP:
//                            WhiteBishop.setPosition(rank * SIZE, file * SIZE);
//                            WhiteBishop.setScale(0.9, 0.9);
//                            window.draw(WhiteBishop);
//                            break;
//
//                        case BLACK_BISHOP:
//                            BlackBishop.setPosition(rank * SIZE, file * SIZE);
//                            BlackBishop.setScale(0.9, 0.9);
//                            window.draw(BlackBishop);
//                            break;
//
//                        case WHITE_KNIGHT:
//                            WhiteKnight.setPosition(rank * SIZE, file * SIZE);
//                            WhiteKnight.setScale(0.9, 0.9);
//                            window.draw(WhiteKnight);
//                            break;
//
//                        case BLACK_KNIGHT:
//                            BlackKnight.setPosition(rank * SIZE, file * SIZE);
//                            BlackKnight.setScale(0.9, 0.9);
//                            window.draw(BlackKnight);
//                            break;
//
//                        case WHITE_ROOK:
//                            WhiteRook.setPosition(rank * SIZE, file * SIZE);
//                            WhiteRook.setScale(0.9, 0.9);
//                            window.draw(WhiteRook);
//                            break;
//
//                        case BLACK_ROOK:
//                            BlackRook.setPosition(rank * SIZE, file * SIZE);
//                            BlackRook.setScale(0.9, 0.9);
//                            window.draw(BlackRook);
//                            break;
//
//                        case WHITE_QUEEN:
//                            WhiteQueen.setPosition(rank * SIZE, file * SIZE);
//                            WhiteQueen.setScale(0.9, 0.9);
//                            window.draw(WhiteQueen);
//                            break;
//
//                        case BLACK_QUEEN:
//                            BlackQueen.setPosition(rank * SIZE, file * SIZE);
//                            BlackQueen.setScale(0.9, 0.9);
//                            window.draw(BlackQueen);
//                            break;
//
//                        case WHITE_KING:
//                            WhiteKing.setPosition(rank * SIZE, file * SIZE);
//                            WhiteKing.setScale(0.9, 0.9);
//                            window.draw(WhiteKing);
//                            break;
//
//                        case BLACK_KING:
//                            BlackKing.setPosition(rank * SIZE, file * SIZE);
//                            BlackKing.setScale(0.9, 0.9);
//                            window.draw(BlackKing);
//                            break;
//                        }
//                    }
//                }
//            }
//
//            // Highlight the selected piece
//            if (selectedPiece != 0)
//            {
//                Sprite Highlight(board);
//                Highlight.setTextureRect(IntRect(0, 0, SIZE, SIZE));
//                Highlight.setPosition(selectedRank * SIZE, selectedFile * SIZE);
//                Highlight.setColor(Color(255, 255, 255, 191));
//                window.draw(Highlight);
//            }
//
//            window.display();
//        }
//    }
//}
//
//void checkMateWindowWhite()
//{
//    RenderWindow window(VideoMode(800, 800), "White Won");
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return;
//    }
//
//    // Set the icon
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Text checkMateText;
//    Text kingIsDead1;
//    Text kingIsDead2;
//
//    setTextProperties(checkMateText, font, Color::Cyan, Vector2f(150, 200), "WHITE WON", 80);
//    setTextProperties(kingIsDead1, font, Color::Cyan, Vector2f(150, 500), "THE KING IS DEAD......", 50);
//    setTextProperties(kingIsDead2, font, Color::Cyan, Vector2f(150, 600), "LONG LIVE THE KING", 50);
//
//
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        window.draw(checkMateText);
//        window.draw(kingIsDead1);
//        window.draw(kingIsDead2);
//
//
//        window.display();
//    }
//
//}
//
//void checkMateWindowBlack()
//{
//    RenderWindow window(VideoMode(800, 800), "Black Won");
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return;
//    }
//
//    // Set the icon
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Text checkMateText;
//    Text kingIsDead1;
//    Text kingIsDead2;
//
//    setTextProperties(checkMateText, font, Color::Cyan, Vector2f(200, 200), "BLACK WON", 80);
//    setTextProperties(kingIsDead1, font, Color::Cyan, Vector2f(150, 500), "THE KING IS DEAD......", 50);
//    setTextProperties(kingIsDead2, font, Color::Cyan, Vector2f(150, 600), "LONG LIVE THE KING", 50);
//
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        window.draw(checkMateText);
//        window.draw(kingIsDead1);
//        window.draw(kingIsDead2);
//
//        window.display();
//    }
//
//}
//
//void HowToPlay()
//{
//    RenderWindow window(VideoMode(800, 800), "How To Play");
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return;
//    }
//
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Text Ins1;
//    Text Ins2;
//    Text Ins3;
//    Text Ins4;
//
//    setTextProperties(Ins1, font, Color::Cyan, Vector2f(130, 150), "-> Hold and Drag to move pieces", 40);
//    setTextProperties(Ins2, font, Color::Cyan, Vector2f(130, 250), "-> Checkmate the Opponent to win", 40);
//    setTextProperties(Ins3, font, Color::Cyan, Vector2f(130, 350), "-> Promote if pawn reaches last rank", 40);
//
//    RectangleShape backButton(Vector2f(100, 50));
//    backButton.setFillColor(Color::Black);
//    backButton.setPosition(50, 700);
//
//    Text backText;
//    setTextProperties(backText, font, Color::White, Vector2f(60, 705), "Back", 30);
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//            {
//                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//                if (backButton.getGlobalBounds().contains(mousePos))
//                {
//                    // Close the window or go back to the previous screen
//                    window.close();
//                }
//            }
//        }
//
//        window.clear(Color::Black);
//
//        window.draw(Ins1);
//        window.draw(Ins2);
//        window.draw(Ins3);
//
//        window.draw(backButton);
//        window.draw(backText);
//
//        window.display();
//    }
//}
//
//void Credits()
//{
//    RenderWindow window(VideoMode(800, 800), "Credits");
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return;
//    }
//
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Text thanks;
//    setTextProperties(thanks, font, Color::Cyan, Vector2f(250, 600), "Thanks for playing", 40);
//
//
//    Text Ali;
//    Text R1;
//    setTextProperties(Ali, font, Color::Cyan, Vector2f(230, 150), "ALI YOUSAF", 60);
//    setTextProperties(R1, font, Color::Cyan, Vector2f(230, 230), "23L-0737", 40);
//
//    Text Haris;
//    Text R2;
//    setTextProperties(Haris, font, Color::Cyan, Vector2f(230, 400), "HARIS FAYYAZ", 60);
//    setTextProperties(R2, font, Color::Cyan, Vector2f(230, 480), "23L-0767", 40);
//
//    RectangleShape backButton(Vector2f(100, 50));
//    backButton.setFillColor(Color::Black);
//    backButton.setPosition(50, 700);
//
//    Text backText;
//    setTextProperties(backText, font, Color::White, Vector2f(60, 705), "Back", 30);
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//            else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//            {
//                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
//                if (backButton.getGlobalBounds().contains(mousePos))
//                {
//                    // Close the window or go back to the previous screen
//                    window.close();
//                }
//            }
//        }
//
//        window.clear(Color::Black);
//
//        window.draw(Ali);
//        window.draw(R1);
//        window.draw(Haris);
//        window.draw(R2);
//
//        window.draw(thanks);
//        window.draw(backButton);
//        window.draw(backText);
//
//        window.display();
//    }
//}
//
//int main()
//{
//    SoundBuffer sweden;
//    SoundBuffer menuClickSound;
//
//    Sound Music;
//    Sound clickSound;
//
//    sweden.loadFromFile("externals/sweden.wav");
//    menuClickSound.loadFromFile("externals/menuClickSound.wav");
//
//    clickSound.setBuffer(menuClickSound);
//    Music.setBuffer(sweden);
//
//    Music.play();
//
//    RenderWindow window(VideoMode(800, 800), "Game Menu");
//
//
//    Font font;
//    if (!font.loadFromFile("externals/OptimusPrinceps.ttf"))
//    {
//        // Error loading font
//        return -1;
//    }
//
//    Image icon;
//    if (!icon.loadFromFile("externals/icon.png"))
//    {
//        return 1;
//    }
//    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
//
//    Button playButton(Vector2f(200, 200), "Play", font);
//    Button howToPlayButton(Vector2f(200, 300), "How to Play", font);
//    Button creditsButton(Vector2f(200, 400), "Credits", font);
//    Button exitButton(Vector2f(200, 500), "Exit", font);
//
//    while (window.isOpen())
//    {
//        Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                window.close();
//            }
//
//            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
//            {
//                if (playButton.isMouseOver(window))
//                {
//                    Music.stop();
//                    clickSound.play();
//                    PlayGame();
//                }
//                else if (howToPlayButton.isMouseOver(window))
//                {
//                    clickSound.play();
//                    HowToPlay();
//                }
//                else if (creditsButton.isMouseOver(window))
//                {
//                    clickSound.play();
//                    Credits();
//
//                }
//                else if (exitButton.isMouseOver(window))
//                {
//                    clickSound.play();
//                    window.close();
//                }
//            }
//        }
//
//        window.clear(Color::Black);
//
//        playButton.draw(window);
//        howToPlayButton.draw(window);
//        creditsButton.draw(window);
//        exitButton.draw(window);
//
//        window.display();
//    }
//
//    return 0;
//}