#include "pong.hpp"

/* #region screens*/

void Pong::hostLobby() {
    buttons.clear();
    buttonsFunctions.clear();
    addButton(350, 150, widthPercentToPos(25), heightPercentToPos(85),
        "Close Lobby", &Pong::handleCloseLobby);

    addButton(350, 150, widthPercentToPos(42), heightPercentToPos(20), "Me",
        &Pong::nothing);
    addButton(350, 150, widthPercentToPos(42), heightPercentToPos(5),
        "\nCopy code\n" + ipToCode(myIP), &Pong::handleCopyCode);

    while (screen) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quitGame();
                break;
            case sf::Event::MouseButtonPressed:
                // if (event.mouseButton.x)
                for (int i = 0; i < buttons.size(); i++) {
                    if (event.mouseButton.x > buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.x < buttons[i].rectangle.getSize().x +
                        buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.y > buttons[i].rectangle.getPosition().y &&
                        event.mouseButton.y < buttons[i].rectangle.getSize().y +
                        buttons[i].rectangle.getPosition().y) {
                        (this->*buttonsFunctions[i])();
                        std::cout << "touched" << std::endl;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitGame();
                    break;
                }
                break;
            }
        }
        window->clear();

        buttonsMTX.lock();
        int tmpSize = buttons.size();
        for (int i = 0; i < tmpSize; i++) {
            buttons[i].update(window);
        }
        buttonsMTX.unlock();

        window->display();
    }
}

void Pong::guestLobby() {
    buttons.clear();
    buttonsFunctions.clear();
    buttons.push_back(
        Button(400, 150, widthRelativeSize(100), height - 100, "Leave", &font));

    while (screen) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quitGame();
                break;
            case sf::Event::MouseButtonPressed:
                // if (event.mouseButton.x)
                for (int i = 0; i < buttons.size(); i++) {
                    if (event.mouseButton.x > buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.x < buttons[i].rectangle.getSize().x +
                        buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.y > buttons[i].rectangle.getPosition().y &&
                        event.mouseButton.y < buttons[i].rectangle.getSize().y +
                        buttons[i].rectangle.getPosition().y) {
                        // (this->*buttonsFunctions[i])();
                        std::cout << "touched" << std::endl;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitGame();
                    break;
                }
            }
        }
        window->clear();

        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].update(window);
        }

        window->display();
    }
}

void Pong::enterCode() {
    buttons.clear();
    buttonsFunctions.clear();
    buttons.push_back(Button(500, 50, widthRelativeSize(960 - 500 / 2),
        heightRelativeSize(540 - 50 / 2), "", &font));
    buttonsFunctions.push_back(&Pong::nothing);
    buttons.push_back(Button(300, 150, widthRelativeSize(960 - 300 / 2),
        heightRelativeSize(540 * 2 - 200), "join", &font));
    buttonsFunctions.push_back(&Pong::handleAttemptConnection);
    sf::Text enterPrompt;
    enterPrompt.setFont(font);
    enterPrompt.setString("Enter code below");
    enterPrompt.setCharacterSize(30);
    enterPrompt.setFillColor(sf::Color::White);
    enterPrompt.setPosition(
        widthRelativeSize(960) - enterPrompt.getGlobalBounds().width / 2,
        heightRelativeSize(540) - enterPrompt.getGlobalBounds().height / 2 - 100);

    while (screen) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quitGame();
                break;
            case sf::Event::MouseButtonPressed:
                // if (event.mouseButton.x)
                for (int i = 0; i < buttons.size(); i++) {
                    if (event.mouseButton.x > buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.x < buttons[i].rectangle.getSize().x +
                        buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.y > buttons[i].rectangle.getPosition().y &&
                        event.mouseButton.y < buttons[i].rectangle.getSize().y +
                        buttons[i].rectangle.getPosition().y) {
                        (this->*buttonsFunctions[i])();
                        std::cout << i << std::endl;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitGame();
                    break;
                }
                break;
            case sf::Event::TextEntered:
                switch (event.text.unicode) {
                case 0x08: // backspace
                {
                    std::string tmp = buttons[0].textBox.getString();
                    tmp = tmp.substr(0, tmp.size() - 1);
                    buttons[0].textBox.setString(tmp);
                    break;
                }
                case 0x0D: // enter key
                    handleAttemptConnection();
                    break;
                case 0x16: // ctrl v
                    buttons[0].textBox.setString(buttons[0].textBox.getString() +
                        sf::Clipboard::getString());
                    break;
                default:
                    buttons[0].textBox.setString(buttons[0].textBox.getString() +
                        event.text.unicode);
                    break;
                }
                break;
            }
        }
        window->clear();

        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].update(window);
            window->draw(enterPrompt);
        }

        window->display();
    }
}

void Pong::mainMenu() {
    buttons.clear();
    buttons.push_back(
        Button(400, 150, widthPercentToPos(50), 100, "Host Game", &font));
    buttons.push_back(
        Button(400, 150, widthRelativeSize(960), 300, "Join Game", &font));
    buttons.push_back(
        Button(400, 150, width / 2 - 400 / 2, 500, "Settings", &font));
    buttons.push_back(
        Button(400, 150, width / 2 - 400 / 2, 700, "Exit Game", &font));
    buttonsFunctions.clear();
    buttonsFunctions.push_back(&Pong::handleHostLobby);
    buttonsFunctions.push_back(&Pong::handleJoinGame);
    buttonsFunctions.push_back(&Pong::nothing);
    buttonsFunctions.push_back(&Pong::quitGame);

    while (screen) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quitGame();
                break;
            case sf::Event::MouseButtonPressed:
                // if (event.mouseButton.x)
                for (int i = 0; i < buttons.size(); i++) {
                    if (event.mouseButton.x > buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.x < buttons[i].rectangle.getSize().x +
                        buttons[i].rectangle.getPosition().x &&
                        event.mouseButton.y > buttons[i].rectangle.getPosition().y &&
                        event.mouseButton.y < buttons[i].rectangle.getSize().y +
                        buttons[i].rectangle.getPosition().y) {
                        (this->*buttonsFunctions[i])();
                        std::cout << "touched" << std::endl;
                    }
                }
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitGame();
                    break;
                }
                break;
            }
        }
        window->clear();

        for (int i = 0; i < buttons.size(); i++) {
            buttons[i].update(window);
        }

        window->display();
    }
}

void Pong::game() {
    ReceivedInfo ri;
    ri.update.update = 3;
    std::cout << "game here" << std::endl;

    myPaddle = Paddle(10, 50, 10, 10, sf::Color::White, window);
    opponentPaddle = Paddle(10, 50, window->getSize().x - 10 - 10, 10,
        sf::Color::White, window);
    ball = Ball(10, 10, width / 2 - 10 / 2, height / 2 - 10 / 2, sf::Color::White, window);

    if (me != 1) {
        srand(time(NULL));
        ball.setyVel(rand() % 10 + 1);
        if (rand() % 2) {
            ball.swapyVel();
        }
        if (rand() % 2) {
            ball.setxVel(-8);
        }
        else {
            ball.setxVel(8);
        }
        addToQueue(SEND_BALL);
    }
    myScore.setPosition(sf::Vector2f(300, 30));
    opponentScore.setPosition(sf::Vector2f(1600, 30));


    while (screen)
    {
        count++;
        std::chrono::microseconds time1 =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window: exit
            switch (event.type) {
            case sf::Event::Closed:
                quitGame();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitGame();
                    break;
                case sf::Keyboard::W:
                    myPaddle.upPressed();
                    addToQueue(SEND_PADDLE);
                    break;
                case sf::Keyboard::S:
                    myPaddle.downPressed();
                    addToQueue(SEND_PADDLE);
                    break;
                }
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::W:
                    myPaddle.upReleased();
                    addToQueue(SEND_PADDLE);
                    break;
                case sf::Keyboard::S:
                    myPaddle.downReleased();
                    addToQueue(SEND_PADDLE);
                    break;
                }
                break;
            }
        }
        // Clear screen
        window->clear();

        if (ball.actor.getPosition().x <
            myPaddle.actor.getPosition().x + myPaddle.actor.getSize().x &&
            ball.actor.getPosition().x + ball.actor.getSize().x >
            myPaddle.actor.getPosition().x &&
            ball.actor.getPosition().y <
            myPaddle.actor.getPosition().y + myPaddle.actor.getSize().y &&
            ball.actor.getPosition().y + ball.actor.getSize().y >
            myPaddle.actor.getPosition().y) {
            ball.setXLoc(myPaddle.actor.getPosition().x + myPaddle.actor.getSize().x);
            ball.swapxVel();
            std::cout << "switch x" << std::endl;
        }
        else if (ball.actor.getPosition().x <
            opponentPaddle.actor.getPosition().x +
            opponentPaddle.actor.getSize().x &&
            ball.actor.getPosition().x + ball.actor.getSize().x >
            opponentPaddle.actor.getPosition().x &&
            ball.actor.getPosition().y <
            opponentPaddle.actor.getPosition().y +
            opponentPaddle.actor.getSize().y &&
            ball.actor.getPosition().y + ball.actor.getSize().y >
            opponentPaddle.actor.getPosition().y) {
            ball.setXLoc(opponentPaddle.actor.getPosition().x - ball.actor.getSize().x);
            ball.swapxVel();
            std::cout << "switch x" << std::endl;
        }

        if (me != 1) {
            if (ball.actor.getPosition().x < 0) {
                int opIntScore = std::stoi(opponentScore.getString().toAnsiString());
                opIntScore += 1;
                opponentScore.setString(std::to_string(opIntScore));

                ball.setxVel(8);

                ball.setyVel(rand() % 10 + 1);
                if (rand() % 2) {
                    ball.swapyVel();
                }

                ball.setXLoc(1920 / 2);
                ball.setYLoc(1080 / 2);

                addToQueue(SEND_BALL);

                addToQueue(SEND_GUEST_SCORE);


            }
            else if (ball.actor.getPosition().x + ball.actor.getSize().x >
                window->getSize().x) {
                int opIntScore = std::stoi(myScore.getString().toAnsiString());
                opIntScore += 1;
                myScore.setString(std::to_string(opIntScore));
                ball.setxVel(-8);

                ball.setyVel(rand() % 10 + 1);
                if (rand() % 2) {
                    ball.swapyVel();
                }

                ball.setXLoc(1920 / 2);
                ball.setYLoc(1080 / 2);

                addToQueue(SEND_BALL);

                addToQueue(SEND_HOST_SCORE);
            }
        }

        // std::cout << count++ << std::endl;
        // if (me == 0)
        // {
        //     std::cout << ball.getXLoc() << " " << ball.getYLoc() << std::endl;
        // }
        // else
        // {
        //     std::cout << 1920 - (ball.getXLoc() + 10) << " " << ball.getYLoc() << std::endl;
        // }

        window->draw(myScore);
        window->draw(opponentScore);

        myPaddle.Update(window);
        opponentPaddle.Update(window);
        ball.Update(window);

        // Update the window
        window->display();
        // std::chrono::microseconds time2 =
        //     std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());

    } //end while (screen)
}

/* #endregion */

/* #region network */

void Pong::bindSocket() {
#ifdef WIN32
    // Prepare the sockaddr_in structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(myIP.c_str());
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) ==
        SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

#else
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr(myIP.c_str());
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
#endif
}

void Pong::openSocket() {
    // Creating socket file descriptor
#ifdef WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    unsigned int tv = 1000;
    char tvchar[sizeof(tv)];
    memcpy(tvchar, &tv, sizeof(tv));
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
#else
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0; ;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif
    len = sizeof(sockaddr_in);

    char host[256];
    struct hostent* host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); // find the host name
    host_entry = gethostbyname(host);                                         // find host information
    myIP = inet_ntoa(*(
        (struct in_addr*)host_entry->h_addr_list[0])); // Convert into IP string
}

void Pong::newConnection() {
    std::string input;
    std::cin >> input;

    int last = 0;
    std::stringstream code;

    for (int i = 0; i < input.length() + 1; i++) {
        if (input[i] == '.') {
            int tempi;
            std::stringstream tempss;
            tempss << std::hex << input.substr(last, i - last);
            tempss >> tempi;
            code << tempi;
            code << ".";
            last = i + 1;
        }
        else if (input[i] == '\0') {
            int tempi;
            std::stringstream tempss;
            tempss << std::hex << input.substr(last, i - last);
            tempss >> tempi;
            code << tempi;
        }
    }
    changeConf("connection", code.str());
}

void Pong::guestNetworkLoop() {
#ifdef WIN32
    unsigned int tv = 1000;
    char tvchar[sizeof(tv)];
    memcpy(tvchar, &tv, sizeof(tv));
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, tvchar, sizeof(tv));
#else
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0; // 1000        * 1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif

    networkLoopBool = true;
    while (networkLoopBool) {
        ReceivedInfo ri = recieve(servaddr);

        switch (ri.type)
        {
        case PING:
            addToQueue(SEND_PING_BACK);
            break;
        case BALL_INFO:
            ball.setxVel(ri.ballInfo.xVel * -1);
            ball.setyVel(ri.ballInfo.yVel);
            ball.setXLoc(1920 - (ball.actor.getSize().x + ri.ballInfo.xLoc));
            ball.setYLoc(ri.ballInfo.yLoc);
            break;
        case CHARACTER_INFO:
            std::cout << "char info" << std::endl;
            opponentPaddle.yLoc = ri.characterInfo.yLoc + ri.characterInfo.yVel * (count - ri.characterInfo.when);
            opponentPaddle.yVel = ri.characterInfo.yVel;
            break;
        case UPDATE:
            switch (ri.update.update)
            {
            case STARTGAME: {
                screen = false;
                currentScreen = &Pong::game;
                std::cout << "startgame" << std::endl;
                break;}
            case HOSTSCORE: {
                int opIntScore = std::stoi(opponentScore.getString().toAnsiString());
                opIntScore += 1;
                opponentScore.setString(std::to_string(opIntScore));
                break;}
            case GUESTSCORE: {
                int myIntScore = std::stoi(myScore.getString().toAnsiString());
                myIntScore += 1;
                myScore.setString(std::to_string(myIntScore));
                break;}
            } //end switch (ri.update.update)
            break;

        } // end switch (ri.type)

        if (currentScreen == &Pong::guestLobby)
        {
            addToQueue(SEND_IM_HERE);
        }
    }
}

void Pong::hostNetworkLoop() {
    int update = 0;
    while (networkLoopBool) {
        ReceivedInfo ri = recieve(cliaddr);
        if (!joinable && currentScreen == &Pong::hostLobby) {
            update++;
            if (update >= 5) {
                update = 0;
                joinable = true;

                buttonsMTX.lock();
                buttons.pop_back();
                buttonsFunctions.pop_back();
                buttons.pop_back();
                buttonsFunctions.pop_back();
                buttonsMTX.unlock();
                std::cout << "kicked" << std::endl;
            }
        }
        switch (ri.type) {
        case PING_BACK:
            // queueWN.notify();
            break;
        case JOIN:
            if (!joinable) {
                break;
            }
            std::cout << "join request" << std::endl;

            ReceivedInfo sendInfo;
            memset(&sendInfo, 0, sizeof(ReceivedInfo));
            sendInfo.type = ACCEPT_JOIN;
            sendInfo.acceptJoin.who = 0;
            // player id based on current number of players in dictioanry
            sendInfo.acceptJoin.assign = 1;

            send(sendInfo, cliaddr);

            buttonsMTX.lock();

            addButton(widthRelativeSize(350), heightRelativeSize(150),
                widthPercentToPos(42), heightPercentToPos(40), "player 2",
                &Pong::nothing);

            addButton(widthRelativeSize(350), heightRelativeSize(150),
                widthPercentToPos(62), heightPercentToPos(85), "StartGame",
                &Pong::handleStartGame);

            buttonsMTX.unlock();

            joinable = false;

            break;
        case UPDATE:
            if (joinable) {
                break;
            }
            if (ri.update.update == 0) {
                buttonsMTX.lock();
                update = 0;
                joinable = true;
                buttons.pop_back();
                buttonsFunctions.pop_back();
                buttons.pop_back();
                buttonsFunctions.pop_back();
                buttonsMTX.unlock();
            }
            else {
                update = 0;
            }
            break;
        case CHARACTER_INFO:
            std::cout << "char info" << std::endl;
            opponentPaddle.yLoc = ri.characterInfo.yLoc + ri.characterInfo.yVel * (count - ri.characterInfo.when);
            opponentPaddle.yVel = ri.characterInfo.yVel;
            break;
        }
    }
    me = -1;
}

void Pong::addToQueue(int toAdd) {
    sendQueue.push(toAdd);
    queueWN.notify();
}

void Pong::queueLoop() {
    while (networkLoopBool) {
        queueWN.wait();

        while (sendQueue.size() > 0) {
            ReceivedInfo si;
            memset(&si, 0, sizeof(ReceivedInfo));
            si.characterInfo.who = me;

            switch (sendQueue.front()) {
            case SEND_PING:
                si.type = PING;
                break;
            case SEND_PING_BACK:
                si.type = PING_BACK;
                si.ping.hit = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
                break;
            case SEND_BALL:
                si.type = BALL_INFO;
                si.ballInfo.xVel = ball.getxVel();
                si.ballInfo.yVel = ball.getyVel();
                si.ballInfo.xLoc = ball.getXLoc();
                si.ballInfo.yLoc = ball.getYLoc();
                break;
            case SEND_GUEST_SCORE:
                si.type = UPDATE;
                si.update.update = GUESTSCORE;
                break;
            case SEND_HOST_SCORE:
                si.type = UPDATE;
                si.update.update = HOSTSCORE;
                break;
            case SEND_START_GAME:
                si.type = UPDATE;
                si.update.update = STARTGAME;
                break;
            case SEND_PADDLE:
                si.type = CHARACTER_INFO;
                si.characterInfo.when = count;
                si.characterInfo.yLoc = myPaddle.yLoc;
                si.characterInfo.yVel = myPaddle.yVel;
                break;
            case SEND_IM_HERE:
                si.type = UPDATE;
                si.update.update = IMHERE;
            } //end switch (sendQueue.front())
            if (me == 0)
            {
                send(si, cliaddr);
            }
            else
            {
                send(si, servaddr);
            }

            sendQueue.pop();
        } //end while (sendQueue.size() > 0)
    }
}

std::string Pong::ipToCode(std::string IP_string) {
    std::stringstream code_ss;
    int last = 0;
    for (int i = 0; i < IP_string.length() + 1; i++) {
        if (IP_string[i] == '.' || IP_string[i] == '\0') {
            code_ss << std::setfill('0') << std::setw(2) << std::hex
                << std::stoi(IP_string.substr(last, i - last));
            last = i + 1;
        }
    }
    return code_ss.str();
}

std::string Pong::codeToIP(const char IP_char[8]) {
    std::string IP_string = "";
    for (int i = 0; i < 8; i += 2) {
        std::stringstream IP_ss;
        int x;
        IP_ss << std::hex << (std::string(1, IP_char[i]) + IP_char[i + 1]);
        IP_ss >> x;
        IP_string += std::to_string(x);
        if (i < 6) {
            IP_string += '.';
        }
    }

    return IP_string;
}

void Pong::join(const char code[8]) {
#ifdef WIN32
    unsigned int tv = 5000;
    char tvchar[sizeof(tv)];
    memcpy(tvchar, &tv, sizeof(tv));
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, tvchar, sizeof(tv));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.S_un.S_addr = inet_addr(codeToIP(code).c_str());
    servaddr.sin_port = htons(PORT);
#else
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0; // 1000        * 1000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr(codeToIP(code).c_str());
    servaddr.sin_port = htons(PORT);
#endif

    ReceivedInfo sendInfo;
    sendInfo.type = JOIN;
    strcpy(sendInfo.join.IP, code);

    send(sendInfo, servaddr);

    ReceivedInfo recInfo = recieve(servaddr);

    if (recInfo.type < 1) {
        std::cout << "timeout" << std::endl;
        return;
    }

    me = recInfo.acceptJoin.assign;
    std::cout << "i am player: " << me << std::endl;
    screen = false;
    currentScreen = &Pong::guestLobby;

    netLoop = std::thread(&Pong::guestNetworkLoop, this);
    std::thread(&Pong::queueLoop, this).detach();
}

ReceivedInfo Pong::recieve(struct sockaddr_in& addr) {
#ifdef WIN32
    ReceivedInfo ri;
    memset(&ri, 0, sizeof(ReceivedInfo));
    n = recvfrom(sockfd, (char*)&ri, sizeof(ReceivedInfo), 0, (struct sockaddr*)&addr,
        &len);
    return ri;
#else
    ReceivedInfo ri;
    memset(&ri, 0, sizeof(ReceivedInfo));
    n = recvfrom(sockfd, &ri, sizeof(ReceivedInfo), MSG_WAITALL,
        (struct sockaddr*)&addr, &len);
    return ri;
#endif
}

void Pong::send(ReceivedInfo& ri, struct sockaddr_in& addr) {
#ifdef WIN32
    sendto(sockfd, (char*)&ri, sizeof(ReceivedInfo), 0,
        (struct sockaddr*)&addr, sizeof(addr));
#else
    sendto(sockfd, &ri, sizeof(ReceivedInfo), 0, (struct sockaddr*)&addr,
        sizeof(addr));
#endif
}

/* #endregion */

/* #region Button Handles*/

void Pong::handleJoinGameFromEnterCode() {
    currentScreen = &Pong::guestLobby;
    screen = false;
}

void Pong::handleleaveLobby() {
    currentScreen = &Pong::mainMenu;
    screen = false;
}

void Pong::handleJoinGame() {
    currentScreen = &Pong::enterCode;
    screen = false;
}

void Pong::handleHostLobby() {
    joinable = true;
    openSocket();

    bindSocket();

    networkLoopBool = true;
    netLoop = std::thread(&Pong::hostNetworkLoop, this);

    std::thread(&Pong::queueLoop, this).detach();

    currentScreen = &Pong::hostLobby;
    screen = false;

    me = 0;
}

void Pong::handleCloseLobby() {
    networkLoopBool = false;
    currentScreen = &Pong::mainMenu;
    screen = false;
    joinable = false;
    close(sockfd);

    if (netLoop.joinable()) {
        netLoop.join();
    }
}

void Pong::handleCopyCode() {
    sf::Clipboard::setString(ipToCode(myIP));
}

void Pong::handleStartGame() {

    addToQueue(SEND_START_GAME);

    if (buttons.size() < 5) {
        return;
    }
    screen = 0;
    currentScreen = &Pong::game;
}

void Pong::handleAttemptConnection() {
    std::cout << buttons[0].textBox.getString().toAnsiString().c_str()
        << std::endl;
    openSocket();
    join(buttons[0].textBox.getString().toAnsiString().c_str());
}

void Pong::addButton(int width, int height, int x, int y, std::string string, void (Pong::* func)()) {
    buttons.push_back(Button(width, height, x, y, string, &font));
    buttonsFunctions.push_back(func);
}

/* #endregion */

/* #region Pong object/whole game/miscelaneous */

Pong::Pong() {
#ifdef WIN32
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
#else
    font.loadFromFile("arial.ttf");
#endif
    window = new sf::RenderWindow(
        sf::VideoMode(std::max((int)width, 256), std::max((int)height, 144)),
        "pongLan", sf::Style::Titlebar | sf::Style::Close);

    window->setFramerateLimit(60);

    window->setPosition(sf::Vector2i(0, 0));
    window->setKeyRepeatEnabled(false);
}

Pong::~Pong() {}

void Pong::quitGame() {
    window->close();
    screen = false;
    running = false;
    networkLoopBool = false;
#ifdef WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif
    usleep(1000 * 1000);
}

int Pong::widthPercentToPos(int percent) {
    return (double)percent / 100 * width;
}

int Pong::heightPercentToPos(int percent) {
    return (double)percent / 100 * height;
}

int Pong::widthRelativeSize(int pos) { return (double)pos / 1920 * width; }

int Pong::heightRelativeSize(int pos) { return (double)pos / 1080 * height; }

void Pong::changeConf(std::string varaible, std::string value) {
    std::ifstream inConfFile(confFile.c_str());
    if (!std::ifstream(confFile)) {
        std::ofstream outConfFile(confFile.c_str());
        outConfFile << "connection=\nwidth=\nheight=\n" << std::flush;
        outConfFile.close();
        inConfFile.open(confFile.c_str());
    }
    std::vector<std::string> lines;
    for (std::string line; getline(inConfFile, line);) {
        std::cout << line << std::endl;
        lines.push_back(line);
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '=') {
                if (varaible == line.substr(0, i)) {
                    std::cout << varaible << std::endl;
                    std::cout << line.substr(0, i) << std::endl;
                    lines.pop_back();
                    lines.push_back(varaible + "=" + value);
                    break;
                }
            }
        }
    }
    inConfFile.close();
    std::ofstream outConfFile(confFile.c_str());
    for (int i = 0; i < lines.size(); i++) {
        outConfFile << lines[i] << std::endl;
    }
    outConfFile.close();
}

std::string Pong::getSubString(int start, std::string input, char stop) {
    for (int i = start; i < input.size(); i++) {
        if (input[i] == stop) {
            return input.substr(start, i);
        }
    }
    return "";
}

void Pong::mainLoop() {
    while (running) {
        screen = true;
        (this->*currentScreen)();
    }
}

void Pong::nothing() {}

/* #endregion */