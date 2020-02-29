//
// Created by Jonathan Ebrahimian on 2/27/20.
//
#include <iostream>
#include "DSString.h"
#include "Indexer.h"
#include "DSVector.h"
#include <fstream>

/*IndexBook
 * This method takes a book and a key word list and indexes the
 * passed in book for the key words. It creates an output file
 * with the key words and the pages they appeared on.
 *
 * Return: void
 */
void Indexer::indexBook(char * keyWordsFileName, char * bookFileName,char * outputFileName) {
    char part [500];//buffer

    //gets keywords
    DSVector<DSString> keyWords;
    keyWords = getKeyWords(keyWordsFileName,part);

    //gets a vector of all pages
    DSVector<DSString> rawPages;
    rawPages = getEachPage(bookFileName,part);

    //gets a vector of each page each keyword appears in
    DSVector<DSString> pagesAppeared;
    pagesAppeared = getPagesForEachWord(keyWords,rawPages);

    //sorts and writes the vector created above to an output file
    writeToOutputFile(outputFileName,keyWords,pagesAppeared);
}

/* AddPageNumbers
 * This method adds page numbers and formats raw .txt files passed
 * in to fit the project requirements. (Only used for testing purposes)
 *
 * Return: void
 */
void Indexer::addPageNumbers(char * rawBookFileName,char * bookInputFileName){

    ifstream rawBook;
    rawBook.open(rawBookFileName);
    if(!rawBook){
        cout << "File did not open" << endl;
        exit(1);
    }
    char part [100];

    ofstream finalBook;
    finalBook.open(bookInputFileName);

    int counter = 0;
    int pageNumber = 2;
    finalBook << "<";
    finalBook << 1;
    finalBook << "> " << endl;
    while(!rawBook.eof()){
        rawBook.getline(part,90,'\n');
        finalBook << part << endl;
        cout << part << endl;
        counter++;
        if(counter == 10){
            finalBook << endl;
            finalBook << "<";
            finalBook << pageNumber;
            finalBook << ">" << endl;
            cout << pageNumber << endl;
            pageNumber++;
            counter = 0;
        }
    }
    finalBook << endl;
    finalBook << "<";
    finalBook << -1;
    finalBook << ">";
    finalBook.close();
    rawBook.close();
}


/*GetKeyWords
 * This method gets the name of a file and creates a DSVector of DSStrings
 * containing each keyword.
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getKeyWords(char * keyWordFileName, char part []){
    //opens keyword file
    ifstream keyWordsFile;
    keyWordsFile.open(keyWordFileName);
    if(!keyWordsFile){
        cout << "Error opening input file key words";
        exit(1);
    }

    DSVector<DSString> keyWords;
    DSString temp;


    char * pch;

    //removes all elements in separator
    char  separator [] = ".?!:',;\"/\\[]{}\n";

    //iterates through keyword file
    while(!keyWordsFile.eof()){
        keyWordsFile.getline(part,500,'\n');//gets a line from keyword file
        pch = strtok(part,separator);//removes special chars
        while (pch != NULL){
            temp = temp + pch;
            pch = strtok(NULL, separator);
        }

        temp.lowercase();//makes keywords lowercase

        //adds keyword to the vector if unique
        if(!keyWords.find(temp)){
            keyWords.append(temp);
        }
        temp = "";//resets temp variable
    }
    keyWordsFile.close();//close file
    return keyWords;
}

/* GetEachPage
 * This method seperates each page of the book into its own DSString and returns
 * a vector of DSStrings with all pages
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getEachPage(char * bookFileName, char part []){
    //open book file
    ifstream book;
    book.open(bookFileName);
    if(!book){
        cout << "Error opening input file book";
        exit(1);
    }


    DSString read;
    bool first = true;
    char * pch;
    char  separator [] = " .?\"\t!:/\\[]{},;\n";

    DSVector<DSString> rawPages;
    DSString tempString;
    DSString pageAt;

    bool add;

    //iterates through book file until <-1> is found
    while(!(tempString == (char *)"<-1>")){
        book.getline(part, 500, '\n');
        add = true;
        tempString = part;

        //checks if new line has the correct angle bracket format and that it is not the
        //first iteration
        if(tempString[0] == '<' && tempString[tempString.getLength() -1] == '>' && !first) {

            //checks if contents of angle brackets is a number
            pageAt = tempString.substring(1,tempString.getLength() -1);
            if(pageAt.isNum()){
                read = read.remove((char *)"'");//removes ' without adding spaces
                rawPages.append(read);
                add = false;//doesnt add the current string to the next element
                read = tempString + (char *)" ";//resets DSString for the next element
            }
        }

        //adds line to DSString and removes special chars and white space
        if(add){
            first = false;
            pch = strtok(part,separator);
            while (pch != NULL){
                read = read + pch + (char *)" ";//adds spaces between each separation
                pch = strtok(NULL, separator);
            }
        }
    }
    return rawPages;
}

/* GetPagesForEachWord
 * Finds each page that each keyword is on and puts it into a DSString and
 * returns a DSVector containing those DSStrings.
 *
 * Return: DSVector<DSString>
 */
DSVector<DSString> Indexer::getPagesForEachWord(DSVector<DSString> & keyWords, DSVector<DSString> & rawPages){
    //variables
    DSVector<DSString> pagesAppeared;
    DSString temp((char *)"");
    DSString end((char *)">");
    DSString tempString((char *)"");
    DSString keyWordTemp;
    DSString space((char *)" ");
    DSString word((char *)"");
    DSString temp2((char *)"");
    DSString temp3((char *)": ");

    keyWords.sort();//sort keywords

    //initialize pagesAppeared DSVector
    for(int j = 0; j < keyWords.getSize(); j++){
        pagesAppeared.append((char *)"-1");
    }

    //iterate through each page and check if a key word exists in the page
    for(int x = 0; x < rawPages.getSize(); x++){
        //get the current page and lowercase it
        tempString = rawPages[x];
        tempString.lowercase();
        for(int j = 0; j < keyWords.getSize(); j++){
            //suround and add spaces to key word
            keyWordTemp = space + keyWords[j] + space;
            keyWordTemp.lowercase();

            //check if current page contains the keyword
            if(tempString.contains(keyWordTemp) != -1){

                //get the page number of the page
                int lastIndex = tempString.contains(end);
                temp2 = tempString.substring(1,lastIndex);

                //add the new page to pagesAppeared DSVector
                temp = pagesAppeared[j];
                if(temp == (char *)"-1"){
                    pagesAppeared.edit(temp2,j);//override -1 if first page found
                } else{
                    temp = temp + (char *)", " + temp2;
                    pagesAppeared.edit(temp,j);
                }
            }
        }
    }
    return pagesAppeared;
}



/* WriteToOutputFile
 * This method takes the key words and the vector containing the info
 * of where each word appears. It sorts the pages where each word appears
 * and writes them to the output file and wraps whenever a line length is
 * more than 70.
 *
 * Return: void
 */
void Indexer::writeToOutputFile(char * fileOutputName, DSVector<DSString>& keyWords, DSVector<DSString>& pagesAppeared){
    DSString temp;
    char currLetter;
    char nextLetter;
    DSVector<DSString> result;
    DSVector<int> intResults;
    int lengthOfLine = 0;

    //opening output file
    ofstream fout;
    fout.open(fileOutputName);
    if(!fout.is_open()){
        cout << "Error opening output file" << endl;
        exit(1);
    }
    //iterates through each key word
    for(int j = 0; j < keyWords.getSize(); j++) {
        temp = pagesAppeared[j];

        //checks if the word was found on any page
        if(!(temp == (char *)"-1")){
            //adds keyword and character index to output file
            addWordToOutputFile(keyWords[j],lengthOfLine,nextLetter,currLetter,fout);
            result = temp.split((char *)", ");//splits string containing page numbers
            intResults = getIntDSVector(result);//converts DSVector of DSStrings to DSVector of ints

            //iterates through each page in the int DSVector
            bool start = true;
            for(int x = 0; x < intResults.getSize();x++){
                temp = intResults[x];
                addPageToOutputFile(temp,lengthOfLine,start,fout);
            }
            fout << endl;//new line for new word
        }
        lengthOfLine = 0;//resets line length
    }
    fout.close();//close file
}

/* addWordToOutputFile
 * This method adds a word passed in to the output file and
 * checks if the first letter of the passed in word is different
 * than the previous word.
 *
 * Return: void
 */
void Indexer::addWordToOutputFile(DSString word, int & lengthOfLine, char & nextLetter, char & currLetter, ofstream & fout) {
    nextLetter = word[0];//gets first letter of word

    //checks if first letter of word is new
    if(currLetter != nextLetter){
        currLetter = nextLetter;
        nextLetter = toupper(nextLetter);
        fout << "[" << nextLetter << "]" << endl;//adds new letter to index
    }
    lengthOfLine += word.getLength();
    fout << word << ": ";//adds word to output file
}

/* getIntDSVector
 * Converts a DSVevtor containing DSStrings that are numbers to a
 * DSVector containing integers and sorts the vector.
 *
 * Return: DSVector<int>
 */
DSVector<int> Indexer::getIntDSVector(DSVector<DSString> & result) {
    DSVector<int> intResults;
    DSString tempString;

    //iterates through results and changes DSString to int
    for(int x = 0; x < result.getSize();x++){
        tempString = result[x];
        intResults.append(tempString.getInt());
    }
    intResults.sort();//sorts int vector from low to high
    return intResults;
}

/* AddPageToOutputFile
 * Adds the word passed in to the output file. Adds commas between numbers.
 * Wraps text at 70 chars per line.
 *
 * Return: void
 */
void Indexer::addPageToOutputFile(DSString temp, int & lengthOfLine,bool& start, ofstream & fout) {
    //doesn't add , if first page being added
    if(start){
        //new line if the key word + the page length > 70
        if(lengthOfLine + temp.getLength() > 70){
            fout << endl << "    " << temp;
            lengthOfLine = 4 + temp.getLength();
        }else{
            fout << temp;
            lengthOfLine += temp.getLength();
        }
        start = false;
    }else {
        //checks if line wraps
        if(lengthOfLine + temp.getLength() + 3 > 70){
            fout << "," << endl << "    ";
            lengthOfLine = 4;
        }else{
            fout << ", ";
            lengthOfLine += 2;
        }
        //adds page to line length and output file
        lengthOfLine += temp.getLength();
        fout << temp;
    }
}



