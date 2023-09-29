#include <iostream>
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//Function to separate words in each sentence, return as a vector of words 
vector<string> wordsPerSentence(string sentence) {
    vector<string> words;
    istringstream iss(sentence);
    string word;
    while(iss >> word) {
        words.push_back(word);
    }
    return words;
}

//Function to remove leading spaces from a string
string removeSpace(string sentence) {
    int beginning = 0;
    while(beginning < sentence.length() && sentence[beginning] == ' ') {
        beginning++;
    }
    sentence = sentence.substr(beginning);
    return sentence;
}

int main(int argc, char** argv) {
    string inputFile = argv[1];
    string output = argv[2];

    ifstream myfile;
    myfile.open(inputFile);
    string token;
    
    vector<string> myLines;
    vector<string> myWords;
    vector<string> mySentences;
    
    //read file once
    if (myfile.is_open()) {
        while(myfile) {
            //Stores each sentence in vector, separates by newline
            while(getline(myfile, token, '\n')) {
                for( unsigned int i = 0; i < token.size(); i++ ) {
                    //converts all characters to lowercase
                    token[i] = tolower(token[i]);
                }
                myLines.push_back(token);
            }
        }
    }

    //separates lines by period symbol
    for( int i = 0; i < myLines.size(); i++ ) {
        istringstream iss(myLines[i]);
        string line;
        while(getline(iss, line, '.')) {
            mySentences.push_back(removeSpace(line));
        } 
    }
    
    //Stores each word in vector
    for( unsigned int i = 0; i < mySentences.size(); i++ ) {
        istringstream iss(mySentences[i]) ;
        string word;
        while(iss >> word) {
            myWords.push_back(word);
        }
    }
    
    //Stores duplicate words in separate vector
    vector<string> duplicates;
    vector<int> freq;
    
    for( unsigned int i = 0; i < myWords.size(); i++) {
        string curr = myWords[i];
        bool isDupe = false;
        int frequ = 0;

        for( unsigned int j = 0; j < myWords.size(); j++) {
            //checks if duplicate is found
            if ( myWords[j] == curr) {
                
                //update frequency
                frequ++;
                if( frequ > 1 ) {
                    isDupe = true;
                }
            }
        }
        //if word is a duplicate, check if in dupe vector
        if(isDupe) {
            bool inVector = false;
            for( unsigned int k = 0; k < duplicates.size(); k++ ) {
                if(duplicates[k] == curr) {
                    inVector = true;
                    break;
                }
            }
            //if word is a duplicate but NOT in vector -- push
            if(!inVector) {
                duplicates.push_back(curr);
                freq.push_back(frequ);
            }
        }
        
    }

    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    for( unsigned int i = 0; i < freq.size(); i++ ) {
        if( freq[i] >= max1 ) {
            max3=max2;
            max2=max1;
            max1 = freq[i];
        } else if ( freq[i] >= max2 ) {
            max3=max2;
            max2 = freq[i];
        } else if ( freq[i] >= max3 ) {
            max3 = freq[i];
        }
    }

    //Find word that has frequency
    string m1;
    string m3;
    for( unsigned int i = 0; i < duplicates.size(); i++ ) {
        if( max1 == freq[i] ) {
            m1 = duplicates[i];
        }
        if ( max3 == freq[i] ) {
            m3 = duplicates[i];
        }
    }

/////////////////////////////////////////////
    //find max occurrence of the word "the" for each sentence
    //output sentence with mac occurrence
    vector<int> theFreq;
    for( int i = 0; i < mySentences.size(); i++ ) {
        
        int frequency = 0;
        // cout << "This is sentence " << i << endl;
        // cout << mySentences[i] << endl;
        vector<string> the = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < the.size(); j++ ) {
            // cout << allWords[j] << endl;
            if(the[j] == "the") {
                frequency++;
            }
        }
        theFreq.push_back(frequency);
    }

    //max value initialized to first number in vector 
    int max = theFreq[0];
    int maxpos;
    vector <int> maxposThe;
    for( int i = 0; i < theFreq.size(); i++ ) {
        if(theFreq[i] > max) {
            max = theFreq[i];
            maxpos = i;
            maxposThe.clear();
            maxposThe.push_back(i);
        } else if (theFreq[i] == max) {
            maxposThe.push_back(i);
        }
    }

    //OUTPUT FOR QUESTION 4
    // for( int i = 0; i < maxposThe.size(); i++ ) {
    //     cout << "the:" << max << ":" << mySentences[maxposThe[i]] << endl;
    // }

    
//////////////////////////////////////////////////

    //find max occurrence of the word of 
    vector <int> ofFreq;
    for( int i = 0; i < mySentences.size(); i++ ) {
        int frequency = 0;
        vector<string> of = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < of.size(); j++ ) {
            if(of[j] == "of") {
                frequency++;
            }
        }
        ofFreq.push_back(frequency);
    }

    int maxOF = ofFreq[0];
    int maxposOf = 0;
    vector<int> maxposOfVec;
    for( int i = 0; i < ofFreq.size(); i++ ) {
        if(ofFreq[i] > maxOF) {
            maxOF = ofFreq[i];
            maxposOf = i;
            maxposOfVec.clear();
            maxposOfVec.push_back(i);
        } else if( ofFreq[i] == maxOF ) {
            maxposOfVec.push_back(i);
        }
    }

//OUTPUT FOR QUESTION 5
    // for( int i = 0; i < maxposOfVec.size(); i++ ) {
    //     cout << "of:" << maxOF << ":" << mySentences[maxposOfVec[i]] << endl;
    // }

//////////////////////////////////////////

    //find max occurrence of the word "was"
    vector <int> wasFreq;
    for( int i = 0; i < mySentences.size(); i++ ) {
        int frequency = 0;
        vector<string> was = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < was.size(); j++ ) {
            if(was[j] == "was") {
                frequency++;
            }
        }
        wasFreq.push_back(frequency);
    }

    int maxWas = wasFreq[0];
    int maxposWas = 0;
    vector<int> maxposWasVec;
    for( int i = 0; i < wasFreq.size(); i++ ) {
        if(wasFreq[i] > maxWas) {
            maxWas = wasFreq[i];
            maxposWas = i;
            maxposWasVec.clear();
            maxposWasVec.push_back(i);
        } else if (wasFreq[i] == maxWas) {
            maxposWasVec.push_back(i);
        }
    }

    //OUTPUT FOR QUESTION 6
    // for( int i = 0; i < maxposWasVec.size(); i++ ) {
    //     cout << "was:" << maxWas << ":" << mySentences[maxposWasVec[i]] << endl;
    // }
/////////////////////////////////////////////////

//find max occurrence of the phrase "but the"
    vector <int> butTheFreq;
    for( int i = 0; i < mySentences.size(); i++ ) {
        int frequency = 0;
        vector <string> butThe = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < butThe.size(); j++ ) {
            if( butThe[j] == "but" && butThe[j+1] == "the") {
                frequency++;
            }
        }
        butTheFreq.push_back(frequency);
    }

    int maxButThe = butTheFreq[0];
    int maxposButThe = 0;
    vector<int> maxposButTheVec;
    for( int i = 0; i < butTheFreq.size(); i++ ) {
        if(butTheFreq[i] > maxButThe) {
            maxButThe = butTheFreq[i];
            maxposButThe = i;
            maxposButTheVec.push_back(i);
        } else if( butTheFreq[i] == maxButThe ) {
            maxposButTheVec.push_back(i);
        }
    }

    //OUTPUT FOR QUESTION 7
    // for( int i = 0; i < maxposButTheVec.size(); i++ ) {
    //     cout << "but the:" << maxButThe << ":" << mySentences[maxposButTheVec[i]] << endl;
    // }
///////////////////////////////

//find max occurrence of the phrase "it was"
    vector <int> itWasFreq;
    for( int i = 0; i < mySentences.size(); i++ ) {
        int frequency = 0;
        vector <string> itWas = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < itWas.size(); j++ ) {
            if( itWas[j] == "it" && itWas[j+1] == "was") {
                frequency++;
            }
        }
        itWasFreq.push_back(frequency);
    }

    int maxItWas = itWasFreq[0];
    int maxposItWas = 0;
    vector <int> maxposItWasVec;
    for( int i = 0; i < itWasFreq.size(); i++ ) {
        if(itWasFreq[i] > maxItWas) {
            maxItWas = itWasFreq[i];
            maxposItWas = i;
            maxposItWasVec.clear();
            maxposItWasVec.push_back(i);
        } else if( itWasFreq[i] == maxItWas) {
            maxposItWasVec.push_back(i);
        }
    }

//OUTPUT FOR QUESTION 8 
    // for( int i = 0; i < maxposItWasVec.size(); i++ ) {
    //     cout << "it was:" << maxItWas << ":" << mySentences[maxposItWasVec[i]] << endl;
    // }

////////////////////////////////////////////////////////////
//find max occurrence of "in my"
    vector <int> inMyFreq;
    for( int i = 0; i < mySentences.size(); i++) {
        int frequency = 0;
        vector <string> inMy = wordsPerSentence(mySentences[i]);
        for( int j = 0; j < inMy.size(); j++ ) {
            if( inMy[j] == "in" && inMy[j+1] == "my" ) {
                frequency++;
            }
        }
        inMyFreq.push_back(frequency);
    }

    int maxInMy = inMyFreq[0];
    int maxposInMy = 0;
    vector<int> maxposInMyVec;
    for( int i = 0; i < inMyFreq.size(); i++ ) {
        if(inMyFreq[i] > maxInMy) {
            maxInMy = inMyFreq[i];
            maxposInMy = i;
            maxposInMyVec.clear();
            maxposInMyVec.push_back(i);
        } else if( inMyFreq[i] == maxInMy) {
            maxposInMyVec.push_back(i);
        }
    }

//OUTPUT FOR QUESTION 9
    // for( int i = 0; i < maxposInMyVec.size(); i++ ) {
    //     cout << "in my:" << maxInMy << ":" << mySentences[maxposInMyVec[i]] << endl;
    // }
//////////////////////////////

// List the word(s) with the highest frequency in a sentence across all sentences in the whole file, also print its frequency and the corresponding sentence.
    vector<string> commonWords;
    vector<int> freqCommonWords;
    
//find most frequent word in EACH SENTENCE 
//INCLUDE DUPLICATES

    int sentencepos = 0;
    vector<int> sentencePositions;
    for( int i = sentencepos; i < mySentences.size(); i++) {
        vector<string> words = wordsPerSentence(mySentences[i]);
        string frequentWord;
        int frequencyWord = 0;

        //loop throguh all words in each sentence
        for( int j = 0; j < words.size(); j++) {
            //set current word to first one, initialize frequency
            string curr = words[j];
            int currFreq = 0;
            //loop through the rest of the words in the sentence
            for(int k = 0; k < words.size(); k++) {
                
                if(words[k] == curr) {
                    currFreq++;
                }
            }
            if(currFreq > frequencyWord) {
                frequencyWord = currFreq;
                frequentWord = curr;
            }
        }
        commonWords.push_back(frequentWord);
        freqCommonWords.push_back(frequencyWord);
        sentencePositions.push_back(sentencepos);
    }

    // for( int i = 0; i < commonWords.size(); i++ ) {
    //     cout << commonWords[i] << ": " << freqCommonWords[i] << endl;
    // }

    //find max elements in vector
    vector<int> maxNums;
    vector<int> sentencePos2;
    vector<string> theWord;
    int maxNum = freqCommonWords[0];
    for( int i = 0; i < freqCommonWords.size(); i++ ) {
        if(freqCommonWords[i] > maxNum) {
            maxNum = freqCommonWords[i];
        }
    }

    for( int i = 0; i < freqCommonWords.size(); i++) {
        if(freqCommonWords[i] == maxNum) {
            theWord.push_back(commonWords[i]);
            maxNums.push_back(maxNum);
            sentencePos2.push_back(i);
        }
    }

    // for( int i = 0; i < maxNums.size(); i++ ) {
    //     cout << theWord[i] << ":" << maxNums[i] << ":" << mySentences[sentencePos2[i]] << endl;
    // }


    string output1 = output + "1.txt";
    string output2 = output + "2.txt";
    string output3 = output + "3.txt";
    string output4 = output + "4.txt";
    string output5 = output + "5.txt";
    string output6 = output + "6.txt";
    string output7 = output + "7.txt";
    string output8 = output + "8.txt";
    string output9 = output + "9.txt";

    ofstream outputFile1(output1);
    outputFile1 << m1 << ":" << max1 << endl;
    outputFile1.close();

    ofstream outputFile2(output2);
    outputFile2 << m3 << ":" << max3 << endl;
    outputFile2.close();

    ofstream outputFile3(output3);
    for( int i = 0; i < maxNums.size(); i++ ) {
        outputFile3 << theWord[i] << ":" << maxNums[i] << ":" << mySentences[sentencePos2[i]] << endl;
    }
    outputFile3.close();

    ofstream outputFile4(output4);
    for( int i = 0; i < maxposThe.size(); i++ ) {
        outputFile4 << "the:" << max << ":" << mySentences[maxposThe[i]] << endl;
    }
    outputFile4.close();

    ofstream outputFile5(output5);
    for( int i = 0; i < maxposOfVec.size(); i++) {
        outputFile5 << "of:" << maxOF << ":" << mySentences[maxposOfVec[i]] << endl;
    }
    outputFile5.close();

    ofstream outputFile6(output6);
    for( int i = 0; i < maxposWasVec.size(); i++ ) {
        outputFile6 << "was:" << maxWas << ":" << mySentences[maxposWasVec[i]] << endl;
    }
    outputFile6.close();

    ofstream outputFile7(output7);
    for( int i = 0; i < maxposButTheVec.size(); i++ ) {
        outputFile7 << "but the:" << maxButThe << ":" << mySentences[maxposButTheVec[i]] << endl;
    }
    outputFile7.close();

    ofstream outputFile8(output8);
    for( int i = 0; i < maxposItWasVec.size(); i++ ) {
        outputFile8 << "it was:" << maxItWas << ":" << mySentences[maxposItWasVec[i]] << endl;
    }
    outputFile8.close();

    ofstream outputFile9(output9);
    for( int i = 0; i < maxposInMyVec.size(); i++ ) {
        outputFile9 << "in my:" << maxInMy << ":" << mySentences[maxposInMyVec[i]] << endl;
    }
    outputFile9.close();

    
}