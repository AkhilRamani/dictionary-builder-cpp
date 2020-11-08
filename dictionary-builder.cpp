#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> words;		//stores words
vector<int> counts;			//stores counts

void insertWord(string word);		//inserts words
void sortData();					      //sorts in counts in decending order
void sortAlphabetically();			//sorts words with same count alphabetically
void printWords();					    //prints first and last 10 words in words list

int main() {
    ifstream file;
    string fileName;

    cerr << "Enter file name: ";
    cin >> fileName;

    file.open(fileName);

    if (!file) {
        cerr << "Unable to open file " << fileName << endl;
        exit(0);
    }

    string w;
    while (file >> w){				//read word by word from file
        int size = w.size();

        //Removes punctuations from string and converts to lowercase
        for(int i = 0; i < size; i++){
            if(ispunct(w[i])){		//if letter is punctuation then it will be earased and remaining letters joined in w (word) string   
                w.erase(i--, 1);
                size = w.size();
            }
            w[i] = tolower(w[i]);   //convert character to lowercase and place it to the ith position in w to form a word
        }

        insertWord(w);				//processed word gets inserted via this frunctoin
    }
    file.close();

    sortData();
    sortAlphabetically();
	printWords();

    return 0;
}

void insertWord(string word){
    int size = words.size();
    bool isInserted = false;

    for(int i = 0; i < size; i++){		//iterates over current words array
        if(words[i] == word){
            ++counts[i];				//increaments count by 1 if word is already in list 
            isInserted = true;
            break;						//no need to check further, as all words are unique in list
        }
    }
    if(size == 0 || !isInserted){		//pushes new word in words list and count = 1 in count list if not present already
      words.push_back(word);
      counts.push_back(1);
    }
}

void sortData() {
	int size = counts.size();
	for (int i = 1; i < size; i++) {			//insertion sort interaters over counts array
		int count = counts[i]; 
		string word = words[i];
		int j = i - 1;

		while (count > counts[j] && j >= 0) {	//compare element in counts arr with the elements in previous direction until a greater element is found 
			counts[j + 1] = counts[j];			//Swaps two count in counts array
			words[j + 1] = words[j];			//swaps two words associated with the count in words array
			--j;								//reduce the value of j to move back further
		}
		counts[j + 1] = count;					//Swaps two count in counts array
		words[j + 1] = word;					//swaps two words associated with the count in words array
	}
}

void sortAlphabetically(){
	int size = counts.size();
	int tmpCount = -1, startIndex = 0;							//tmpCount stores count value to compare and find indexes

	//first it finds the startIndex and endIndex of same count words
	for(int i = 0; i < size; i++){
		if(tmpCount == -1){										//here -1 means first iteration with no count value
			tmpCount = counts[i];								//so it sets tmpCount to first element of counts array
		}
		else if(tmpCount != counts[i] || i == size - 1) {		//tmpCount not equal to ith element means new count value is encountered
																//or when it is end of array
			int endIndex = (i == size - 1) ? i : i - 1;			//so, it sets the endIndex to i - 1, as i is new count's index. or sets i when end of array
			int subArrSize = endIndex - startIndex + 1;			//calculates the size of sub array with same counts words

			if(subArrSize > 1){									//no need to sort when there is only 1 element 
				for(int step = startIndex + 1; step <= endIndex; step++){		//insertion sort begins within sub array start and end index 
					string word = words[step];
					int j = step - 1;

					while (j >= startIndex && word[0] < words[j][0]){			//compares the first letter of word untill it is in alphabatically order
						words[j + 1] = words[j];								//swaps the words
						--j;
					}
					words[j + 1] = word;										//swaps the words. No need to swap associated counts because they are same in current sub array
				}
			}

			tmpCount = counts[i];			//sets tmpCount value to newly occurred count
			startIndex = i;					//sets the start index for next sub array of newly occurred count
		}
	}
}

void printWords(){
	cout << "\nfirst 10 words\n--------------" << endl;
	for(int i = 0; i < 10; i++)
		cout << "- " << words[i] << ",   count: " << counts[i] << endl;
	
	cout << "\n\nlast 10 words\n--------------" << endl;
	for(int i = words.size() - 10; i < words.size(); i++)
		cout << "- " << words[i] << ",  count: " << counts[i] << endl;
}
