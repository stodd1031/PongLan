#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <unordered_map>
#include <string.h>
#include <unistd.h>
#include <mutex>
#include <queue>
#include <condition_variable>


// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <net/if.h>
// #include <sys/ioctl.h>
// #include <array>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define MSG_CONFIRM 0
// #define MSG_WAITALL 0
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/param.h>
#include <sys/socket.h>
#endif

#include "ball.hpp"
#include "button.hpp"
#include "paddle.hpp"
#include "waitNotify.h"

//types
#define JOIN 1
#define CHARACTER_INFO 2
#define ACCEPT_JOIN 3
#define UPDATE 4
#define BALL_INFO 5
#define PING 6
#define PING_BACK 6

//updates
#define IMHERE 1
#define STARTGAME 2
#define HOSTSCORE 3
#define GUESTSCORE 4

#define BALL -2

//addToQueue values
#define SEND_BALL 0
#define SEND_PADDLE 1
#define SEND_CHANGE_BALL 2
#define SEND_HOST_SCORE 3
#define SEND_GUEST_SCORE 4
#define SEND_START_GAME 5
#define SEND_IM_HERE 6
#define SEND_PING 7
#define SEND_PING_BACK 8

#define PORT 8080
#define MAXLINE 1024

struct CharacterInfo
{
    char type;
    char who;
    int when;
    char xVel;
    char yVel;
    short xLoc;
    short yLoc;
};

struct Join
{
    char type;
    char who;
    char IP[8];
};

struct AcceptJoin
{
    char type;
    char who;
    char assign;
};

struct Update
{
    char type;
    char who;
    char update;
};

struct BallInfo
{
    char type;
    char who;
    char xVel;
    char yVel;
    short xLoc;
    short yLoc;
};

struct Ping
{
    char type;
    char who;
    unsigned long long hit;
};

union ReceivedInfo
{
    char type;
    char who;
    CharacterInfo characterInfo;
    Join join;
    AcceptJoin acceptJoin;
    Update update;
    BallInfo ballInfo;
    Ping ping;
};

class Pong
{
public:
    int count = 0;

    const unsigned int loopsSecond = 60;
    const unsigned int wait = 1000000 / loopsSecond;

    // relating to players/objects
    std::unordered_map<int, Paddle> whoToPaddle;
    std::unordered_map<int, std::string> whoToIP;
    int me = -1;

    // relating to overall program/miscelaneous
    bool running = true;
    bool joinable = false;

    Pong();
    ~Pong();
    void mainLoop();
    int widthRelativeSize(int pos);
    int heightRelativeSize(int pos);
    int widthPercentToPos(int percent);
    int heightPercentToPos(int percent);
    std::string getSubString(int start, std::string input, char stop);
    void quitGame();

    // relating to screen/display/output
    sf::RenderWindow* window;
    bool screen = true;
    unsigned short width = 1920;
    unsigned short height = 1020;
    void (Pong::* currentScreen)() = &Pong::mainMenu;
    sf::Font font;
    Paddle myPaddle;
    Paddle opponentPaddle;
    Ball ball;
    sf::Text opponentScore = sf::Text("0", font, 50);
    sf::Text myScore = sf::Text("0", font, 50);

    void game();
    void mainMenu();
    void guestLobby();
    void hostLobby();
    void settings();
    void enterCode();

    // relating to network
#ifdef WIN32
    WSADATA wsa;
    int len;
    SOCKET sockfd;
#else
    socklen_t len;
    int sockfd;
#endif

    int n;

    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
    std::string myIP;
    std::string hostIP;
    bool networkLoopBool = false;
    std::thread netLoop;
    std::queue<int> sendQueue;
    unsigned long long oneWayTrip = 0;
    unsigned long long advanceOfMe = 0;
    unsigned long long oneWayTripAverage = 0;
    unsigned long long advanceOfMeAverage = 0;

    waitNotify queueWN;

    waitNotify pingWN;
    std::thread pingThread;

    void addToQueue(int toAdd);
    std::string ipToCode(std::string IP_string);
    std::string codeToIP(const char IP_char[8]);
    ReceivedInfo recieve(struct sockaddr_in& addr);
    void send(ReceivedInfo& ri, struct sockaddr_in& addr);
    void guestNetworkLoop();
    void hostNetworkLoop();
    void queueLoop();
    void join(const char code[8]);
    void newConnection();
    void openSocket();
    void bindSocket();

    // relating to conf/settings
    std::string confFile = "conf.txt";
    void changeConf(std::string varaible, std::string value);

    // relating to button press
    std::vector<Button> buttons;
    std::vector<void (Pong::*)()> buttonsFunctions;
    void addButton(int width, int height, int x, int y, std::string string, void (Pong::* func)());
    void handleHostLobby();
    void handleCloseLobby();
    void handleJoinGame();
    void handleJoinGameFromEnterCode();
    void handleleaveLobby();
    void handleCopyCode();
    void handleAttemptConnection();
    void handleStartGame();
    void nothing();

    // Mutexs
    std::mutex buttonsMTX;
};