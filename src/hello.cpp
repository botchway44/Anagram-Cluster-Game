#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <fstream>
#include "map.h"
#include "set.h"
#include "gobjects.h"


using namespace std;
void swap(char &a, char &b);
string signature(string word);
void readFromFile(Map<string, Set<string> > &mapping, string filename);
void countAnagramsAndWords(Map< string, Set<string> > &list);

int wordsCount =0;
int anagramsCount =0;

string longestWordInTheDictionary = "";
string highestAnagramName = "";

void title(){

    cout<<"\t\t *** ANAGrAM cLUSTer ***\n\n";

    cout<<"\t  ************************************************************************* "<<endl;
    cout<<"\t *                                                                         *"<<endl;
    cout<<"\t*     ---INSTRUCTION---                                                     *"<<endl;
    cout<<"\t*   ENTER A WORD TO DISPLAY SET OF ANAGRAMS                                 *"<<endl;
    cout<<"\t*   EVERY WORD IS IDENTIFIED BY A SIGNATURE                                 *"<<endl;
    cout<<"\t*   WHICH IS OBTAINED FROM THE RE_ARRANGEMENT OF THE CHARACTERS IN THE WORD *"<<endl;
    cout<<"\t*   IN ALPHABETICAL ORDER                                                   *"<<endl;
    cout<<"\t*   EXAMPLE : WORD { CHEAP }                                                *"<<endl;
    cout<<"\t*   SIGNATURE = ACEHP                                                       *"<<endl;
    cout<<"\t*   ANAGRAMS = { CHAPE, CHEAP, PEACH }                                      *"<<endl;
    cout<<"\t*   NOTE : THE WORD LENGHT SHOULD BE THE SAME FOR ALL ANAGRAMS              *"<<endl;
    cout<<"\t *                                                                         *"<<endl;
    cout<<"\t  ************************************************************************* "<<endl;
    cout<<endl;
}

int main() {

    string font = "consolas-20";
    setConsoleFont(font);

    Map<string,Set<string>> list;
    readFromFile(list, "my_words.txt");

    title(); //displays the title of the console

    countAnagramsAndWords(list);
    cout<<" >> Number of anagrams : "<<anagramsCount<<endl;
    cout<<" >> Number of words : "<<wordsCount<<endl;
    cout<<" >> Longest anagram  : "<<longestWordInTheDictionary<<" with lenght of "<<longestWordInTheDictionary.length()<<" and the word is "<<list[longestWordInTheDictionary]<<endl;
    cout<<" >> The anagram with the largest words : "<<highestAnagramName<<" with "<<list[highestAnagramName].size()<<" number of anagrams "<<endl;
    cout<<" >> "<<list[highestAnagramName].toString()<<endl<<endl;

    int countWords = 0;
    while(true){
        cout<<(countWords++);
        string word = getLine(". Enter a word : ");

            word = signature(word);
           for(string key : list){
               if(key == word){
                   cout<<"  >>signature is : "<<word <<" list are :"<<list[word].toString();
             }
           }
           cout<<endl<<endl;
        }


    cout<<"done"<<endl;
    return 0;
}

void swap(char &a, char &b){
    char temp = a;
    a = b;
    b = temp;
}

string signature(string word){
    word = toLowerCase(word);
    int length = word.length();
    for(int i=0; i<length; i++){
       for(int j=0; j<length-1; j++){
           if(word[i] < word[j]){
               swap(word[i], word[j]);
           }
       }
    }
    return word;
}

void readFromFile(Map< string, Set<string> > &mapping, string filename){
    ifstream in;
    in.open(filename.c_str());
    while(true){
        string word = "";
        getline(in, word);
        word = toLowerCase(word);
        if( in.fail() ){
            break;
        }
        string sig = signature(word);
        mapping[sig].add(word);
        //cout<<word<<" has key "<<sig<<endl;
    }

}

void countAnagramsAndWords(Map< string, Set<string> > &list){
    int highestAnagram =0;
    int longestWordInTheDictionaryLenght = 0;

               for(string word : list){
                anagramsCount+=1;
                int temp = list[word].size();
                int temp1 = word.length();

                //store the longest word in the dictionary
                if(temp1 > longestWordInTheDictionaryLenght){
                    longestWordInTheDictionaryLenght = temp1;
                    longestWordInTheDictionary = word;

                }

                //store the largest anagram
                if(temp > highestAnagram){
                    highestAnagram = temp;
                    highestAnagramName = word;
                }
                wordsCount += list[word].size();
//                   for(string wrd : list[word]){
//                        wordsCount+=1;
//                     }
               }
}
