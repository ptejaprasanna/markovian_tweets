#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <map>
#include <string>
#include <fstream>
#include <time.h>


using namespace std;

class Word {
    //stores every second word as well as the frequency of the word
    public:
        string second_word;
        int frequency;      
};

typedef std::multimap < string, Word > Map;

void AddDataToMap(Map &newmap, string filename) {
    
    Map::iterator it;
    ifstream file;
    Word data;
    bool flag = 0;
    string first;      //store the first word
    string second;     //store the second word
    
    file.open( filename.c_str() ); 
    
    //get the data from the file word by word.
    file >> first;
    file >> second;
    data.frequency = 1;
    data.second_word = second;
    
    newmap.insert ( make_pair( first, data ) );
    
    //get the next consecutive set of words
    first = second;
    file >> second;
    
    while ( !file.eof() ) {
        //it = newmap.begin();
        flag = 0;
        for( it = newmap.begin() ; it != newmap.end() ; ++it) {
            //check if the key and data already present
            if( it -> first == first && it -> second.second_word == second){
                //increase the frequency of the word
                it -> second.frequency++;
                flag = 1;
            }
        }
        //add the new element to the map
        if( !flag ) {
            data.second_word = second;
            data.frequency = 1;
            newmap.insert( make_pair( first,data ) );
        }
        
        //get the next consecutive word
        first = second;
        file >> second;
        
    }
    
}

void GenerateTweet ( Map &newmap, int CharCount) {
    
    Map::iterator itmax, it;        //create an max iterator as well
    string first;
    string second;
    int counter = 0;                //to keep count of the number of characters
    
    //get a random word at the begin to start the tweet
    it = newmap.begin();
    srand(time(NULL));
    advance( it, rand() % newmap.size() );
    cout << it->first << " ";
    counter = it->first.length() + 1;
    itmax = it;
    
    while( counter < CharCount ) {
        
        while( it != newmap.end() ) {
            if( it->first == first && it->second.frequency > itmax->second.frequency) {
                itmax = it;
            }
            ++it;
        }
        
        
        cout << itmax->second.second_word << " ";
        
        //get the next consecutive words
        if ( newmap.find( itmax -> second.second_word ) != newmap.end() ) {
            it = newmap.find( itmax -> second.second_word );
        }
        else {
            it = newmap.begin();
            advance( it, rand () % newmap.size() );
        }
        
        itmax -> second.frequency -= 500;
        itmax = it;
        first = it->first;
        counter = 1 + counter + first.length();
    }
    cout <<"."<< endl;
}


int main() {
    Map newmap;
    string filename = "grinch.txt";
    AddDataToMap( newmap, filename );
    int CharCount = 280;    //number of characters for the tweet
    GenerateTweet( newmap, CharCount ); 
    return 0;
}