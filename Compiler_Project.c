#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// Utility function to remove newline characters from strings
void removeNewline(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}


// 1. Show the string
void showString(char *str) {
    printf("The input string is: %s\n", str);
}


// 2. Tokenize the string
void tokenizeString(char *str) {
    char temp[1000];
    strcpy(temp, str);  // Copy to avoid modifying the original string
    char *token = strtok(temp, " ");
    printf("Tokens:\n");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}


// 3. Count articles
bool isArticle(char *word) {
    return (strcmp(word, "a") == 0 || strcmp(word, "an") == 0 || strcmp(word, "the") == 0);
}


void countArticles(char *str) {
    char temp[1000];
    strcpy(temp, str);
    int count = 0;
    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (isArticle(token)) {
            count++;
        }
        token = strtok(NULL, " ");
    }
    printf("Number of articles: %d\n", count);
}


// 4. Count auxiliary verbs
bool isAuxiliaryVerb(char *word) {
    const char *auxVerbs[] = {"am","Am","is","Is","are","Are","was","Was","were","Were","been","have","Have"
 ,"Has","has","Had","had","Shall","shall","Will","will","can","Can","Could","could","Would","would","May","may","Might","might"};
    for (int i = 0; i < sizeof(auxVerbs) / sizeof(auxVerbs[0]); i++) {
        if (strcmp(word, auxVerbs[i]) == 0) return true;
    }
    return false;
}


void countAuxiliaryVerbs(char *str) {
    char temp[1000];
    strcpy(temp, str);
    int count = 0;
    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (isAuxiliaryVerb(token)) {
            count++;
        }
        token = strtok(NULL, " ");
    }
    printf("Number of auxiliary verbs: %d\n", count);
}


// 5. Count prepositions
bool isPreposition(char *word) {
    const char *prepositions[] = {"about", "above", "across", "after", "against", "along", "among", "around",
    "as", "at", "before", "behind", "between", "by", "during","except","for" ,"from","in","like","next","of",
    "on","over","past","than","through","to","until","up","with","within"};
    for (int i = 0; i < sizeof(prepositions) / sizeof(prepositions[0]); i++) {
        if (strcmp(word, prepositions[i]) == 0) return true;
    }
    return false;
}


void countPrepositions(char *str) {
    char temp[200];
    strcpy(temp, str);
    int count = 0;
    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (isPreposition(token)) {
            count++;
        }
        token = strtok(NULL, " ");
    }
    printf("Number of prepositions: %d\n", count);
}


// 6. Remove extra spaces
void removeExtraSpaces(char *str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (!(isspace(str[i]) && isspace(str[i + 1]))) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    printf("String after removing extra spaces: %s\n", str);
}


// 7 & 8. Check valid and invalid identifiers
bool isValidIdentifier(char *str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return false;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return false;
    }
    return true;
}


// 9. Count strong/weak verbs (using "strong" list as example)
bool isStrongVerb(char *word) {
    const char *strongVerbs[] = {
  "be", "become", "begin", "choose", "do", "draw", "eat","beat", "beaten", "become", "became", "begin", "began", "begun", "bend", "bent", "bet", "bid", "bite", "bit", "bitten", "blow", "blew", "blown","break", "broke", "broken", "bring", "brought", "build", "built",
  "burn", "burned", "burnt", "burnt", "buy", "bought", "bought", "works", "runs", "catch", "caught", "caught", "choose", "chose", "chosen", "come", "came", "cost", "cost", "cost", "cut", "cut", "cut", "dig", "dug", "dive", "work", "sits", "dove", "dived", "do", "did",
  "done", "draw", "drew", "dream", "dreamt", "dreamed", "drive", "drove", "driven", "drink", "drank", "drunk", "eat", "eats", "ate", "eaten", "fall", "fell", "fallen", "feel", "felt", "felt", "fight", "fought", "fought", "find", "found", "found", "fly", "flew", "flown",
  "holds", "forget", "forgot", "forgotten", "forgive", "forgave", "forgiven", "freeze", "froze", "frozen", "get", "got", "gotten", "give", "gave", "given", "rises", "go", "went", "gone", "grow", "hang", "hung", "hear", "heard", "hide", "hid", "hidden", "hit", "hold", "held",
  "hurt", "keep", "bets", "bits", "blows", "loses", "kept", "know", "knew", "known", "lay", "laid", "laid", "lead", "led", "leave", "left", "lend", "lent", "let", "lie", "lay", "lain", "lose", "brings", "solve", "lost", "make", "made", "mean", "meant", "meet", "met", "pay",
  "paid", "put", "read", "ride", "rode", "ridden", "ring", "rang", "rung", "rise", "love", "solved", "rose", "risen", "ran", "run", "say", "said", "see", "saw", "seen", "sell", "sold", "send", "sent", "show", "showed", "shown", "shut", "sing", "loves", "solves", "sang", "sung",
  "sit", "sat", "sleep", "slept", "speak", "spoke", "spoken", "spend", "spent", "stand", "stood", "swim", "swam", "swum", "take", "loved", "took", "taken", "teach", "taught", "tear", "tore", "torn", "tell","told", "told", "think", "thought", "throw", "threw", "thrown","understand",
  "brings","understood", "wake", "woke", "woken", "wear", "wore", "worn", "win", "won", "won", "write", "wrote","written", "comes", "writes", "meets", "feels", "leaves", "shows", "forgets", "goes", "eats", "means", "tears", "sleeps", "teaches", "wins", "tells", "drives", "breaks",
  "becomes", "builds", "burns", "comes", "falls", "does","forgets", "draws", "sings", "fights", "dreams", "catches", "lays", "blows", "costs", "cuts", "buys", "drinks", "hears", "chooses", "gets", "wears", "makes", "knows"
};
    for (int i = 0; i < sizeof(strongVerbs) / sizeof(strongVerbs[0]); i++) {
        if (strcmp(word, strongVerbs[i]) == 0) return true;
    }
    return false;
}


void countStrongVerbs(char *str) {
    char temp[200];
    strcpy(temp, str);
    int count = 0;
    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (isStrongVerb(token)) {
            count++;
        }
        token = strtok(NULL, " ");
    }
    printf("Number of strong verbs: %d\n", count);
}


// 10. Count vowels, consonants, digits, whitespace, and words
void countCharacters(char *str) {
    int vowels = 0, consonants = 0, digits = 0, spaces = 0, words = 0;
    bool inWord = false;
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') vowels++;
        else if (isalpha(ch)) consonants++;
        else if (isdigit(ch)) digits++;
        else if (isspace(ch)) spaces++;
        if (!isspace(ch) && !inWord) {
            words++;
            inWord = true;
        } else if (isspace(ch)) {
            inWord = false;
        }
    }
    printf("Vowels: %d\nConsonants: %d\nDigits: %d\nSpaces: %d\nWords: %d\n", vowels, consonants, digits, spaces, words);
}


// 11. Show length of the string
void lengthOfString(char *str) {
    printf("Length of the string: %ld\n", strlen(str));
}


// 12. Reverse the string
void reverseString(char *str) {
    int length = strlen(str);
    printf("Reversed string: ");
    for (int i = length - 1; i >= 0; i--) {
        putchar(str[i]);
    }
    putchar('\n');
}


// 13. Count number of sentences
void countSentences(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.' || str[i] == '!' || str[i] == '?') count++;
    }
    printf("Number of sentences: %d\n", count);
}
// 14. Search an item from the string
bool searchItem(char *str, char *item) {
    char temp[1000];
    strcpy(temp, str);
    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (strcmp(token, item) == 0) {
            return true;
        }
        token = strtok(NULL, " ");
    }
    return false;
}
// 15. Remove a word from the string
void removeWord(char *str, char *word) {
    char temp[200] = "";
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strcmp(token, word) != 0) {
            strcat(temp, token);
            strcat(temp, " ");
        }
        token = strtok(NULL, " ");
    }
    strcpy(str, temp);
    printf("String after removing \"%s\": %s\n", word, str);
}
//16. Lexical Analyzer Helper Functions
bool isKeyword(char *str) {
    const char *keywords[] = {"int", "float", "if", "else", "while", "return", "for", "do", "switch","case","double","sizeof","char","long","continue","bool","extern","union","const","enum","volatile","struct","unsigned","void","static","short","typedef"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

bool isOperator(char ch) {
    const char operators[] = "+-*/=<>";
    for (int i = 0; i < sizeof(operators) - 1; i++) {
        if (ch == operators[i]) return true;
    }
    return false;
}

bool isNumber(char *str) {
    int i = 0;
    if (str[i] == '-' || str[i] == '+') i++;  // Handle negative and positive numbers
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// 16. Lexical Analyzer with User Input
void lexicalAnalyzer() {
    char inputStr[1000];
    printf("Enter a string for lexical analysis: ");
    fgets(inputStr, sizeof(inputStr), stdin);
    removeNewline(inputStr);

    char *token = strtok(inputStr, " ");
    printf("Lexical Analysis:\n");
    while (token != NULL) {
        if (isKeyword(token)) {
            printf("%s : Keyword\n", token);
        } else if (isNumber(token)) {
            printf("%s : Number\n", token);
        } else if (isOperator(token[0]) && token[1] == '\0') {
            printf("%s : Operator\n", token);
        } else if (isalpha(token[0]) || token[0] == '_') {
            printf("%s : Identifier\n", token);
        } else {
            printf("%s : Special Character\n", token);
        }
        token = strtok(NULL, " ");
    }
}

// 17.Interactive Regular Expression Check for `ab*`
void checkRegularExpression() {
    char choice;
    do {
        char testStr[100];
        printf("Enter a string: ");
        fgets(testStr, sizeof(testStr), stdin);
        removeNewline(testStr);

        // Check if the string matches the `ab*` pattern
        if (testStr[0] == 'a' && strspn(testStr + 1, "b") == strlen(testStr) - 1) {
            printf("Acceptable\n");
        } else {
            printf("Not acceptable\n");
        }

        // Ask the user if they want to check another string
        printf("Do you want to check regular expression for (ab*)-(Y/N): ");
        scanf(" %c", &choice);
        getchar();  // To consume newline left by scanf
    } while (choice == 'Y' || choice == 'y');
}

// Main program
int main() {
    char str[1000];
    printf("Enter a string: ");
    scanf("%[^-]", &str);
    removeNewline(str);


    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Show the string\n2. Tokenize the string\n3. Number of articles\n");
        printf("4. Number of auxiliary verbs\n5. Number of prepositions\n6. Remove extra spaces\n");
        printf("7. Find valid identifier\n8. Find invalid identifier\n9. Number of strong verbs\n");
        printf("10. Count vowels, consonants, digits, spaces, words\n11. Show length of string\n");
        printf("12. Reverse the string\n13. Count number of sentences\n14. Search an item from the string\n");
        printf("15. Remove a word\n16. Lexical Analyzer\n17. Regular Expression\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume newline left by scanf
        char item[50];
        char tempStr[1000];
        //strcpy(tempStr, str);  // Copy of str for safe tokenization
        switch (choice) {
            case 1: showString(str); break;
            case 2: tokenizeString(str); break;
            case 3: countArticles(str); break;
            case 4: countAuxiliaryVerbs(str); break;
            case 5: countPrepositions(str); break;
            case 6: removeExtraSpaces(str); break;
            case 7: printf("Valid Identifier: %s\n", isValidIdentifier(str) ? "Yes" : "No"); break;
            case 8: printf("Invalid Identifier: %s\n", isValidIdentifier(str) ? "No" : "Yes"); break;
            case 9: countStrongVerbs(str); break;
            case 10: countCharacters(str); break;
            case 11: lengthOfString(str); break;
            case 12: reverseString(str); break;
            case 13: countSentences(str); break;
            case 14:
                printf("Enter the item to search: ");
                fgets(item, sizeof(item), stdin);
                removeNewline(item);
                printf("Search result: %s\n", searchItem(str, item) ? "Found" : "Not found");
                break;
            case 15:
                printf("Enter the word to remove: ");
                fgets(item, sizeof(item), stdin);
                removeNewline(item);
                removeWord(str, item);
                break;
            case 16:
                lexicalAnalyzer(tempStr);
                break;    
            case 17:
                checkRegularExpression(str);
                break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);


    return 0;
}
