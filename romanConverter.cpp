#include <iostream>
#include <string>
#include <map>

bool getInput(int &integers, std::string &roman);
int romanToInt(std::string numerals);
std::string intToRoman(int n);
std::string checkLargest(int &n);

/*main:
 * Main doesn't do much here. It declares the integers, type, and roman variables, and then has a loop that runs getInput until it returns -1.
 */
int main(){
    int integers;
    std::string roman;
    int type;
    std::cout << "Roman numeral converter." << std::endl;
    do{
        type = getInput(integers, roman);
        std::cout << std::endl;
    } while(type); //Until the user enters an invalid integer, or enters "3" to quit.

    return 0;
}

/* getInput:
 * This function uses a switch statement to create a menu. It takes input to find the type of conversion the user wants, and then takes input
 * to get the appropriate string or integer. It then calls the appropriate function and outputs the converted string or integer. It returns true if the user
 * wanted to convert something (so the loop in main is repeated) or false if the user wants to quit or gives an invalid integer as an input.
 * 
 * INPUT SANITIZATION: If I had more time, I would implement error checking to make sure the input is valid. I kept running into bugs and I don't have enough time
 * to get it working.
 */
bool getInput(int &integers, std::string &roman){
    int type = 0;
    std::cout << "Enter 1 to convert integers to Roman numerals, 2 to convert Roman numerals to integers, or 3 to quit." << std::endl;
    std::cin >> type; //gets input from the user
    std::cout << std::endl;

    switch(type){ //Depending on user input, sets "integers" or "numerals" equal to the input, and then sets the other using the appropriate function.
        case 1:
            std::cout << "Enter integer to convert: ";
            std::cin >> integers;
            std::cout << std::endl;
            roman = intToRoman(integers);
            std::cout << integers << " converted to Roman numerals is: " << roman << std::endl;
            return true;
        case 2:
            std::cout << "Enter numeral to convert: ";
            std::cin >> roman;
            std::cout << std::endl;
            integers = romanToInt(roman);
            std::cout << roman << " converted to Roman numerals is: " << integers << std::endl;
            return true;
        case 3:
            return false;
    }
    return false;
}


/*romanToInt:
 * This function uses a map to assign numerals in a string to their appropriate value. Each character is found in the map, and
 * if it's smaller than the character following it, it should be subtracted from the total. If it's bigger or equal, we add it
 * to the total. Once we reach the end of the string, we add the last character and return the total.
 */
int romanToInt(std::string numerals){
    std::map<char, int>romMap;
    romMap['M'] = 1000;
    romMap['D'] = 500;
    romMap['C'] = 100;
    romMap['L'] = 50;
    romMap['X'] = 10;
    romMap['V'] = 5;
    romMap['I'] = 1;

    int total = 0;
    for(int i = 0; i < numerals.length(); i++){ //For each character in the input string
        char currentChar = numerals[i]; //The current character in the input string
        char nextChar = numerals[i + 1]; //The next character in the input string
        if(i + 1 == numerals.length()){ //If the next character is past the end, our current character is the last and we can just add it to the total and return it.
            total += romMap[currentChar];
            return total;
        }
        if(romMap[currentChar] > romMap[nextChar]){ //If the current character is bigger than or equal to the next character, we can just add it to the running total.
            total += romMap[currentChar];
        }
        else if(romMap[currentChar] < romMap[nextChar]){ //If the current character is smaller than the next character, the subtractive notation part of roman numerals comes into play. We can deal with this by subtracting the current character from the total, since the next character will always be bigger than the one after that, if it is a valid Roman numeral.
            total -= romMap[currentChar];
        }
        if(romMap[currentChar] == romMap[nextChar]){
            total += romMap[currentChar];
        }
    }
    return -1; //this should never be triggered.
}

/* intToRoman:
 * This function will keep subtracting the value of the biggest possible Roman numeral(s) from the input
 * string (and add that/those Roman numeral(s) to the returning string) until we reach 0. Then, we return the resulting string.
 */
std::string intToRoman(int n){
    std::string str;
    while(n != 0){
        str += checkLargest(n);
    }

    return str;
}

/* checkLargest:
 * This function uses two arrays, holding strings of Roman numerals and values of those numerals. There are only 6 valid
 * instances of subtractive notation for Roman numerals, so I just added those strings to the arrays. This function returns the
 * string of Roman numeral(s) associated with the largest value smaller than the input integer. If I had more time, I would
 * change the map used in the romanToInt function to accept strings instead of just characters, so I could reuse it here,
 * but I kept running into errors.
*/
std::string checkLargest(int &n){
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    std::string numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    for(int i = 0; i < 13; i++){
        if(n >= values[i]){
            n-=values[i];
            return numerals[i];
        }
    }
    return "error"; //This should never be triggered
}