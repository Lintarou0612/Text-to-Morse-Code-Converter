#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;

// STRUCT VE CAC THUOC TINH
struct textMorse
{
    vector<string> SentencesList; // 1 dimention array of list of Sentences
    vector<string> MorseList;     // 1 dimention array of list of  Morsecode
    vector<string> ErrorsList;    // 1 dimention array of list of  ErrorsList
    int errorWords, successWords, wordCount;    // statistics
    int totalChar, convertedChar, nonConVertedChar;   // statistics
    double Duration;       
    string date, time, timeAndDate;    // time, date for statistic; timeAndDate for fileName of log file
    string FileIn, FileOut;         // name of input and output file
    textMorse()   // initial value
    {
        date = time = timeAndDate = "";
        Duration = 0;
        wordCount = successWords = errorWords = 0;
        totalChar = totalChar = nonConVertedChar = 0;
        FileIn = FileOut = "";
    }
};
typedef struct textMorse textMorse;
// // protocol
void transferMorse(string, textMorse &);
string ErrorTextToMorse(string, int);
void SaveStatistic(textMorse);

// Convert text char to morse code char
string TextToMorse(char c)
{
    switch (c)
    {
    case 'a':
        return ".-";
    case 'b':
        return "-...";
    case 'c':
        return "-.-.";
    case 'd':
        return "-..";
    case 'e':
        return ".";
    case 'f':
        return "..-.";
    case 'g':
        return "--.";
    case 'h':
        return "....";
    case 'i':
        return "..";
    case 'j':
        return ".---";
    case 'k':
        return "-.-";
    case 'l':
        return ".-..";
    case 'm':
        return "--";
    case 'n':
        return "-.";
    case 'o':
        return "---";
    case 'p':
        return ".--.";
    case 'q':
        return "--.-";
    case 'r':
        return ".-.";
    case 's':
        return "...";
    case 't':
        return "-";
    case 'u':
        return "..-";
    case 'v':
        return "...-";
    case 'w':
        return ".--";
    case 'x':
        return "-..-";
    case 'y':
        return "-.--";
    case 'z':
        return "--..";
    case '1':
        return ".----";
    case '2':
        return "..---";
    case '3':
        return "...--";
    case '4':
        return "....-";
    case '5':
        return ".....";
    case '6':
        return "-....";
    case '7':
        return "--...";
    case '8':
        return "---..";
    case '9':
        return "----.";
    case '0':
        return "-----";
    case '.':
        return ".-.-.-";
    case ',':
        return "--..--";
    case ':':
        return "---...";
    case '?':
        return "..--..";
    case '/':
        return "-..-.";
    case '-':
        return "-....-";
    case '(':
        return "-----";
    case ')':
        return "-----";
    case '\"':
        return "-----";
    case '=':
        return "-----";
    case '+':
        return "-----";
    case '*':
        return "-----";
    case '@':
        return "-----";
    }
    return "#";
} // them truong hop vao nhe !!
//====================================================================================================================
// Ham kiem tra file da ton tai chua
bool checkFileExist(string inFile)
{
    ifstream f;
    f.open(inFile.c_str(), ios ::in);
    if (f.is_open())
        return true;
    else
        return false;
}
//===
//========================================TASK1----CHINH SUA DU LIEU VAO========================================================
// LowerCase a string
string lowerCase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ' && s[i] >= 65 && s[i] <= 90)
            s[i] = s[i] + 32;
    }
    return s;
}
//====================================================================================================================
// Tra ve dang dung cua so. VD: 01, 02, 03,.....
string returnLineNumber(int LineNumber)
{
    string temp = to_string(LineNumber);
    if (LineNumber < 10)
        temp = "0" + temp;
    return temp;
}
//=================================================================================================================
// Lay du lieu va gep vao thanh 1 string
void getData(vector<string> &str, string fileName)
{
    ifstream file;
    string temp = "";
    file.open(fileName.c_str(), ios::in);
    while (!file.eof())
    {
        // read every character from file
        getline(file, temp, '\n');
        if (temp != "")
            str.push_back(temp);
    }
    file.close();
}
//====================================================================================================================
// Loai bo dau space thua, chi de lai 1 dau space giua cac chu
string removeExtraSpaces(string s)
{
    string str;
    bool spaceFound = 0;
    int j = -1;
    while (++j < s.length() && s[j] == ' ')
        ; // chay het nhung dau cach dau tien
    for (int i = j; i < s.length(); i++)
    {
        if (s[i] != ' ')
        {
            str.push_back(s[i]);
            spaceFound = 0;
        }
        else if (s[i] == ' ' && spaceFound == 0)
        {
            str.push_back(s[i]);
            spaceFound = 1;
        }
    }
    if (str[str.length() - 1] == ' ')
        str.pop_back();
    return str;
}
//================================================TASK2---TIME====================================================================
// TRA VE CAU TRUC NGAY GIO NAM
const string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80] = {};
    tstruct = *localtime(&now);
    char Year[11], Month[11], Day[11], Time[11];
    strftime(Year, 11, "%Y-", &tstruct);
    strcat(buf, Year);
    strftime(Month, 11, "%m", &tstruct);

    switch (1 + tstruct.tm_mon)
    {
    case (1):
        strcat(buf, "Jan");
        break;
    case (2):
        strcat(buf, "Feb");
        break;
    case (3):
        strcat(buf, "Mar");
        break;
    case (4):
        strcat(buf, "Apr");
        break;
    case (5):
        strcat(buf, "May");
        break;
    case (6):
        strcat(buf, "Jun");
        break;
    case (7):
        strcat(buf, "Jul");
        break;
    case (8):
        strcat(buf, "Aug");
        break;
    case (9):
        strcat(buf, "Sep");
        break;
    case (10):
        strcat(buf, "Oct");
        break;
    case (11):
        strcat(buf, "Nov");
        break;
    case (12):
        strcat(buf, "Dec");
        break;
    }
    strftime(Day, 11, "-%d", &tstruct);
    strcat(buf, Day);
    strftime(Time, 11, " %H:%M:%S", &tstruct);
    strcat(buf, Time);
    return buf;
}
//================================================================================================
// Lay time hien tai ==>>>>> lam ten file log
const string getDateName()
{

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct);

    return buf;
}
//========== Time
const string getTimeName()
{
    struct tm *ptr;

    time_t t;

    t = time(NULL);

    ptr = localtime(&t);

    return returnLineNumber(ptr->tm_hour) + returnLineNumber(ptr->tm_min) + returnLineNumber((ptr->tm_sec));
}

//===========================================TASK3--MORSE TO TEXT--=========================================================
// Convert Morse string to text char
char MoreToText(string A)
{
    if (A.length() > 7)
        return '#';
    if (A == ".-")
        return 'a';
    if (A == "-...")
        return 'b';
    if (A == ".-.-.-")
        return '.';
    if (A == "-.-.")
        return 'c';
    if (A == "--..--")
        return ',';
    if (A == "-..")
        return 'd';
    if (A == "---...")
        return ':';
    if (A == ".")
        return 'e';
    if (A == "..--..")
        return '?';
    if (A == "..-.")
        return 'f';
    if (A == ".----.")
        return '\'';
    if (A == "--.")
        return 'g';
    if (A == "-....-")
        return '-';
    if (A == "....")
        return 'h';
    if (A == "-..-.")
        return '/';
    if (A == "..")
        return 'i';
    if (A == "-.--.")
        return '(';
    if (A == ".---")
        return 'j';
    if (A == "-.--.-")
        return ')';
    if (A == "-.-")
        return 'k';
    if (A == ".-..-.")
        return '"';
    if (A == ".-..")
        return 'l';
    if (A == "-...-")
        return '=';
    if (A == "--")
        return 'm';
    if (A == "-...")
        return '+';
    if (A == "-.")
        return 'n';
    if (A == ".--.-.")
        return '@';
    if (A == "---")
        return 'o';
    if (A == ".--.")
        return 'p';
    if (A == "--.-")
        return 'q';
    if (A == ".-.")
        return 'r';
    if (A == "...")
        return 's';
    if (A == "-")
        return 't';
    if (A == "..-")
        return 'u';
    if (A == "...-")
        return 'v';
    if (A == ".--")
        return 'w';
    if (A == "-..-")
        return 'x';
    if (A == "-.--")
        return 'y';
    if (A == "--..")
        return 'z';
    if (A == ".----")
        return '1';
    if (A == "..---")
        return '2';
    if (A == "...--")
        return '3';
    if (A == "....-")
        return '4';
    if (A == ".....")
        return '5';
    if (A == "-....")
        return '6';
    if (A == "--...")
        return '7';
    if (A == "---..")
        return '8';
    if (A == "----.")
        return '9';
    if (A == "-----")
        return '0';
    if (A == ".-.-.-")
        return '.';
    if (A == "--..--")
        return ',';
    if (A == "---...")
        return ':';
    if (A == "..--..")
        return '?';
    if (A == ".----.")
        return '\'';
    if (A == "-....-")
        return '-';
    if (A == "-..-.")
        return '/';
    if (A == "-.--.")
        return '(';
    if (A == "-.--.-")
        return ')';
    if (A == ".-..-.")
        return '\"';
    if (A == "-...-")
        return '=';
    if (A == ".-.-.")
        return '+';
    if (A == "-..-")
        return '*';
    if (A == ".--.-.")
        return '@';
    else
        return '*';
}
//====================================================================================================================
// Tra ve vi tri ky tu sai trong khi chuyen ma Morse
string ErrorMorseToText(string morseCode, int lineNumber)
{
    string temp = "";
    // “Error AB: Invalid Morse code CODE on line XX.”
    temp.append("Error 07: Invalid Morse code ");
    temp.append(morseCode); // morseCode la thang bi sai
    temp.append(" on line ");
    temp.append(returnLineNumber(lineNumber));
    return temp;
}
//====================================================================================================================
// func transfer text to morse, wordcount, charcount
void transferText(string FileIn, textMorse &textCode)
{
    clock_t startTime = clock();
    int space = 0, previousIndex = 0, spaceCheck = 1, errorChar = 0, line = 0;
    string morsecode = "";
    string temp = "";
    getData(textCode.SentencesList, FileIn);

    for (int i = 0; i < textCode.SentencesList.size(); i++)
    {
        line++;
        temp = "";
        previousIndex = 0;
        textCode.SentencesList[i] = lowerCase(textCode.SentencesList[i]);
        textCode.SentencesList[i] = removeExtraSpaces(textCode.SentencesList[i]);
        for (int j = 0; j < textCode.SentencesList[i].length(); j++)
        {
            if (textCode.SentencesList[i][j] == ' ')
            {
                temp.push_back('/');
                temp.push_back(' ');
                space++;
                spaceCheck = 1;
            }
            else
            {
                textCode.totalChar++;
                morsecode = TextToMorse(textCode.SentencesList[i][j]);
                string charSentence = "";
                charSentence.push_back(textCode.SentencesList[i][j]);
                if (morsecode == "#")
                {
                    if (spaceCheck == 1)
                    {
                        textCode.errorWords++;
                        spaceCheck = 0;
                    }
                    textCode.nonConVertedChar++; // char khong convert duoc
                    temp.push_back('#');
                    temp.push_back(' ');
                    textCode.ErrorsList.push_back(ErrorTextToMorse(charSentence, line));
                }

                else
                {
                    temp.append(morsecode);
                    temp.push_back(' ');
                }
            }
            // sang 1 line moi
        }
        spaceCheck = 1;
        space++; // sau moi dong cong them 1 dau cach
        textCode.MorseList.push_back(temp);
    }
    textCode.convertedChar = textCode.totalChar - textCode.nonConVertedChar;
    textCode.wordCount = space; // bang tong so dau cach, ben tren da cong vao dau cach cuoi cung
    textCode.successWords = textCode.wordCount - textCode.errorWords;
    textCode.timeAndDate = currentDateTime();
    textCode.Duration = (double)(clock() * 15 - startTime) / CLOCKS_PER_SEC;
    textCode.date = getDateName();
    textCode.time = getTimeName();
}
// ================================================================================================
// lUU DU LIEU DA CHUYEN SANG TEXT VAO 1 FILE
void saveDataMorseToText(textMorse textCode)
{
    ofstream Fileout;
    Fileout.open(textCode.FileOut.c_str(), ios::trunc);
    for (int i = 0; i < textCode.SentencesList.size(); i++)
        Fileout << textCode.SentencesList[i] << endl;
    for (int i = 0; i < textCode.ErrorsList.size(); i++)
        Fileout << textCode.ErrorsList[i] << endl;
}
// IN TEXT
void PrintMorseToText(string FileIn, string FileOut)
{
    textMorse textCode;
    textCode.FileOut = FileOut;
    transferMorse(FileIn, textCode);
    for (int i = 0; i < textCode.SentencesList.size(); i++)
        cout << textCode.SentencesList[i] << endl;
    for (int i = 0; i < textCode.ErrorsList.size(); i++)
        cout << textCode.ErrorsList[i] << endl;
    if (!checkFileExist(FileOut))
        saveDataMorseToText(textCode);
    else
    {
        cout << "\nWarning: " << FileOut << " already exists. Do you wish to overwrite (y, n)? ";
        char c = _getch();
        cout << c;
        if (c == 'y' || c == 'Y')
        {
            saveDataMorseToText(textCode);
            cout << "\nSaving successfully!" << '\n';
        }
        else if (c == 'n' || c == 'N')
            cout << "\nNothing has been done!" << endl;
        else
            cout << "\nWrong choice" << endl;
        return;
    }
}
//================================================================================================
// IN RA THONG KE LOI KHI CHUYeN TU MORSE SANG TEXT
void statisticMorseToText(string FileIn, string FileOut)
{
    textMorse textCode;
    textCode.FileOut = FileOut;
    textCode.FileIn = FileIn;
    transferMorse(FileIn, textCode);
    cout << "Input file: " << textCode.FileIn;
    cout << "\nOutput file: " << textCode.FileOut;
    cout << "\nTime complete: " << textCode.timeAndDate; // viet ham bieu dien timeanđate
    cout << "\nDuration [seconds]: " << textCode.Duration;
    cout << "\nWord count in input file: " << textCode.wordCount;
    cout << "\nWord converted: " << textCode.successWords;
    cout << "\nTotal number of characters: " << textCode.totalChar;
    cout << "\nNumber of characters have been converted: " << textCode.convertedChar;
    cout << "\nNumber of characters are NOT converted: " << textCode.nonConVertedChar << endl;
    textCode.FileIn = FileIn;
    textCode.FileOut = FileOut;
    SaveStatistic(textCode);
}
// cut phan extention cua ten file de cho vao file log
string cutExtention(string fileName)
{
    string afterCut = "";
    int i = 0;
    while (true)
    {
        if (fileName[i] == '.')
            break;
        afterCut.push_back(fileName[i]);
        i++;
    }
    return afterCut;
}
// Tao file LOG
void SaveStatistic(textMorse TextAndMorse)
{
    string FileLogName = cutExtention(TextAndMorse.FileIn) + "_" + cutExtention(TextAndMorse.FileOut) + "_" + TextAndMorse.date + "_" + TextAndMorse.time + ".log"; // sửa time date
    ofstream FileOut;
    FileOut.open(FileLogName.c_str(), ios::out);
    FileOut << "Input file: " << TextAndMorse.FileIn;
    FileOut << "\nOutput file: " << TextAndMorse.FileOut;
    FileOut << "\nTime complete: " << TextAndMorse.timeAndDate; // viet ham bieu dien timeanđate
    FileOut << "\nDuration [seconds]: " << TextAndMorse.Duration;
    FileOut << "\nWord count in input file: " << TextAndMorse.wordCount;
    FileOut << "\nWord converted: " << TextAndMorse.successWords;
    FileOut << "\nTotal number of characters: " << TextAndMorse.totalChar;
    FileOut << "\nNumber of characters have been converted: " << TextAndMorse.convertedChar;
    FileOut << "\nNumber of characters are NOT converted: " << TextAndMorse.nonConVertedChar <<endl;
    for (int i = 0; i < TextAndMorse.SentencesList.size(); i++)
        FileOut << TextAndMorse.SentencesList[i] << endl;
    for (int i = 0; i < TextAndMorse.ErrorsList.size(); i++)
        FileOut << TextAndMorse.ErrorsList[i] << endl;
}

//===============================================TASK 4-----TEXT-TO-MORSE=====================================================
// Tra ve vi tri ky tu sai trong khi chuyen ma Text
string ErrorTextToMorse(string c, int line)
{
    string temp = "";
    // “Error AB: Unrecognized character C on line XX.”
    temp.append("Error 06: Unrecognized character ");
    temp.append(c); // morseCode la thang bi sai
    temp.append(" on line ");
    temp.append(returnLineNumber(line));
    return temp;
}
//====================================================================================================================
// func transfer MORSE to TEXT, wordcount, charcount,...
void transferMorse(string FileIn, textMorse &morseCode)
{
    clock_t startTime = clock();
    getData(morseCode.MorseList, FileIn); // lay du lieu nhieu dong da duoc nen lai thanh 1 dong
    int previousIndex = 0, spaceFound = 1;
    string temp = "";
    string subString = "";
    int line = 0;
    for (int i = 0; i < morseCode.MorseList.size(); i++)
    {
        morseCode.MorseList[i] = removeExtraSpaces(morseCode.MorseList[i]);
        morseCode.MorseList[i].push_back(' ');
        for (int j = 0; j < morseCode.MorseList[i].length(); j++)
        {
            if (morseCode.MorseList[i][j] == '/')
            {
                temp.push_back(' ');
                j += 1;
                previousIndex = j + 1;
                spaceFound = 1;
                morseCode.wordCount++;
                continue;
            }
            if (morseCode.MorseList[i][j] == ' ')
            {
                subString = morseCode.MorseList[i].substr(previousIndex, j - previousIndex); // cat 1 string tu vi tri sau dau cach truoc den truoc dau cach nay
                char cutCode = MoreToText(subString);
                morseCode.totalChar++; // moi dau space se cho 1 char
                if (cutCode == '#' || cutCode == '*')
                {
                    if (spaceFound == 1)
                    {
                        morseCode.errorWords++;
                        spaceFound = 0;
                    }
                    morseCode.nonConVertedChar++;
                    morseCode.ErrorsList.push_back(ErrorMorseToText(subString, line + 1));
                }
                temp.push_back(cutCode);
                previousIndex = j + 1;
            }
        }
        previousIndex = 0;
        line++;
        spaceFound = 1; // sang 1 line moi
        morseCode.SentencesList.push_back(temp);
        temp = "";
    }
    morseCode.wordCount = morseCode.wordCount + line; // so tu bang so space cong so dong, de dem duoc chu cuoi dong
    morseCode.successWords = morseCode.wordCount - morseCode.errorWords;
    morseCode.totalChar = morseCode.totalChar;
    morseCode.convertedChar = morseCode.totalChar - morseCode.nonConVertedChar;
    morseCode.timeAndDate = currentDateTime();
    clock_t endTime = (double)(clock()*15 - startTime) / CLOCKS_PER_SEC;
    morseCode.Duration = endTime;
    morseCode.date = getDateName();
    morseCode.time = getTimeName();
    morseCode.FileIn = FileIn;
}
//===================================================================================================================
// lUU DU LIEU DA CHUYEN SANG TEXT VAO 1 FILE
void saveDataTextToMorse(textMorse textCode)
{
    ofstream FileOut;
    FileOut.open(textCode.FileOut.c_str(), ios::trunc);
    for (int i = 0; i < textCode.MorseList.size(); i++)
        FileOut << textCode.MorseList[i] << endl;
    for (int i = 0; i < textCode.ErrorsList.size(); i++)
        FileOut << textCode.ErrorsList[i] << endl;
}
//===================================================================================================================
// IN MORSE
void PrintTextToMorse(string FileIn, string FileOut)
{
    textMorse textCode;
    textCode.FileOut = FileOut;
    transferText(FileIn, textCode);
    for (int i = 0; i < textCode.MorseList.size(); i++)
        cout << textCode.MorseList[i] << endl;
    for (int i = 0; i < textCode.ErrorsList.size(); i++)
        cout << textCode.ErrorsList[i] << endl;
    if (!checkFileExist(FileOut))
        saveDataTextToMorse(textCode);
    else
    {
        cout << "\nWarning: " << FileOut << " already exists. Do you wish to overwrite (y, n)? ";
        char c = _getch();
        cout << c;
        if (c == 'y' || c == 'Y')
        {
            saveDataTextToMorse(textCode);
            cout << "\nSaving successfully!" << '\n';
        }
        else if (c == 'n' || c == 'N')
            cout << "\nNothing has been done!" << endl;
        else
            cout << "\nWrong choice" << endl;
        return;
    }
}
//================================================================================================
// IN RA THONG KE LOI KHI CHUYEN TU TEXT SANG MORSE
void statisticTextToMorse(string FileIn, string FileOut)
{
    textMorse textCode;
    textCode.FileOut = FileOut;
    textCode.FileIn = FileIn;
    transferText(FileIn, textCode);
    cout << "\nInput file: " << textCode.FileIn;
    cout << "\nOutput file: " << textCode.FileOut;
    cout << "\nTime complete: " << textCode.timeAndDate; // viet ham bieu dien timeanđate
    cout << "\nDuration [seconds]: " << textCode.Duration;
    cout << "\nWord count in input file: " << textCode.wordCount;
    cout << "\nWord converted: " << textCode.successWords;
    cout << "\nWord with errors: " << textCode.errorWords;
    cout << "\nTotal number of characters: " << textCode.totalChar;
    cout << "\nNumber of characters have been converted: " << textCode.convertedChar;
    cout << "\nNumber of characters are NOT converted: " << textCode.nonConVertedChar << endl;
    textCode.FileIn = FileIn;
    textCode.FileOut = FileOut;
    SaveStatistic(textCode);
}
//============================================TASK 5------FILE========================================================================
// HUONG DAN NGUOI DUNG
void readme()
{
    cout << "                                          INSTRUCTION\n\n"
         << "To get help, usage: morse -h\n"
         << "Note: The instruction on the screen is also saved in a file name readme.txt\n"
         << "you can check it!\n\n"
         << "You must follow format command to use below optional commands:\n"
         << "    morse <inputFileName> <outputFileName> <yourCommand>\n\n"
         << "A few optional commands, you can use:\n\n"
         << "-t : To order the program to take the input file as a text file\n"
         << "and produce the output file as the Morse code one.\n\n"
         << "-m : To order the program to take the input file as a Morse-code file\n"
         << " and produce the output file as the interpreted text file.\n\n"
         << "-c : To print the statistics of the successful conversion to the screen.\n"
         << "It is also saved in file .log. Check it!\n\n"
         << "Some errors can be occurred:\n\n"
         << "Error 01: Unrecognized command. Type \"morse -h\" for help\n"
         << "Error 02: Unknown command. Type \"morse -h\" for help\n"
         << "Error 03: Your input file could not be opened.\n"
         << "Error 04: Invalid FileName. Your input file and output file must have different name.\n"
         << "Error 05: Missing Arguments. Type \"morse -h\" for help\n"
         << "Error 06: Unrecognized character C on line XX.\n"
         << "Error 07: Invalid Morse code CODE on line XX.\n";
    ofstream helpFile("readme.txt", ios::trunc);
    helpFile << "                                          INSTRUCTION\n\n"
             << "To get help, usage: morse -h\n"
             << "Note: The instruction on the screen is also saved in a file name readme.txt\n"
             << "you can check it!\n\n"
             << "You must follow format command to use below optional commands:\n"
             << "    morse <inputFileName> <outputFileName> <yourCommand>\n\n"
             << "A few optional commands, you can use:\n\n"
             << "-t : To order the program to take the input file as a text file\n"
             << "and produce the output file as the Morse code one.\n\n"
             << "-m : To order the program to take the input file as a Morse-code file\n"
             << " and produce the output file as the interpreted text file.\n\n"
             << "-c : To print the statistics of the successful conversion to the screen.\n"
             << "It is also saved in file .log. Check it!\n\n"
             << "Some errors can be occurred:\n\n"
             << "Error 01: Unrecognized command. Type \"morse -h\" for help\n"
             << "Error 02: Unknown command. Type \"morse -h\" for help\n"
             << "Error 03: Your input file could not be opened.\n"
             << "Error 04: Invalid FileName. Your input file and output file must have different name.\n"
             << "Error 05: Missing Arguments. Type \"morse -h\" for help\n"
             << "Error 06: Unrecognized character C on line XX.\n"
             << "Error 07: Invalid Morse code CODE on line XX.\n";
}
//================================================================================================
// KIEM TRA TEN FILE DA TON TAI
bool checkSameFileName(string &inFile, string &outFile)
{
    if (inFile == outFile)
        return true;
    else
        return false;
}
//================================================================================================
// KIEM TRA CO PHAI FILE MORSE KHONG
bool isMorseInputFile(string File)
{
    vector<string> str;
    getData(str, File);
    for (int i = 0; i < str.size(); ++i)
        for (int j = 0; j < str[i].length(); ++j)
            if ((str[i][j] != ' ') & (str[i][j] != '/') & (str[i][j] != '-') & (str[i][j] != '.'))
                return false;
    return true;
}
//================================================================================================
// HAM LAY TEN FILE
string fileName(string inFile)
{
    ifstream f;
    f.open(inFile.c_str());
    return inFile;
}
//================================================================================================
// KIEM TRA DA NHAP DUNG TEN FILE CHUA
bool checkArgument(string File)
{
    string temp = "";
    for (int i = File.length() - 1; i >= 0; --i)
    {
        temp.push_back(File[i]);
        if (File[i] == '.')
            break;
    }
    if (temp == "txt.")
        return true;
    else
        return false;
}
//================================================================================================
// create function to get commands from user
int optionCommand(int argc, char *argv[])
{
    // morse <inputFileName> <outputFileName> <yourCommand>
    if (argc == 1)
        return -1; // Error 01
    if (argc > 4)
        return -2; // Error 02

    string cmd[4];
    for (int i = 0; i < argc; i++)
        cmd[i].append(argv[i]);
    if (argc == 2)
        if (cmd[1] == "-h")
            return 1; // Read help-file readme.txt
        else
            return -2; // Error 02

    if (argc == 3)
    {
        //check input file
        if (!checkFileExist(argv[1]))
            return -3; //Error 03
        if (checkSameFileName(cmd[1], cmd[2]))
            return -4; // Error 04
        if (!checkArgument(argv[2]))
            return -5; // Error 05
        if (isMorseInputFile(argv[1]))
            return 5; //statistic morse -> text
        else
            return 4; //statistic text -> morse
    }

    if (argc == 4)
    {
        if (checkSameFileName(cmd[1], cmd[2]))
            return -4; // Error 04
        if (!checkFileExist(argv[1]))
            return -3; // error 03 ko mo dc
        if (!checkArgument(argv[2]))
            return -5; // Error 05
        if (!strcmp(argv[3], "-t"))
            return 2; // print text -> morse
        if (!strcmp(argv[3], "-m"))
            return 3; // print morse -> text
        if (!strcmp(argv[3], "-c"))
        {
            if (isMorseInputFile(argv[1]))
                return 5; // -c morse to text
            else
                return 4; // -c text to morse
        }
    }
    return 0;
}
//================================================================================================
int main(int argc, char *argv[])
{
    switch (optionCommand(argc, argv))
    {
    case -1:
        cout << "Error 01: Unrecognized command. Type \"morse -h\" for help" << endl;
        break;
    case -2:
        cout << "Error 02: Unknown command. Type \"morse -h\" for help" << endl;
        break;
    case -3:
        cout << "Error 03: Your inputfile "
             << "\"" << fileName(argv[1]) << "\""
             << " could not be opened." << endl;
        break;
    case -4:
        cout << "Error 04: Invalid FileName. Your input file and output file must have different name." << endl;
        break;
    case -5:
        cout << "Error 05: Missing Arguments. Type \"morse -h\" for help" << endl;
        break;
    case 1:
        readme();
        break;
    case 2:
        PrintTextToMorse(argv[1], argv[2]);
        break;
    case 3:
        PrintMorseToText(argv[1], argv[2]);
        break;
    case 4:
        statisticTextToMorse(argv[1], argv[2]);
        PrintTextToMorse(argv[1], argv[2]);
        break;
    case 5:
        statisticMorseToText(argv[1], argv[2]);
        PrintMorseToText(argv[1], argv[2]);
        break;
    }
}
